/// @note Thien Nguyen,revision: 3/17/2022
/* 

   This program prompts the user for a month, day, and year, and then
   will run through various switch statements, calculations, and
   equations in order to neatly output them.

   Expected input: Integers for month, day, and year

   Expected output: The day of the week, the month and day corresponding
                    to the given integer, and the year.
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
    int month = 0, day = 0, year = 0, century = 0, dow = 0, tempYear = 0; 
    // preset all values to 0
    string monthName, dayOfTheWeek;

    cout << "Enter in a month (1-12): ";
    cin >> month;
    if (cin.fail()==true) { // error checks if its the correct variable type and is consistent
        cout << "Error: Enter in a number"; // throughout the whole program
        return 0;
    }
    else if (month < 1 || month > 12) { // will check if integer of month being inputted is between
        cout << "Error: Enter in a number between 1-12\n"; // January and February
        return 0;
    }
    else { // name of month will switch to corresponding integer given
        switch(month) {
        case 1:
            monthName = "January";
            month = 13; // for cases of January and February, month will change according
            break;      // to Zeller's Rule
        case 2:
            monthName = "February";
            month = 14;
            break;
        case 3:
            monthName = "March";
            break;
        case 4:
            monthName = "April";
            break;
        case 5:
            monthName = "May";
            break;
        case 6:
            monthName = "June";
            break;
        case 7:
            monthName = "July";
            break;
        case 8:
            monthName = "August";
            break;
        case 9:
            monthName = "September";
            break;
        case 10:
            monthName = "October";
            break;
        case 11:
            monthName = "November";
            break;
        case 12:
            monthName = "December";
            break;
        }
        cout << "\nEnter in a day (1-31): ";
        cin >> day;
        if (cin.fail()==true) {
            cout << "Error: Enter in a number";
            return 0;
        }
        else if (day < 1 || day > 31) {
            cout << "Error: Enter in a day between 1-31\n";
            return 0;
        }
        else {
            cout << "\nEnter in a year: ";
            cin >> year;
            if (cin.fail()==true) {
                cout << "Error: Enter in a number";
                return 0;
            }
            else {
                tempYear = year; // tempYear is used so it can alter the value of year for the equations
                century = tempYear/100; // but at the end output, the year can be neatly outputted
                tempYear = tempYear - (century*100); // This will get the last 2 digits of the year given
                if(month == 1 || month == 2) {
                    if(tempYear = 0) { // this is the case if it's January or February is century is 99
                        century -= 1;
                        dow = (day+(month*(month+1))/5+(tempYear-1)+((tempYear-1)/4)+(century/4)+5*century)%7;
                    }
                    else { //this is the case for months of January and February, but not the century 99
                        dow = (day+(month*(month+1))/5+(tempYear-1)+((tempYear-1)/4)+(century/4)+5*century)%7;
                    }
                }
                else { //this is the case for all months other than January and February
                    dow = (day+(month*(month+1))/5+(tempYear)+((tempYear)/4)+(century/4)+5*century)%7;
                }
                switch (dow) { //depending on the number given, it will give a corresponding day
                case 0:     //of the week
                    dayOfTheWeek = "Saturday";
                    break;
                case 1:
                    dayOfTheWeek = "Sunday";
                    break;
                case 2:
                    dayOfTheWeek = "Monday";
                    break;
                case 3:
                    dayOfTheWeek = "Tuesday";
                    break;
                case 4:
                    dayOfTheWeek = "Wednesday";
                    break;
                case 5:
                    dayOfTheWeek = "Thursday";
                    break;
                case 6:
                    dayOfTheWeek = "Friday";
                    break;
                }
                cout << endl << dayOfTheWeek << ", " << monthName << " " << day << ", "
                     << year << endl;
                // the final output is the day of the week, month, day, and year
                // all neatly outputted to the screen
            }
        }
    }
}
