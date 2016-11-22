#include <iostream>
#include <random>
using namespace std;

// Square class and Board class definitions
class Square
{
private:
	bool visibility;
	// The number of mines around the current square (displayed when visible)
	int mineCount;
	bool containsMine;
public:
	Square();
	void setMineCount(int newMineCount);
	int getMineCount();
	bool isVisible();
	void setVisibility(bool newVisibility);
	bool hasMine();
	void setMine(bool newMineStatus);
};

class Board
{
private:
	const int ROWS = 9;
	const int COLS = 9;
	const int MINES = 10;
	Square board[9][9];
public:
	Board();
	Board(int rows, int cols);
	int getRows();
	int getCols();
	Square Board::getSquare(int row, int col);
	void displayBoard();
	void layMines();
	void calculateHints();
};


void displayMenu()
{
	cout << "------------------------------- MAIN MENU -------------------------------" << endl;
	cout << "1. Start game" << endl;
	cout << "2. Load game" << endl;
	cout << "3. High scores" << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "Please enter the number of your choice (1-3 or 0 to exit):" << endl;
}

void newGame()
{
	Board board = Board();
	board.layMines();
	board.calculateHints();
}

void loadGame()
{

}

void displayHighScores()
{

}



int main()
{
	int choice;
	Board board = Board();

	do
	{
		displayMenu();
		cin >> choice;

		// Get a new choice if the input was invalid
		while (!(choice >= 0) && !(choice < 4))
		{
			cout << "That's not a valid choice, please enter 1-3, or 0 to exit: " << endl;
			cin >> choice;
		}
		cout << endl << endl;

		switch (choice)
		{
		case 1:
			//newGame();
			board.displayBoard();
			break;

		case 2:
			//loadGame();
			break;

		case 3:
			//displayHighScores();
			break;

		case 0:
			// If the user just wants to exit, don't print default error message and just break
			break;

		default:
			// If not an expected entry, get a new choice number
			cout << "That's not a valid choice, please enter 1-3, or 0 to exit: " << endl;
			cin >> choice;
			break;
		}

		//end of main menu
	} while (choice != 0);

	cout << "Thank you, good bye :)" << endl;

	return 0;
}


// Square method definitions
Square::Square()
{
	visibility = false;
	mineCount = 0;
}

void Square::setMineCount(int minesCounted)
{
	mineCount = minesCounted;
}

int Square::getMineCount()
{
	return mineCount;
}

bool Square::isVisible()
{
	return visibility;
}

void Square::setVisibility(bool newVisibility)
{
	visibility = newVisibility;
}

bool Square::hasMine()
{
	return containsMine;
}

void Square::setMine(bool mineStatus)
{
	containsMine = mineStatus;
}


// Board method definitions
Board::Board()
{
	//board = new Square*[rows];
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = Square();
		}
	}
	//board[i] = new Square[cols];
}

int Board::getRows()
{
	return ROWS;
}

int Board::getCols()
{
	return COLS;
}

Square Board::getSquare(int row, int col)
{
	return board[row][col];
}

void Board::layMines()
{
	// The row and column of the square to receive a mine
	int row;
	int col;
	int minesLaid = 0;
	// Create a random number generator and two distributions of numbers for it to choose from 
	// (as the number of rows and cols may at some point be different)
	random_device generator;
	uniform_int_distribution<int> rowDistribution(0, (ROWS - 1));
	uniform_int_distribution<int> colDistribution(0, (COLS - 1));

	// Keep going until all mines are laid
	while (MINES > minesLaid)
	{
		// As long as the current square already has a mine, get new random coordinates
		do
		{
			row = rowDistribution(generator);
			col = colDistribution(generator);

		} while (board[row][col].hasMine());

		// Set a mine on the current random square and add one to the mines-laid counter
		board[row][col].setMine(true);		
		minesLaid++;
	}

}

void Board::calculateHints()
{
	//for (int row = 0; row <)
}

void Board::displayBoard()
{
	cout << "   1 2 3 4 5 6 7 8 9" << endl << "   -----------------";
	for (int row = 0; row < ROWS; row++)
	{
		cout << endl << (row + 1) << " |";
		for (int col = 0; col < COLS; col++)
		{
			if (board[row][col].isVisible())
			{
				if (board[row][col].hasMine())
				{
					cout << "* ";
				}
				else if (board[row][col].getMineCount() == 0)
				{
					cout << "  ";
				}
				else
				{
					cout << board[row][col].getMineCount();
				}
			}
			else
			{
				cout << "# ";
			}
		}
	}
	cout << endl << endl;
}