#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

// setting up namespace scope
using namespace std;

// global constants
const int SIZE = 5;
const int MANUF_CT = 6;
const int HEAD_CT = 6;

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------
// Phase I
void testFile(ifstream& fin);
void printFile_1(ifstream& fin);
void printFile_2(const string& fn);
void printFile_3(const string& fn);
void clearHeadings(string a[]);
void printHeadingArray(const string a[]);
void readHeadingByChar(const string& fn, string headings[]);
void readHeadingByLabel(const string& fn, string headings[]);
void readHeadingDistructive(const string& fn, string headings[]);
void readHeadingNonDistructive(const string& fn, string headings[]);

// Phase II
void setHeadings(ifstream& fin, string headings[]);
void setManuf(ifstream& fin, string manufs[], int idx);
void setCounts(ifstream& fin, int inventory[][SIZE], int idx);
void readInventory(const string& fn,
                   string headings[],
                   string manufs[],
                   int inventory[][SIZE]);

// Phase III
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
    // constant definition(s)


    // variable declarations(s)
    ifstream inData;            // input file stream handler
    string inFileName;          // user supplied input file name var
    string outFileName;         // output file name var

    string headings[HEAD_CT] = { "" };
    string manufs[MANUF_CT]  = { "" };
    int    inventory[MANUF_CT][SIZE] = {{ 0 }};

    // read char data from standard in: used to make sure cars.txt can be read
    // usage ./lab08b < cars.txt
    //    char ch;
    //    while (cin.get(ch)) {
    //        cout << ch << endl;
    //    }

    // get the file name from the user / set output file name
    // cout << "Enter the inventory data file name: ";
    // cin >> inFileName;
    inFileName = "cars.txt";
    outFileName = "report.txt";

    inData.open(inFileName);

    cout << "\nTesting file for open..." << endl;
    testFile(inData);

    cout << "\nReading file using stream extraction (>>) ..." << endl;
    printFile_1(inData);

    inData.close();

    cout << "\nReading file using streamVar.get(ch) ..." << endl;
    printFile_2(inFileName);

    cout << "\nReading file using getline(streamVar, line) ..." << endl;
    printFile_3(inFileName);

    cout << "\nReading heading labels char-by-char ..." << endl;
    readHeadingByChar(inFileName, headings);
    printHeadingArray(headings);

    cout << "\nReading whole heading labels ..." << endl;
    readHeadingByLabel(inFileName, headings);
    printHeadingArray(headings);

    cout << "\nDistructive Method for reading heading labels ..." << endl;
    readHeadingDistructive(inFileName, headings);
    printHeadingArray(headings);

    cout << "\nNon-Distructive Method for reading heading labels ..." << endl;
    readHeadingNonDistructive(inFileName, headings);
    printHeadingArray(headings);

    cout << endl;

    readInventory(inFileName, headings, manufs, inventory);

    printReport(headings, manufs, inventory);

    saveReport(outFileName, headings, manufs, inventory);

    // return to the operating system
    return 0;
}

/// -----------------------------------------------------------------------
/// Function Implementations Phase I
/// -----------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// Print the open or closed state of a file
///
/// @param fin The input file handler
/// ---------------------------------------------------------------------------
void testFile(ifstream& fin) {
    if (fin.is_open()) {
        cout << "File is open!" << endl;
    } else {
        cout << "File is NOT open!" << endl;
    }
}

/// ---------------------------------------------------------------------------
/// Reads and Prints the contents of a file using the stream extraction operator
/// Outputs file contents without linefeeds because they were filtered out
///
/// @param fin The input file handler
/// ---------------------------------------------------------------------------
void printFile_1(ifstream& fin) {
    if (fin.is_open()) {
        char ch;
        while (fin >> ch) {
            cout << ch;
        }
        cout << endl;
        fin.close();
    } else {
        cout << "inData is NOT open!" << endl;
    }
    cout << endl;
}

/// ---------------------------------------------------------------------------
/// Opens, reads, and Prints the contents of a file using the get(ch) method
/// Outputs the linefeeds because get(ch) gets white space as well
///
/// @param fn The name of the file
/// ---------------------------------------------------------------------------
void printFile_2(const string& fn) {
    ifstream fin;
    fin.open(fn);

    if (fin.is_open()) {
        char ch;
        while (fin.get(ch)) {
            cout << ch;
        }
        cout << endl;
        fin.close();
    } else {
        cout << "inData is NOT open!" << endl;
    }


}

/// ---------------------------------------------------------------------------
/// Opens, reads, and Prints the contents of a file using the getline() method
/// Linefeeds have to be added on output
///
/// @param fn The name of the file
/// ---------------------------------------------------------------------------
void printFile_3(const string& fn) {
    ifstream fin;
    fin.open(fn);
    string line;

    if (fin.is_open()) {
        while (getline(fin, line)) {
            cout << line << endl;
        }
        cout << endl;

        fin.close();
    } else {
        cout << "inData is NOT open!" << endl;
    }


}

/// ---------------------------------------------------------------------------
/// Clears headings[] by setting each element to "".
///
/// @param a references the array
/// ---------------------------------------------------------------------------
void clearHeadings(string a[]) {
    for (int i = 0; i < HEAD_CT; i++) {
        a[i] ="";
    }
}

/// ---------------------------------------------------------------------------
/// Prints headings[] elements separated by a space
///
/// @param a references the array
/// ---------------------------------------------------------------------------
void printHeadingArray(const string a[]) {
    for (int i = 0; i < HEAD_CT; i++) {
        cout << a[i] << ' ';
    }
    cout << endl;
}

/// ---------------------------------------------------------------------------
/// Opens the datafile and reads the comma delimited first line using get(ch)
/// character-by-character, building each heading label, and places it into
/// the headings array
///
/// @param fn is the name of the data file
/// @param headings references the headings array to store the labels
/// ---------------------------------------------------------------------------
void readHeadingByChar(const string& fn, string headings[]) {
    ifstream fin;                   // streaming variable
    const char DEL = ',';           // the delimiter
    const char NL = '\n';           // the end of the line
    char ch;                        // holds each character for processing
    int idx = 0;                    // tracks the index of the headings array
    string heading = "";            // holds the label as it is constructed

    fin.open(fn);                   // open data file for read

    if (fin.is_open()) {
        fin.get(ch);                // get a characgter
        while (ch != NL) {          // if it's a newline, then done looping
            if (ch == DEL) {
                headings[idx] = heading;  // if a delimiter is found store label
                heading = "";       // clear the var used to build label
                idx++;              // update the indes
            } else {
                heading += ch;      // append the character just read
            }
            fin.get(ch);            // get the next character for processing
        }
        headings[idx] = heading;    // save the last label read
        fin.close();                // close the data file

    } else {
        cout << "inData is NOT open!" << endl;
    }


}

/// ---------------------------------------------------------------------------
/// Opens the datafile and reads the comma delimited first line
/// using getline() with the delimiter option to read each lable at a time
///
/// @param fn is the name of the data file
/// @param headings references the headings array to store the labels
/// ---------------------------------------------------------------------------
void readHeadingByLabel(const string& fn, string headings[]) {
    ifstream fin;                   // streaming variable
    const char DEL = ',';           // the delimiter
    string heading = "";            // holds the label

    clearHeadings(headings);        // clear headings[] to insure lab fidelity

    fin.open(fn);                   // open the data file for read
    if (fin.is_open()) {
        for (int i = 0; i < HEAD_CT - 1; i++) {
            getline(fin, heading, DEL);   // read each label up to the delimiter
            headings[i] = heading;        // save the label
        }
        getline(fin, heading);            // read last label up to the new line
        headings[HEAD_CT - 1] = heading;  // save the label

        fin.close();                      // close the data file
    } else {
        cout << "inData is NOT open!" << endl;
    }
}

/// ---------------------------------------------------------------------------
/// Opens the datafile and reads the first line
/// string extraction is used to extract the headings by peeling them off the
/// front of the line
///
/// @param fn is the name of the data file
/// @param headings references the headings array to store the labels
/// ---------------------------------------------------------------------------
void readHeadingDistructive(const string& fn, string headings[]) {
    ifstream fin;                   // streaming variable
    const char DEL = ',';           // the delimiter
    string line;                    // stores the line read from the file
    int arrayIdx = 0;               // tracks the headings array location

    // alias the string size type to something more managable
    using strSize_t = std::string::size_type;
    strSize_t strIdx;               // holds the string index value

    clearHeadings(headings);        // clear headings[] to insure lab fidelity

    fin.open(fn);                   // open the data file for read
    if (fin.is_open()) {
        getline(fin, line);         // get the first line
        fin.close();                // close the data file

        // begin work on the line
        while ((strIdx = line.find(DEL)) != std::string::npos) {
            // copy the heading text up to the delimiter and place in the array
            headings[arrayIdx++] = line.substr(0, strIdx);

            // erase the information just copied along with the delimiter
            line.erase(0, strIdx + 1);
        }
        // place the last heading label into the array
        headings[arrayIdx] = line;
    } else {
        cout << "inData is NOT open!" << endl;
    }
}

/// ---------------------------------------------------------------------------
/// Opens the datafile and reads the first line
/// string extraction is used to extract the headings while preserving the line
///
/// @param fn is the name of the data file
/// @param headings references the headings array to store the labels
/// ---------------------------------------------------------------------------
void readHeadingNonDistructive(const string& fn, string headings[]) {
    ifstream fin;                   // streaming variable
    const char DEL = ',';           // the delimiter
    string line;                    // stores the line read from the file
    int arrayIdx = 0;               // tracks the headings array location

    // alias the string size type to something more managable
    using strSize_t = std::string::size_type;
    strSize_t last = 0;             // track the last location of the delimiter
    strSize_t next;                 // track the next location of the delimiter

    clearHeadings(headings);        // clear headings[] to insure lab fidelity

    fin.open(fn);                   // open the data file for read
    if (fin.is_open()) {
        getline(fin, line);         // read the first line
        fin.close();                // close the data file

        // process the line
        while ((next = line.find(DEL, last)) != std::string::npos) {
            // after we locate the next comma, copy the heading
            // from the line
            headings[arrayIdx++] = line.substr(last, next-last);
            last = next + 1;  // move the pointer past the delimiter last found
        }
        // copy the last heading from the last comma to the end of the line
        headings[arrayIdx] = line.substr(last);

    } else {
        cout << "inData is NOT open!" << endl;
    }


}

/// ---------------------------------------------------------------------------
/// Function Implementations Phase II
/// ---------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// Reads the datafile first line, extracts the labels and places them into
/// the headings array
///
/// @param fin is the file streaming input variable
/// @param headings references the headings array to store the labels
/// ---------------------------------------------------------------------------
void setHeadings(ifstream& fin, string headings[]) {
    const char DEL = ',';               // delimiter to separate fields

    // use the delimiter to read the labels from the file into the
    // headings array
    for (int i = 0; i < HEAD_CT - 1; i++) {
        getline(fin, headings[i], DEL);
    }
    // read the last label into the headings array
    getline(fin, headings[HEAD_CT - 1]);
}

/// ---------------------------------------------------------------------------
/// Reads the Manufacturer from the record and stores it into the manufs array
///
/// @param fin is the file streaming input variable
/// @param manufs references the manufs array
/// @param idx is the manufs array index where the manufacturer will be stored
/// ---------------------------------------------------------------------------
void setManuf(ifstream& fin, string manufs[], int idx) {
    const char DEL = ',';               // delimiter to separate fields
    // get the first field in the record
    getline(fin, manufs[idx], DEL);
}

/// ---------------------------------------------------------------------------
/// Reads the inventory data from the record and stores it into the matrix
///
/// @pre manufacturer must have been read from the record
///
/// @param fin is the file streaming input variable
/// @param inventory references the inventory matrix
/// @param idx is the manufs array index where the manufacturer will be stored
/// ---------------------------------------------------------------------------
void setCounts(ifstream& fin, int inventory[][SIZE], int idx) {
    int count;                      // holds the currently read inventory count

    // assume that manuf has been read
    for (int i = 0; i < SIZE; i++) {
        fin >> count;
        inventory[idx][i] = count;
        fin.ignore();
    }
}

/// ---------------------------------------------------------------------------
/// Reads the inventory data from the record and stores it into the matrix
///
/// @param fn is the name of the file to be read
/// @param headings references the array holding the heading labels
/// @param manufs references the array holding the manufacturers
/// @param inventory references the inventory matrix
/// ---------------------------------------------------------------------------
void readInventory(const string& fn,
                   string headings[],
                   string manufs[],
                   int inventory[][SIZE]) {
    ifstream fin;                           // streaming variable

    fin.open(fn);                           // open the data file for read
    if (fin.is_open()) {
        setHeadings(fin, headings);         // get the heading labels
        for (int i = 0; i < MANUF_CT; i++) {
            setManuf(fin, manufs, i);       // get manufacturer from record
            setCounts(fin, inventory, i);   // get inventory counts from record
        }
        fin.close();                        // close the data file
    } else {
        cout << "inData is NOT open!" << endl;
    }
}

/// ---------------------------------------------------------------------------
/// Function Implementations Phase III
/// ---------------------------------------------------------------------------

/// ---------------------------------------------------------------------------
/// Prints the inventory report to the screen
///
/// @param headings references the array holding the heading labels
/// @param manufs references the array holding the manufacturers
/// @param inventory references the inventory matrix
/// ---------------------------------------------------------------------------
void printReport(const string headings[],
                 const string manufs[],
                 const int inventory[][SIZE]) {
    const int W = 7;                            // set column width

    // print heading labels
    for (int col = 0; col < HEAD_CT; col++) {
        cout << setw(W) << headings[col];
    }
    cout << endl;

    // print line under heading labels
    for (int col = 0; col < HEAD_CT; col++) {
        cout << std::string(W, '-');
    }
    cout << endl;

    // print records line by line
    for (int row = 0; row < MANUF_CT; row++) {
        cout << setw(W) << manufs[row];              // print manufacturer
        for (int col = 0; col < SIZE; col++) {
            cout << setw(W) << inventory[row][col];  // print inventory counts
        }
        cout << endl;
    }
    cout << endl;
}

/// ---------------------------------------------------------------------------
/// Write the inventory report to the file
///
/// @param fn is the name of the output file
/// @param headings references the array holding the heading labels
/// @param manufs references the array holding the manufacturers
/// @param inventory references the inventory matrix
/// ---------------------------------------------------------------------------
void saveReport(const string& fn,
                const string headings[],
                const string manufs[],
                const int inventory[][SIZE]) {
    const int W = 7;                    // set column width
    ofstream fout;                      // declare output file stream handler

    fout.open(fn);                      // open file for write

    if (fout.is_open()) {
        // print heading labels
        for (int col = 0; col < HEAD_CT; col++) {
            fout << setw(W) << headings[col];
        }
        fout << endl;

        // print line under heading labels
        for (int col = 0; col < HEAD_CT; col++) {
            fout << std::string(W, '-');
        }
        fout << endl;

        // print records line by line
        for (int row = 0; row < MANUF_CT; row++) {
            fout << setw(W) << manufs[row];              // print manufacturer
            for (int col = 0; col < SIZE; col++) {
                fout << setw(W) << inventory[row][col];  // print counts
            }
            fout << endl;
        }
        fout << endl;

        fout.close();                                     // close output file
    }
}

/* Sample Data File: cars.txt
 MANUF,RED,BROWN,BLACK,WHITE,GRAY
 GM,10,7,12,10,4
 FORD,18,11,15,17,10
 TOYOTA,12,10,9,5,12
 BMW,16,6,13,8,3
 NISSAN,10,7,12,6,4
 VOLVO,9,4,7,12,11

 */

/* Sample Ouput
  MANUF    RED  BROWN  BLACK  WHITE   GRAY
------------------------------------------
     GM     10      7     12     10      4
   FORD     18     11     15     17     10
 TOYOTA     12     10      9      5     12
    BMW     16      6     13      8      3
 NISSAN     10      7     12      6      4
  VOLVO      9      4      7     12     11

 */