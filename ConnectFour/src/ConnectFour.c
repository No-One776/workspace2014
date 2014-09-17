/*
 ============================================================================
 Name        : Connect Four.c
 Author      : Justin Rohr & Kyle Niewiada
 Version     : 1
 Copyright   : Fall 2014
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int row = 1, col = 1, win = 4, size = 10, playerTurn = 1;

int main(int size, int win) {
	char board[size][size];
	for (int row = 0; row < size; row++)
		for (int col = 0; col < size; col++)
			board[row][col] = '.';
	//printBoard();
	return EXIT_SUCCESS;
}

int checkWin(char board[size][size], int row, int col, int r, int c,
		int foundWin) {
	if ((row + r < 0 || row + r >= size) || (col + c < 0 || col + c >= size)
			|| board[row][col] != board[row + r][col + c])
		return 0;
	else if (foundWin == win)
		return 1;
	else
		checkWin(board, row+r, col+c, r, c, foundWin++);
	return -1;
}

/*void printBoard(char board[size][size]) {
//Print Board
	for (int row = 0; row < size; row++){
		printf("\n");
		for (int col = 0; col < size; col++)
			printf(" %c ", board[row][col]);
	}
}*/
