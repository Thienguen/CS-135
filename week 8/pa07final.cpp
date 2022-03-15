/// @file pa07.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 11/15/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment conver a string duodecimal to a decimal value
///         with X,x representing 10, and E,e representing 11
///
/// @note People who helped: TA Miguel
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.
///       https://www.youtube.com/watch?v=8nlvj60Ef-k


// include libs
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cstdlib>
#include <limits>

// setting a namcespace scope

// no more namespace

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------

int to_int(const std::string& dozenal);
int at_this_c(char idx);


/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {

    // variable (declarations)
    int test = 0;        // the amount of tests

    std::string duo;     // input string

    std::cin >> test;

    while (test > 0) {
        std::cin >> duo;
        std::cout << to_int(duo) << std::endl;
        test--;
    }

    // return to the operating system
    return EXIT_SUCCESS;

}
/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// Interprets a signed duodecimal value in the string dozenal. Skips any
/// whitespace characters (as defined by `std::isspace`) until the first
/// non-whitespace character is found, then takes as many characters as
/// possible to form a valid integer value.
///
/// The duodecimal value consists of the following parts:
///     * (optional) plus or minus sign
///     * a sequence of duodecimal digits 0-9,Xx,Ee (case ignored)
///
/// If the minus sign was part of the input sequence, the numeric value
/// calculated from the sequence of digits is negated.
///
/// @note If the value of the result cannot be represented, i.e., the
/// converted value falls out of the range of an int, behavior is undefined.
///
/// @param dozenal A string containing a signed duodecimal value
/// to be interpreted.
///
/// @returns The integer value corresponding to the content of dozenal
/// on success. If no conversion can be performed, 0 is returned.

int to_int(const std::string& dozenal) {

    // variable (declarations)
    int product = 0;            // part of the algorithm
    long sum = 0;               // the result
    int duo_at_c = 0;           // the interget value from 0-9 when looping
    int p = 0;                  // power variable

    bool nonsense = true;       // if the input is not 0-9 and X,e cases
    bool negative = false;      // if the input is negative


    // loop backward of the string
    // c iterate from the end of the string to 0
    for (int c = dozenal.length() - 1; c >= 0; c--) {
        // if the char right now is a digit then
        if (isdigit(dozenal.at(c))) {
            duo_at_c = at_this_c(dozenal.at(c));
            product = duo_at_c * pow(12, p);
            sum = sum + product;
            p++;

        } else if (dozenal.at(c) == 'X' || dozenal.at(c) == 'x') {
            // if the char is X,x, E,e cases
            product = 10 * pow(12, p);
            sum = sum + product;
            p++;

        } else if (dozenal.at(c) == 'E' || dozenal.at(c) == 'e') {
            product = 11 * pow(12, p);
            sum = sum + product;
            p++;

        } else if (isspace(dozenal.at(c))) {
            // if there is any white spaces
            // don't do anything and iterate
            c--;

            // check the '-' is on the right or left side of the string
            // for example 30-something or -Ex42
        } else if (dozenal.at(c) == '-') {
            if (isdigit(dozenal.at(c + 1)) || dozenal.at(c + 1) == 'X'
                || dozenal.at(c + 1) == 'x' || dozenal.at(c + 1) == 'E'
                || dozenal.at(c + 1) == 'e') {
                negative = true;
            } else {
                negative = false;
            }
        } else {
            // if it's gibberish, keep iterating
            c--;
        }
    }

    // return the negative value if the input is negative
    if (negative) {
        sum *= -1;
    }

    // return the decimal value
    return sum;
}

/// @param idx the character and the index right now during the loop
/// @note only take '0' to '9' duo to case sensitive, and also
///       condensed the function to a shorter version.
/// @return the interger value corresponding to the content of dozenal
///         on success 0 - 9.

int at_this_c(char idx) {
    int duo_at_c_function = 0;

    // the index contain the content of the string
    // at idx
    switch (idx) {
        case '0':
            duo_at_c_function = 0;
            break;

        case '1':
            duo_at_c_function = 1;
            break;

        case '2':
            duo_at_c_function = 2;
            break;

        case '3':
            duo_at_c_function = 3;
            break;

        case '4':
            duo_at_c_function = 4;
            break;

        case '5':
            duo_at_c_function = 5;
            break;

        case '6':
            duo_at_c_function = 6;
            break;

        case '7':
            duo_at_c_function = 7;
            break;

        case '8':
            duo_at_c_function = 8;
            break;

        case '9':
            duo_at_c_function = 9;
            break;
    }

    // retturn the interger value
    return duo_at_c_function;
}

/// @paragraph I get this struck me a lot when it comes to programming out an actual 
/// @note      program to do this, better on paper tho