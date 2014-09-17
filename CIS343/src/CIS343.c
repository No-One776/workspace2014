/*
 ============================================================================
 Name        : CIS343.c
 Author      : Justin Rohr
 Version     :
 Copyright   : Fall 2014
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char c;
	printf("Enter a character: ");
	c = getchar();
	//printf("%c", c);

	if (c == EOF)
		printf("You're no fun.\n");
	else {
		switch (c) {
		case 'a':
			printf("A is for Apple.\n");
			break;
		case 'b':
			printf("B is for Banana.\n");
			break;
		default:
			printf("Not very fruitful.\n");
		}
	}
	return EXIT_SUCCESS;
}
