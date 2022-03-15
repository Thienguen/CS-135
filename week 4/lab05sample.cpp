/// @brief This program prompts the user for a year
///        User must supply correct input - loop until success
///        If good: print
///            the number of the month (LCV)
///            name of month
///            days in month accounting for leap years
///            day of the week for the last day of the month
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include i/o libs
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

// setting up namespace scope
using namespace std;

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------

int main() {

    // constant definition(s)
    // the months of the year
    const int JAN =  1;         // numeric value for January
    const int FEB =  2;         // numeric value for February
    const int MAR =  3;         // numeric value for March
    const int APR =  4;         // numeric value for April
    const int MAY =  5;         // numeric value for May
    const int JUN =  6;         // numeric value for June
    const int JUL =  7;         // numeric value for July
    const int AUG =  8;         // numeric value for August
    const int SEP =  9;         // numeric value for September
    const int OCT = 10;         // numeric value for October
    const int NOV = 11;         // numeric value for November
    const int DEC = 12;         // numeric value for December
    const int MON =  0;         // numeric value for Monday
    const int TUE =  1;         // numeric value for Tuesday
    const int WED =  2;         // numeric value for Wednesday
    const int THU =  3;         // numeric value for Thursday
    const int FRI =  4;         // numeric value for Friday
    const int SAT =  6;         // numeric value for Saturday
    const int SUN =  7;         // numeric value for Sunday

    // set up table columns
    const int COL0 = 6;
    const int COL2 = COL0;
    const int COL1 = 2 * COL0;
    const int COL3 = COL1;

    const int MIN_YEAR = 1753;          // min acceptable year for input

    // variable declarations(s)
    bool good    = false;               // track input success
    int yearIn;                         // user entered year
    int fDays;                          // holds the number of days in Feb
    int day;                            // holds the last day in a month
    int weekday    ;                    // holds the computed weekday
    int month;                          // holds month value to compute weekday
    int year;                           // holds year value to compute weekday

    string dName = "";                  // holds the week day name
    string mName = "";                  // holds the month name

    /* ******* input phase ************************************************* */

    // repeatidly try to obtain a year from the user until a good entry is made
    do {
        cout << "Enter year: ";
        cin >> yearIn;
        if (cin.fail() || yearIn < MIN_YEAR) {
            // clear the error and input buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            good = true;
            cout << endl;
        }
    } while (!good);

    /* ******* processing phase ******************************************** */

    // set Feb day count
    // test for every four years
    if (static_cast<bool>(yearIn % 4)) {
        fDays = 28;      // not divisable by 4: is common
    } else if (static_cast<bool>(yearIn % 100)) {
        fDays = 29;      // not divisable by 100: is a leap year
    } else if (static_cast<bool>(yearIn % 400)) {
        fDays = 28;      // not divisable by 400: is a common year
    } else {
        fDays = 29;
    }


    /* ******* output phase ************************************************ */
    // print the header
    cout << left << yearIn << '\n'
    << setw(COL0) << "Month"
    << setw(COL1) << "Name"
    << setw(COL2) << "Days"
    << setw(COL3) << "Last Day"
    << endl;

    // iMonth is the month interator
    for (int iMonth = JAN; iMonth <= DEC; iMonth++ ) {
        // set the number of days in the month.
        if (iMonth == APR || iMonth == JUN || iMonth == SEP || iMonth == NOV) {
            day = 30;
        } else if (iMonth == FEB) {
            day = fDays;
        } else {
            day = 31;
        }

        // set the month name
        switch (iMonth) {
            case JAN : mName = "January"  ; break;
            case FEB : mName = "February" ; break;
            case MAR : mName = "March"    ; break;
            case APR : mName = "April"    ; break;
            case MAY : mName = "May"      ; break;
            case JUN : mName = "June"     ; break;
            case JUL : mName = "July"     ; break;
            case AUG : mName = "Agust"    ; break;
            case SEP : mName = "September"; break;
            case OCT : mName = "October"  ; break;
            case NOV : mName = "November" ; break;
            case DEC : mName = "December" ; break;
            default : break;
        }

        // compute the weekday

        // set up vars to compute weekday
        month = iMonth + 1;
        year  = yearIn;

        if (month == 1 || month == 2) {
            month += 12;
            year--;
        }

        // compute the weekday code
        weekday = ( day + (13 * (month + 1) / 5) + year + (year / 4) -
                (year / 100) + (year / 400) + 5 ) % 7;

        // Obtain the name from the weekday code
        switch (weekday) {
            case MON: dName = "Monday"      ; break;
            case TUE: dName = "Tuesday"     ; break;
            case WED: dName = "Wednesday"   ; break;
            case THU: dName = "Thursday"    ; break;
            case FRI: dName = "Friday"      ; break;
            case SAT: dName = "Saturday"    ; break;
            case SUN: dName = "Sunday"      ; break;
            default: break;
        }

        // print the month number
        cout << setw(COL0) << iMonth

        // print the month name
        << setw(COL1) << mName

        // print the number of days in the month
        << setw(COL2) << day

        // print the weekday name
        << setw(COL3) << dName

        << endl;
    }

    // return to the operating system
    return 0;
}

/// @paragraph input would be any valid year