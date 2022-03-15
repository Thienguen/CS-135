/// @file lab07.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 11/12/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment reads string input and determine
///         whether the inpud is valid or not in format
///         000-0000 as phone number then convert it to 
///         800-000-000
/// @note People who helped me: None
///
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include libs
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

// setting a namcespace scope
using namespace std;

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
bool is_number(const std::string& s);
bool secondvalidation(const std::string& s);

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {
    // variable declaration(s)
    bool first_validation = false;      // first check 
    string phone_num = " ";             // user input of phone num
    string tele = "800-";               // step 2 of the program

    
    /* ******* input phase ********************************************* */
    cout << "Enter a seven-digit phone number in the form 000-0000: ";
    getline(cin, phone_num);

    // check to ensure the length of the 
    // string is exactly 8, and, the character at position 3 is a '-'. 
    first_validation = !cin.fail() && phone_num.length() == 8
                    && phone_num.find('-') == 3;

    if (first_validation) {
        //  check that all the characters (except the one at position 3!)
        //  are digit characters
        if (secondvalidation(phone_num)) {
            cout << "The number is in proper format.\n";
        } else {
            cout << "The number is not in proper format.\n";
        }
    } else {
        cout << "The number is not in proper format.\n";
    }

    // Step 2 of the program
    if (first_validation && secondvalidation(phone_num)) {
        cout << "formatted phone number: " << phone_num.insert(0, tele) 
        << '\n';
    }
    
    // return to the operating system
    return EXIT_SUCCESS;
}

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// Return whether the input is valid or not
/// @param s The phone number
/// @return validation 
bool secondvalidation(const std::string& s) {
    bool valid =  true;
    // using str_t std::string::size_type
    // for (size_t i = 0; valid && i < s.length(); ++i) {
        
    for (size_t i = 0; valid && i < s.length(); ++i) {
        if (s.at(3) != '-') {
            valid = false;
        } 
        if (i != 3) {
            valid = isdigit(s.at(i));
        }
    }
    return valid;
}