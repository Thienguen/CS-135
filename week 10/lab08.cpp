/// @file lab08b.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 12/4/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment prepare for pa08b
///
///
/// @note People who helped: TA Miguel.
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
#include <fstream>


// setting a namcespace scope
using namespace std;

// constant variables(s)
const int SIZE = 5;                 // SIZE of the data column
const int MANUF_CT = 6;             // SIZE of the data row
const int HEAD_CT = 6;              // heading label size

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------

// fin is the variables of type ifstream pass by references(&) in which
// change the content or what is inside the iostream
void testFile(ifstream& fin);

void printFile_1(ifstream& fin);
void printFile_2(const string& fn);
void printFile_3(const string& fn);

void printHeadingArray(string headings[]);
void clearHeadings(string headings[]);

void readHeadingByChar(const string& fn, string headings[]);
void readHeadingByLabel(const string& fn, string headings[]);
void readHeadingDistructive(const string& fn, string headings[]);
void readHeadingNonDistructive(const string& fn, string headings[]);

void setHeadings(ifstream& fin, string headings[]);
void setManuf(ifstream& fin, string manufs[], int idx);
void setCounts(ifstream& fin, int inventory[][SIZE], int idx);
void readInventory(const string& fn,
                   string headings[],
                   string manufs[],
                   int inventory[][SIZE]);

void printReport(const string headings[],
                 const string manufs[],
                 const int a[][SIZE]);

void saveReport(const string& fn,
                const string headings[],
                const string manufs[],
                const int a[][SIZE]);


/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
int main() {

    ifstream inData;               // inData type ifstream to open file cars
    string inFileName;             // cars.txt to store input or the file name

    string head[HEAD_CT];    // heading array initialize to empty
    string manufacturer[MANUF_CT];  // manufs array initialize to empty

    int data[MANUF_CT][SIZE] = {{ 0 }};    // data 2D array, 6 row and 5 colum

    // get the file name
    cout << "Enter the file name: ";
    cin >> inFileName;

    // open the file cars.txt
    inData.open(inFileName);

    // testing whether file was open succesfully
    cout << "\nTesting file for open...";
    testFile(inData);

    /// ---------------------------------------------------------------------
    /// @paragraph down below is the function call in main
    //             since there is no sample interaction so I commented them
    /// ---------------------------------------------------------------------

    // cout << "\nReading file using stream extraction(>>)... " << endl;
    // printFile_1(inData);
    // cout << endl;

    // printFile_2(inFileName);
    // cout << endl;

    // printFile_3(inFileName);
    // cout << endl;

    // cout << "\nReading heading labels char-by-char..." << endl;

    // readHeadingByChar(inFileName, head);
    // printHeadingArray(head);

    // readHeadingByLabel(inFileName, head);
    // printHeadingArray(head);

    // readHeadingDistructive(inFileName, head);
    // printHeadingArray(head);

    // readHeadingNonDistructive(inFileName, head);
    // printHeadingArray(head);

if (inData.is_open()) {
    // read the file
    readInventory(inFileName, head, manufacturer, data);
    // print the report
    printReport(head, manufacturer, data);
}

    // if we want to overwrite any file the result
    // saveReport(inFileName, head, manufacturer, data);

    // we need to flush the buffer, so we close the fstream
    inData.close();

    // return to the operating system
    return EXIT_SUCCESS;
}


/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------

/// test whether the file is open or not
/// @param fin the file after we open it
void testFile(ifstream& fin) {
    // if file is open or not
    if (fin.is_open()) {
        cout << "File is open" << endl;
    } else {
        cout << "File is NOT open" << endl;
    }

    cout << endl;
}

/// print the output of file in character by character
/// @param fin the file after we open it
void printFile_1(ifstream& fin) {
    if (fin.is_open()) {    // open the file
        char ch;            // ch type char

        // store input in file fin in ch until eof
        while (fin >> ch) {
            // print it out
            cout << ch;
        }

        cout << endl;
    } else {    // if open the wrong file name
        cout << "File is NOT open!" << endl;
    }

    cout << endl;

}

/// print the output of file inclduing the white spaces
/// @param fn name of the file
void printFile_2(const string& fn) {
    ifstream fin;           // fin type ifstream
    char ch;                // ch type ch to store character by character

    fin.open(fn);           // open the file

    if (fin.is_open()) {
        // get characters by character, including the white space
        while (fin.get(ch)) {
            cout << ch;
        }

        cout << endl;
    } else {        // if open the wrong file name
        cout << "File is NOT open!" << endl;
    }

    // close the fstream
    fin.close();
}

/// print the output of file in a single line
/// @param fn name of the file
void printFile_3(const string& fn) {
    fstream fin;                   // fin type ifstream to open the file
    string line;                   // to hold every thing in a sigle line

    fin.open(fn);                  // open the file

    if (fin.is_open()) {
        // get the file input in one line
        while (getline(fin, line)) {
            // print it all at once
            cout << line;
        }

        cout << endl;
    } else {      // if open the wrong file name
        cout << "File is NOT open!" << endl;
    }

    // close the fstream
    fin.close();

}

/// read the input heading by char
/// @param fn the name of the file
/// @param headings the array name
void readHeadingByChar(const string& fn, string headings[]) {

    ifstream fin;                   // fin type ifstream to open the file
    string heading = "";            // hold the current empty heading label
    const char DEL = ',';           // delimeter ,
    const char NL = '\n';           // newline character
    char ch;                        // ch type char
    int i = 0;                      // tracking character in file cars.txt

    fin.open(fn);                   // open the file for read

    if (fin.is_open()) {
        fin.get(ch);                // read a character from the file

        while (ch != NL) {          // while it's not a newline character
            // if we found a coma in a loop
            if (ch == DEL) {
                // save the string without coma into the array
                headings[i] = heading;
                // clear the heading lable variable, make sure the next time
                // we get the label such as MANUF, RED, BROWN without the coma
                heading = "";
                // increment the array index, after storing 1 heading label.
                i++;
            } else {
                // adding character by character to the heading string
                heading += ch;
            }

            // getting the last character to ch
            fin.get(ch);
        }

        // there is no coma at the end so we have to store the last
        // label outside of the loop, since it only store after ch == DEL
        headings[i] = heading;
    } else {
        // when we open the wrong file or file name differently.
        cout << "File is NOT open!" << endl;
    }

    // close the fstream.
    cout << endl;
    fin.close();

}

void printHeadingArray(string headings[]) {
    // print all element in heading array with coma
    // except the last element
    for (int i = 0; i < HEAD_CT - 1; i++) {
        if (i < HEAD_CT - 2) {
            cout << headings[i] << ",";
        } else {
            cout << headings[i];
        }
    }
}

/// clear the heading array to empty
/// @param headings the array name
void clearHeadings(string headings[]) {
    // initialize all variables in headings[] to empty.
    for (int i = 0; i < HEAD_CT - 1; i++) {
        headings[i] = "";
    }

}

/// read the input heading by label
/// @param fn the name of the file
/// @param headings the array name
void readHeadingByLabel(const string& fn, string headings[]) {
    ifstream fin;           // fin type ifstream
    string heading;         // to hold the input of fin in one string
    const char DEL = ',';   // delimeter ,

    // clear the array to empty
    clearHeadings(headings);

    fin.open(fn);            // use ifstream type varibales to open file fn

    // if file is open, we get the data inside and print it out
    if (fin.is_open()) {
        // create a loop that getline
        // file fin, string heading, and delimeter ,
        // since we are getting label to label
        for (int i = 0; i < HEAD_CT - 1; i++) {
            // get label, and the coma inside file
            getline(fin, heading, DEL);
            // set label to each index in heading
            headings[i] = heading;
        }

        // get the last label without coma
        getline(fin, heading);
        headings[HEAD_CT - 1] = heading;
    }

    // close the fstream
    fin.close();
}

/// reading each input in file fn then remove so the following
/// label will always be first
/// @param fn file name
/// @param headings the array name
void readHeadingDistructive(const string& fn, string headings[]) {
    ifstream fin;           // fin type ifstream
    string line;            // store in variable line type string
    const char DEL = ',';   // delimeter ,
    int arrayindex = 0;     // array index
    bool valid = true;      // if file is successfuly opened

    // represent the sizes of any strings, larger than 2^32 bytes of memories
    using strSize_t = std::string::size_type;
    strSize_t stringindex;  // stringindex type strSize_t

    // clear the heading array and set all variable to be 0
    clearHeadings(headings);

    // open the file
    fin.open(fn);

    if (fin.is_open()) {
        // get all input into line type string
        getline(fin, line);
    } else {
        cout << "File is not open!" << endl;
        valid = false;
    }

    // close the fstream since we already get the data from file
    fin.close();

    if (valid) {
        // if find the position of coma in line not npos number
        // repeat
        while ((stringindex = line.find(DEL)) != std::string::npos) {
            // just get the label only into the array (no coma)
            // then increment the index after the first label
            headings[arrayindex++] = line.substr(0, stringindex);
            // erase the label, moving on to the next coma we found
            line.erase(0, stringindex + 1);
        }

        // get the last label
        headings[arrayindex] = line.substr(0, stringindex);

    }
}

void readHeadingNonDistructive(const string& fn, string headings[]) {
    ifstream fin;           // fin type ifstream
    string line;            // store in variable line type string
    const char DEL = ',';   // delimeter ,
    int arrayindex = 0;     // array index
    bool valid = true;      // if file is successfuly opened

    // represent the sizes of any strings, larger than 2^32 bytes of memories
    using strSize_t = std::string::size_type;

    // open file fn (cars.txt)
    fin.open(fn);

    if (fin.is_open()) {
        getline(fin, line);
    } else {    // if oopen the wrong file
        cout << "File is not open!" << endl;
        valid = false;
    }

    // close the fstream
    fin.close();

    if (valid) {
        strSize_t last = 0;
        strSize_t next = 0;

        // find the next coma starting from last (begining at 0)
        // find the position of it and differ from npos number
        while ((next = line.find(DEL, last)) != std::string::npos) {
            // copy the label into the array
            // increment the index after the first copy
            headings[arrayindex++] = line.substr(last, next - last);
            last = next + 1;
        }

        headings[arrayindex] = line.substr(last);
    }
}


/// get the input heading label
/// @param fin the file cars.txt after open
/// @param headings heading array
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

/// read the manufacturer GM, FORD, TOYOTA, etc
/// @param fin the file after open
/// @param manufs manufacturer index
/// @param idx index for the manufacturer
void setManuf(ifstream& fin, string manufs[], int idx) {
    // delimeter ,
    const char DEL = ',';
    // get input from file fin, manuf_CT, coma
    getline(fin, manufs[idx], DEL);
}

/// read the input from file fin and the count of data
/// @param fin file cars.txt after opened
/// @param inventory 2-dimension array contain rows and column
/// @param idx index value that passed into the fucntion
void setCounts(ifstream& fin, int inventory[][SIZE], int idx) {
    int count = 0;

    // assume that manuf has been read
    for (int i = 0; i < SIZE; i++) {
        // count how many data from file
        fin >> count;
        inventory[idx][i] = count;
        fin.ignore();
    }

}

/// read and distribute all information in file cars.txt
/// to the right place
/// @param fn name of the file
/// @param headings the hearing array
/// @param manufs the manufacturer array
/// @param inventory 2D array, rows and column of the data
void readInventory(const string& fn,
                   string headings[],
                   string manufs[],
                   int inventory[][SIZE]) {
    // fin type ifstream
    ifstream fin;

    // open the file fn (parameter)
    fin.open(fn);

    if (fin.is_open()) {
        // get heading first in the input
        setHeadings(fin, headings);

        for (int i = 0; i < MANUF_CT; i++) {
            // get the manuf
            setManuf(fin, manufs, i);
            // count the data
            setCounts(fin, inventory, i);
        }

        fin.close();
    } else {
        cout << "File is NOT open!" << endl;
        fin.close();
    }

    // close the fstream
}

/// printing the report in a 2D chart
/// @param headings the heading array
/// @param manufs manufacturer array
/// @param a 2D array that print the chart
void printReport(const string headings[],
                 const string manufs[],
                 const int a[][SIZE]) {
    // constants declaration
    const int w = 7;

    // print the heading label store in heading array
    for (int col = 0; col < HEAD_CT; col++) {
        cout << setw(w) << headings[col];
    }

    cout << endl;

    // print the straight ----- line
    for (int col = 0; col < HEAD_CT; col++) {
        cout << std::string(w, '-');
    }

    cout << endl;

    // print the row data
    for (int row = 0; row < MANUF_CT; row++) {
        cout << setw(w) << manufs[row];

        for (int col = 0; col < SIZE; col++) {
            cout << setw(w) << a[row][col];
        }

        cout << endl;
    }

    cout << endl;

}

/// save report into disk
/// @param fn file name (here is cars.txt)
/// @param headings heading array
/// @param manufs manufacturer array
/// @param a 2D array of column and row data
void saveReport(const string& fn,
                const string headings[],
                const string manufs[],
                const int a[][SIZE]) {
    const int W = 7;
    // fout type output file stream
    ofstream fout;
    // use fout to open file cars.txt we stored in fn
    fout.open(fn);

    if (fout.is_open()) {
        // write in the file cars.txt the column
        for (int col = 0; col < HEAD_CT; col++) {
            fout << setw(W) << headings[col];
        }

        fout << endl;

        // write in file cars.txt the ----- line
        for (int col = 0; col < HEAD_CT; col++) {
            fout << std::string(W, '-');
        }

        fout << endl;

        // write out each data row
        for (int row = 0; row < MANUF_CT; row++) {
            fout << setw(W) << manufs[row];

            // write the number data
            for (int col = 0; col < SIZE; col++) {
                fout << setw(W) << a[row][col];
            }

            fout << endl;
        }
    } else {        // if open the wrong file
        cout << "File is NOT open!" << endl;
    }

    fout << endl;
    // close the fstream
    fout.close();
}
