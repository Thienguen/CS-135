/// @note Thien Nguyen revision on 3/17/2022
/*
    This program takes 2 text files, one for airplane locations and one
    for airport locations. It will then calculate the manhattan distances
    and euclidean distances from those airplane locations with the data from
    the airport text files.

    There's no expected input for this program, it's all done from the text
    files.

    The expected output is the error messages for x1, y1, x2, and y2, as well as
    the output file with all the contents.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    
    // need to declare 2 
    // ifstreams and 1 ofstream for
    ifstream dataFile;  
    ifstream queryFile; 
    
    // the text files
    ofstream oFile;
    string plane, label;

    int x1, x2, y1, y2, manDist, eucDist;
    
    if (argc == 1) {
        cout << "Usage: ./a.out dataFile queryFile outputFile\n";
        return 0;
    }
    else if (argc != 4 && argc!= 1) {
        cout << "Error: Incorrect amount of command line arguments\n";
        return 0;
    }
    dataFile.open(argv[1]);                         // opens up the textfile put in the second command line argument
    if (dataFile.is_open() == false) {              // (AirplaneLocations.txt)
        cout << "Error: Invalid data file extension\n";
        return 0;
    }
    else {
        queryFile.open(argv[2]);                // opens up the textfile put in the third command line argument
        if (queryFile.is_open() == false) {     // (AirportLocations.txt)
            cout << "Error: Invalid query file extension\n";
            return 0;
        }
        oFile.open(argv[3]);        // whatever text file name is put in the fourth command line
        while (!dataFile.eof()) {   // argument will be the name of the output text file
            if (dataFile.eof()) {
                break; //breaks out of loop if at the end of file
            }
            dataFile >> x1;
            if (dataFile.fail()) {  // error checks for invalid entries, consistent for x1, y1, x2, and y2
                cout << "Error: Invalid x1 entry\n";
                dataFile.clear();
                dataFile.ignore(10000, '\n');
            }

            dataFile >> y1;
            if (dataFile.fail()) {
                cout << "Error: Invalid y1 entry\n";
                dataFile.clear();
                dataFile.ignore(10000, '\n');
            }
            dataFile >> plane;
            oFile << setw(8) << left << "\nx1" << setw(8) << left << "y1" // neatly outputted text
                  << setw(8) << left << "label" << endl                   // to the output file

                  << setw(7) << left << x1 << setw(8) << left << y1
                  << setw(8) << left << plane << endl << endl

                  << setw(8) << left << "manDist" << setw(8) << left << "eucDist"
                  << setw(8) << "label" << endl;

            while (!queryFile.eof()) {
                if (queryFile.eof()) {
                    break;
                }
                queryFile >> x2;
                if (queryFile.fail()) {
                    cout << "Error: Invalid x2 entry\n";
                    queryFile.clear();
                    queryFile.ignore(10000, '\n');
                }

                queryFile >> y2;
                if (queryFile.fail()) {
                    cout << "Error: Invalid y2 entry\n";
                    queryFile.clear();
                    queryFile.ignore(10000, '\n');
                }
                queryFile >> label;
                queryFile.clear();
                queryFile.ignore(10000, '\n');
                manDist = abs(x2-x1)+abs(y2-y1);
                eucDist = sqrt(pow(x2-x1,2)+pow(y2-y1,2));

                oFile << setw(8) << left << manDist << setw(8) << left << eucDist
                      << setw(8) << left << label << endl;

            }
            queryFile.clear();
            queryFile.seekg(0, ios::beg);
        }

    }
    dataFile.close();   // when done with the program always close the files
    queryFile.close();  // you were using to prevent errors
    oFile.close();
}
