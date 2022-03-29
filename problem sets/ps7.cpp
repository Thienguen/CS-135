/// @note Thien Nguyen revision on 3/17/2022
/*
   This program takes 2 text files, one for airplane locations and one
   for airport locations. It will then calculate the manhattan distances
   and euclidean distances from those airplane locations with the data from
   the airport text files. It utilizes functions to calculate the distances.

   There's no expected input for this program, it's all done from the text
   files.

   The expected output is the error messages for x1, y1, x2, and y2, as well as
   the output file with all the contents.
*/
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double manhattanDist(int x1, int x2, int y1, int y2) {
    double manDist = abs(x2-x1)+abs(y2-y1);
    return manDist; //function for manhattan distance, it calculates the
}                 //distance and returns the value

double euclideanDist(int x1, int x2, int y1, int y2) {
    double eucDist = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    return eucDist; //function for euclidean distance, it calculates the
}                 //distance and returns the value

int main(int argc, char* argv[]) {
    ifstream dataFile; //need to declare 2 ifstreams and 1 ofstream for
    ifstream queryFile; //the text files
    ofstream oFile;
    int x1, x2, y1, y2;
    string plane, label, fileName;
    if (argc == 1) {
        cout << "Usage: ./a.out dataFile queryFile\n";
        return 0;
    }
    else if (argc != 3 && argc!= 1) {
        cout << "Error: Incorrect amount of command line arguments\n";
        return 0;
    }
    dataFile.open(argv[1]); //opens up the textfile put in the second command line argument
    if (dataFile.is_open() == false) {
        cout << "Error: Unable to open then data file\n";
        return 0;
    }
    else {
        queryFile.open(argv[2]); //opens up the textfile put in the third command line argument
        if (queryFile.is_open() == false) {
            cout << "Error: Unable to open the query file\n";
            return 0;
        }
        while (!dataFile.eof()) {
            if (dataFile.eof()) {
                break; //breaks out of loop if at the end of file
            }
            dataFile >> x1;
            if (dataFile.fail()) { //error checks for invalid entries, consistent for x1, y1, x2, and y2
                dataFile.clear();
                dataFile.ignore(10000, '\n');
            }

            dataFile >> y1;
            if (dataFile.fail()) {
                dataFile.clear();
                dataFile.ignore(10000, '\n');
            }
            dataFile >> plane;

            fileName = "Distances_" + plane + ".txt"; //creates text file for each plane
            oFile.open(fileName);
            oFile << "x1 y1 label\n"
                  << x1 << " " << y1 << " " << plane
                  << "\nx2 y2 manDist eucDist label\n";

            while (!queryFile.eof()) {
                if (queryFile.eof()) {
                    break;
                }
                queryFile >> x2;
                if (queryFile.fail()) {
                    queryFile.clear();
                    queryFile.ignore(10000, '\n');
                }

                queryFile >> y2;
                if (queryFile.fail()) {
                    queryFile.clear();
                    queryFile.ignore(10000, '\n');
                }
                queryFile >> label;
                queryFile.clear();
                queryFile.ignore(10000, '\n');
                if (queryFile.eof()) { //makes sure it won't repeat the last line
                    break;
                }

                double manDist = manhattanDist(x1, x2, y1, y2); //calls the function and gets
                double eucDist = euclideanDist(x1, x2, y1, y2); //their distances
                oFile << x2 << " " << y2 << " " << manDist << " " << eucDist
                      << " " << label << endl;

            }
            queryFile.clear();
            queryFile.seekg(0, ios::beg);
            oFile.close();
        }
    }
    dataFile.close(); //when done with the program always close the files
    queryFile.close(); //you were using to prevent errors
}
