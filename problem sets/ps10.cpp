/// @note Thien Nguyen revision on 3/17/2022
/*
    This program accepts a series of command line arguments and parses them
    into options and values. It utilizes 2 functions to do these tasks.

    No expected input, its all in command line arguments.

    The expected output is the command line arguments parsed with options
    and values.
*/

#include <iostream>

using namespace std;

struct optionType {
    string option;
    string value;
    bool optionValid;
    bool valueValid;
};

bool getNextOption( int argc, char* argv[], optionType& opt );
void printCmdArgs( int argc, char * argv[]);

int main(int argc, char * argv[] ) {

    optionType myOptions;
    bool more = false;

    // print out the arguments as passed from Linux
    printCmdArgs( argc, argv );

    cout << endl;
    cout << "-------------------------" << endl;
    cout << "Parsed Options and Values" << endl;

    // process the arguments, one at a time.
    // loop repeats until more is set to false.
    do {
        more = getNextOption( argc, argv, myOptions);
        if ( myOptions.optionValid ) 
        {
            cout << "option: " << myOptions.option ;
            if ( myOptions.valueValid ) 
            {
                cout << " value: " << myOptions.value << endl; 
            } else { cout << endl; }
        }
    } while( more );
}

    // this function prints all command line arguments
void printCmdArgs( int argc, char * argv[]) { 
        // argc has to be atleast 1
    if(argc < 1) { 
        exit(0);
    }
    cout << "Raw argv from Linux\n"
         << "Command line argument count: " << argc;
        // runs through all the command line arguments and prints them
    for(int i = 0; i < argc; i++) { 
        cout << "\nArgc #" << i << " [" << argv[i] << "]";
    }
}

    // this function will evaluate each argument
bool getNextOption(int argc, char* argv[], optionType& opt  ) { 
    string tempString, tempString2;

    // starts at 1 because we dont need to check ./a.out
    static int counter = 1; 

    // saves the argument into a string
    tempString = argv[counter]; 

    // checks if the first character of the argument is a '-'
    if(tempString[0] == '-') { 
        // if its not, then it outputs and error saying its invalid
        opt.value = "";         
        opt.valueValid = false;
        // assigns the first character of string after the '-' to option
        opt.option = tempString[1]; 
        opt.optionValid = true;
        // will account for if the argument is only -(char)
        if(tempString.length() == 2) { 
            // if it is, then this will check if the next argument is supposed
            tempString2 = argv[counter + 1]; 
            // to be a new argument, or the value for the previous argument
            if (tempString2[0] != '-') {   
                opt.valueValid = true;
                opt.value = tempString2;
                counter++;
            }
        } else {
                // this allows us to get the rest of the string
            for(int j = 2; j < tempString.length(); j++) { 
                // and make it equal the value
                opt.valueValid = true;                    
                opt.value += tempString[j];
            }
        }
    } else {
        // have to set both to false because they might be set to true from the
        opt.valueValid = false; 
        // previous times the function was called
        opt.optionValid = false; 
        // if argument doesnt start with dash, it's invalid
        cout << "Error - invalid option " << tempString << endl; 
    }

                            counter++;

        // once the counter gets through all the arguments, it will end
    if (counter == argc) { return false; } else { return true; }
}
