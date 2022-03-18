/// @note Thien Nguyen Revision on 3/17/2022
/* 
    This program requires the user to use command line arguments, and
    depending on what they input, the program will act accordingly.
    The program requires 3 command line arguments, and argv[1] will determine
    if the user wants to calculate Manhattan Distance or Euclidean Distance, and
    argv[2] will determine how many times the user wants to calculate these
    distances. At the end, the program will determine the highest slope and
    lowest slope, as well as show you the points you inputted to get those
    slopes.

    Expected input: The command lines arguments & x1, y1, x2, and y2 values

    Expected output: Calulations for Manhattan Distance, Euclidean Distance,
                     slope, as well as the highest and lowest slope, and the
                     points correlating w those slopes.
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) 
{
    string argvCalc, atoiString;
    int atoiInt = 0;
    double x1, x2, y1, y2, manDist, eucDist, slope, minX1 = 0, minX2 = 0, minY1 = 0,
                                                    minY2 = 0, minSlope =  100000000, minDist = 0, maxX1 = 0, maxX2 = 0, maxY1 = 0,
                                                    maxY2 = 0, maxSlope =- 100000000, maxDist = 0;
    // preset the variable values for the mins/maxs so later in the program
    // it can be compared to the current slope value

    if (argc != 3) {
        cout << "Error: Incorrect amount of command line arguments\n";
        return 0;
    }
    // this checks if theres 3 command line arguments provided, and if not
    // the error will show
    else {
        argvCalc = argv[1];
        atoiString = argv[2];
        if (argvCalc != "-m" && argvCalc != "-e" && argvCalc != "-M" && argvCalc != "-E") {
            cout << "Error: Not a valid option\n";
            return 0;
            // if the first if statement is passed, then it checks if the second command
            // argument is either "-m, -M, -e or -E" which is for Manhattan distance
            // or Euclidean distance.
        }
        else {
            atoiInt = atoi(atoiString.c_str());
            if (atoiInt < 2 || atoiInt > 5) {
                cout << "Error: Iteration count not in range 2-5\n";
                return 0;
                // since the third command line argument is saved as a string, we use atoi
                // in order to convert it into an integer, which then we range check if its
                // anywhere between 2-5
            }
            else {
                if(argvCalc == "-m" || argvCalc == "-M") {
                    cout << "Manhattan Distance\n\n";
                    // For the Manhattan Distance calculations, we run it through a for loop
                    // and the condition is that itll stop when we reach the amount of iterations
                    // provided from argv[3]
                    for (int i = 0; i < atoiInt; i++) {
                        cout << "Enter a x1 value:\n**";
                        cin >> x1;
                        // Error checks whether the variable type that was inputted is corect,
                        // or if its in the correct range from 0-99, if not it will display
                        // and error message and reiterate the question until both those
                        // the conditions are met, this error checking is consistent for all
                        // x1, x2, y1, and y2 values
                        while ((cin.fail() == true) || (x1 < 0 || x1 >= 100)) {
                            cout << "Error: Invalud Input\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Enter a x1 value:\n**";
                            cin >> x1;
                        }
                        cout << "Enter a y1 value:\n**";
                        cin >> y1;
                        while ((cin.fail() == true) || (y1 < 0 || y1 >= 100)) {
                            cout << "Error: Invalud Input\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Enter a y1 value:\n**";
                            cin >> y1;
                        }
                        cout << "\nEnter a x2 value:\n**";
                        cin >> x2;
                        while ((cin.fail() == true) || (x2 < 0 || x2 >= 100)) {
                            cout << "Error: Invalud Input\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Enter a x2 value:\n**";
                            cin >> x2;
                        }
                        cout << "Enter a y2 value:\n**";
                        cin >> y2;
                        while ((cin.fail() == true) || (y2 < 0 || y2 >= 100)) {
                            cout << "Error: Invalud Input\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Enter a y2 value:\n**";
                            cin >> y2;
                        }
                        manDist = abs(x2 - x1) + abs(y2 - y1);
                        slope   = (y2 - y1) / (x2 - x1);
                        // this segment is where it will check if the current slope is higher
                        // than the current maximum, or lower than the current minumum,
                        // and if it is, it will replaces the value as the new max/min slope
                        // as well as replace the values of the points to get this slope
                        if (slope > maxSlope) {
                            maxSlope = slope;
                            maxX1    = x1;
                            maxX2    = x2;
                            maxY1    = y1;
                            maxY2    = y2;
                            maxDist  = manDist;
                        } else if (slope < minSlope) {
                            minSlope = slope;
                            minX1 = x1;
                            minX2 = x2;
                            minY1 = y1;
                            minY2 = y2;
                            minDist = manDist;
                        }
                        // this displays the calculations after all the intput is given
                        cout << "\nCALCULATION " << i + 1 << endl << setw(10) << left
                             << "manDist" << left << "slope\n" << setw(10) << manDist
                             << setw(8) << slope << "\n\n";
                    }
                    // after all iterations of the loop are done, and the max/min slope is
                    // determined, this part will output the highest and lowest slope
                    cout << fixed << setw(16) << left << "Highest Slope" << setw(4) << left
                         << "x1" << setw(4) << left << "y1" << setw(4) << left
                         << "x2" << setw(4) << left << "y2" << setw(7) << left
                         << "eucDist\n"
                         << setw(16) << left << maxSlope << setw(4) << left
                         << static_cast<int>(maxX1) << setw(4) << left << static_cast<int>(maxY1) << setw(4) << left
                         << static_cast<int>(maxX2) << setw(4) << left << static_cast<int>(maxY2);
                    printf("%g", maxDist);
                    // we use static_cast because they're currently saved as doubles, but in the
                    // example output they're shown as integers.
                    cout << "\n\n" << setw(16) << left << "Lowest Slope" << setw(4) << left
                         << "x1" << setw(4) << left << "y1" << setw(4) << left
                         << "x2" << setw(4) << left << "y2" << setw(7) << left
                         << "eucDist\n"
                         << setw(16) << left << minSlope << setw(4) << left
                         << static_cast<int>(minX1) << setw(4) << left << static_cast<int>(minY1) << setw(4) << left
                         << static_cast<int>(minX2) << setw(4) << left << static_cast<int>(minY2);
                    printf("%g", minDist);
                    cout << "\n\n";
                }

                // the rest is the same as the Manhattan Distance calculation portion, except
                // with the data and equations for Euclidean Distance instead
                // and except of using a for loop this time, we use a do while loop
                else if (argvCalc == "-e" || argvCalc == "-E") {
                    int i = 0;
                    cout << "Euclidean Distance\n\n";
                    do {
                        cout << "Enter a x1 value:\n**";
                        cin >> x1;
                        while ((cin.fail() == true) || (x1 < 0 || x1 >= 100)) {
                            cout << "Error: Invalud Input\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Enter a x1 value:\n**";
                            cin >> x1;
                        }
                        cout << "Enter a y1 value:\n**";
                        cin >> y1;
                        while ((cin.fail() == true) || (y1 < 0 || y1 >= 100)) {
                            cout << "Error: Invalud Input\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Enter a y1 value:\n**";
                            cin >> y1;
                        }
                        cout << "\nEnter a x2 value:\n**";
                        cin >> x2;
                        while ((cin.fail() == true) || (x2 < 0 || x2 >= 100)) {
                            cout << "Error: Invalud Input\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Enter a x2 value:\n**";
                            cin >> x2;
                        }
                        cout << "Enter a y2 value:\n**";
                        cin >> y2;
                        while ((cin.fail() == true) || (y2 < 0 || y2 >= 100)) {
                            cout << "Error: Invalud Input\n";
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Enter a y2 value:\n**";
                            cin >> y2;
                        }
                        eucDist = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
                        slope = (y2-y1)/(x2-x1);
                        if(slope > maxSlope) {
                            maxSlope = slope;
                            maxX1 = x1;
                            maxX2 = x2;
                            maxY1 = y1;
                            maxY2 = y2;
                            maxDist = eucDist;
                        }
                        else if (slope < minSlope) {
                            minSlope = slope;
                            minX1 = x1;
                            minX2 = x2;
                            minY1 = y1;
                            minY2 = y2;
                            minDist = eucDist;
                        }
                        cout << "\nCALCULATION " << i+1 << endl << setw(10) << left
                             << "eucDist" << left << "slope\n" << setw(10) << eucDist
                             << setw(8) << slope << "\n\n";
                        i++;
                    }
                    while (i<atoiInt);
                    cout << fixed << setw(16) << left << "Highest Slope" << setw(4) << left
                         << "x1"  << setw(4)  << left << "y1" << setw(4) << left
                         << "x2"  << setw(4)  << left << "y2" << setw(7) << left
                         << "eucDist\n"
                         << setw(16) << left << maxSlope << setw(4) << left
                         << static_cast<int>(maxX1) << setw(4) << left << static_cast<int>(maxY1) << setw(4) << left
                         << static_cast<int>(maxX2) << setw(4) << left << static_cast<int>(maxY2);
                    printf("%g", maxDist);


                    cout << "\n\n"<< setw(16) << left  << "Lowest Slope"  << setw(4) << left
                         << "x1"  << setw(4)  << left  << "y1" << setw(4) << left
                         << "x2"  << setw(4)  << left  << "y2" << setw(7) << left
                         << "eucDist\n"
                         << setw(16) << left << minSlope << setw(4) << left
                         << static_cast<int>(minX1) << setw(4) << left << static_cast<int>(minY1) << setw(4) << left
                         << static_cast<int>(minX2) << setw(4) << left << static_cast<int>(minY2);
                    printf("%g", minDist);
                    cout << "\n\n";
                }
            }
        }
    }
}
