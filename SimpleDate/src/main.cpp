//============================================================================
// Name        : main.cpp
// Author      : Justin Rohr
// Version     : 1
// Description : SimpleDate.java to C++ Conversion Main Function Testing File
//============================================================================

#include "SimpleDate.h"
#include <stdio.h>

int main() {
	SimpleDate date(9, 17, 2014);
	printf("\nDay: %d", date.getDay());
	printf("\nMonth: %d", date.getMonth());
	printf("\nYear: %d", date.getYear());
	printf("\nDay of Week: %d", date.dayOfWeek());
	printf("\n2 Days from now: %d", date.daysFromNow(2).getDay());
	printf("\n20 Days from now: %d", date.daysFromNow(20).getDay());
	printf("\n20 Days from now - Month: %d\n", date.daysFromNow(20).getMonth());
	date.isLeapYear() ?
			printf("It's a leap year!") : printf("Its not a leap year!");
	printf("\nOrdinal date: %d", date.ordinalDate());
	printf("\n200 Days from now: %d", date.daysFromNow(200).getDay());
	printf("\n200 Days from now - Month: %d", date.daysFromNow(200).getMonth());
	printf("\n200 Days from now - Year: %d", date.daysFromNow(200).getYear());
	date = SimpleDate(2, 1, 2016);
	printf("\nDay: %d", date.getDay());
	printf("\nMonth: %d", date.getMonth());
	printf("\nYear: %d\n", date.getYear());
	date.isLeapYear() ?
			printf("It's a leap year!") : printf("Its not a leap year!");
	printf("\nCompare to Same Date: %d",
			date.compareTo(new SimpleDate(2, 1, 2016)));
	printf("\nCompare to Different Day Date: %d",
			date.compareTo(new SimpleDate(2, 4, 2016)));
	printf("\nCompare to Different Year Date: %d",
			date.compareTo(new SimpleDate(2, 1, 2014)));
	printf("\nCompare to Different Month Date: %d",
			date.compareTo(new SimpleDate(1, 1, 2016)));
	return 0;
}
