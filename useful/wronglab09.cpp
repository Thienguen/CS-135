/// @note I pledge my word of honor that I have abided by the
/// the CSN Academic Integrity Policy while completing this assignment.
///
/// @brief This program modifies lab08c to use namespaces and adds example 9-1
/// as a function.
///
/// @note People who helped me: professor Brodersen
/// @note check the end of this file


// include i/o libs
#include <iostream>
#include <iomanip>
#include <string>

// define namespace for project
namespace lab09 {
// constants for columns and NA message
const int LABEL_COL = 25;
char const NA[] = "Not Available";

// Structures
struct houseType {
    
    int numOfBedrooms = -1;
    int numOfBathrooms = -1;
    int numOfCarsGarage = -1;
    int yearBuilt = -1;
    int finishedSquareFootage = -1;
    int dummy = 0;                  // added to silence allignment warnings
    double price = -1.0;
    double tax = -1.0;
    std::string style = "none";
};

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
int seqSearch(const int list[], const int listLength, const int searchItem);
void examp8_8();
void selectionSort(int list[], const int length);
void examp8_9();
void examp9_1();
void printStructure(const houseType house, const std::string owner);
void printMember(const std::string label, const int memberData);
void printMember(const std::string label, const double memberData);
void printMember(const std::string label, const std::string memberData);
}  // namespace lab09

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {
    lab09::examp8_8();
    lab09::examp8_9();
    lab09::examp9_1();

    return EXIT_SUCCESS;
}

namespace lab09 {
/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------


/// @brief examp8_8 implements the example in the text
void examp8_8() {
    const int ARRAY_SIZE = 10;          // Array size

    int intList[ARRAY_SIZE];            // list of numbers for searching
    int number = 5;                     // target search number

    bool debug = true;                  // flag to propopulate data


    if (debug) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            intList[i] = i;
            std::cout << i << " ";
        }
        std::cout << std::endl;
    } else {
        // allow the user to populate the array
        std::cout << "Enter " << ARRAY_SIZE << " integers: " << std::endl;
        for (int index  = 0; index < ARRAY_SIZE; index++) {
            std::cin >> intList[index];
        }
        std::cout << std::endl;

        // ask the user for the target search number
        std::cout << "Enter the number to be searched: ";
        std::cin >> number;
        std::cout << std::endl;
    }

    // perform the search
    const int POS = seqSearch(intList, ARRAY_SIZE, number);

    // print the index of the found search item, else not found.
    if (POS!= -1) {
        std::cout << number << " is found at index " << POS << std::endl;
    } else {
        std::cout << number << " is not in the list." << std::endl;
    }
    std::cout << std::endl;
}

/// @brief seqSearch is a helper function that searches an array.
/// @param list is the list of numbers in an array
/// @param listLength the length of the array
/// @param searchItem the target search item
/// @return the index of the search item, else -1
int seqSearch(const int list[], const int listLength, const int searchItem) {
    int loc = -1;           // the location of the target
    int idx = 0;            // LCV and array index
    bool found = false;     // LCV Sentinal

    while (idx < listLength && !found) {
        if (list[idx] == searchItem) {
            found = true;
            loc = idx;
        } else {
            idx++;          // update index ptr
        }
    }

    return loc;
}

/// @brief examp8_9 implements the example in the text
void examp8_9() {
    // init an example array to be sorted
    int list[] = {2, 56, 34, 25, 73, 46, 89, 10, 5, 16};

    // sort the array
    selectionSort(list, 10);

    std::cout << "After sorting, the list elements are:" << std::endl;

    // print the array
    for (int i = 0; i < 10; i++) {
        std::cout << list[i] << " ";
    }
    std::cout << std::endl;
}

/// @brief selectionSort sorts an array of integers
/// @param list is the list of numbers in an array
/// @param length the length of the array
void selectionSort(int list[], const int length) {
    int smallestIndex;              // tracks smallest value
    int location;                   // tracks current sort location
    int temp;                       // temp var for swap

    // loop through the array and sort
    for (int index = 0; index < length - 1; index++) {
        smallestIndex = index;

        // inner loop used to test for and set smallest value location
        for (location = index + 1; location < length; location++) {
            if (list[location] < list[smallestIndex]) {
                smallestIndex = location;
            }
        }

        // swap the elements now that the smallest value is located.
        temp = list[smallestIndex];
        list[smallestIndex] = list[index];
        list[index] = temp;
    }
}

/// @brief examp9_1 implements the example from the text
void examp9_1() {
    houseType ryanHouse;            // data for ryan's house
    houseType anitaHouse;           // data for anita's house

    // populate house data for ryan's house
    ryanHouse.style = "Colonial";
    ryanHouse.numOfBedrooms = 3;
    ryanHouse.numOfBathrooms = 2;
    ryanHouse.numOfCarsGarage = 2;
    ryanHouse.yearBuilt = 2005;
    ryanHouse.finishedSquareFootage = 2250;
    ryanHouse.price = 290000;
    ryanHouse.tax = 5000.50;

    // update the style, number of bedrooms, and price of anita's house
    std::cout << "\n\nEnter the style, number of bedrooms, and price \n"
    << "separated by spaces: ";
    std::cin >> anitaHouse.style >> anitaHouse.numOfBedrooms
    >> anitaHouse.price;

    printStructure(ryanHouse, "Ryan");
    std::cout << std::endl;

    printStructure(anitaHouse, "Anita");
    std::cout << std::endl;
}

/// @brief printStructure prints the contents of the houseType
/// structure
/// @param house is the structure variable to be printed
/// @param owner of the house whose data is stored in the structure
void printStructure(const houseType house, const std::string owner) {
    std::cout << std::endl;
    std::cout << owner << std::endl;
    std::cout << "------------------------" << std::endl;
    printMember("Style: ", house.style);
    std::cout << std::endl;

    printMember("Number of Bedrooms: ", house.numOfBedrooms);
    std::cout << std::endl;

    printMember("Garage: ", house.numOfCarsGarage);
    std::cout << std::endl;

    printMember("Year built: ", house.yearBuilt);
    std::cout << std::endl;

    printMember("Finished Square Footage: ", house.finishedSquareFootage);
    std::cout << std::endl;

    printMember("Price: ", house.price);
    std::cout << std::endl;

    printMember("Tax: ", house.tax);
    std::cout << std::endl;
}

/// @brief printMember is a helper function to print
/// an integer member of the houseType structure
/// @param label is the label of them member
/// @param memberData is the data associated with the label
void printMember(const std::string label, const int memberData) {
    // print the label and set up formatting
    std::cout
    << std::right << std::setw(LABEL_COL) << label
    << std::left;

    // if the data are initialized values, print Not Available
    // otherwise print the data
    if (memberData < 0) {
        std::cout << NA;
    } else {
        std::cout << memberData;

        // if the label indicates that it's the garage, append
        // the unit car to the output
        if (label == "Garage: ") {
            std::cout << std::left << " car";
        }
    }
}

/// @brief printMember is a helper function to print
/// an double member of the houseType structure
/// @param label is the label of them member
/// @param memberData is the data associated with the label
void printMember(const std::string label, const double memberData) {
    // print the label and set up formatting
    std::cout
    << std::right << std::setw(LABEL_COL) << label
    << std::left;

    // if the data are initialized values, print Not Available
    // otherwise print the data
    if (memberData < 0) {
        std::cout << NA;
    } else {
        std::cout << memberData;

        // if the label indicates that it's the garage, append
        // the unit car to the output
        if (label == "Garage: ") {
            std::cout << std::left << " car";
        }
    }
}

/// @brief printMember is an overloaded helper function to print
/// a string member of the houseType structure
/// @param label is the label of them member
/// @param memberData is the data associated with the label
void printMember(const std::string label, const std::string memberData) {
    std::cout
    << std::right << std::setw(LABEL_COL) << label
    << std::left;
    if (memberData == "none") {
        std::cout << NA;
    } else {
        std::cout << memberData;
    }
}

}  // namespace lab09

/// @paragraph Someting again I get from my professor as a mean to practice