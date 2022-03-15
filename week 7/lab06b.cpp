/// @file lab06b.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 11/5/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment compute the gross pay and netpay
///        using a void function.
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
#include <iostream>
#include <iomanip>
#include <string>

// setting a namcespace scope
using namespace std;


/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
void compute_pay(double& netpay, 
                 double& grosspay, 
                 double  payrate, 
                 double  hours, 
                 double  tax);

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------

int main() {
    // variable declaration(s)
    // function variable(s)
    double netpay;          // holds value of the netpay
    double grosspay;        // holds value of the grosspay
    double payrate;         // holds value of the payrates from the users
    double hours;           // holds value of the hours from the users
    double tax;             // holds value of the tax [0 - 100] from the users
    string name;            // get the user name

    /* ******* input phase ****************************************** */
    

    cout << "Enter the employee name:  ";        // get input for the name
    getline(cin, name);

    cout << "Enter the hourly payrate: ";      // get input for the rate
    cin >> payrate;

    cout << "Enter the hours worked:   ";        // get input for the hours
    cin >> hours;

    cout << "Enter tax percentage:     ";   // get the tax
    cin >> tax;
    cout << endl;                           // create a new line

    /* ******* processing phase ************************************* */
    compute_pay(netpay,grosspay,payrate,hours,tax);

    /* ******* output phase ********************************************* */
    // 
    cout << setw(12) << left << name 
         << setprecision(2) << showpoint << fixed
         << setw(9) << right << payrate 
         << setw(9) << right << hours 
         << setw(9) << right << tax 
         << setw(9) << right << grosspay 
         << setw(9) << right << netpay << endl;
    
    // return to the operating system
    return EXIT_SUCCESS;
}

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// Compute and return gross pay and net pay given payrate, hours, and tax rate.
/// @param [out] netpay    The calculated net pay.
/// @param [out] grosspay  The calculate gross pay.
/// @param payrate         The hourly pay rate in dollars.
/// @param hours           The nubmer of hours worked.
/// @param tax             The tax percentage to be deducted.

void compute_pay(double& netpay, 
                 double& grosspay, 
                 double  payrate, 
                 double  hours, 
                 double  tax) {
    grosspay = hours * payrate;
    netpay = grosspay - (grosspay * (tax / 100.0));
}

/// @paragraph Input format, just run the program bro