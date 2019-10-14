//
// Replicated by Andy on 8/29/2018.
//
#include "SimpleDate.h"
#include <stdexcept>

using namespace std;

const int SimpleDate::DAYS_IN_MONTH[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int SimpleDate::DAYS_THUS_FAR[] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

/**
 * Constructor taking month, day, and year as integers.
 *
 * @param month the month
 * @param day the day
 * @param year the year
 * @throws IllegalArgumentException if {@code month}/{@code day}/{@code year}
 * 			doesn't represent a valid date.
 */
SimpleDate::SimpleDate(int m, int d, int y) {
    month = m;
    day = d;
    year = y;

    if (!isValidDate(month, day, year))
        throw std::invalid_argument("invalid values for fields");
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

/**
 * Compares two {@code SimpleDate}s.
 *
 * @param other Other {@code SimpleDate}
 * @return -1 if {@code this < other}, 0 if {@code this} is equal to
 *         {@code other}, 1 if {@code this > other}.
 */
 int SimpleDate::compareTo(SimpleDate other) const {
    if (getYear() != other.getYear()) {
        return getYear() - other.getYear();
    }

    if (getMonth() != other.getMonth()) {
        return getMonth() - other.getMonth();
    }

    return getDay() - other.getDay();
}

 int SimpleDate::dayOfWeek() const {
    int daysElapsed = 0;
    for (int year = MIN_YEAR; year < getYear(); year++) {
        daysElapsed += daysInYear(year);
    }
    daysElapsed += ordinalDate();

    return daysElapsed % 7;
}

 int SimpleDate::daysInYear(int year) const {
    return isLeapYear(year) ? 366 : 365;
}

 SimpleDate SimpleDate::daysFromNow(int n) const {
    if (n == 0) {
        return SimpleDate(month, day, year);
    } else if (n < 0) {
        throw std::invalid_argument("n can't be negative");
    } else {
        SimpleDate date = nextDate();
        for (int i = 1; i < n; i++) {
            date = date.nextDate();
        }

        if (date.getYear() < MIN_YEAR)
            throw std::invalid_argument("Resulting date is before 1/1/1753");

        return date;
    }
}

 bool SimpleDate::isLeapYear() const {
    return isLeapYear(getYear());
}

 bool SimpleDate::isLeapYear(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

/**
     * Returns the number of days that have elapsed (including this day) since 1
     * January. For example,
     * <ul>
     * <li>1 January will return 1.
     * <li>31 January will return 31.
     * <li>1 February will return 32.
     * </ul>
     *
     * @return the number of days that have elapsed (including this day) since 1
     *         January.
     */
 int SimpleDate::ordinalDate() const {
    int answer = DAYS_THUS_FAR[month] + day;
    if (isLeapYear() && month > 2) {
        answer++;
    }
    return answer;
}

// Determines if values for month, day, and year represent a valid date.
 bool SimpleDate::isValidDate(int month, int day, int year) {
    if (month < 1 || month > NUM_MONTHS) {
        return false;
    }

    if (day < 1 || day > daysInMonth(month, year)) {
        return false;
    }

    return year >= MIN_YEAR;
}

// Returns the number of days in a month for a given year
  int SimpleDate::daysInMonth(int month, int year) {
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return DAYS_IN_MONTH[month];
}

// Returns the next date of this date.
 SimpleDate SimpleDate::nextDate() const {
    // handle 31-day months
    if (month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10) {
        if (day < 31) {
            return SimpleDate(month, day + 1, year);
        } else {
            return SimpleDate(month + 1, 1, year);
        }
    }

    // handle 30-day month
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day < 30) {
            return SimpleDate(month, day + 1, year);
        } else {
            return SimpleDate(month + 1, 1, year);
        }
    }

    // handle February month
    if (month == 2) {
        if (day < 28) {
            return SimpleDate(month, day + 1, year);
        } else {
            if (isLeapYear()) {
                return SimpleDate(month, day + 1, year);
            } else {
                return SimpleDate(month + 1, 1, year);
            }
        }
    }

    // handle December month
    if (month == 12) {
        if (day < 31) {
            return SimpleDate(month, day + 1, year);
        } else {
            return SimpleDate(1, 1, year + 1);
        }
    }
}
