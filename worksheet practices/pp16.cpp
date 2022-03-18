/// @note Thien Nguyen revision on 3/17/2022, example of overloading function
/* 
    This program prompts the user to enter 'i' or 'I' for Integers
    or 's' or 'S' for strings, then depending on their input, it will go to
    the function larger overloaded for either integers or strings, and execute
    the code there.

    The expected input is the option for strings or integers, as well as 2
    of the option they choose.

    The expected output is larger of the 2 inputs they input.
*/

#include <iostream>

using namespace std;

// overloads function larger for integers
void larger (int a, int b) { 
    // passes int a and b from main
    cout << "Largest integer "; 
    if (a > b) {
        cout << a << endl;
    }
    else {
        cout << b << endl;
    }
}

// overloading function larger for strings
void larger (string a1, string b1) { 
    // passes string a1 and b1 from main
    cout << "Largest string "; 
    if (a1 > b1) {
        cout << a1 << endl;
    }
    else {
        cout << b1 << endl;
    }
}

int main() {
    // declare a, b, a1, and b1 in main to use in the functions
    int a, b; 
    string a1, b1;
    char result;

    cout << "Please select i/I/S/s: ";
    cin >> result;

    if (result == 'i' || result == 'I') {
        cout << "Please enter two integers:\n";
        cin >> a >> b;
        // calls larger function for ints
        larger(a, b); 
    } else if (result == 's' || result == 'S') {
        cout << "Please enter two strings:\n";
        cin >> a1 >> b1;
        // calls larger function for strings
        larger(a1, b1); 
    }

    return 0;
}
