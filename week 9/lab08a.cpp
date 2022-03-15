/// @file lan08a.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 11/20/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment Write a program that simulates the rolling of 
///        two dice. The program should call rand() to roll the first
///        die, and should call rand() again to roll the second die. 
/// @note People who helped:
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
#include <limits>
#include <list>

// setting a namcespace scope
using namespace std;


/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {


    const long ROLLS = 36000;
    const int SIZE   = 13;
    const int CW     = 10;

    //  contains counts for the expected number 
    //  of times each sum occurs in 36 rolls.
    int count_expected[SIZE] = {0, 0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
    int dice1;                  // first dice
    int dice2;                  // second dice
    int sum[SIZE] = { 0 };      // array sum

    srand(static_cast<unsigned>(time(nullptr)));    

// Loop the dice 36,000 times
for (int i = 0; i < ROLLS; i++) {
    // ramdom a number from 1 to 6
    dice1 = 1 + rand() % 6; 

    // random a number from 1 to 6
    dice2 = 1 + rand() % 6; 

    // Calculate the sum of two dice
    // then increment to the next approriate counter 
    sum[dice1 + dice2]++; 
}

    cout << fixed << showpoint << setprecision(3);

    cout << setw(CW) << "Sum" << setw(CW) << "Total"
         << setw(CW) << "Expected" << setw(CW) << "Actual" << endl;

//Display results of rolling dice
for (int j = 2; j < SIZE; j++) {
    cout << setw(CW) << j << setw(CW) << sum[j]
            << setw(CW - 1) << (100.0 * count_expected[j] / 36)
            << '%' << setw(CW - 1) << (100.0 * sum[j] / ROLLS) << '%'
            << endl;

}

// return to the operating system
return EXIT_SUCCESS;
}

/// @note huh, I have no memory of this...anyway 
