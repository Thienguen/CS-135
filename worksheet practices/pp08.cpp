/// @note Thien Nguyen revision on 3/17/2022
/* 
    This program prompts the user to input a letter grade, and depending
    on the letter, the switch statement will follow whichever letter
    they inputted for the grade char variable. All the outputs will be the
    grade range of the user-given letter.

    The expected input is the letter grade.

    The expected output is the grade range for that letter grade
*/
#include <iostream>

using namespace std;
int main() {
    char grade = 0;
    cout << "Enter a letter grade: ";
     cin >> grade;
    // can put both cases at the top, 
    // for both upper and lower case
    switch(grade) 
    {
        case 'a': 
        case 'A':
            cout << "Grade range is 90-100\n";
            break;
        case 'b':
        case 'B':
            cout << "Grade range is 80-89\n";
            break;
        case 'c':
        case 'C':
            cout << "Grade range is 70-79\n";
            break;
        case 'd':
        case 'D':
            cout << "Grade range is 60-69\n";
            break;
        case 'f':
        case 'F':
            cout << "Grade range 0-59\n";
        default:
            cout << "Error: Not a letter in the grade range\n";
    }
}
