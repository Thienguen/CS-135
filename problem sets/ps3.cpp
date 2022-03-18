/// @note Thien Nguyen revision on 3/17/2022
/* 
    This program acts as a calculator for 3 different calculations:
    Slope, Manhattan Distance, and Euclidean Distance, it also has the
    option to quit out of the calculator immediately as well. This program
    is essentially a bunch of nested if statements that error check for
    invalid input and input failure. And if the user input passes all those
    if statement tests, then the result for their inputs will show at the end.

    The exptected input of the program is the values for x1, x2, y1, and y2.

    The expected output is the error messages if they input something
    incorrectly, or the calculation values based on their options, if
    the inputs they put in are valid.
*/

#include <iostream>
#include <cmath> 
#include <iomanip>

using namespace std;

int main() {
    char menuOption;
    double x1, x2, y1, y2, slope, yInt, manDist, eucDist;

    // we can setprecision right in the beginning and all the values
    // will be set to 3 decimals for the rest of the program
    cout << setprecision(3) << fixed;
    cout << "**************************************\n"
         << "* Welcome to the Distance Calculator *\n"
         << "**************************************\n"
         // setw to the left makes sure whats outputted after it goes directly to
         // the left, and allows the buttons youre supposed to be pressing show
         // up neatly on the right up to the 23rd space.
         << setw(23) << left << "Slope" << "-   (s/S)\n"
         << setw(23) << left << "Manhattan Distance" << "-   (m/M)\n"
         << setw(23) << left << "Euclidean Distance" << "-   (e/E)\n"
         << setw(23) << left << "Quit"  << "-   (q/Q)\n\n"
         << "Enter an Option:\n**";
     cin >> menuOption;
    /*
        This is the first option of the nested if statements, which take
        either 's' OR (||) 'S', which then afterwards, it will ask for a series
        of values in which each if statement will check whether it's the
        correct type of variable, if not it will output an error message
        and terminate the program, and if its not, it will continue with the
        series of questions until it reaches the end where it will calculate
        the value of the slope and Y Intercept
    */
    if (menuOption == 's' || menuOption == 'S') 
    {
        // useless
        cout << "\nEnter a x1 value:\n**";
        cin >> x1;

        // seperated
        if (cin.fail() == true) { 
            cout << "Error: invalid input\n"; 
            return 0;             
        } else if (x1 > 100) {   
            //this is consistent throughout the whole program
            cout << "Error: invalid x value, max is 100\n"; 
            return 0;
        } else {
            cout << "Enter a y1 value:\n**";
            cin >> y1;
            // new one
            if (cin.fail() == true) {
                cout << "Error: invalid input\n";
                return 0;
            } else if (y1 > 150) { 
                // this else if statement will make sure that
                // values inputted cant exceed 150 for y, or
                // 100 for x, and this is consistent throughout
                // the whole program as well
                cout << "Error: invalid y value, max is 150\n";
                return 0;
            } else {
                cout << "\nEnter a x2 value:\n**";
                cin >> x2;
                // new one
                if (cin.fail() == true) {
                    cout << "Error: invalid input\n";
                    return 0;
                } else if (x2 > 100) {
                    cout << "Error: invalid x value, max is 100\n";
                    return 0;
                } else {
                    cout << "Enter a y2 value:\n**";
                    cin >> y2;
                    // new one
                    if (cin.fail() == true) {
                        cout << "Error: invalid input\n";
                        return 0;
                    } else if (y2 > 150) {
                        cout << "Error: invalid y value, max is 150\n";
                        return 0;
                    } else {
                        slope = (y2-y1)/(x2-x1);
                         yInt = y1 - (slope*x1);
                        cout << "\nSlope: " << slope << endl
                             << "Y-Intercept: " << yInt << endl;
                    }
                }
            }
        }

        /*
            This is the second option of the nested if statements, which take
            either 'm' OR (||) 'M', which then afterwards, it will ask for a series
            of values in which each if statement will check whether it's the
            correct type of variable, if not it will output an error message
            and terminate the program, and if its not, it will continue with the
            series of questions until it reaches the end where it will calculate
            the Manhattan Distance
        */

    } else if (menuOption == 'm' || menuOption == 'M') {
        cout << "\nEnter a x1 value:\n**";
        cin >> x1;
        if (cin.fail() == true) {
            cout << "Error: invalid input\n";
            return 0;
        } else if (x1 > 100) {
            cout << "Error: invalid x value, max is 100\n";
            return 0;
        } else {
            cout << "Enter a y1 value:\n**";
            cin >> y1;
            // if inside an else
            if (cin.fail() == true) {
                cout << "Error: invalid input\n";
                return 0;
            } else if (y1 > 150) {
                cout << "Error: invalid y value, max is 150\n";
                return 0;
            } else {
                cout << "\nEnter a x2 value:\n**";
                cin >> x2;
                // if inside an else
                if (cin.fail() == true) {
                    cout << "Error: invalid input\n";
                    return 0;
                } else if (x2 > 100) {
                    cout << "Error: invalid x value, max is 100\n";
                    return 0;
                } else {
                    cout << "Enter a y2 value:\n**";
                    cin >> y2;
                    // if inside an else
                    if (cin.fail() == true) {
                        cout << "Error: invalid input\n";
                        return 0;
                    } else if (y2 > 150) {
                        cout << "Error: invalid y value, max is 150\n";
                        return 0;
                    } else {
                        manDist = abs(x2-x1)+abs(y2-y1);
                        cout << "\nManhattan Distance: " << manDist << endl;
                    }
                }
            }
        }

        /*  this is the third option of the nested if statements, which take
            either 'e' OR (||) 'E', which then afterwards, it will ask for a series
            of values in which each if statement will check whether it's the
            correct type of variable, if not it will output an error message
            and terminate the program, and if its not, it will continue with the
            series of questions until it reaches the end where it will calculate
            the Euclidean Distance  
        */

    } else if (menuOption == 'e' || menuOption == 'E') {
        // usless - 3
        cout << "\nEnter a x1 value:\n**";
        cin >> x1;
        // if inside an else
        if (cin.fail() == true) {
            cout << "Error: invalid input\n";
            return 0;
        } else if (x1 > 100) {
            cout << "invalid x value, max is 100\n";
            return 0;
        } else {
            cout << "Enter a y1 value:\n**";
            cin >> y1;
            // if inside an else
            if (cin.fail() == true) {
                cout << "Error: invalid input\n";
                return 0;
            } else if (y1 > 150) {
                cout << "Error: invalid y value, max is 150\n";
                return 0;
            } else {
                cout << "\nEnter a x2 value:\n**";
                cin >> x2;
                // if inside an else
                if (cin.fail() == true) {
                    cout << "Error: invalid input\n";
                    return 0;
                } else if (x2 > 100) {
                    cout << "invalid x value, max is 100\n";
                    return 0;
                } else {
                    cout << "Enter a y2 value:\n**";
                    cin >> y2;
                    // if inside an else
                    if (cin.fail() == true) {
                        cout << "Error: invalid input\n";
                        return 0;
                    } else if (y2 > 150) {
                        cout << "error y value, max is 150\n";
                        return 0;
                    } else {
                        eucDist = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
                        cout << "\nEuclidean Distance: " << eucDist << endl;
                    }
                }
            }
        }
        /*
            this is the fourth and last option of else if statements which
            allows the user to exit the Distance Calculator from the start
        */
    } else if (menuOption == 'q' || menuOption == 'Q') {
        cout << "\nThank you for using the Distance Calculator\n";
        return 0;
        // This is the else statement that error checks if the user doesn't choose
        // an option off the menu from the beginning of the program
    } else {
        cout << "\nError: Invalid selection\n";
        return 0;
    }
}
