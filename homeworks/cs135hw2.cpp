
/// @paragraph This program calculates the radius of a sand worm given the
/// beta & slant distance.

// The expected input of the program is the values for beta (in degrees)
// and the slant distance (in feet).

// The expected output of the program is the value of the radius given
// the values provided.

// incldue libs
#include <iostream>
#include <string>
#include <cmath> //gives the program access to sin(), sqrt(), & pow()
using namespace std;

int main() {
    double beta;
    const double pi    = 3.14159;
    double beta1       = 0.0;
    double alpha       = 0.0;
    double slantDist;
    double y           = 1.570795;
    double chordLength = 0.0;
    double radius      = 0.0;

    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
         << "Program to calculate a sandworm radius\n"
         << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";

    // recieves the input provided by user, and
    cout << "Enter beta in degrees: ";
    cin  >> beta;   
    
    //recieves the input provided by user, and
    cout << "Enter the slant distance (feet): ";
    cin  >> slantDist; 

    beta1 = (beta * pi) / 180;
    alpha = ((90 - (0.5 * beta)) * pi) / 180;
    chordLength = slantDist * (sin(beta1) / sin(alpha));
    radius = chordLength * (sin(y - alpha)) / sin(alpha * 2);
    /*
      What beta1 does is take the value that the user inputs for beta, and
      converts it into radians.
      You put the value into beta when it instructs you to (degrees),
      then this function will turn that value into radians
      in order to make the other calculations have the correct values.

      What alpha is doing is taking the formula for alpha(α) and converting
      it into radians.
      Once you put the value for beta, alpha takes that value and applies
      it to the formula for alpha, then converts it into radians.

      chordLength and radius just takes those newly acquired values, and
      applies them into the formula provided in the assignment.
    */
    cout << ">>>>>>>>>>>>>>>>>>>>>\n"
         << "Sandworm calculations:\n"
         << "Beta: " << beta << " degrees.\n"
         << "Slant distance: " << slantDist << " feet.\n"
         << "Radius: " << radius << " feet.\n";
    /*
      The rest of the program simply outputs the data that was provided,
      as well as the value of the radius which the program is meant
      to determine.
    */
    return 0;
}
