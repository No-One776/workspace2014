#!/usr/bin/python
"""
# Authors: Justin Rohr & Kyle Niewiada 
# Python Term Paper Project
# Description: Simple Date project in Python with test case
"""
import argparse
from _overlapped import NULL

# define some useful constants
MIN_YEAR = 1753   # minimum allowable year in a date
NUM_MONTHS = 12
DAYS_YEAR = 365
DAYS_LEAP_YEAR = 366
DAYS_IN_MONTH = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
DAYS_THUS_FAR = [0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334]
# define few more useful constants representing day of week
SUNDAY = 0
MONDAY = 1
TUESDAY = 2
WEDNESDAY = 3
THURSDAY = 4
FRIDAY = 5
SATURDAY = 6

class SimpleDate:

    """
    # Initializes the instance variables @month, @day, and @year using the values
    # of parameters.
    #
    # Raises ArgumenttypeError exception when the following is true:
    #     values of month, day, and year do not represent a valid date
    """
    def __init__(self, month, day, year):
        if  not SimpleDate.validDate(month, day, year):
            raise argparse.ArgumentTypeError("Arguments aren't valid")
        self.month = month
        self.day = day
        self.year = year
   
    """    
    # yields @month, @day, and @year values one at a time in that order
    """
    def each(self):
        yield self.month()
        yield self.day()
        yield self.year()   
    
    """
    # Defines an ordering between this SimpleDate object and the other object.
    # Returns a negative, zero, or postive number depending on whether the receiver
    # is less than, equal to, or greater than the other object. If the other
    # object is not comparable then the <=> operator should return null.
    """
    def compareTo(self, other):
        if not isinstance(other, SimpleDate):
            return NULL 
        elif self.year == other.year:
            if self.month == other.month:
                return self.day - other.day
            return self.month - other.month
        return self.year - other.year    
   
    """
    # Returns an integer (must be same as constants SUNDAY, MONDAY, etc.)
    # representing the day of the week for this date.
    """
    def dayOfWeek(self):
        daysElapsed = 0;
        for y in range(MIN_YEAR, self.year):
            daysElapsed += self.dayInYear(y)
        daysElapsed += self.ordinalDate(self)
        return daysElapsed % 7
      
    """
    # Returns the number of days in the year of this date
    """
    def daysInYear(self):
        self.daysInYear(self.year())
      
    """
    # Returns true if this date is in a leap year, false otherwise
    """
    def leapYear(self):
        self.isleapYear(self.year)
    
    """
    # Returns the number of days that have elapsed (including this day)
    # since 1 January.
    """
    def ordinalDate(self):
        ordinalDate = DAYS_THUS_FAR[self.month] + self.day
        if self.leapYear(self) and self.month > 2:
            ordinalDate += 1
        return ordinalDate
       
    """
    # Returns a SimpleDate object representing the next date of this date.
    """
    def nextDate(self):
        if self.day < SimpleDate.daysInMonth(self.month, self.year):
            return SimpleDate(self.month, self.day+1, self.year)
        elif self.month == NUM_MONTHS:
            return SimpleDate(1, 1, self.year+1)
        return SimpleDate(self.month+1, 1, self.year)
        
    """
    # Returns a SimpleDate object representing the previous date of this date 
    # or nil if previous date is before the MIN_YEAR (i.e.. 1753).
    """
    def prevDate(self): 
        if self.day > 1:
            return SimpleDate(self.month, self.day-1, self.year)
        elif self.month == 1:
            return SimpleDate(NUM_MONTHS, SimpleDate.daysInMonth(NUM_MONTHS, self.year), self.year - 1)
        return SimpleDate(self.month-1, SimpleDate.daysInMonth(self.month-1, self.year), self.year)    
    
    """
    # Returns a new SimpleDate object representing the date n days ago.
    # If n is negative, then return the date n days in the future.
    # Raise ArgumentTypeError if the new date is before the minimum allowable date.
    """
    def daysAgo(self, n):
        if n == 0:
            return self
        elif n < 0:
            return self.daysFromNow(-n)
        current = SimpleDate
        current.__init__(current, self.month, self.day, self.year)
        for i in range(0, n):
            current = SimpleDate.prevDate(current)
            if not SimpleDate.validDate(current.month, current.day, current.year):
                raise argparse.ArgumentError("New Date Doesn't meet minimum")
        return current     
    
    """
    # Returns a new SimpleDate object representing the date n days from now.
    # If n is negative, then return the date n days in the past.
    # Raise ArgumentTypeError if the new date is before the minimum allowable date.
    """
    def daysFromNow(self, n):  
        if n < 1:
            return self.daysAgo(-n)
        else:
            current = SimpleDate
            current = self
            for i in range(0,n):
                current = SimpleDate.nextDate(current)    
            return current
        return self      
    
    """
    # Returns a string representation of this SimpleDate object.
    """
    def to_s(self):  
        return str(self.month) + "/" + str(self.day) + "/" + str(self.year)
    
    """
    # Class method that returns true if the given year is a leap year,
    # false otherwise.
    """
    def isleapYear(year):  # @NoSelf
        if ((year%4==0 and year%100!=0) or year%400==0):
            return True
        return False
   
    """
    # Class method that returns the number of days in the given year.
    """
    def dayInYear(year):  # @NoSelf
        if SimpleDate.isleapYear(year):
            return DAYS_LEAP_YEAR
        else:
            return DAYS_YEAR 
  
    """
    # Class method that returns the number of days in a month for a given year.
    """
    def daysInMonth(month, year):  # @NoSelf
        if SimpleDate.isleapYear(year) and month==2:
            return 29
        else:    
            return DAYS_IN_MONTH[month] 
 
    """
    # Class method that determines if values for 
    # month, day, and year represent a valid date.
    """
    def validDate(month, day, year):  # @NoSelf
        if month < 1 or month > NUM_MONTHS:
            return False    
        if year < MIN_YEAR:
            return False    
        if day < 1 or day > SimpleDate.daysInMonth(month, year):
            return False 
        return True
       
# end of SimpleDate class
"""
#Test Cases below to test the Simple Date classes' functions for full operation
"""

date = SimpleDate
date.__init__(date, 1, 2, 2014)
print(date.to_s(date))
print(date.dayOfWeek(date))
print(date.compareTo(date, date))
current = date.daysAgo(date, 7849)
print(current.to_s())
print(date.compareTo(date, current))
next = date.daysFromNow(date,30)
print(SimpleDate.to_s(next))
