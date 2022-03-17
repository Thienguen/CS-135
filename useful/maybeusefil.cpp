/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This program looks at an integer and determines the number of
///        even, zero, and odd digits
///
/// @note People who helped me: none


// include i/o libs
#include <iostream>

using namespace std;

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
void digitCount(long long num, int& eCount, int& oCount, int& zCount);

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------

int main() {
    long long number;       // user input

    int evenCount = 0;      // track the number of even digits
    int oddCount = 0;       // track the number of odd digits
    int zeroCount = 0;      // track the number of zero digits

    cout << "Enter an integer: ";
    cin >> number;
    cout << endl;

    digitCount(number, evenCount, oddCount, zeroCount);

    cout << "The number of even digits: " << evenCount << endl;
    cout << "The number of odd digits: " << oddCount << endl;
    cout << "The number of zeros: " << zeroCount << endl;

    return 0;
}

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

void digitCount(long long num, int& eCount, int& oCount, int& zCount) {
    int digit;

    bool done = false;

    do
    {
        if (num < 10) {
            done = true;
        }

        // get least significant digit
        digit = static_cast<int>(num % 10);

        // peal off least significant digit
        num = num / 10;

        // check even, zero, or odd and update counters
        // zero is considered an even digit
        if (digit % 2 == 0) {
            eCount++;           // update the even counter

            if (digit == 0) {
                zCount++;       // update the zero counter
            }

        } else {
            oCount++;           // update the odd counter
        }

    } while (!done);
}