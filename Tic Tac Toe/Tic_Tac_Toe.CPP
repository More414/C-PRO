#include <iostream>
#include <cstdlib> // For system("cls") and exit()
#include <limits>	 // For clearing input buffer
using namespace std;

char square[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int checkwin(); // FUNCTION FOR RESULT
void board();		// FUNCTION TO DRAW THE BOARD
void guide();		// FUNCTION FOR USER GUIDE

int main()
{
	// Password system
	string password;
	int attempts = 0;

	cout << "Enter the password to enter the Game (4 attempts) : ";
	while (attempts < 4)
	{
		cin >> password;
		if (password == "password")
		{
			cout << "\nAccess Granted!\n";
			break;
		}
		else
		{
			attempts++;
			cout << "Access Denied! (" << attempts << " of 4 attempts used)\n";
			if (attempts < 4)
				cout << "Try again: ";
		}
	}
	if (attempts >= 4)
	{
		cout << "\nYou have entered the wrong password 4 times.\n";
		return 0;
	}

	int player = 1, i, choice, option;
	char mark, choice1;

	do
	{
		// system("cls"); // Clear screen (use "clear" on Linux/Mac)
		cout << "1. ENTER THE GAME\n2. USER GUIDE\n3. EXIT\n";
		cout << "Choose an option: ";
		cin >> option;

		switch (option)
		{
		case 1:
			do
			{
				system("cls");
				board();
				player = (player % 2) ? 1 : 2;

				cout << "Player " << player << ", enter a number: ";
				while (!(cin >> choice) || choice < 1 || choice > 9)
				{
					cout << "Invalid input! Enter a number between 1 and 9: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				mark = (player == 1) ? 'X' : 'O';

				if (choice >= 1 && choice <= 9 && square[choice] == '0' + choice)
					square[choice] = mark;
				else
				{
					cout << "Invalid move! Try again.\n";
					player--;
					cin.ignore();
					cin.get(); // Wait for Enter
				}

				i = checkwin();
				player++;
			} while (i == -1);

			system("cls");
			board();
			if (i == 1)
				cout << "==> Player " << --player << " wins!\n";
			else
				cout << "==> Game Draw!\n";
			break;

		case 2:
			guide();
			break;

		case 3:
			exit(0);
			break;

		default:
			cout << "Wrong Choice!\n";
		}

		cout << "\nDo you want to continue? (y/n): ";
		cin >> choice1;
	} while (choice1 == 'y' || choice1 == 'Y');

	return 0;
}

int checkwin()
{
	if (square[1] == square[2] && square[2] == square[3])
		return 1;
	else if (square[4] == square[5] && square[5] == square[6])
		return 1;
	else if (square[7] == square[8] && square[8] == square[9])
		return 1;
	else if (square[1] == square[4] && square[4] == square[7])
		return 1;
	else if (square[2] == square[5] && square[5] == square[8])
		return 1;
	else if (square[3] == square[6] && square[6] == square[9])
		return 1;
	else if (square[1] == square[5] && square[5] == square[9])
		return 1;
	else if (square[3] == square[5] && square[5] == square[7])
		return 1;
	else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
					 square[4] != '4' && square[5] != '5' && square[6] != '6' &&
					 square[7] != '7' && square[8] != '8' && square[9] != '9')
		return 0;
	else
		return -1;
}

void board()
{
	cout << "\n\n\tTic Tac Toe\n\n";
	cout << "Player 1 (X)  -  Player 2 (O)\n\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << "\n";
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << "\n";
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << "\n";
	cout << "\t     |     |     \n\n";
}

void guide()
{
	system("cls");
	cout << "\nTIC-TAC-TOE GUIDE:\n";
	cout << "The board looks like this:\n\n";
	cout << "\t     |     |     \n";
	cout << "\t  1  |  2  |  3  \n";
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  4  |  5  |  6  \n";
	cout << "\t_____|_____|_____\n";
	cout << "\t     |     |     \n";
	cout << "\t  7  |  8  |  9  \n";
	cout << "\t     |     |     \n\n";
	cout << "Players take turns to place X or O.\n";
	cout << "The first to align 3 marks horizontally, vertically, or diagonally wins!\n";
	cin.ignore();
	cout << "Enter the \"ENTER KEY\" for continue" << endl;
	cin.get();
}
