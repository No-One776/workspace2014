#
# SimpleDate class represents a calendar date and contains methods to analyze dates.
#
# Author: Justin Rohr & Kyle Niewiada 
#
class SimpleDate

  include Comparable, Enumerable

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

  # generates getter methods for @month, @day, and @year instance variables
  attr_reader :month, :day, :year

  #
  # Initializes the instance variables @month, @day, and @year using the values
  # of parameters.
  #
  # Raises ArgumentError exception when the following is true:
  #     month, day, and year are not Fixnum type, or
  #     values of month, day, and year do not represent a valid date
  #
  def initialize(month, day, year)
    begin
      raise ArgumentError.new("Argument is not a Simple Date object") unless SimpleDate.validDate?(month, day, year) && month.is_a?(Fixnum) && day.is_a?(Fixnum) && year.is_a?(Fixnum)
    rescue NoMethodError
      raise ArgumentError.new("Argument is not a Simple Date object")
    end
    @month = month
    @day = day
    @year = year
  end

  #
  # yields @month, @day, and @year values one at a time in that order
  #
  def each
    yield self.month()
    yield self.day()
    yield self.year()
  end

  #
  # Defines an ordering between this SimpleDate object and other SimpleDate object.
  # Returns a negative, zero, or postive number depending on whether the receiver
  # is less than, equal to, or greater than the other object. If the other
  # object is not comparable then the <=> operator should return nil.
  #
  def <=>(other)
    return nil unless other.instance_of?(SimpleDate)
    if self.year() == other.year
      if self.month() == other.month
        return self.day() <=> other.day
      end
      return self.month() <=> other.month
    end
    return self.year() <=> other.year
  end

  #
  # Returns an integer (must be same as constants SUNDAY, MONDAY, etc.) representing
  # the day of the week for this date.
  #
  def dayOfWeek
    daysElapsed = 0;
    for y in MIN_YEAR...self.year
      daysElapsed += SimpleDate.daysInYear(y)
    end
    daysElapsed += ordinalDate()
    return daysElapsed % 7
  end

  #
  # Returns the number of days in the year of this date
  #
  def daysInYear
    self.class.daysInYear(self.year())
  end

  #
  # Returns true if this date is in a leap year, false otherwise
  #
  def leapYear?
    self.class.leapYear?(self.year())
  end

  #
  # Returns the number of days that have elapsed (including this day) since 1 January.
  #
  def ordinalDate
    ordinalDate = DAYS_THUS_FAR[self.month()] + self.day
    if self.leapYear?() && self.month() > 2
      ordinalDate += 1
    end
    return ordinalDate
  end

  #
  # Returns a SimpleDate object representing the next date of this date.
  #
  def nextDate
    if self.day() < self.class.daysInMonth(self.month(), self.year())
      return SimpleDate.new(self.month(), self.day()+1, self.year())
    elsif self.month() == NUM_MONTHS
      return SimpleDate.new(1, 1, self.year()+1)
    end
    return SimpleDate.new(self.month()+1, 1, self.year())
  end

  #
  # Returns a SimpleDate object representing the previous date of this date or nil if
  # previous date is before the MIN_YEAR (i.e.. 1753).
  #
  def prevDate
    if self.day() > 1
      return SimpleDate.new(self.month(), self.day()-1, self.year())
    elsif self.month() == 1
      return SimpleDate.new(NUM_MONTHS, SimpleDate.daysInMonth(NUM_MONTHS, self.year()), self.year() - 1)
    end
    return SimpleDate.new(self.month()-1, SimpleDate.daysInMonth(self.month()-1, self.year()), self.year())
  end

  #
  # Returns a new SimpleDate object representing the date n days ago.
  # If n is negative, then return the date n days in the future.
  # Raise ArgumentError if the new date is before the minimum allowable date (1/1/1753).
  #
  def daysAgo(n)
    if n == 0
      return self
    elsif n < 0
      return self.daysFromNow(-n)
    end
    current = self
    for i in 1..n do
      current = current.prevDate
      raise ArgumentError.new("New Date Doesn't meet minimum") unless SimpleDate.validDate?(current.month(), current.day(), current.year())
    end
    return current
  end

  #
  # Returns a new SimpleDate object representing the date n days from now.
  # If n is negative, then return the date n days in the past.
  # Raise ArgumentError if the new date is before the minimum allowable date (1/1/1753).
  #
  def daysFromNow(n)
    if n < 1
      return self.daysAgo(-n)
    else
      current = self
      for i in 1..n do
        current = current.nextDate
      end
      return current
    end
    return self
  end

  #
  # Returns a string representation of this SimpleDate object.
  #
  def to_s
    "#{@month}/#{@day}/#{@year}"
  end

  #
  # Class method that returns true if the given year is a leap year, false otherwise.
  #
  def self.leapYear?(year)
    if ((year%4==0 && year%100!=0) || year%400==0)
      return true
    end

  end

  #
  # Class method that returns the number of days in the given year.
  #
  def self.daysInYear(year)
    if SimpleDate.leapYear?(year)
      return DAYS_LEAP_YEAR
    else
      return DAYS_YEAR
    end
  end

  #
  # Class method that returns the number of days in a month for a given year.
  #
  def self.daysInMonth(month, year)
    if SimpleDate.leapYear?(year) && month==2
      return 29
    else
      return DAYS_IN_MONTH[month]
    end
  end

  #
  # Class method that determines if values for month, day, and year represent a valid date.
  #
  def self.validDate?(month, day, year)
    if month < 1 || month > NUM_MONTHS
      return false
    end
    if year < MIN_YEAR
      return false
    end
    if day < 1 || day > SimpleDate.daysInMonth(month, year)
      return false
    end
    return true
  end

end   # end of SimpleDate class

