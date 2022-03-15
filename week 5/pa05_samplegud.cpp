/// @brief This program reads a month and year from std input
///        and prints a calendar.
///        Input format: MM YYYY
///
/// @note People who helped me:
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include i/o libs
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

// setting up namespace scope
using namespace std;

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {
    // constant definition(s)
    // months of the year
    const int JAN =  1;                 // numeric value for January
    const int FEB =  2;                 // numeric value for February
    const int MAR =  3;                 // numeric value for March
    const int APR =  4;                 // numeric value for April
    const int MAY =  5;                 // numeric value for May
    const int JUN =  6;                 // numeric value for June
    const int JUL =  7;                 // numeric value for July
    const int AUG =  8;                 // numeric value for August
    const int SEP =  9;                 // numeric value for September
    const int OCT = 10;                 // numeric value for October
    const int NOV = 11;                 // numeric value for November
    const int DEC = 12;                 // numeric value for December

    const int COLW = 3;                 // set column width for date output

    const int MIN_YEAR  = 1753;         // min acceptable year for input
    const int MIN_MONTH = 1;            // min value for a month
    const int MAX_MONTH = 12;           // max value for a month

    // variable declarations(s)
    bool   good = false;                   // tracks input success
    int    month;                          // user input month
    int    yearIn;                         // user input year
    int    year;                           // computed year for weekday calcs
    int    day;                            // computed day for weekday calcs
    int    fDays;                          // days in Feb
    int    mDays;                          // days in user month
    int    weekday;                        // 1 = Mo, 2 = Tu, ..., 7 = Su
    int    startPos;                       // starting position of first day
    int    dayCtr;                         // output loop control variable
    int    calWeekDay;                     // weekday pos during output
    string mName;                          // Month name string




    /* ******* input phase ************************************************* */
    // read month and year from standard input

    cin >> month >> yearIn;

    if (cin.fail() ||
        yearIn < MIN_YEAR ||
        month < MIN_MONTH ||
        month > MAX_MONTH) {
        // clear the error and the entire input buffer, requires <limits> header
        cin.clear();

        // note: requires limits.h
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        good = false;
    } else {
        good = true;
    }


    /* ******* processing phase ******************************************** */
    if (!good) {
        cout << "Error: invalid date";
    } else {
        // set month string
        switch (month) {
            case JAN : mName = "January"; break;
            case FEB : mName = "February"; break;
            case MAR : mName = "March"; break;
            case APR : mName = "April"; break;
            case MAY : mName = "May"; break;
            case JUN : mName = "June"; break;
            case JUL : mName = "July"; break;
            case AUG : mName = "August"; break;
            case SEP : mName = "September"; break;
            case OCT : mName = "October"; break;
            case NOV : mName = "November"; break;
            case DEC : mName = "December"; break;
            default : break;
        }

        // Set Feb day count
        // test for every four years
        if (static_cast<bool>(yearIn % 4)) {
            fDays = 28;      // not divisible by 4: is common
        } else if (static_cast<bool>(yearIn % 100)) {
            fDays = 29;      // not divisible by 100: is a leap year
        } else if (static_cast<bool>(yearIn % 400)) {
            fDays = 28;      // not divisible by 400: is a common year
        } else {
            fDays = 29;
        }

        // set user month last day value
        if (month == APR || month == JUN || month == SEP || month == NOV) {
            mDays = 30;
        } else if (month == FEB) {
            mDays = fDays;
        } else {
            mDays = 31;
        }

        // set year for calculating weekday
        year = yearIn;

        // set first day of the month
        day = 1;

        // modify month and year so that it will work in Zeller's formula
        if (month == 1 || month == 2) {
            month += 12;
            year--;
        }

        // compute the weekday code to start with Monday as 1
        weekday = 1 + (day + (13 * (month + 1) / 5) + year + (year / 4) -
                    (year / 100) + (year / 400) + 5) % 7;

        /* ******* output phase ************************************************ */

        // print heading
        cout << mName << ' ' << yearIn << endl
        << "Mo Tu We Th Fr Sa Su" << endl;

        // set calendar day tracker
        calWeekDay = weekday;

        // calc starting position of first day
        startPos = (COLW * weekday) - 1;  // first column is one less

        // set right justify
        cout << right;

        // print first day
        cout << setw(startPos) << 1;
        dayCtr = 2;

        do {
            // add a new line when at the end of the row
            if ((calWeekDay) % 7 == 0) {
                cout << '\n';
                cout << setw(COLW - 1) << dayCtr;
            } else {
                // print the day
                cout << setw(COLW) << dayCtr;
            }

            // update the day counter and calendar week day tracker
            dayCtr++;
            calWeekDay++;

        } while (dayCtr <= mDays);

    }
    cout << endl;

    // return to the operating system
    return static_cast<int>((good) ? 0 : 1);
}

/// @paragraph input would me MM YYYY, eg: 05 2002