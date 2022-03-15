/// @file lab06a.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 11/1/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment try out many different
///        function like floor, max, min, average, bool, etc.
///
/// @note People who helped me: None
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include libs
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cstdlib>

// setting a namcespace scope
using namespace std;


/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
double fahrenheit(double celsius);

double celsius(double fahrenheit);

int minimum(int a, int b);

int maximum(int a, int b);

double average(int n1, int n2, int n3);

int median(int n1, int n2, int n3);

bool is_leapyear(int year);

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// ----------------------------------------------------------------------
int main() {
    // variables declaration(s)
    int  n1;
    int  n2;
    int  n3;
    int  year;
    bool leapyear;


    // Built-in value-returning functions
    cout << "a. floor(44.56): " << floor(44.56)
         << ", and floor(-23.78):  " << floor(-23.78) << endl;

    cout << "b. ceil(25.23): " << ceil(25.23)
         << ", and ceil(-2.89): " << ceil(-2.89) << endl;

    cout << "c. pow(5.0,3): " << pow(5.0, 3)
         << ", and pow(5,- 3): " << pow(5, -3) << endl;

    cout << "d. sqrt(44.56): " << sqrt(44.56) << endl;

    // test c -> f
    cout << "\n-40c  = "  << fahrenheit(-40) << " degrees f\n"
         << " 0c   = "  << fahrenheit(0)   << "  degrees f\n"
         << " 15c  = "  << fahrenheit(15)  << "  degrees f\n"
         << " 25c  = "  << fahrenheit(25)  << "  degrees f\n"
         << " 100c = "  << fahrenheit(100) << " degrees f" << endl;

    // test f -> c
    cout << "\n-40c  = " << celsius(-40) << " degrees f\n"
         << " 32f  = " << celsius(32)  << "   degrees c\n"
         << " 59f  = " << celsius(59)  << "  degrees c\n"
         << " 77f  = " << celsius(77)  << "  degrees c\n"
         << " 212f = " << celsius(212) << " degrees c" << endl;

    // random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // the minimum function
    cout << endl;

    for (int i = 0; i < 5; i++) {
        n1 = (rand() % 100) + 1;
        n2 = (rand() % 100) + 1;
        n3 = (rand() % 100) + 1;

        // result of the test
        cout << "The smallest of"
             << setw(4) << n1
             << setw(4) << n2
             << setw(4) << n3
             << " is:  " << minimum(minimum(n1, n2), n3) << endl;
    }

    // the maximum function
    cout << endl;

    for (int i = 0; i < 5; i++) {
        n1 = (rand() % 100) + 1;
        n2 = (rand() % 100) + 1;
        n3 = (rand() % 100) + 1;

        // result of the test
        cout << "The largest of"
             << setw(4) << n1
             << setw(4) << n2
             << setw(4) << n3
             << " is:  " << maximum(maximum(n1, n2), n3) << endl;
    }

    // the average function
    cout << endl;

    for (int i = 0; i < 5; i++) {
        n1 = (rand() % 100) + 1;
        n2 = (rand() % 100) + 1;
        n3 = (rand() % 100) + 1;

        // return the average
        cout << "The average of" << setprecision(2) << fixed
             << setw(4) << n1
             << setw(4) << n2
             << setw(4) << n3
             << " is:  " << average(n1, n2, n3) << endl;
    }

    // the median fucntion
    cout << endl;

    for (int i = 0; i < 5; i++) {
        n1 = (rand() % 100) + 1;
        n2 = (rand() % 100) + 1;
        n3 = (rand() % 100) + 1;

        // return the average
        cout << "The median of"
             << setw(4) << n1
             << setw(4) << n2
             << setw(4) << n3
             << " is:  " << median(n1, n2, n3) << endl;
    }

    // the leapyear fucntion
    cout << endl;
    leapyear = 0;

    for (int i = 0; leapyear == 0; i++) {
        year = (rand() % (2026 - 1776)) + 1776;
        is_leapyear(year) ? leapyear = 1 : leapyear = 0;

        if (leapyear == 1) {
            cout << year << " is a leap year. It took "
                 << i << " random tries to find this leap year."
                 << endl;
        }
    }

    // return to the OS
    return EXIT_SUCCESS;
}

/// -----------------------------------------------------------------------
/// Function Implementation
/// -----------------------------------------------------------------------

/// Returns Fahrenheit equivalent of celsius temperature.
/// @param celsius A Celsius temperature to convert.
/// @return The Fahrenheit temperature.

double fahrenheit(double celsius) {
    double f;
    // calculate f from c
    f = 9.0 / 5 * celsius + 32;
    return f;
}

/// Returns Celsius equivalent of fahrenheit temperature.
/// @param fahrenheit A Fahrenheit temperature to convert.
/// @return The Celsius temperature.

double celsius(double fahrenheit) {
    double c;
    // calculate c from f
    c = (5.0 / 9) * (fahrenheit - 32);
    return c;
}

/// Returns the smaller of the given values.
/// @param n1 A value to compare.
/// @param n2 A value to compare.
/// @return the minimum

int minimum(int n1, int n2) {
    int answer;

    // compare the minimum
    if (n1 < n2) {
        answer = n1;
    } else {
        answer = n2;
    }

    return answer;
}

/// Returns the larger of the given values.
/// @param n1 A value to compare.
/// @param n2 A value to compare.
/// @return the maximum

int maximum(int n1, int n2) {
    // compare the maximum
    return (n1 > n2) ? n1 : n2;
}

/// Returns the average of the given values.
/// @param n1 A value from random.
/// @param n2 A value from random.
/// @param n3 A value from random.
/// @return the average of three random values

double average(int n1, int n2, int n3) {
    double answer;
    double total;
    total = static_cast<double>(n1 + n2 + n3);
    answer = total / 3;
    // return the average of three numbers
    return answer;
}

/// Returns the median of the given values.
/// @param n1 A value from random.
/// @param n2 A value from random.
/// @param n3 A value from random.
/// @return the median of three random values
int median(int n1, int n2, int n3) {
    int answer;
    answer = max(min(n1, n2), min(max(n1, n2), n3));
    // return the median
    return answer;
}

/// Returns the true or false statement indicate
/// whether the input is leap year or not
/// @param year A value from random.
/// @return the median of three random values
bool is_leapyear(int year) {
    bool LeapYear = false;

    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                LeapYear = true;
            }
        } else {
            LeapYear = true;
        }
    }

    return LeapYear;
}

/// @paragraph just testing out random stuff