/// @note Thien Nguyen revision on 3/17/2022
/* 
    This program has 2 void functions that have their own purposes, showHeader
    will display a header of the data base, and getQuery will get a query from the user
    and return it to the passed string, and they get called into main.

    Expected input: The string for getQuery.

    Expected output: The header display and the string inputted from the user.
*/

// include libs
#include <iostream>
#include <string>

using namespace std;

void showHeader() 
{ 
    cout << "+---------------------------------------------------------------------+\n"
         << "|   __   __  _______  _______  _     _    _______  _______  ___       |\n"
         << "|  |  |_|  ||       ||       || | _ | |  |       ||       ||   |      |\n"
         << "|  |       ||    ___||   _   || || || |  |  _____||   _   ||   |      |\n"
         << "|  |       ||   |___ |  | |  ||       |  | |_____ |  | |  ||   |      |\n"
         << "|  |       ||    ___||  |_|  ||       |  |_____  ||  |_|  ||   |___   |\n"
         << "|  | ||_|| ||   |___ |       ||   _   |   _____| ||      | |       |  |\n"
         << "|  |_|   |_||_______||_______||__| |__|  |_______||____||_||_______|  |\n"
         << "|                                                               v0.1.0|\n"
         << "+---------------------------------------------------------------------+\n";
}

// string needs to be passed in to change the value of it
// uses getline because it will take all the whitespaces as well
void getQuery(string& str) { 
    while (str != "exit" && str != "EXIT") 
    {
        cout << "> ";
        getline(cin, str);  

        // if wrong input, set str back to empty
        if (cin.fail() == true) { str = ""; }

        // any input beside the conditions?
        if (str != "exit" && str != "EXIT") { cout << "The entered query was: " << str << endl; }
    }
}

int main() {
    string str; 
    showHeader(); 
    getQuery(str);
    cout << "Thanks for using this, idk what to it with life anymore bro...\nGoodbye...\n";
}
