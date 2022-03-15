/// @file pa04.cpp
/// @author Thien Nguyen thien.nguyen.csn.edu
/// @date 6/10/2021
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This program calculate the weekday of the given date
///        Base on the Gregorian calendar. 
/// @note People who helped me:
/// @note This is but one possible solution to the assignment and likely is
///       not the best one to make sure commands in this solution are aligned
///       with the current chapter, labs, and lecture

// include libs
#include <iostream>
#include <string>
#include <math.h>

// setting up namespace scope
using namespace std;

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------

int main() {
    // variable decleration(s)
    int day;                       // the day given
    int month;                     // the month given
    int year;                      // the year given  
    int a, b, c, d, e, f, weekday; // all the term in the algorithm
    /* Multiple declaration here */ 
    int valid_date = 1;
    char slash;
    /* ******* input phase ********************************************* */
    cin >> year >> slash >> month >> slash >> day; // The date given

    if (day < 1 || day > 31) {
        cout << "Error: invalid date \n"; // invalid date
        valid_date = 1;
    } else if (month < 1 || month > 12) {
        cout << "Error: invalid date \n"; // invalid date
        valid_date = 1;
    } else if (year < 1753) {
        cout << "Error: invalid date \n"; // invalid date
        valid_date = 1;
    } else {
    valid_date = 0;
    if (month == 1) {
    month == 13; // consider Jan to be the 13th month of last year
    year  --;
    }

    if (month == 2) {
    month == 14; // consider Feb to be the 14th month of last year
    year  --;
    }

    a = day;      // formula 1st term
    b = ((13*(month + 1))/5); // formula 2nd term
    c = year;     // formula 3rd term
    d = year/4;   // formula 4th term
    e = year/100; // Multiple of 100, we back-off one or 
                  // 5th term of the formula
    f = year/400; // 6th term of the formula
    weekday = (a + b + c + d - e + f + 5) % 7; // Zeller algorithm

    switch (weekday) {
    case 0:
        cout << weekday << " Monday \n";
        break;
    case 1:
        cout << weekday << " Tuesday \n";
        break;
    case 2:
        cout << weekday << " Wednesday \n";
        break;
    case 3:
        cout << weekday << " Thursday \n";
        break;
    case 4:
        cout << weekday << " Friday \n";
        break;
    case 5:
        cout << weekday << " Saturday \n";
        break;
    case 6:
        cout << weekday << " Sunday \n";
        break;
    }
    }
    return valid_date;
    
}




