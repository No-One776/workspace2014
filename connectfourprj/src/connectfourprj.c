/*
 ============================================================================
 Name        : connectfour.c
 Author      : Justin Rohr & Kyle Niewiada
 Version     : 1
 Copyright   : Fall 2014
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int row = 1, col = 1, win = 4, size = 10, playerTurn = 1;

void switchPlayer() {
	if (playerTurn == 1)
		playerTurn = 2;
	else
		playerTurn = 1;
}

int scanBoard(char board[size][size]) {
	for (int row = 0; row < size; row++)
		for (int col = 0; col < size; col++) {
			if (board[row][col] != '.') {
				if (checkWin(board, row, col, -1, -1, 1))
					return 1;
				if (checkWin(board, row, col, -1, 0, 1))
					return 1;
				if (checkWin(board, row, col, -1, 1, 1))
					return 1;
				if (checkWin(board, row, col, 0, 1, 1))
					return 1;
				if (checkWin(board, row, col, 1, 1, 1))
					return 1;
				if (checkWin(board, row, col, 1, 0, 1))
					return 1;
				if (checkWin(board, row, col, 1, -1, 1))
					return 1;
				if (checkWin(board, row, col, 0, -1, 1))
					return 1;
			}
		}
	return 0;
}

int checkWin(char board[size][size], int row, int col, int r, int c,
		int foundWin) {
	if (foundWin == win) {
		return 1;
	} else if ((row + r < 0 || row + r >= size)
			|| (col + c < 0 || col + c >= size)
			|| board[row][col] != board[row + r][col + c]) {
		return 0;
	} else
		checkWin(board, row + r, col + c, r, c, foundWin + 1);
	//return -1;
}

void printBoard(char board[size][size]) {
//Print the Column headers
	for (int col = 1; col < size + 1; col++)
		printf("%3d", col);
	printf("\n");
	//Print the game board
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++)
			printf("%3c", board[row][col]);
		printf("\n");
	}
}

int placeChecker(char board[size][size], int col) {
	col--;
	for (int r = size; r >= 0; r--)
		if (board[r][col] == '.') {
			if (playerTurn == 1)
				board[r][col] = 'X';
			else
				board[r][col] = 'O';
			return 0;
		}
	return 1;
}

int checkTie(char board[size][size]) {
	for (int r = 0; r < size; r++)
		if (board[r][0] == '.')
			return 0;
	printf("Tie Game!\n");
	return 1;
}

int main(int argc, char *argv[]) {

	if (argc == 3) {
		if (atoi(argv[1]) > 9 && atoi(argv[1]) < 21)
			size = atoi(argv[1]);
		if (atoi(argv[2]) > 3 && atoi(argv[2]) < 9)
			win = atoi(argv[2]);
	}
	printf(
			"Welcome to Connect Four!\nBoard size for this game is %d by %d \nConnection length is %d\n",
			size, size, win);

	char board[size][size];
	for (int row = 0; row < size; row++)
		for (int col = 0; col < size; col++)
			board[row][col] = '.';
	printBoard(board);

	while (scanBoard(board) == 0 /*&& checkTie(board) == 0*/) {
		int col = -1;
		do {
			do {
				printf("Player %d's turn. Enter a column number (1-%d): ",
						playerTurn, size);
				//scanf("%d", &col);
			} while (col > size || col < 1);
		} while (placeChecker(board, col));

		printBoard(board);
		switchPlayer();
	}

	switchPlayer(); //Unswitch back to the winning player
	printf("Winner is Player: %d", playerTurn);

	return EXIT_SUCCESS;
}

