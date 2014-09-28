/*
 ============================================================================
 Name        : Project2.c
 Author      : Justin Rohr & Kyle Niewiada
 Version     : 1.0
 Description : FSM Scanner
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum {
	start, identifier, number, build_id, build_num, stop
} state;
state transition(state current, char transition) {
	if (current == start) {
		if (isdigit(transition))
			return build_num;
		if (isalpha(transition))
			return build_id;
		if (transition == '.')
			return stop;
		if (transition == ' ')
			return start;
	}

	if (current == build_id) {
		if (isdigit(transition))
			return build_id;
		if (isalpha(transition) || transition == '_')
			return build_id;
		if (transition == ' ')
			return identifier;
	}

	if (current == build_num) {
		if (isdigit(transition))
			return build_num;
		if (transition == ' ')
			return number;
	}
	return stop;
}

int main(void) {
	state current_state = start;
	char transition_char = ' ';
	do {
		if (current_state == identifier) {
			printf(" � Identifier\n");
			current_state = start;
		} else if (current_state == number) {
			printf(" � Number\n");
			current_state = start;
		}
		scanf("%c", &transition_char);

		if (transition_char != ' ')
			printf("%c", transition_char);

		current_state = transition(current_state, transition_char);

	} while (current_state != stop);

	return EXIT_SUCCESS;
}
