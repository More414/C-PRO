#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
struct Client
{
  int id;
  double requestedBandwidth; // Mbps
  double allocatedBandwidth; // Mbps
  int remainingTime;         // in minutes
  Client(int id_, double bandwidth_, int time_){
    id=id_;
    requestedBandwidth= bandwidth_;
    remainingTime=time_;
  }
      
};
class Cafe
{
private:
  double totalBandwidth; // Mbps
  vector<Client> clients;
  int nextClientId;
  const int maxClients;

public:
  Cafe(double bandwidth, int maxClients_) : totalBandwidth(bandwidth), nextClientId(1), maxClients(maxClients_) {}
  void addClient(double requestedBandwidth, int timeMinutes)
  {
    if (clients.size() >= maxClients)
    {
      cout << "Cannot add more clients. Maximum limit reached.\n";
      return;
    }
    clients.emplace_back(nextClientId++, requestedBandwidth, timeMinutes);
    allocateBandwidth();
  }
  void simulateMinute()
  {
    cout << "----- Simulating 1 minute -----" << endl;

    // Decrease time for each client
    for (auto &client : clients)
    {
      client.remainingTime--;
    }

    // Remove clients with 0 remaining time
    clients.erase(remove_if(clients.begin(),
                            clients.end(),
                            [](Client &c)
                            { return c.remainingTime <= 0; }),
                             clients.end());

    // Reallocate bandwidth
    allocateBandwidth();

    // Display current state
    displayStatus();
  }
  void allocateBandwidth()
  {
    if (clients.empty())
      return;

    double demandSum = 0;
    for (const auto &client : clients)
    {
      demandSum +=client.requestedBandwidth;
    }

    if (demandSum <= totalBandwidth)
    {
      // Give everyone what they want
      for (auto &client : clients)
      {
        client.allocatedBandwidth =
            client.requestedBandwidth;
      }
    }
    else
    {
      // Scale down proportionally
      for (auto &client : clients)
      {
        client.allocatedBandwidth =
            (client.requestedBandwidth / demandSum) * totalBandwidth;
      }
    }
  }

  void displayStatus() const
  {
    cout << "Current Clients (" << clients.size() << "):\n";
    for (const auto &client : clients)
    {
      cout << "Client " << client.id
           << " - Allocated: " << client.allocatedBandwidth << " Mbps"
           << ", Remaining Time: " << client.remainingTime << " minutes\n";
    }
    cout << "-------------------------------\n";
  }

  bool isEmpty() const
  {
    return clients.empty();
  }
};

class Simulator
{
private:
  Cafe cafe;
  int initialClients;

public:
  Simulator(double bandwidth, int maxClients)
      : cafe(bandwidth, maxClients) {}

  void setupClients()
  {
    cout << "Enter number of clients to connect (max allowed: " << 10 << "): ";
    cin >> initialClients;

    if (initialClients > 10)
    {
      cout << "Too many clients! Limiting to 10.\n";
      initialClients = 10;
    }

    for (int i = 0; i < initialClients; ++i)
    {
      double bandwidth;
      int time;
      cout << "Client " << (i + 1) << " - Enter requested bandwidth (Mbps): ";
      cin >> bandwidth;
      cout << "Client " << (i + 1) << " - Enter session time (minutes): ";
      cin >> time;

      cafe.addClient(bandwidth, time);
    }
  }

  void run()
  {
    setupClients();

    while (!cafe.isEmpty())
    {
      cafe.simulateMinute();
    }

    cout << "Simulation complete. All clients disconnected.\n";
  }
};

int main()
{

  const double TOTAL_BANDWIDTH = 100;// Total available bandwidth in Mbps
  const int MAX_CLIENTS = 10; // Maximum allowed clients

  Simulator sim (TOTAL_BANDWIDTH, MAX_CLIENTS);
  sim.run();

  return 0;
}