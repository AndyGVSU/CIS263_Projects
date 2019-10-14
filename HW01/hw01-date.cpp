#include <iostream>
#include "SimpleDate.h"

using namespace std;

int main() {
    //tests all public functions (and therefore all private functions)
    //It should be noted: the original code for compareTo() does not work as defined in its comment block
    SimpleDate date1 (1,1,2018);
        cout << date1.getDay() << endl;
        cout << date1.getMonth() << endl;
        cout << date1.getYear() << endl;
    SimpleDate date3 (1,1,2018);
    SimpleDate date4 (1,7,2018);
        cout << date3.compareTo(date4) << endl;
        cout << date4.dayOfWeek() << endl;
    SimpleDate date5 = date3.daysFromNow(3);
        cout << date5.getDay() << endl;
        cout << date3.isLeapYear() << endl;
    SimpleDate date6 (1,1,2020);
        cout << date6.isLeapYear() << endl;
        cout << SimpleDate::isLeapYear(2020) << endl;
    try {SimpleDate date2 (-1,1,2018);}
        catch(invalid_argument) {std::cout << "date2 error caught successfully" << std::endl;}
        cout << date6.ordinalDate() << endl;

    return 0;
}