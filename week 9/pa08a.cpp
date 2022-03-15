/// @file pa08a.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 11/29/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment reads and filters a delimited data stream
///        to identify and report those transactions occurring on a given
///        weekday. The largest quantity and sale are noted and reported at
///        the end of the report, along with a count of items sold
///        and the total sales for the period.
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

namespace cs135
{
    void print(const int list[], int size);
    void copy(const int source[], int dest[], int count);
    void selection_sort(int list[], int size);

    double median(const int list[], int size);
    double average(const int list[], int size);
    double stdevp(const int list[], int size);

    int maximum(const int list[], int size);
    int minimum(const int list[], int size);
    int read(int list[], int capacity);

    long sum(const int list[], int size);

} // namespace cs135



/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {

#ifndef ONLINE_JUDGE
freopen("input.txt","r",stdin); 
freopen("output.txt","w",stdout); 
#endif

    // constant declaration(s)
    const int MAX = 100;                // maximum capacity

    // variable declaration(s)
    int used = 0;                       // to count how many input
    int array[MAX] = { 0 };             // array will be sorted
    int array_copy[MAX] = { 0 };        // array hold value before sort

    // read the input also hold the amount of elements
    used = cs135::read(array, MAX);
    // copy the array to array_copy
    cs135::copy(array, array_copy, used);

    // sort the array
    cs135::selection_sort(array_copy, used);

    cout << fixed << showpoint << setprecision(1);

    // calculate the statistics
    cout << "Descriptive Statistics";
    cout << "\nCount:"   << right << setw(11) << used
         << "\nMiminum:" << right << setw(9)  << cs135::minimum(array_copy, used)
         << "\nMaximum:" << right << setw(9)  << cs135::maximum(array_copy, used)
         << "\nSum:"     << right << setw(13) << cs135::sum(array_copy, used)
         << "\nMean:"    << right << setw(14) << cs135::average(array_copy, used)
         << "\nMedian:"  << right << setw(12) << cs135::median(array_copy, used)
         << "\nStd Dev:" << right << setw(11) << cs135::stdevp(array_copy, used)
         << endl;
    // print the result
    cout << "\nInput data (unsorted):" << endl;
    cs135::print(array, used);
    cout << "\nInput data (sorted):" << endl;
    cs135::print(array_copy, used);

    // return to the operating system
    return EXIT_SUCCESS;
}

namespace cs135
{

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// Returns the average of list.
/// @param list the original array
/// @param size the size of the input entered
double average(const int list[], int size) {
    double answer = 0;
    answer = static_cast<double>(sum(list, size));
    answer = answer / size;

    return answer;
}

/// Copies the contents of one array to another.
/// @param source the original array unsorted (const)
/// @param dest the sort array but now we copy the unsorted
/// @param count how many elements in the array
void copy(const int source[], int dest[], int count) {
    for (int i = 0; i < count; i++) {
        // copy source to destination
        dest[i] = source[i];
    }
}

/// Returns index of maximum value in list, or -1 if list is empty.
/// @param list the original array
/// @param size the size of the input entered
int maximum(const int list[], int size) {
    int max = list[0];

    for (int index = 1; index < size; index++) {
        if (list[index] > max) {
            max = list[index];
        }
    }
    return max;
}

/// Returns median value of list.
/// @param list the original array
/// @param size the size of the input entered
double median(const int list[], int size) {
    double answer;

    if (size % 2 != 0) {
        answer = (list[size / 2]);
    } else {
        answer = floor(list[(size / 2)]);
    }
    return answer;
}

/// Returns index of minimum value in list, or -1 if list is empty.
/// @param list the original array
/// @param size the size of the input entered
int minimum(const int list[], int size) {
    int min = list[0];

    for (int index = 1; index < size; index++) {
        if (list[index] < min) {
            min = list[index];
        }
    }
    return min;
}

/// Neatly prints a list in 10 columns of width 8.
void print(const int list[], int size) {
    // print the input
    for (int i = 0; i < size; i++) {
        cout << right << setw(8) << list[i];

        if (i == size - 1 || (i + 1) % 10 == 0) {
            cout << '\n';
        }
    }
}
/// Reads and appends integers from the standard input stream until (1) eof,
/// or (2) list has reached capacity. Returns number of values appended to list.
/// @param [out] list the original array
/// @param [out] capacity the maximum elements could be enter

int read(int list[], int capacity) {
    int index = 0;
    // int value = 0;
    // cin >> value;
    // list[0] == value;
    while (cin.good() && index < capacity) {
        cin >> list[index];
        ++index;
    }
    return index;
}

/// Sorts the list in ascending order using the selection sort algorithm.
/// @param list the original array waited to be sort
/// @param size the size of the input entered
void selection_sort(int list[], int size) {
    int index;

    for (index = 0; index < size - 1; index++) {
        int smallestIndex;
        int location;
        int temp;
        //  step a
        smallestIndex = index;
        for (location = index + 1; location < size; location++) {
            if (list[location] < list[smallestIndex]) {
                smallestIndex = location;
            }
        }

        //  step b
        temp = list[smallestIndex];
        list[smallestIndex] = list[index];
        list[index] = temp;
    }
}

/// Returns the population standard deviation of list.
/// @param list the original array
/// @param size the size of the input entered
double stdevp(const int list[], int size) {
    double m = 0;           // the median
    double answer = 0;      // final result

    m = average(list, size);

    for (int i = 0; i < size; i++) {
        answer += pow(list[i] - m, 2);
    }

    answer = sqrt(answer / size);

    return answer;
}

/// Returns the sum of all elements in list.
/// @param list the original array
/// @param size the size of the input entered
long sum(const int list[], int size) {
    // calculate the sum
    int answer = 0;

    for (int index = 0; index < size; index++) {
        answer += list[index];
    }

    return answer;
}

} // namespace cs135

/// @note 3/15/2022 , solo the damn thing... still gud tho