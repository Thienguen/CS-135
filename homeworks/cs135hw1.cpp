/*
This program outputs an excerpt from the Constituion and Bill of Rights.
There is nothing to be inputed into this program.
The output is the  specific excerpt from the Constitution and the Bill of Rights provided by our instructor.
*/

#include <iostream> //This stands for Input Output streams, which allows the program to run input and output function.
using namespace std; //Allows the program to use classes or functions from the namespace "std", that way we don't have to type the prefix each time.

int main() 
{ 
    //The beginning of our program
    cout << "********************************************************************************\n";  //cout allows me to output characters,
    cout << "We the People of the United States, in Order to form a more perfect Union,     *\n";  //and this is done for the whole program
    cout << "establish Justice, insure domestic Tranquility, provide for the common defence,\n";
    cout << "promote the general Welfare, and secure the Blessings of Liberty to ourselves\n";
    cout << "and our Posterity, do ordain and establish this Constitution for the\n";
    cout << "United States of America.\n\n";

    cout << "Article. I.\n" << "Section. 1.\n\n"; //To save some line space, for the lines of text that were short,
    //I combined it with the next line of text. I did this a few times throughout the program.

    cout << "All legislative Powers herein granted shall be vested in a \n";
    cout << "Congress of the United States, which shall consist of a \n";
    cout << "Senate and House of Representatives.\n";
    cout << "...\n" << "Article. VII.\n\n";

    cout << "The Ratification of the Conventions of nine States, shall be sufficient\n";
    cout << "for the Establishment of this Constitution between the States\n";
    cout << "so ratifying the Same.\n\n";
    cout << "The U.S. Bill of Rights\n\n" << "Amendment I\n\n";

    cout << "Congress shall make no law respecting an establishment of religion,\n";
    cout << "or prohibiting the free exercise thereof; or abridging the freedom of speech,\n";
    cout << "or of the press; or the right of the people peaceably to assemble, \n";
    cout << "and to petition the Government for a redress of grievances.\n\n" << "Ammendment II\n\n";

    cout << "A well regulated Militia, being necessary to the security of a free State,\n";
    cout << "the right of the people to keep and bear Arms, shall not be infringed.         *\n";
    cout << "********************************************************************************";
    cout << 1+1;

    return 0; // Indicates that program runs successfully
}
