/// @note Thien Nguyen revision on 3/17/2022
/* 

    This program takes 2 text files, one for airplane locations and one
    for airport locations. It will then calculate the euclidean distance and
    go through different equations where it will calculate the time a plane
    will reach a certain destination.

    The expected input is the names of the text files.

    The expected output is the output file with the times of the planes till they arrive.
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]) {
    int x1, x2, y1, y2;
    ofstream oFile;
    ifstream iFile, iFile2;
    char yN = 'y', planeType;                               // preset yN to yes so it runs
    double eucDist, totalhour, day, hour, min, sec, speed;
    string airplaneFile, airportFile, outputFileName, planeName, destination, destination2;
    for (int i = 1; yN == 'y' || yN == 'Y'; i++ ) {
        cout << "\nPlease enter airplanes file: ";
        cin >> airplaneFile;
        while (airplaneFile != "AirplaneLocations.txt" && airplaneFile != "MoreAirplaneLocations.txt") 
        {
            cout << "Please enter airplanes file: ";
                    cin >> airplaneFile;
        }
            cout <<"\nPlease enter airports file: ";
                    cin >> airportFile;
        while (airportFile != "AirportLocations.txt") 
        {
            cout << "Please enter airports file: ";
                    cin >> airportFile;
        }
        // i is saved as an int so needs
        // to convert to string
        outputFileName = "output_" + to_string(i) + ".txt"; 
        iFile.open(airplaneFile.c_str());
        iFile2.open(airportFile.c_str());
        oFile.open(outputFileName.c_str());

        // checks for eofs through the 
        // loop and will break if so
        while (!iFile.eof()) { 
            iFile >> x1;
            if (iFile.eof()) {
                break;
            }
            iFile >> y1;
            if (iFile.eof()) {
                break;
            }
            iFile >> planeName;
            if (iFile.eof()) {
                break;
            }
            iFile >> planeType;
            if (iFile.eof()) {
                break;
            }
            iFile >> destination;
            if (iFile.eof()) {
                break;
            }
            // inner loop will find the x2 and y2 
            // values to compare for the euclidean distance
            do { 
                iFile2 >> x2;
                if (iFile2.eof()) {
                    break;
                }
                iFile2 >> y2;
                if (iFile2.eof()) {
                    break;
                }
                iFile2 >> destination2;
                if (iFile2.eof()) {
                    break;
                }
            } while(destination != destination2);
            iFile2.clear();
            iFile2.seekg(0, iFile2.beg);
            eucDist = sqrt(pow(x2-x1,2)+pow(y2-y1,2));

            // speed changes according to the class type
            if (planeType == 'A') { 
                speed = 575;
            }
            else if (planeType == 'L') {
                speed = 90;
            }
            else if (planeType == 'P') {
                speed = 35;
            }
            else if (planeType == 'R') {
                speed = 200;
            }
            else if (planeType == 'W') {
                speed = 75;
            }
            totalhour = 0; // preset all values to 0
            day = 0;
            hour = 0;
            min = 0;
            sec = 0;
            totalhour = eucDist/speed;
            if (totalhour >= 24) {
                day =  static_cast<int>(totalhour / 24); 
                totalhour -= day*24;                    
            }                                           
            if (totalhour >= 1) {
                hour = static_cast<int>(totalhour / 1);
                totalhour -= hour;
            }

            min = static_cast<int>(totalhour * 60);
            totalhour -= min/60;

            sec = static_cast<int>(totalhour * 3600);
            totalhour -= sec/3600;

            oFile << planeName << " arrives at " << destination << " in ";
            if (day != 0) {
                oFile << day << " day(s) ";
            }
            if (hour != 0) {
                oFile << hour << " hour(s) ";
            }
            if (min != 0) {
                oFile << min << " minute(s) ";
            }
            if (sec != 0) {
                oFile << sec << " second(s)\n";
            }
        }

        cout << "\nOk, results are written into " << outputFileName
             << "\n\nDo you wish to continue? (Y/N): ";
        
                            cin >> yN;

        while (yN != 'y' && yN != 'Y' && yN != 'n' && yN != 'N') {
            cout << "Do you wish to continue? (Y/N): ";
                            cin >> yN;
        }
    }
    iFile.close(); 
    iFile2.close();
    oFile.close();
    cout << "Great, all flight times are scheduled! Good day!\n";
}
