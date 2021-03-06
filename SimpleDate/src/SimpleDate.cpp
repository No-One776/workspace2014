//============================================================================
// Name        : SimpleDate.cpp
// Author      : Justin Rohr
// Version     : 1
// Description : SimpleDate.java to C++ Conversion
//============================================================================

#include "SimpleDate.h"
#include <stdexcept>

const int SimpleDate::daysInMonths[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30,
		31, 30, 31 };
const int SimpleDate::DAYS_THUS_FAR[] = { 0, 0, 31, 59, 90, 120, 151, 181, 212,
		243, 273, 304, 334 };
const int SimpleDate::MIN_YEAR = 1753;
const int SimpleDate::NUM_MONTHS = 12;

bool SimpleDate::isLeapYear(int year) {
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

bool SimpleDate::isLeapYear() {
	return isLeapYear(year);
}

int SimpleDate::daysInMonth(int month, int year) {
	if (month == 2 && isLeapYear(year))
		return 29;
	return daysInMonths[month];
}

int SimpleDate::daysInYear(int year) {
	return isLeapYear(year) ? 366 : 365;
}

int SimpleDate::ordinalDate() {
	int answer = DAYS_THUS_FAR[month] + day;
	(isLeapYear(year) && month > 2) ? answer++ : 0;
	return answer;
}

int SimpleDate::dayOfWeek() {
	int daysElapsed = 0;
	for (int y = MIN_YEAR; y < year; y++)
		daysElapsed += daysInYear(y);

	daysElapsed += ordinalDate();
	return daysElapsed % 7;
}

bool SimpleDate::isValidDate(int month, int day, int year) {
	if (month < 1 || month > NUM_MONTHS)
		return false;
	if (day < 1 || day > daysInMonth(month, year))
		return false;
	return year >= MIN_YEAR;
}

SimpleDate::SimpleDate(int monthin, int dayin, int yearin) {
	month = monthin;
	day = dayin;
	year = yearin;

	if (!isValidDate(month, day, year)) {
		throw std::invalid_argument("Not a valid date");
	}
}

int SimpleDate::getMonth() const {
	return month;
}

int SimpleDate::getDay() const {
	return day;
}

int SimpleDate::getYear() const {
	return year;
}

int SimpleDate::compareTo(SimpleDate* other) {
	if (year != other->getYear())
		return year - other->getYear();

	if (month != other->getMonth())
		return month - other->getMonth();

	return day - other->getDay();
}

SimpleDate SimpleDate::nextDate() {
	SimpleDate next(1, 1, 2000);

	// handle 31-day months
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
			|| month == 10) {
		if (day < 31)
			next = SimpleDate(month, day + 1, year);
		else
			next = SimpleDate(month + 1, 1, year);
	}

	// handle 30-day month
	if (month == 4 || month == 6 || month == 9 || month == 11) {
		if (day < 30)
			next = SimpleDate(month, day + 1, year);
		else
			next = SimpleDate(month + 1, 1, year);
	}

	// handle February month
	if (month == 2) {
		if (day < 28)
			next = SimpleDate(month, day + 1, year);
		else if (isLeapYear())
			next = SimpleDate(month, day + 1, year);
		else
			next = SimpleDate(month + 1, 1, year);
	}

	// handle December month
	if (month == 12) {
		if (day < 31)
			next = SimpleDate(month, day + 1, year);
		else
			next = SimpleDate(1, 1, year + 1);
	}

	return next;
	delete &next;
}

SimpleDate SimpleDate::daysFromNow(int n) {
	if (n == 0)
		return SimpleDate(month, day, year);

	SimpleDate date(month, day, year);
	if (n < 0)
		throw std::invalid_argument("n can't be negative");
	else
		for (int i = 0; i < n; i++)
			date = date.nextDate();

	if (date.getYear() < MIN_YEAR)
		throw std::invalid_argument("Resulting date is before 1/1/1753");
	return date;
}
