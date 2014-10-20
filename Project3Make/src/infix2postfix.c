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
	char *postfixStr = NULL;
	stack s;
	stackInit(&s);
	while (infixStr != NULL) {
		if (isOperand(infixStr)) {
			postfixStr = infixStr;
			postfixStr++;
		}
		if (isLeftParen(infixStr))
			stackPush(&s, infixStr);
		if (isOperator(infixStr))
			if (isOperator((char) stackPeek(&s)))
				if (stackPrecedence((char) stackPeek(&s))
						>= inputPrecedence(infixStr)) {
					char c;
					c = (char) stackPop(&s);
					postfixStr = c;
					postfixStr++;
					stackPush(&s, infixStr);
				}
		if (isRightParen(infixStr)) {
			while (!isLeftParen(stackPeek(&s))) {
				postfixStr = (char) stackPop(&s);
				postfixStr++;
			}
			stackPop(&s);
		}
	}
	return postfixStr;
}

/* function that returns true if the string is an operator */
bool isOperator(char *str) {
	if (str == '+' || str == '-' || str == '*' || str == '/' || str == '%'
			|| str == '(' || str == '^')
		return true;
	return false;
}

/* function that returns true if the string is an operand/integer */
bool isOperand(char *str) {
	if (isdigit(str))
		return true;
	return false;
}

/* function that returns true if the string is a left parenthesis */
bool isLeftParen(char *str) {
	if (str == '(')
		return true;
	return false;
}

/* function that returns true if the string is a right parenthesis */
bool isRightParen(char *str) {
	if (str == ')')
		return true;
	return false;
}

/* function that returns the stack precedence of given operator */
int stackPrecedence(char *str) {
	if (str == '+' || str == '-')
		return 1;
	if (str == '*' || str == '/' || str == '%')
		return 2;
	if (str == '^')
		return 3;
	if (str == '(')
		return -1;
	return 0;
}

/* function that returns the input precedence of given operator */
int inputPrecedence(char *str) {
	if (str == '+' || str == '-')
		return 1;
	if (str == '*' || str == '/' || str == '%')
		return 2;
	if (str == '^')
		return 4;
	if (str == '(')
		return 5;
	return 0;
}

/* function that evaluates a postfix expression and returns the result */
int evaluatePostfix(char *postfixStr) {
	stack s;
	stackInit(&s);
	while (postfixStr != NULL) {
		if (isOperand(postfixStr))
			stackPush(&s, postfixStr);
		if (isOperator(postfixStr)) {
			int x, y;
			y = (int) stackPop(&s);
			x = (int) stackPop(&s);
			stackPush(&s, applyOperator(x, y, postfixStr));
		}
		postfixStr++;
	}
	return stackPop(&s);
}

/* apply operator to num1 and num2 and return the result */
int applyOperator(int num1, int num2, char *opr) {
	if (opr == "+")
		return num1 + num2;
	if (opr == '-')
		return num1 - num2;
	if (opr == '*')
		return num1 * num2;
	if (opr == '/')
		return num1 / num2;
	if (opr == '%')
		return num1 % num2;
	if (opr == '^')
		return num2 ^ num1;

}