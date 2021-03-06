#ifndef  SIMPLEDATE_H_
#define SIMPLEDATE_H_

class SimpleDate {
public:
	static const int MIN_YEAR;
	int getMonth() const;
	int getDay() const;
	int getYear() const;
	int dayOfWeek();
	int compareTo(SimpleDate* other);
	SimpleDate daysFromNow(int n); // throw std::invalid_agument;
	int ordinalDate();
	static bool isLeapYear(int year);
	bool isLeapYear();
	SimpleDate(int monthin, int dayin, int yearin);
private:
	int month;
	int day;
	int year;
	int daysInYear(int year);
	static const int daysInMonths[];
	static const int DAYS_THUS_FAR[];
	static const int NUM_MONTHS;
	static int daysInMonth(int month, int year);
	static bool isValidDate(int month, int day, int year);
	SimpleDate nextDate();
};
#endif
