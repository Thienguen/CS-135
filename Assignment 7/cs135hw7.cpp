/// @paragraph Thien Nguyen 2001904928@student.csn.edu
/// Revised ths assignment on 3/16/2022 
/// it was 3 in the morning, send nud, I mean help

/// It was a fun assignment, just a lot of revision 
/*
  Description: This program loads up a text file containing shapes, and their size
               and character. Then it creates an output textfiles for each of contents
               inside the input file (AS7Data.txt), and names them with the shape and the
               size. Those output textfiles will contain a picture of that shape with the
               given size and the given character.
  Input: The expected input of the program is just the name of the text file
         containing the contents, (AS7Data.txt)
  Output: The output is gonna be textfiles containing a picture of the shapes
          that were provided by the input text file and their corresponding
          size and character.
*/

// include libs
#include <iostream>
#include <fstream>
#include <iomanip>

// this is horrible, please don't hate me
using namespace std;

// function prototyoe
void openInputFile( ifstream&, string, string="");

bool openOutputFile( ofstream & oFile, string fname);

void outputChar( ofstream&, int count, char l);

void makeArrow( ofstream& oFile, int size, char c );

void makeBracket( ofstream& oFile, int size, char c );

void makeTheta( ofstream& oFile, int size, char c );

bool readRecord( ifstream& iFile, string& typeString, int& lSize, char& c );

string createOutputFilename( string typeString, int labelSize );

// parameter is file containing specification
// we take in exactly 1 argument as ASData7.txt, only
int main(int argc, char* argv[]) 
{
    // variable declartion(s)
    ifstream  iFile;                //
    ofstream  oFile;                //

    string    ofName;               //
    string    typeString;           //
    string    passedString;         //

    int       labelSize    = 0;     //
    int       recordCount  = 0;     //

    char      labelChar    = 0;     //
    bool      done         = false; //
    
    // welcome message
    cout << setw(50) <<  "\n\nWelcome to Arrakis Computational Support\n" << endl;

    // our specifications
    if( argc > 1 ) { passedString = argv[1]; }

    // Open input file
    openInputFile( iFile, "Input Specification File: ", passedString );

    // read a record from the specification file.
    while(true) {

        // read a record from the file
        done = readRecord ( iFile, typeString,  labelSize, labelChar );

        // verify that it worked, if not exit.
        if ( !done ) 
        {

            cout << "Finished processing input file"  << endl;
            cout << recordCount << " Shapes Created " << endl;
            
            /// @note  I belive open file on line 59, then read or
            ///        rather perform the function on line 65
                iFile.close();
                oFile.close();

            exit(0);
        }

        // counting our record for ...
        recordCount++;

        // create the output filename
        ofName = createOutputFilename( typeString, labelSize );

        // open output file
        if( !openOutputFile( oFile, ofName )) {
            cout << "Output file \"" << ofName << "\" did not open"  << endl;
            cout << "File \""        << ofName << "\" not generated" << endl;
        } else {
            cout << "File \""        << ofName << "\" -----successfully opened\n";

            if ( typeString == "arrow")         { makeArrow( oFile, labelSize, labelChar ); }
            else if (typeString == "theta")     { makeTheta( oFile, labelSize, labelChar); }
            else if ( typeString == "bracket")  { makeBracket( oFile, labelSize, labelChar ); }
        }
        // close the shape file so that we can re-use oFile variable
        oFile.close();
    }
}

/* **********************************************
    function_identifier: this function reads into the text file for all the
                         strings, integers, and characters, and it will
                         continue until it reaches the end of the file.
    parameters: the input filestream, strings, integers, and characters
    return value: false or true
*********************************************** */
bool readRecord ( ifstream& iFile, string& typeString,
                  int& lSize, char& c ) {
    /// @note check ASData7.txt to see input format
    iFile >> typeString;
    iFile >> lSize;
    iFile >> c;

    // prtty obvious
    if(iFile.eof()) { return false; } else { return true; }
}

/* ****************************************************************
    function_identifier: this function creates the output file name
    parameters: strings and integers
    return value: the string output
* *****************************************************************/
string createOutputFilename(  string typeString, int labelSize ) {
    string output = typeString + "_" + to_string(labelSize) + ".txt";
    return output;
}

/* ***********************************************************
    function_identifier: this function opens the text file once the user
                         inputs the correct text file, and if they don't
                         put in the right text file it will display an
                         error message and have it prompt up again
                         until they do
    parameters: the input file,
    return value: none
**************************************************************/
void openInputFile( ifstream& iFile, string prompt, string name ) {
    cout << prompt;
    cin  >> name;
    while(name != "AS7Data.txt") {
        cout << "Error - \"" << name << "\" did not open. Try again \n";
        cout << prompt;
        cin >> name;
    }

    // if correct, open here baby
    iFile.open("AS7Data.txt");
}

/* *******************************************************
    function_identifier: this function opens up the output file
    parameters: the output filestream and the string of the filename
    return value: true or false
* *******************************************************/
bool openOutputFile( ofstream & oFile, string fname) {
    
    // std lib, open function does it job, open the file 
    // we going to write/ overwritten in
                    oFile.open(fname);

    // pretty obvious
    if(oFile.is_open()) { return true; } else { return false; }
}

/* ***************************************************
    function_identifier: the function outputs a picture of an Arrow
                         with the corresponding size and character it's
                         given in the text file.
    parameters: the output filestream, integer for size, and character
                the shape will be made out of
    return value: none

Algorithm
    The algorithm is to start by prompting the details of the shape, then if
    the size of the symbol is even it'll prompt the text saying the width
    will be reduced by 1, but if not it will just automatically continue
    to draw out the top column of numbers. Afterwards, the the side column
    is drawn out at the same time as each line of the shape is drawn. The
    arrow is drawn first by detecting when it'll reaches half of width,
    to which it will then increment the amount of spaces and characters on
    each line by 1. Once it reaches half, it will start to decrement
    the spaces and characters on each line by 1 to mirror the top half.
    It will also check if the size is even or not, and if it is it will
    draw 2 middle lines, and if not, it will start decrementing immediately
    after one middle line.
*/

void makeArrow( ofstream& oFile, int size, char c ) {
    int width      = size;
    int ruler      = 1;
    int topNumbers = 1;
    int oneThruTen = 0;
    int spaceCount = 0;
    int charCount  = 1;

    oFile << "Symbol: Arrow "
          << "Size: "        << size
          << " Character:  " << c << "'" << endl;
    
    // setting the width 
    if (size % 2 == 0) { width -= 1; oFile << "Note: Symbol size is even, width will be size-1: " << width << endl; }

    // cout top number from 0 to 9 and repeat, idk why tbh
    oFile << setw(4);
    while(oneThruTen < width) 
    {   //Top Column
        if(topNumbers > 9) { topNumbers = 0; }

        // eg: 12345678901234
        oFile << topNumbers;

        // rep[eat]
        topNumbers++;
        oneThruTen++;
    }

    // the first half arrow we getting is from this block of code
    oFile << endl;

    // half topping
    for (int i = 0; i <= width / 2; i++) 
    {   //Checks when the arrow reaches half
        oFile << right << setw(2) << ruler << " ";

        //Increments spaces outputted until half
        for (int k = 0; k < spaceCount; k++) { oFile << " "; }

        //Increments characters outputted until half
        for (int l = 0; l < charCount; l++) { oFile << c; }

        // add up but only half, all we want is 
        // half space, half arrow (char), check line 263-265
        spaceCount++;
         charCount++;
             ruler++;

        // extra line
        oFile << endl;
    }

    // since we did post-increment on line 235 and line 236
    // they +1 after we finish the file/ before exit the loop
        spaceCount--;       // takes off the extra increment from Space and
         charCount--;        // char count from the post increment on the last loop

    // if it's an even size, it'll repeat the last line of the first half
    // this is the other half we were doing
    if (size % 2 == 0) 
    {
        for(int i = 0; i <= width / 2; i++)
        {
            oFile << right << setw(2) << ruler << " ";
            
            for(int k = 0; k < spaceCount; k++) { oFile << " "; }

            for(int l=0; l < charCount; l++) { oFile << c; }

            // we did half top, this half bottom, in reverse sorta order
            spaceCount--;
             charCount--;
                 ruler++;
            
            // extra line
            oFile << endl;
        }
    } else if (size % 2 == 1) 
        {   // if it's an odd size, it will immediately start decremeting
            // not ruler since it's an odd unmber (I believe so)
            spaceCount--;
            charCount--;
            
            // just another loop, depends on the size we do be given
            for(int i = 0; i < width / 2; i++) 
            {   // ruler is the number line we are printing, it gets bigger
                // over time and size
                oFile << right << setw(2) << ruler << " ";

                // same old technique and arrow, but this for print space
                for(int k = 0; k < spaceCount; k++) { oFile << " "; }

                // tis for print the symbol
                for(int l = 0; l < charCount; l++) { oFile << c; }

                // return them to stable state
                spaceCount--;
                 charCount--;
                     ruler++;

                // extra space
                oFile << endl;
            }
        }
}

/* *******************************************************************
    function_identifier: this function outputs a picture of a bracket with
                         a corresponding size and character given by the
                         input text file
    parameters: the output filestream, the integer for the size, and
                the character it's given in the text file
    return value: none

Algorithm
    Similarly to the arrow, it has the same algorithm to output the details
    of the shape, then output the top column, and output the side column
    alonside each line of the shape. The algortihm to make the bracket was
    to first draw out the top rectangle of bracket, then the middle one,
    then the bottom one.
*/

void makeBracket( ofstream& oFile, int size, char c ) {
    // variable declarations(s)
    int width        = size / 2;
    int bracketWidth = size / 10;
    int ruler        = 1;
    int oneThruTen   = 0;
    int topNumbers   = 1;
    int sideRuler    = size - 2*bracketWidth;

    // output the file, after receiving our input
    // eg: Symbol: Bracket Size: 29 Width: 14 Character: '&'
    oFile << "Symbol: Bracket "
          << "Size: "        << size
          << " Width: "      << width
          << " Character: '" << c << "'" << endl;

    // setting format for the topnumber don't ask
    oFile << setw(4);

    // me idkw this being written as topnumber as well
    while (oneThruTen < width) 
    {   // Top Ruler
        if (topNumbers > 9) { topNumbers = 0; }

        // eg: 12345678901234
        oFile << topNumbers;

        // incrementing bing bing chilling
        topNumbers++;
        oneThruTen++;
    }

    // extra space
    oFile << endl;

    // Min has to be 1
    if (bracketWidth < 1) { bracketWidth = 1; }

    //  eg:  1 &&&&&&&&&&&&&&
    //       2 &&&&&&&&&&&&&&
    for (int i = 1; i <= bracketWidth; i++) 
    {
        // Top part of ruler column on the side
        oFile << right << setw(2) << ruler << " ";  

        // Top part of bracket
        for (int j = 1; j <= width; j++) { oFile << c; }
        
        // newline so we go to ruler
        oFile << endl;
        
        // ruler increment go go go
        ruler++;
    }

    // side symbol ruler, the without density
    for (int i = 1; i <= sideRuler; i++) 
    {
        // still side number ruler
        oFile << right << setw(2) << ruler << " ";

        // the body loop
        for (int j = 1; j <= width; j++) 
        {
            // the empty space loop
            while(j <= width - bracketWidth) { oFile << " "; j++; }

            // finally, the symbol
            oFile << c;
        }

        // increment ruler for our legs part

        ruler++;
        oFile << endl;
    }

    //  eg:  28 &&&&&&&&&&&&&&
    //       29 &&&&&&&&&&&&&&    
    for (int i = 1; i <= bracketWidth; i++) 
    {
         //Bottom part of ruler column on the side
        oFile << right << setw(2) << ruler << " ";

        //Bottom part of bracket
        for (int j = 1; j <= width; j++) { oFile << c; }
        
        //endl file
        oFile << endl;
        ruler++;
    }
}


/* *************************************************************
    function_identifier: this function outputs a picture of a theta symbol
                         with the corresponding size and text given in the
                         input text file.
    parameters: the output text file, the integer for size, and character
                it's given in the text file
    return value: none

Algorithm
    Like the arrow and the bracket, it begins by prompting the details
    of the shape. Then proceeds to draw out the top column, and then
    the side column alongside each line of the shape being drawn.
    The algorithm the draw the theta was to first draw the top line
    which is always 3 characters in the middle of the width, then draw
    the lines going down towards the middle by decrasing the spaces outside
    the characters and icnrasing the spaces inside the characters, then draw
    the lines in the middle, then draw the lines going down towards the bottom
    line by increasing the spaces outside the characters and decreasing the
    spaces inside the characters, then finally drawing the last line which,
    like the top line, is just 3 characters in the middle of the width.
 **************************************************************/

void makeTheta( ofstream& oFile, int size, char c ) {
    int oneThruTen  = 0;
    int topNumbers  = 1;
    int spaceCount  = 0;
    int insideSpace = 3;
    int ruler       = 1;

    // header, eg: Symbol: Theta Size: 25 Character: '*'
    oFile << "Symbol: Theta " << "Size: " << size << " Character: '" << c << "'" << endl;

    // first half of the diagram
    if (size % 2 == 0) { size += 1; oFile << "Symbol size must be odd, size is " << size << endl; }

    spaceCount = size / 2;

    // setw for our diagram
    oFile << setw(4);

    // top Ruler
    while(oneThruTen < size) 
    { 
        // i still idkw we need o print 0 - 9 range
        if (topNumbers > 9) {topNumbers = 0; }

        // eg: 1234567890123456789012345
        oFile << topNumbers;

        // increment gog o go 
        topNumbers++;
        oneThruTen++;
    }

    // new line and set width again, with the ruler start from 1 now
    oFile << endl;
    oFile << right << setw(2) << ruler << " ";

    // the first line this loop print space
    for (int j = 1; j < spaceCount; j++) { oFile << " "; }

    // this loop print the symbol
    for (int j = 0; j < 3; j++) { oFile << c; }

    // post-increment, since we have taht damn symbol line 
    ruler++;

    // new line
    oFile << endl;

    // this loop print the first half, size need to deduct by 1, see line 484
    // line 3 theeta_25.txt is what we just did above
    // now, before te line
    for (int i = 0; i < (size / 2) - 1; i++ ) 
    {
        // the ruler line
        oFile << right << setw(2) << ruler << " ";

        // this print the space, before the first symbol
        for(int j = 1; j < spaceCount - 1; j++) { oFile << " "; }

        // see theta_25.txt line 14, 15 and so on
        spaceCount--;

        // print the symbol out, yes
        oFile << c;

        // this loop print the inside space, before the last symbol
        for (int j = 0; j < insideSpace; j++) { oFile << " "; }
        
        // faster pace
        insideSpace += 2;

        // the final symbol
        oFile << c;

        // increase our ruler line
        ruler++;

        // new line
        oFile << endl;
    }

    // print out our ruler line
    oFile << right << setw(2) << ruler << " ";

    // this loop print out the long cut between two half
    // eg: 13 *************************
    for (int i = 0; i < size; i++) { oFile << c; }

        // increment our ruler line
        ruler++;

        // newline
        oFile << endl;

        // leave our bottom half stable before it goes out of range
        spaceCount   = 1;
        insideSpace -= 2;

    /// @note
    /// this print actual bottom half
    for (int i = 0; i < (size / 2) - 1; i++ ) 
    {
        // the ruler line
        oFile << right << setw(2) << ruler << " ";

        // the space before the first symbol
        for(int j=1; j < spaceCount; j++) { oFile << " "; }

        // leave it to our range
        spaceCount++;

        // the first symbol
        oFile << c;

        // the inside space, before the secpnd symbol
        for (int j = 0; j < insideSpace; j++) { oFile << " "; }
        // faster pace
        insideSpace-=2;

        // the final symbol
        oFile << c;

        // our next ruler incremented
        ruler++;

        // newline
        oFile << endl;
    }

    // print out the ruler line
    oFile << right << setw(2) << ruler << " ";

    // the final line of paragram
    for (int j=1; j < spaceCount; j++) { oFile << " "; }

    // the stars *** at the end
    for (int j = 0; j < 3; j++) { oFile << c; }

    // new line
    oFile << endl;
}


/// @note Input file: AS7Data.txt
