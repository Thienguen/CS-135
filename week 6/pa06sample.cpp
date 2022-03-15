/// @brief This program calculates and reports the week day number and
///        the Julian date
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include i/o libs
#include <iostream>
#include <string>
#include <iomanip>

// setting up namespace scope
using namespace std;


/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
int month_number(const std::string& month_name);
long julian_day_number(int year, int month, int day);
double julian_date(int year, int month, int day, int hour, int minute, int sec);
int weekDay(int year, int month, int day);


/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {

    // variable declarations(s)
    string monthIn;                 // a three character month name: Jan, etc.

    /* ******* input phase ************************************************* */
    while (cin >> monthIn) {
        int month;                          // holds month as int [1, 12]
        int day;                            // day of month [1, 31]
        int hour;                           // hour of day [0, 23]
        int minute;                         // minute of day [0, 59]
        int second;                         // second of day [0, 59]
        int year;                           // year (valid 4713 BCE forward)
        char del1;                          // first time delimeter [:]
        char del2;                          // second time delimeter [:]

        double  jd;                         // holds the julian date
        int     wd;                         // holds weekday, mon = 0

        // get the data string
        month = month_number(monthIn);      // convert month string to int code
        cin >> day;                         // read in the day
        cin >> hour;                        // read in the hours
        cin.get(del1);                      // read the colon
        cin >> minute;                      // read the minutes
        cin.get(del2);                      // read the second colon
        cin >> second;                      // read in the seconds
        cin >> year;                        // read in the year


        jd = julian_date(year, month, day, hour, minute, second);
        wd = weekDay(year, month, day);
        cout << fixed << setprecision(6);
        cout << wd << ' ' << jd << endl;
    }

    // return to the operating system
    return 0;
}

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// Returns the month number given the month name, e.g. 1 for "Jan"
/// @param month_name 3-chars 1st uppercase 2nd and 3rd lowercase
/// @return month value in the range of 1 to 12, else 0 on fail
int month_number(const std::string& month_name) {
    int m = 0;      // holds month number

    // translate month to int
    if (month_name == "Jan") {
        m = 1;
    } else if (month_name == "Feb") {
        m = 2;
    } else if (month_name == "Mar") {
        m = 3;
    } else if (month_name == "Apr") {
        m = 4;
    } else if (month_name == "May") {
        m = 5;
    } else if (month_name == "Jun") {
        m = 6;
    } else if (month_name == "Jul") {
        m = 7;
    } else if (month_name == "Aug") {
        m = 8;
    } else if (month_name == "Sep") {
        m = 9;
    } else if (month_name == "Oct") {
        m = 10;
    } else if (month_name == "Nov") {
        m = 11;
    } else if (month_name == "Dec") {
        m = 12;
    } else {
        m = 0;  // no translation available
    }

    return m;
}

/// Returns the Julian Day Number for a Gregorian calendar date
/// @param year is the year
/// @param month is the month
/// @param day is the day of the month
/// @return Julian day number
long julian_day_number(int year, int month, int day) {
    long jdn;

    jdn = static_cast<long>((1461 * (year + 4800 + (month - 14) / 12)) / 4 +
    (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12 -
    (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 +
    day - 32075);

    return jdn;
}

/// Returns the Julian Date for an instant in time.
/// @param year is the year
/// @param month is the month
/// @param day is the day of the month
/// @param hour is the hour of the day
/// @param minute is the minute of the hour
/// @param sec is the second of the minute
/// @return Julian date
double julian_date(int year, int month, int day,
                   int hour, int minute, int sec) {
    double jd;
    long jdn;

    jdn = julian_day_number(year, month, day);
    jd = jdn + (hour - 12.0) / 24.0 + minute / 1440.0 + sec / 86400.0;

    return jd;
}


/// Returns the week day, mon = 0
/// @param year is the year
/// @param month is the month of the year
/// @param day is the day of the month
/// @return integer day of the weekday, mon = 0
int weekDay(int year, int month, int day) {
    return static_cast<int>(julian_day_number(year, month, day) % 7);
}

/// @paragraph Input format: Month (abbreviated to 3 letters)
/// MMM Day Hour:Minute:Second Year, eg: Jan 2 24/12/2 2002