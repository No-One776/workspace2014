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
	//printf("%c and %c \n", board[row][col], board[row + r][col + c]);
	if (foundWin == win) {
		return 1;
	} else if ((row + r < 0 || row + r >= size)
			|| (col + c < 0 || col + c >= size)
			|| board[row][col] != board[row + r][col + c]) {
		return 0;
	} else
		checkWin(board, row + r, col + c, r, c, foundWin + 1);
}

void printBoard(char board[size][size]) {
//Print the game Board
	for (int col = 1; col < size + 1; col++)
		printf("%3d", col);
	printf("\n");
	for (int row = 0; row < size; row++) {
		for (int col = 0; col < size; col++)
			printf("%3c", board[row][col]);
		printf("\n");
	}
}

void placeChecker(char *board[size][size], int col){
	for (int r = row - 1; r >=0; r--){
		if (board[r][col] != '.')
			board[r][col] = 'X'; //Temporary, place an X
	}
}

int main(int argc, char *argv[]) {
	if (argc == 3) {
		size = atoi(argv[1]);
		win = atoi(argv[2]);
	}
//printf("%d and %d\n", atoi(argv[1]), atoi(argv[2]));

	char board[size][size];
	for (int row = 0; row < size; row++)
		for (int col = 0; col < size; col++)
			board[row][col] = '.';
	//printBoard(board);
	placeChecker(*board, 2);
	printBoard(board);
	return EXIT_SUCCESS;
}

