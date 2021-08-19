#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"

//THIS IS A PROGRAM THAT SIMULATES THE WELL KNOWN GAME CONNECT 4



/*************** Board ***************/
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];


/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

//printing the game board
void printboard();
void printhead();
void printarr();

//check for a valid input
int check1to7(int col);

//gets colomn number and return the first empty slot int the colomn
int checkforemptyrow(int col);



//checking if this was a winner move for player 1
int checkforwinner1(int rownum, int colnum, char psx);

//checking for horizontal win for player 1
int checkforhor(int row, char playersign);

//checking for vertical win for player 1
int checkforver(int col, char playersign);

//checking for diagonal from right to left for player 1
int lefttorightdiag(int arr, char playersign);

//calculating the start point for the lefttorightdiag function
int startpointLTR(int arr);

//checking for diagonal from left to right for player 1
int righttoleftdiag(int arr, char playersign);

//calculating the start point for the righttoleftdiag function
int startpointRTL(int arr);


//checking if this was a winner move for plaer 2
int checkforwinner2(int rownum, int colnum, char pso);

//checking for horizontal win for player 2
int checkforhor2(int row, char playersign);

//checking for vertical win for player 2
int checkforver2(int col, char playersign);

//checking for diagonal from right to left for player 2
int lefttorightdiag2(int arr, char playersign);

//calculating the start point for the lefttorightdiag function
int startpointLTR2(int arr);

//checking for diagonal from left to right for player 2
int righttoleftdiag2(int arr, char playersign);

//calculating the start point for the righttoleftdiag function
int startpointRTL2(int arr);



/*************** Main ****************/
int main()
{
	int i, colnum;
	char pso = 'O', psx = 'X';
	int rownum;

	printboard();

	for ( i = 0; i < 42; i++)
	{
		if (i % 2 == 0)
		{
			printf("player number 1:\n");
			printf("Please enter column input (a number between 1-7):\n");
			scanf("%d", &colnum);
			colnum = check1to7(colnum);
			rownum = checkforemptyrow(colnum);
			if (rownum>ROWS)
			{
				printf("The col you entered is full\n");
				i--;
			}
			else
			{
				setCell(rownum, colnum, psx);
				clearScreen();
				printboard();
				i = i + checkforwinner1(rownum, colnum, psx);
			}

		}
		else
		{
			printf("player number 2:\n");
			printf("Please enter column input (a number between 1-7):\n");
			scanf("%d", &colnum);
			colnum = check1to7(colnum);
			rownum = checkforemptyrow(colnum);
			if (rownum > ROWS)
			{
				printf("The col you entered is full\n");
				i--;
			}
			else
			{
				setCell(rownum, colnum, pso);
				clearScreen();
				printboard();
				i = i + checkforwinner2(rownum, colnum, pso);
			}

		}
	}
	if (i == 42)
		printf("this is a draw");
}


/********** Implementations **********/
char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}

void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

void initBoard()
{
	int i, j;

	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}

void clearScreen()
{
	system("cls");
}



void printboard()
{
	printhead();
	printarr();
}

void printhead()
{
	int i = 0, num = 1;

	for (i = 0; i <= COLS; i++)
	{
		if (i == 0)
		{
			printf(" ");
		}
		else
		{
			printf("    %d", num);
			num++;
		}
	}
	printf("\n");
}

void printarr()
{
	int i, j;
	char lett = 'A';

	for (i = 1; i <= ROWS; i++)
	{
		for (j = 0; j <= COLS; j++)
		{
			if (j == 0)
			{
				printf("%c", lett);
				lett++;
			}
			else
			{
				printf("    %c", getCell(i, j));
			}
		}
		printf("\n");
	}
}




int check1to7(int col)
{
	int tempcol = col;

	if (tempcol > 0 && tempcol < 8)
		return tempcol;
	else
	{
		while (tempcol>7 || tempcol<0)
		{
			printf("The col you entered is not between 1-7.\n");
			printf("Please enter column input (a number between 1-7):");
			scanf("%d", &tempcol);
			
			if (tempcol > 0 && tempcol < 8)
				return tempcol;

		}
	}
}

int checkforemptyrow(int col)
{
	int i = ROWS;

	for (i; i > 0; i--)
	{
		if (getCell(i,col) == '\0')
		{
			return i;
		}
	}
	return 10;
}




int checkforwinner1(int rownum, int colnum, char psx)
{
	int winr, winc, wind, wind2;
	int arr;
	int rtl, ltr;

	arr = ((rownum-1) * 7) + (colnum-1);
	ltr = startpointLTR(arr);
	rtl = startpointRTL(arr);

	winr = checkforhor(rownum, psx);
	winc = checkforver(colnum, psx);
	wind = lefttorightdiag(ltr, psx);
	wind2 = righttoleftdiag(rtl, psx);

	if (winr + winc + wind + wind2 > 0)
		return 99;
	else
		return 0;
}

int checkforhor(int rownum, char playersign)
{
	int i=1, win = 0;

	for (i; i <= COLS; i++)
	{

		if (getCell(rownum, i) == playersign)
			win++;
		else
			win = 0;

		if (win == 4)
		{
			printf("player 1 won!");
			return 1;
		}
	}
	return 0;
}

int checkforver(int colnum, char playersign)
{
	int i = 1, win = 0;

	for (i; i <= ROWS; i++)
	{

		if (getCell(i, colnum) == playersign)
			win++;
		else
			win = 0;

		if (win == 4)
		{
			printf("player 1 won!");
			return 1;
		}
	}
	return 0;

}

int lefttorightdiag(int ltr, char playersign)
{
	int win = 0;
	while (ltr>0)
	{
		if (board[0][ltr] == playersign)
		{
			win++;
		}
		else
		{
			win = 0;
		}
		
		ltr = ltr - 6;

		if (win == 4)
		{
			printf("player 1 won!");
			return 1;
		}
	}
	return 0;
}

int righttoleftdiag(int arr, char playersign)
{
	int win = 0;
	while (arr > 0)
	{
		if (board[0][arr] == playersign)
		{
			win++;
		}
		else
		{
			win = 0;
		}

		arr = arr - 8;

		if (win == 4)
		{
			printf("player 1 won!");
			return 1;
		}
	}
	return 0;
}

int startpointLTR(int ltr)
{
	while (ltr<42)
	{
		ltr = ltr + 6;
	}
	return ltr;
}

int startpointRTL(int rtl)
{
	while (rtl < 42)
	{
		rtl = rtl + 8;
	}
	return rtl;

}


int checkforwinner2(int rownum, int colnum, char pso)
{
	int winr, winc, wind, wind2;
	int arr;
	int rtl, ltr;

	arr = ((rownum - 1) * 7) + (colnum - 1);
	ltr = startpointLTR2(arr);
	rtl = startpointRTL2(arr);

	winr = checkforhor2(rownum, pso);
	winc = checkforver2(colnum, pso);
	wind = lefttorightdiag2(ltr, pso);
	wind2 = righttoleftdiag2(rtl, pso);

	if (winr + winc + wind + wind2 > 0)
		return 99;
	else
		return 0;
}

int checkforhor2(int rownum, char playersign)
{
	int i = 1, win = 0;

	for (i; i <= COLS; i++)
	{

		if (getCell(rownum, i) == playersign)
			win++;
		else
			win = 0;

		if (win == 4)
		{
			printf("player 2 won!");
			return 1;
		}
	}
	return 0;
}

int checkforver2(int colnum, char playersign)
{
	int i = 1, win = 0;

	for (i; i <= ROWS; i++)
	{

		if (getCell(i, colnum) == playersign)
			win++;
		else
			win = 0;

		if (win == 4)
		{
			printf("player 2 won!");
			return 1;
		}
	}
	return 0;

}


int lefttorightdiag2(int ltr, char playersign)
{
	int win = 0;
	while (ltr > 0)
	{
		if (board[0][ltr] == playersign)
		{
			win++;
		}
		else
		{
			win = 0;
		}

		ltr = ltr - 6;

		if (win == 4)
		{
			printf("player 2 won!");
			return 1;
		}
	}
	return 0;
}

int righttoleftdiag2(int arr, char playersign)
{
	int win = 0;
	while (arr > 0)
	{
		if (board[0][arr] == playersign)
		{
			win++;
		}
		else
		{
			win = 0;
		}

		arr = arr - 8;

		if (win == 4)
		{
			printf("player 2 won!");
			return 1;
		}
	}
	return 0;
}

int startpointLTR2(int ltr)
{
	while (ltr < 42)
	{
		ltr = ltr + 6;
	}
	return ltr;
}

int startpointRTL2(int rtl)
{
	while (rtl < 42)
	{
		rtl = rtl + 8;
	}
	return rtl;

}
