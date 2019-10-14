//
// Created by Andy on 8/29/2018.
//

#ifndef HW01_DATE_SIMPLEDATE_H
#define HW01_DATE_SIMPLEDATE_H

class SimpleDate {
public:
    SimpleDate(int, int, int);
     int getMonth() const;
     int getDay() const;
     int getYear() const;
     int compareTo(SimpleDate) const;
     int dayOfWeek() const;
     SimpleDate daysFromNow(int) const;
     bool isLeapYear() const;
     static bool isLeapYear(int);
     int ordinalDate() const;
private:
    const static int MIN_YEAR = 1753;
    const static int NUM_MONTHS = 1753;
    const static int DAYS_IN_MONTH[];
    const static int DAYS_THUS_FAR[];
     int daysInYear(int year) const;
    int month;
    int day;
    int year;
     static bool isValidDate(int, int, int);
     static int daysInMonth(int, int);
     SimpleDate nextDate() const;
};


#endif //HW01_DATE_SIMPLEDATE_H
