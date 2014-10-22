#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "stack.h"
#include "infix2postfix.h"

/* function to convert an infix to postfix */
char *infixToPostfix(char *infixStr) {
	char *postfixStr = malloc(50* sizeof(char));
	stack s;
	stackInit(&s);
	char *str;
	str = strtok(infixStr, " ");

	//example
	//int num1 = atoi(stackPop(&s));
	//char *buffer = malloc(10 * sizeof(char));
	//Allocate the buffer
	//sprintf(buffer, "%d", num1);
	//stackPush(&s, buffer);

	while (str != NULL) {
		if (isOperand(str)){
			strcat(postfixStr, str);
			strcat(postfixStr, " ");
		}	
		if (isOperator(str)){
			while (!stackIsEmpty(&s) && stackPrecedence(stackPeek(&s)) >= inputPrecedence(str)) {
					char *c = malloc(10 * sizeof(char));
					c = stackPop(&s);
					if (!isLeftParen(c)){
						strcat(postfixStr, c);
						strcat(postfixStr, " ");
					}
			}	
			stackPush(&s, str);
		}
		if (isRightParen(str)) {
			while (!isLeftParen(stackPeek(&s))) {
				char *c = malloc(10 * sizeof(char));
				c = stackPop(&s);
				strcat(postfixStr, c);
				strcat(postfixStr, " ");
			}
			stackPop(&s);
		}
		str = strtok(NULL, " ");
	}
	while (!stackIsEmpty(&s)){
		char *c = malloc(10 * sizeof(char));
		c = stackPop(&s);
		strcat(postfixStr, c);
		strcat(postfixStr, " ");
	}
	stackDestroy(&s);
	return postfixStr;
}

/* function that returns true if the string is an operator */
bool isOperator(char *str) {
	if (*str == '+' || *str == '-' || *str == '*' || *str == '/' || *str == '%'
			|| *str == '(' || *str == '^')
		return true;
	return false;
}

/* function that returns true if the string is an operand/integer */
bool isOperand(char *str) {
	return isdigit(*str);
}

/* function that returns true if the string is a left parenthesis */
bool isLeftParen(char *str) {
	return *str == '(';
}

/* function that returns true if the string is a right parenthesis */
bool isRightParen(char *str) {
	return *str == ')';
}

/* function that returns the stack precedence of given operator */
int stackPrecedence(char *str) {
	if (*str == '+' || *str == '-')
		return 1;
	if (*str == '*' || *str == '/' || *str == '%')
		return 2;
	if (*str == '^')
		return 3;
	if (*str == '(')
		return -1;
	return 0;
}

/* function that returns the input precedence of given operator */
int inputPrecedence(char *str) {
	if (*str == '+' || *str == '-')
		return 1;
	if (*str == '*' || *str == '/' || *str == '%')
		return 2;
	if (*str == '^')
		return 4;
	if (*str == '(')
		return 5;
	return 0;
}

/* function that evaluates a postfix expression and returns the result */
int evaluatePostfix(char *postfixStr) {
	stack s;
	stackInit(&s);
	char *str;
	str = strtok(postfixStr, " ");
	while (str != NULL){
	  if (isOperand(str))
	    stackPush(&s, str);
	  if (isOperator(str)) {
			int x, y;
			y = atoi(stackPop(&s));
			x = atoi(stackPop(&s));
			char *c = malloc(10*sizeof(char));
			int z = applyOperator(x, y, str);
			sprintf(c, "%d", z);
			stackPush(&s, c);
		}
		str = strtok(NULL, " ");
	}
	return atoi( stackPop(&s));
}

/* apply operator to num1 and num2 and return the result */
int applyOperator(int num1, int num2, char *opr) {
	if (*opr == '+')
		return num1 + num2;
	if (*opr == '-')
		return num1 - num2;
	if (*opr == '*')
		return num1 * num2;
	if (*opr == '/')
		return num1 / num2;
	if (*opr == '%')
		return num1 % num2;
	if (*opr == '^')
		return pow(num1, num2);

	return 0;
}
