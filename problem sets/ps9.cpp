/// @note Thien Nguyen revision on 3/17/2022
/* 

    This program takes a text file, and uses 1D and 2D arrays to perform various
    operations on the values provided

    No expected input, its all in command line arguments.

    The expected output is the results of various operations done with the arrays.
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

// declare global variables
const int row = 22; 
const int col = 6;

// opens input file
void openFile(ifstream& iFile, string filename) { 
    iFile.open(filename);
    if (iFile.is_open() == false) {
        cout << "Error: File not open\n";
        exit(0);
    }
}

// opens output file
void openFile(ofstream& oFile, string filename) { 
    oFile.open(filename);
    if (oFile.is_open() == false) {
        cout << "Error: File not open\n";
        exit(0);
    }
}

// reads in data from the file
void readFile(ifstream& iFile, string headers[], double data[][col]) { 
    for (int i = 0; i < 6; i++) {
        // saves all header names into a 1D array
        iFile >> headers[i]; 
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            iFile >> data[i][j];
        }
    }
}

// prints headers
void print(ofstream& oFile, string headers[]) { 
    for (int i = 0; i < col; i++) {
        oFile << headers[i] << " ";
    }
}

// print data
void print(ofstream& oFile, double data[][col], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < col; j++) {
            oFile << setw(13) << left << data[i][j];
        }
        oFile << "\n";
    }
}

// same
void print(ofstream& oFile, double data[][row], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < row; j++) {
            oFile << setw(13) << left << data[i][j];
        }
        oFile << "\n";
    }
}

// same
void transpose(double matrix[][col], double matrix2[][row]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix2[j][i] = matrix[i][j];
        }
    }
}

// same
void transpose(double matrix[][row], double matrix2[][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            matrix2[i][j] = matrix[j][i];
        }
    }
}

// arithmetic 
void add(int size, double matrix1[][col], double matrix2[][col], double matrix3[][col]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < col; j++) {
            // adds matrices and puts them into matrix3
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j]; 
        }
    }
}

// above
void add(int size, double matrix1[][row], double matrix2[][row], double matrix3[][row]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < row; j++) {
            matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

// above
void subtract(int size, double matrix1[][col], double matrix2[][col], double matrix3[][col]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < col; j++) {
            // subtracts matrices and puts them into matrix3
            matrix3[i][j] = matrix1[i][j] - matrix2[i][j]; 
        }
    }
}

// above
void subtract(int size, double matrix1[][row], double matrix2[][row], double matrix3[][row]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < row; j++) {
            matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
}

// above
void multiply(double matrix[][col], double matrix2[][row], double matrix3[][row]) {
    i  = 0; i < row; i++) {
    for (int  
            // Going through all the rows
        for (int j=0; j < row; j++) {  
            // Initializing
            matrix3[i][j] = 0;  
            for (int k = 0; k < col; k++) { 
                // Going through all columns
                // Multiply the 2 matrices and add into the matrix
                matrix3[i][j] += matrix[i][k] * matrix2[i][j];  
            }
        }
    }
}

// above
void multiply(double matrix[][row], double matrix2[][col], double matrix3[][col]) {
    for (int i=0; i < col; i++) {
            // Going through all the rows
        for (int j=0; j < col; j++) {  
            // Initializing
            matrix3[i][j] = 0;  
                // Going through all columns
            for (int k = 0; k < row; k++) {  
                // Multiply the 2 matrices and add into the matrix
                matrix3[i][j] += matrix[i][k] * matrix2[i][j];  
            }
        }
    }
}

// int main function
int main(int argc, char* argv[]) {
    ifstream iFile;
    ofstream oFile;
    string filename;
    int size;
    if (argc == 1) {
        cout << "Usage: ./a.out dataFile\n";
        return 0;
    }
    else if (argc != 1 && argc != 2) {
        cout << "Error: Incorrect amount of command line arguments\n";
        return 0;
    }

    string headers[6];
    double data[row][col];

    openFile(iFile, argv[1]);
    openFile(oFile, "output.txt");


    // outputs the headers
    oFile << "Headers\n"; 
    readFile(iFile, headers, data);
    print(oFile, headers);

    oFile << "Original File (X)\n";
    print(oFile, data, row);
    oFile << endl;

    // 6*22
    double trans1[col][row];  
    oFile << "Transpose of File (X')\n";
    transpose(data, trans1);
    print(oFile, trans1, col);
    oFile << endl;

    double trans2[row][col];
    oFile << "Transpose of X' (X'')\n";
    transpose (trans1, trans2);
    print (oFile, trans2, row);
    oFile << endl;

    // declaring arrays to print (consistent for all)
    double mult1[col][row];  
    oFile << "Product of XX'\n";
    multiply(data, trans1, mult1);
    print(oFile, mult1, col);
    oFile << endl;

    double mult2[row][col];
    oFile << "Product of X'X\n";
    multiply(trans1, data, mult2);
    print(oFile, mult2, row);
    oFile << endl;

    double ad[row][col];
    oFile << "Result of X + X\n";
    add(size, data, data, ad);
    print(oFile, ad, row);
    oFile << endl;

    double add1[col][row];
    oFile << "Result of X' + X'\n";
    add(size, trans1, trans1, add1);
    print(oFile, add1, col);
    oFile << endl;

    double add2[col][row];
    oFile << "Result of Mult1 + Mult1\n";
    add(size, mult1, mult1, add2);
    print(oFile, add2, col);
    oFile << endl;

    double add3[row][col];
    oFile << "Result of Mult2 + Mult2\n";
    add(size, mult2, mult2, add3);
    print(oFile, add3, row);
    oFile << endl;

    double subtrac[col][row];
    oFile << "Result of (X' + X') - X'\n";
    subtract(size, add1, add1, subtrac);
    print(oFile, subtrac, col);
    oFile << endl;

    double subtract1[col][row];
    oFile << "Result of (Mult1 + Mult1) - Mult1\n";
    subtract(size, mult1, mult1, subtract1);
    print(oFile, subtract1, col);
    oFile << endl;

    double subtract2[row][col];
    oFile << "Result of (Mult2 + Mult2) - Mult2\n";
    subtract(size, mult2, mult2, subtract2);
    print(oFile, subtract2, col);
    oFile << endl;

    iFile.close();
    oFile.close();
}
