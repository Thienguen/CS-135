/// @note Thien Nguyen revision on 3/17/2022
/* 
    This program reads into a text file containing a bunch of double variable
    numbers, and then saves them into an array, to where it then calculates
    the average of those numbers.

    The expected input: N/A.

    The expected output is the average of the numbers in the list.
*/
#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
    // declare array at 100 b/c there is
    // no more than 100 values in the file
    double array1 [100] = {}, average = 0; 
    ifstream fin;                         
    int i = 0;
    int x = 0;

    fin.open("wksheet17.txt");
    // checks if file is open and if not will output
    if (fin.is_open() == false) 
    { 
        // an error message
        cout << "Error: File not open\n"; 
        return 0;
    } else {
        while (fin.eof() == false) 
        {
            // reads into all the doubles in the file
            fin >> array1[i]; 
            if (fin.eof()) { break; }
            i++;
        }
        while (x<i) 
        {
            // will grab the sum of all the numbers
            average += array1[x]; 
            x++;
        }
        average = (average / i); 
        cout << "Average is " << average << endl;
    }
}
