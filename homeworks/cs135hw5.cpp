/// @note Revision on 3/18/2022
//  * Description: This program takes the user through 3 different minigames
//                 utilizing loop functions, the first one takes the user's
//                 guess of a number between 1 - 10 until he/she types in
//                 the same number that was randomly generated, the second one
//                 asks the user to input a word, and the amount of times to
//                 repeat it, and it will do just that, and the last one
//                 works as the pow() function using loops.
//  * Input: The expected input of this function is the user's input of choice
//           for what the different minigames ask for.
//  * Output: The expected output is the what the user's input results to
//            after being ran through the various functions the minigames
//            incorporate.

// include libs
#include <iostream>
#include <string>
#include <time.h>    //For Time
#include <stdlib.h>  //For srand

using namespace std;
/*
/// ------------------------------------------------------------------------
/// ------------------------------------------------------------------------
                            User-defined fucntions
/// ------------------------------------------------------------------------
/// ------------------------------------------------------------------------
*/
void guessAnumber(int s) 
{
    int    random = rand() % s + 1;    // random number in range [1 to s]
    int    guess  = 0;
    
    bool   done   = false;
    string error;

    cout << "Guess a Number between 1 and " << s << endl;

    while(guess != random) {      
        //This error checks if the user input is not
        if (cin.fail()) {          
            // an integer, that way it wont have an
            cin.clear();          
            // infinite loop if user input is the wrong
            getline(cin, error); 
        }
                            cin >> guess;
        //If the guess the user inputs is the same, it'll move on to the next part
        if (guess == random) { cout << "The Force is strong with this one! You win!\n";}
            else { cout << "The force is not with you. Try Again!\n"; }
    }
}

void repeatWord()
{
    int repeats;
    string word;
    
    // input phase
    cout << "Enter a Single word to repeat: ";
    cin  >> word;

    cout << "\nEnter How many times to repeat: ";
    cin  >> repeats;

    // int i is a counter just to determine
    for(int i = 0; i < repeats ; i++) { cout << word << endl; }   
    
    cout << "Done repeating word " << repeats << " times!" << endl;
}

void mypow() {
    // variable declaraitoisn
    // then why declared it as float??? - line 89 just confused me
    float base;
    float exponent;
    float answer = 1;

    // Your Code Here
    cout << "My Power Function!\n" << "Enter base number: ";
    cin  >> base;

    cout << "Enter exponent: ";
    cin  >> exponent;

    //The condition of this for loop casts
    for(int i = 0 ;(i < int(exponent) || i < int(-exponent)); i++) { answer = answer * int(base); }
                    // the values for exponent and base to
                    // integers in order to prevent decimals
    // and it also makes sure positive and negative numbers that the the for loop will run with both
    if ((base > 0 && exponent > 0) || (base < 0 && exponent > 0)) { cout << "The answer is: " << answer << endl; }   

    else if (base > 0 && exponent < 0)   { cout << "The answer is: 1/" << answer << endl; }                                                                

    else if (base < 0 && exponent < 0)   { cout << "The answer is: -1/" << -answer << endl; }

    else if (base == 0 && exponent > 0)  { cout << "The answer is 0" << endl; }
    
    else if (base == 0 && exponent <= 0) { cout << "The answer is UND" << endl; }

    else if (base > 0 && exponent == 0)  { cout << "The answer is 1" << endl; }
    
    else if (base < 0 && exponent == 0)  { cout << "The answer is -1" << endl; }
}

int main(int argc, char *argv[]) {
    
    srand(time(NULL)); guessAnumber(10); repeatWord(); mypow();

    cout << "Thanks for playing, Goodbye!" << endl;

    // return to the OS 
    return 0;
}
