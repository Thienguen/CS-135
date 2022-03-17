/// @note Thien Nguyen revision on 3/17/2022
/* 
    This program prompts the user for various inputs, but most importantly
    the total points of an assignment and the total points recieved from
    that assignment, when going through the prompt for these inputs it will
    check if the input is the correct variable type, if it's not it will
    display an error message and stop the program, but if it is then it will
    continue through the prompts until it reaches the end, where it will
    calculate the percentage grade a particular user got and their letter
    grade based on the inputs given.

    The exptected input of the program is the first and last names of
    the people, the column names, & the total points and recieved points
    for both assignments.

    The expected output is the the information provided by the user, as well
    as the percentage they got and the corresponding letter grade.
*/
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    string firstName, lastName, column1, column2;
    double tas1, ras1, tas2, ras2, percent1, percent2;
    cout << "CS135 Lab 4\nGRADE SHEETS\n\nEnter first name\n";
     cin >> firstName;

    cout << "**Enter last name\n";
     cin >> lastName;

    cout << "**Enter name of column 1\n";
     cin >> column1;

    cout << "**Enter name of column 2\n";
     cin >> column2;

    cout << "**Enter total points for Asst 1\n";
     cin >> tas1;

    // We have nested if else statements to test each individual prompt one
    // after another, cin.fail() will test if the user input is the correct
    // variable type
    if (cin.fail() == true) {
        cout << "**Invalid total points for Asst 1!\n";
        return 0;
    } else {
        cout << "**Enter recieved points for Asst 1\n";
        cin >> ras1;
        if (cin.fail() == true) {
            cout << "**Invalid recieved points for Asst 1!\n";
            return 0;
        } else {
            cout << "**Enter total points for Asst 2\n";
            cin >> tas2;
            if (cin.fail() == true) {
                cout << "**Invalid total points for Asst 2!\n";
                return 0;
            } else {
                cout << "**Enter recieved points for Asst 2\n";
                cin >> ras2;
                if (cin.fail() == true) {
                    cout << "**Invalid recieved points for Asst 2!\n";
                    return 0;
                } else {
                    percent1 = (ras1/tas1)*100;     // after we recieved all the values
                    percent2 = (ras2/tas2)*100;     // these declarations calculate
                    // their percentage

                    // this will output to the screen the first and last names
                    // then it will output the first row which is the names of everything
                    cout << "**\n\nFIRST NAME: " << firstName << "\nLAST NAME: " << lastName 
                         << setw(6) << left << "\nASST" 
                         << setw(6) << left << "TOTAL" 
                         << setw(9) << left << "RECIEVED" 
                         << setw(8) << left << "PERCENT"
                         << setw(6) << left << "LETTER\n";

                    // this will output to the screen the first row of values
                    // including the grade percent and corresponding letter grade
                    cout << setw(5) << left << "1" << setw(6) << left << tas1
                         << setw(9) << left << ras1 << setw(8) << left << percent1;
                    if (percent1 >= 90) {
                        cout << "A\n";
                    } else if (percent1 >= 80 && percent1 <= 89.99) {
                        cout << "B\n";
                    } else if (percent1 >= 70 && percent1 <= 79.99) {
                        cout << "C\n";
                    } else if (percent1 >= 60 && percent1 <= 69.99) {
                        cout << "D\n";
                    } else if (percent1 <= 59.99) {
                        cout << "F\n";
                    }

                    // this will output to the screen the second row of values
                    // including the grade percent and corresponding letter grade
                    cout << setw(5) << left << "2" << setw(6) << left << tas2
                         << setw(9) << left << ras2 << setw(8) << left << percent2;
                    if (percent2 >= 90) {
                        cout << "A\n";
                    } else if (percent2 >= 80 && percent2 <= 89.99) {
                        cout << "B\n";
                    } else if (percent2 >= 70 && percent2 <= 79.99) {
                        cout << "C\n";
                    } else if (percent2 >= 60 && percent2 <= 69.99) {
                        cout << "D\n";
                    } else if (percent2 <= 59.99) {
                        cout << "F\n";
                    }
                }
            }
        }
    }
}
