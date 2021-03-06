/*
 ============================================================================
 Name        : matrix.c
 Author      : Justin Rohr & Kyle Niewiada
 Version     : 1.1
 Copyright   : Fall 2014
 Description : Matrix Multiplication for CIS 343 Homework #3
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float matrixA[3][4] = { { 2.0, 4.0, -3.0, 0.0 }, { 5.0, -5.0, -1.0, 2.0 }, {
			1.0, -4.0, 1.0, -2.0 } };
	float matrixB[4][3] = { { -3, -5, 2 }, { 0.0, 0.0, 3.0 }, { 3.0, 0.0, 3.0 },
			{ -4.0, -4.0, 2.0 } };

	int c = 0;
	float matrixC[3][3];
	float total = 0;

	for (int r = 0; r < 3; r++) {
		for (int y = 0; y < 3; y++) {
			total = 0;
			for (c = 0; c < 4; c++) {
				total += matrixA[r][c] * matrixB[c][y];
			}
			matrixC[r][y] = total;
		}

	}
	for (int r = 0; r < 3; r++) {
		for (c = 0; c < 3; c++) {
			printf("%7.2f", matrixC[r][c]);
		}
		printf("\n");
	}
}
