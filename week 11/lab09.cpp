/// @file lab09.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 12/11/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief Lab09 generate a report of the cars that are in inventory.
/// @note People who helped: None
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade - off
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
#include <fstream>

// setting a namcespace scope
using namespace std;

// global constants
const int MANUF_CT = 6;
const int HEAD_CT = 6;
const int W = 7;

/// ----------------------------------------------------------------------
/// Function Prototypes
/// ----------------------------------------------------------------------

// enum type of the color name, color count to track the data
enum color_t {RED, BROWN, BLACK, WHITE, GRAY, COLOR_COUNT};

// structure cars include manufacturer, 5 data, and the total of each manuf
struct cars_t {
    string manuf = "";
    int inventory[COLOR_COUNT] = {0};
    int totalCars = 0;
};

string mostPopularBetweenManuf(const cars_t dataSet[], int color);

string mostPopularWithinManuf(const cars_t record);

string colorCode2String(int colorCode);

cars_t getRecord(ifstream& fin);

void printRecord(const cars_t record);

void setHeadings(ifstream& fin, string headings[]);

void getDataSet(const string fn, string headings[], cars_t dataSet[]);

void printHeading(const string headings[]);

void printLine();

void printReport(const string headings[], const cars_t dataSet[]);

void printRecords(const cars_t dataSet[], cars_t& totals);

void printMostColorBetweenManuf(const cars_t dataSet[]);

void printMostColorWithinManuf(const cars_t dataSet[]);

/// ----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @param argc is the size of *argv
/// @param argv is an array of char strings forming command line args
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// ----------------------------------------------------------------------

int main(int argc, const char *argv[]) {
    // variable declaration(s)
    // heading array set to empty
    string headings[HEAD_CT] = { "" };
    // dataset of each manufactuer
    cars_t dataSet[MANUF_CT];

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " fileName.csv" << endl;
    } else {
        // get data
        getDataSet(argv[1], headings, dataSet);
        // print the result
        printReport(headings, dataSet);
    }
    // return to the operating system
    return EXIT_SUCCESS;
}


/// ---------------------------------------------------------------------- -
/// Function Implementations
/// ---------------------------------------------------------------------- -

/// get the heading data
/// @param fin stream handler variable
/// @param headings access to the heading array
void setHeadings(ifstream& fin, string headings[]) {
    // variables delcaration
    // delimeter ,
    const char DEL = ',';

    // get heading label, and coma
    for (int i = 0; i < HEAD_CT - 1; i++) {
        getline(fin, headings[i], DEL);
    }

    // get the last label
    getline(fin, headings[HEAD_CT - 1]);
}

/// get the data in the file
/// @param fn name of the file we getting data from
/// @param headings access to the heading array
/// @param dataSet access to each set of data we stored
void getDataSet(const string fn, string headings[], cars_t dataSet[]) {
    // stream handler variable
    ifstream fin;
    // open the file
    fin.open(fn);

    if (fin.is_open()) {
        // get the data for heading array
        setHeadings(fin, headings);

        // get the rest of the data like manuf, inventory
        for (int i = 0; i < MANUF_CT; i++) {
            dataSet[i] = getRecord(fin);
        }
    }

    fin.close();
}

/// get the inventory data
/// @param fin open input file variable pass by references
cars_t getRecord(ifstream& fin) {
    // delimeter , seperated by each inventory
    const char DEL = ',';
    // access to all member in cars_t structer
    cars_t record;
    // accumulate the total after 5 data set
    int total = 0;
    // get input from filename, get into manufacturer
    getline(fin, record.manuf, DEL);

    // get the inventory
    for (int i = 0; i < COLOR_COUNT; i++) {
        fin >> record.inventory[i];
        // accumulate 5 inventory
        total += record.inventory[i];
        // ignore the white spaces
        fin.ignore();
    }

    // assign member in cars_t totalCars to the total we just calculated
    // so in the printRecords we can add to cal the grand final
    record.totalCars = total;
    // return variable record type cars_t that stored all data of 1 row
    return record;
}

/// print the heading manuf and color
/// @param headings accesing to the heading array
void printHeading(const string headings[]) {
    // print heading labels
    for (int i = 0; i < HEAD_CT; i++) {
        // to print the heading out including the coma
        cout << setw(W) << headings[i];
    }

    // print the total
    cout << setw(W) << "Total" << endl;
    // print line under heading labels
    printLine();
}

/// print the -------- line
void printLine() {
    // print line under heading labels
    for (int col = 0; col < HEAD_CT + 1; col++) {
        cout << string(W, '-');
    }

    cout << endl;
}

/// print the data after stored data
/// @param record to access the cars_t structure
void printRecord(const cars_t record) {
    // print the manufacturer
    cout << setw(W) << record.manuf;

    // print out the data for each color
    for (int i = 0; i < COLOR_COUNT; i++) {
        // the data of each color base off index
        cout << setw(W) << record.inventory[i];
    }

    // print the total cars
    cout << setw(W) << record.totalCars << endl;
}

/// print the record of all manufacturer and the total row
/// @param dataSet each manufacturer has a set of 5 data
/// @param totals the total of each set of data
void printRecords(const cars_t dataSet[], cars_t& totals) {
    // loop through all manufacturer
    for (int record = 0; record < MANUF_CT; record++) {
        // print the manuf and the inventory and the total of each manuf
        printRecord(dataSet[record]);

        // total of each color
        for (int color = 0; color < COLOR_COUNT; color++) {
            totals.inventory[color] += dataSet[record].inventory[color];
        }

        // total of all cars and color
        totals.totalCars += dataSet[record].totalCars;
    }
}

/// translate the color code since we use enum type
/// @param colorCode the position of the pointer after calculating
string colorCode2String(int colorCode) {
    // variable declaration
    // string type to hold the translation
    string color;

    // switch statement
    switch (colorCode) {
        case RED:
            color = "red";
            break;

        case BROWN:
            color = "brown";
            break;

        case BLACK:
            color = "black";
            break;

        case WHITE:
            color = "white";
            break;

        case GRAY:
            color = "gray";
            break;

        default:
            color = "FALSE";
            break;
    }

    // return the translation
    return color;
}

/// get the manuf that has the most [color] cars
/// @param dataSet access to inventory
/// @param color the color index
string mostPopularBetweenManuf(const cars_t dataSet[], int color) {
    int idx = 0;
    // hold the current and to compare the next value
    int current = 0;
    int compare = 0;

    // go through each row and stay in 1 column
    // to determine which brand has the most car in that specific color
    for (int i = 0; i < MANUF_CT; i++) {
        // set the current to the first red color of GM
        current = dataSet[idx].inventory[color];
        // set the compare to also first red color of GM
        compare = dataSet[i].inventory[color];

        // compare which one is bigger
        if (compare > current) {
            idx = i;
        }
    }

    // return the what brand at what index are holding the
    // largest [color] cars
    return dataSet[idx].manuf;
}

void printMostColorBetweenManuf(const cars_t dataSet[]) {
    // loop through each color
    for (int i = 0; i < COLOR_COUNT; i++) {
        // print the brand then the color
        // i is the index of color from RED to GRAY
        cout << setw(W) << mostPopularBetweenManuf(dataSet, i)
             << " has the most " << setw(5) << colorCode2String(i) << " cars."
             << endl;
    }
}

/// get the color that each brand are owning the most cars
/// @param record the record of dataset we are in
string mostPopularWithinManuf(const cars_t record) {
    int idx = 0;
    // hold the value we do the comparision
    int current = 0;
    int compare = 0;

    // LOOP THROUGH each column [color] and stay in specific row [manuf]
    for (int i = 0; i < COLOR_COUNT; i++) {
        current = record.inventory[idx];
        compare = record.inventory[i];

        // compare the 2 values
        if (compare > current) {
            idx = i;
        }
    }

    // return the color in string, currently of what index
    return colorCode2String(idx);
}

void printMostColorWithinManuf(const cars_t dataSet[]) {
    // print the result, loop through each brand
    for (int i = 0; i < MANUF_CT; i++) {
        // print the brand and what color do they have the most
        cout << setw(W) << dataSet[i].manuf << " has more " << setw(5)
             << mostPopularWithinManuf(dataSet[i]) << " cars than any other."
             << endl;
    }
}

/// print the final report
void printReport(const string headings[], const cars_t dataSet[]) {
    // access to the cars_t structure for the total row
    cars_t totals;
    // assign the manuf of total row to be "Totals"
    totals.manuf = "Totals";

    // print the heading and the ---- line
    /* MANUF    RED  BROWN  BLACK  WHITE   GRAY  Total */
    printHeading(headings);
    // print the record between two ----- line
    printRecords(dataSet, totals);
    printLine();
    // print the total row
    printRecord(totals);

    cout << endl;
    // set the result to all left
    cout << left;
    // printing who sold the most car colors
    printMostColorBetweenManuf(dataSet);
    cout << endl;

    // printing the most popular car by manufacturer
    printMostColorWithinManuf(dataSet);
    cout << endl;
}
