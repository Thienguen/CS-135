/// @note Thien Nguyen revision on 3/17/2022
/* 
     This program takes in various lengths of a triangle from a text file
     and then calculates the area of triangles in 4 different ways, then outputs
     those values at the very end in a neat matter.

     The exptected input of the program is the values of what it's asking
     of the triangle.

     The expected output is the the 4 different calculated areas
*/
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() 
{ 
     // All the variable names of what's being called
     const  double pi = 3.14159265;
     double sideLength, base, height, sl1, sl2, sl3, sla1, sla2, angle;
     double equilateral;
     double baseHeight;
     double s;
     double threeSides;
     double radians;
     double sideLengthAngle;

    // start from here
     cout << "\nCS135 Lab 3\n"
          << "\nTRIANGLE AREAS\n"
          << "\nEquilateral Triangle\n"
          << "\nEnter the side length(ft) of your triangle\n** : ";
      cin >> sideLength;

     cout << "\nWith Base/Height Given\n"
          << "\nEnter the base length(ft) of your triangle\n** : ";
      cin >> base;

     cout <<"\nEnter the height length(ft) of your triangle\n** : ";
      cin >> height;

     cout << "\nWith 3 Side Lengths Given\n"
          << "\nEnter the first side length(ft) of your triangle\n** : ";
      cin >> sl1;

     cout << "\nEnter the second side length(ft) of your triangle\n** : ";
      cin >> sl2;

     cout << "\nEnter the third side length(ft) of your triangle\n** : ";
      cin >> sl3;

     cout << "\nWith Side Lengths and The Angle Between Them Given\n"
          << "\nEnter the first side length(ft) of your triangle\n** : ";
      cin >> sla1;

     cout << "\nEnter the second side length(ft) of your triangle\n** : ";
      cin >> sla2;

     cout << "\nEnter the angle(degrees) between the 2 sides\n** : ";
      cin >> angle;

     equilateral     = (pow(sideLength, 2) * sqrt(3)) / 4;        // the equations that the
     baseHeight      = (base / 2) * height;                       // values are put through
     s               = (sl1 / 2) + (sl2 / 2) + (sl3 / 2);         // after given a value
     threeSides      = (sqrt(s * (s - sl1) * (s - sl2) * (s - sl3)));
     radians         = (angle * (pi / 180));
     sideLengthAngle = (sla1 * sla2 * sin(radians)) / 2;

     cout << left 
          << setw(14) << "\nEquilateral | " 
          << setw(14) << "Base/Height |"
          << setw(10) << "3 Sides | " 
          << setw(15) << "2 Sides w/ Angle\n"
          << setw(14) << equilateral
          << setw(14) << baseHeight 
          << setw(10) << threeSides 
          << setw(15) << sideLengthAngle 
          << endl;
     
     // return to the OS
     return 0;
}
