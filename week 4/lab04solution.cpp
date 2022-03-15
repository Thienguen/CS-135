/// @date 10/1/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This program prompts the user for a year and then reads an integer
///        representing a year in the Gregorian calendar.
///        The program outputs '1' if the year is a leap year, or
///        '0' if it is a common year.
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

// setting up namespace scope
using namespace std;

// prototype
bool leap(int y) {
    bool isLeap = false;
    if (static_cast<bool>(y % 4)) {
        isLeap = false;         // not divisible by 4: is common
    } else if (static_cast<bool>(y % 100)) {
        isLeap = true;          // not divisible by 100: is a leap year
    } else if (static_cast<bool>(y % 400)) {
        isLeap = false;         // not divisible by 400: is a common year
    } else {
        isLeap = true;
    }

    return isLeap;
}

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {
    // constant definition(s)

    // variable declarations(s)
    int year;                   // user input: 4 digit year

    bool isLeap;                // results of leap year test
    // false : 0 - if common year
    // true  : 1 - if leap year

    /* ******* input phase ************************************************* */
    cout << "Enter a year: ";
    cin >> year;

    /* ******* processing phase ******************************************** */

    // test for leap year
    // test for every four years
    if (static_cast<bool>(year % 4)) {
        isLeap = false;         // not divisible by 4: is common
    } else if (static_cast<bool>(year % 100)) {
        isLeap = true;          // not divisible by 100: is a leap year
    } else if (static_cast<bool>(year % 400)) {
        isLeap = false;         // not divisible by 400: is a common year
    } else {
        isLeap = true;
    }


    /* ******* output phase ************************************************ */
    cout << isLeap << endl;

    for (int i = 1800; i < 3000; i++) {
        if (leap(i)) {
            cout << i << ", ";
        }
    }
    cout << endl;

    // return 1 if it is not a leap year, 0 if it is.
    // remember: the OS sees a 0 as a success
    return static_cast<int>(!isLeap);
}