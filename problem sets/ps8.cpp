/// @note Thien Nguyen revision on 3/17/2022
/* 

    This program takes a text file, and utilizes functions and arrays
    to cleanly output to the file the intercept, average of both columns,
    as well as the minimums and maximums

    No expected input, its all in command line arguments.

    The expected output is the slope, intercept, averages, minimums, and maximums.
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void openFile(ifstream& iFile, string filename) {
    iFile.open(filename);
    if (iFile.is_open() == false) {
        cout << "Error: File not open\n";
    }
}

void readFile(ifstream& iFile, double data1[], double data2[], int size) {
    double gallons, miles;
    int i = 0;

    // ignores the first 2 lines in the text file
    for (int i=0; i < 2; i++) { 
        iFile.ignore(40,'\n');
    }

    while (!iFile.eof()) {
        if (iFile.eof()) {
            break;
        }

        iFile >> gallons;
        iFile >> miles;

        // fail checks
        if(iFile.fail()) { 
            iFile.clear();
            iFile.ignore(100,'\n');
            cout << "Invalid entry\n";
        }
        else {
            data1[i] = gallons;
            data2[i] = miles;

            i++;
        }
    }
}

// overloading functions depending on whats being passed in
double mySum(double data[], int size) {
    double sum = 0;
    for (int i=0; i < size; i++) {
        sum += data[i];
    }
    return sum;
}

double mySum(double data1[], double data2[], int size) {
    double sum = 0;
    double product = 0;
    for (int i=0; i < size; i++) {
        product = data1[i]*data2[i];
        sum += product;
    }
    return sum;
}

double average(double data[], int size) {
    double avg;
    for (int i=0; i < size; i++) {
        avg += data[i];
    }
    avg = avg / size;
    return avg;
}

// need to start it at a big number
double min(double data[], int size) {
    double minimum = 1000000000; 
    for (int i=0; i < size; i++) {
        if (data[i] < minimum)
            minimum = data[i];
    }
    return minimum;
}

double max(double data[], int size) {
    double maximum = 0;
    for (int i=0; i < size; i++) {
        if (data[i] > maximum)
            maximum = data[i];
    }
    return maximum;
}

// split into three parts to properly output the right number
double slope(int count, long x, long y, long xy, long xSquared) {
    double one, two, three; 
    one = count * xy;
    two = x*y;
    three = (count* xSquared) - (x*x);
    return (one - two) / three;
}

double intercept(int count, long x, long y, long xy, long xSquared) {
    double one, two, three;
    one = y * xSquared;
    two = x * xy;
    three = ((count * xSquared) - (x * x));
    return (one - two) / three;
}

int main(int argc, char* argv[]) {
    ifstream iFile;
    ofstream oFile;
    string filename;
    int size;
    long x, y, xy, xSquared;
    double slopeDist, intDist, avgFuel, avgDist, minFuel, maxFuel, minDist, maxDist;

    if (argc == 1) {
        cout << "Usage: ./a.out dataFile\n";
        return 0;
    }
    else if (argc != 1 && argc != 2) {
        cout << "Error: Incorrect amount of command line arguments\n";
        return 0;
    }

    //the file name is taken from the second command line argument
    filename = argv[1]; 
    openFile(iFile, filename);

    iFile >> size;
    double data1[size];
    double data2[size];

    // calling all functions with respective variables
    readFile(iFile, data1, data2, size); 

    x = mySum(data1, size);
    y = mySum(data2, size);
    xy = mySum(data1, data2, size);
    xSquared = mySum(data1, data1, size);

    slopeDist = slope(size, x, y, xy, xSquared);
    intDist = intercept(size, x, y, xy, xSquared);

    avgFuel = average(data1, size);
    avgDist = average(data2, size);

    minFuel = min(data1, size);
    maxFuel = max(data1, size);

    minDist = min(data2, size);
    maxDist = max(data2, size);

    oFile.open("output/Results.txt");

    // outputting data into Results.txt
    oFile << "slope: " << slopeDist 
          << "\nintercept: " << intDist
          << "\naverage col 1: " << avgFuel
          << "\naverage col 2: " << avgDist
          << "\nminX -> maxX: " << minFuel << " -> " << maxFuel
          << "\nminY -> maxY: " << minDist << " -> " << maxDist << endl;

    // close all files at the end
    iFile.close(); 
    oFile.close();

}
