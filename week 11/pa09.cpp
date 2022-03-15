/// @file pa09.cpp
/// @author Thien Nguyen thiennguyen@.csn.edu
/// @date 12/13/21
/// @note I pledge my word of honor that
///       I have abided by the the CSN Academic Integrity Policy
///       while completing this assignment.
///
/// @brief This assignment write a report of a year-end information
///        at a company has 50 full-time employees
/// @note People who helped: TA Sao Thao
/// @note This is but one possible solution to the assignment.
///       Programming techniques and commands in this solution
///       are aligned with the current and previous chapters,
///       labs, and lectures, which may result in a trade-off
///       between efficient coding and what student are
///       currently able to understand.


// include libs
#include <cmath>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <list>

// setting a namcespace scope
using namespace std;

// employee record
struct employee_t {
    string firstName = "";   // obtained from employee data file
    string lastName = "";    // obtained from employee data file
    int personID = 0;        // obtained from employee data file
    int deptID = 0;          // obtained from employee data file
    double salary = 0.0;     // obtained from employee data file
    double giving = 0.0;     // obtained from donations data file
};

// global constant
// SIZE is 50 employees of the company
const int SIZE = 50;
// away is the stadnard deduction 25k
const double away = 25000;

/// -----------------------------------------------------------------------
/// Function Prototypes
/// -----------------------------------------------------------------------

employee_t getEmployeeRecord(ifstream& fin);
double grossIncomeTax(double income, double donations);
double getTax(double prevTax, double perc, double income, double low);

void printReport(const employee_t list[]);
void printSave(employee_t list[], const string outputfile);

void printLine();
void printHeading();
void printHeading_Save(ofstream& outputfile);

void readEmployeeDonations(employee_t list[], const string& fn);
void readEmployeeData(employee_t list[], const string& fn);
void saveDonation2Employee(employee_t list[], int id, double donation);

void processData(const string inputDataFile,
                 const string inputDonationsFile);
void saveReport( const string inputDataFile,
                 const string inputDonationsFile, 
                 const string outputFile); 

/// -----------------------------------------------------------------------
/// Main entry-point for this application
///
/// @returns Exit-code for the process - 0 for success, else an error code.
/// -----------------------------------------------------------------------
            
            // int main(int argc, const char *argv[]) {
            //     // only need 3 argument at program name, employeeData.csv
            //     // and donations.csv
            //     if (argc == 3) {
            //         // if enough argument, process the data
            //         processData(argv[1], argv[2]);
            //     } else {
            //         // if not enough arguments
            //         cout << "Usage: " << argv[0] << " fileName.csv" << endl;
            //     }

            //     // return to the operating system
            //     return EXIT_SUCCESS;
            // }


int main() {

    const string input1 = "employeeData.csv";
    const string input2 = "donations.csv";

    const string output = "report.txt";

    saveReport(input1, input2, output);

}

/// -----------------------------------------------------------------------
/// Function Implementations
/// -----------------------------------------------------------------------
/// -----------------------------------------------------------------------
/// Reads the data from the files into the array of structures
///
/// @pre the array passed into the function must exist
///
/// @param inputDataFile is the employee data file name
/// @param inputDonationsFile is the donation file name
/// -----------------------------------------------------------------------
void processData(const string inputDataFile,
                 const string inputDonationsFile) {

    // create an empty employee data set
    employee_t employees[SIZE];

    // populate the data set with employee data
    readEmployeeData(employees, inputDataFile);

    // add employee donation information to the employee records
    readEmployeeDonations(employees, inputDonationsFile);

    // print the report
    printReport(employees);
}

/// -----------------------------------------------------------------------
/// Reads a single record from the employee data file
///
/// @pre the file must be open and pointing to a record
///
/// @param fin is the input streaming variable
/// @return the next employee record without donation information
/// -----------------------------------------------------------------------
employee_t getEmployeeRecord(ifstream& fin) {
    // delimeter
    const char DEL = ',';
    // create an object of structure employe_t
    employee_t record;

    // get full name of the employee
    getline(fin, record.firstName, DEL);

    // get last name
    getline(fin, record.lastName, DEL);

    // get the rest to the record
    fin >> record.personID;
    fin.ignore();
    fin >> record.deptID;
    fin.ignore();
    fin >> record.salary;
    fin.ignore(1, '\n');
    // ignore the \n at the end of every employee entry

    // return one record
    return record;
}


/// -----------------------------------------------------------------------
/// Reads the employee data file and populates the data set
/// without donations
///
/// @param [out] list is the array of employee records (structures)
/// @param fn of employee data file
/// -----------------------------------------------------------------------
void readEmployeeData(employee_t list[], const string& fn) {
            // const char DEL = ',';   // delimeter
            // ifstream fin;           // streaming variable
            // fin.open(fn);           // open the file
            // string heading[5];      // to store the heading

            // // or we could ignore the heading but
            // // I stored it just in case

            // if (fin.is_open()) {
            //     // get the heading out of the way
            //     for (int i = 0; i < 4; i++) {
            //         getline(fin, heading[i], DEL);
            //     }

            //     // the last piece of heading
            //     getline(fin, heading[4]);

            //     for (int i = 0; i < SIZE; i++) {
            //     }

            //     // run a loop to get 50 data set
            //     for (int i = 0; i < SIZE; i++) {
            //         list[i] = getEmployeeRecord(fin);
            //     }

            //     // flush the buffer
            //     fin.close();
            // }

    ifstream fin;

    fin.open(fn);
    if (fin.is_open()) {
        // ignore the heading line
        fin.ignore(255, '\n');
        for (int i = 0; i < SIZE; i++) {
            list[i] = getEmployeeRecord(fin);
        }
    } else {
        cout << "Data File isn't open" << endl;
    }

    fin.close();

}

/// -----------------------------------------------------------------------
/// Searches through the list of employees and places donation information
/// into the record
///
/// @param [out] list is the array of employee records
/// @param id is the employee id (used as a search key)
/// @param donation is the donation amount to place in the employee record
/// -----------------------------------------------------------------------
void saveDonation2Employee(employee_t list[], int id, double donation) {
    // search through the id match with the id we get from input
    for (int i = 0; i < SIZE; i++) {
        // if we found the same id
        if (list[i].personID == id) {
            // we assign it with the amount donation
            list[i].giving = donation;
        }
    }
}

/// -----------------------------------------------------------------------
/// Reads the donation file and places donation information into the
/// correct record of the employee data set
///
/// @param [out] list is the array of employee records
/// @param fn is the name of the file holding the donations
/// -----------------------------------------------------------------------
void readEmployeeDonations(employee_t list[], const string& fn) {
    ifstream fin;       // streaming variable
    fin.open(fn);       // open the file
    int id;             // to hold the value of id
    double donate;      // to hold the value of donation from input

    if (fin.is_open()) {
        // ignore the heading
        fin.ignore(255, '\n');

        // loop 50 times to get input from donation.csv
        for (int i = 0; i < SIZE; i++) {
            fin >> id;
            fin.ignore();
            fin >> donate;
            fin.ignore(1, '\n');
            // save to the exact
            saveDonation2Employee(list, id, donate);
        }
    } else {
        cout << "File is not OPEN!" << endl;
    }

    // we need to flush the buffer
    fin.close();
}


/// -----------------------------------------------------------------------
/// Helper function to grossIncomeTax that calculates tax owed to the IRS
///
/// @param prevTax is the tax collected from the previous bracket
/// @param perc is the percentage tax for the current bracket
/// @param income is the gross income
/// @param low is the lowest feduciary amount in the bracket range
/// @return tax owed
/// -----------------------------------------------------------------------
double getTax(double prevTax, double perc, double income, double low) {
    // formula to get the tax owed to the IRS
    return prevTax + (perc * (income - low));
}

/// -----------------------------------------------------------------------
/// Uses the IRS tax table and standard deductions to calculate
/// tax owed to the IRS
///
/// @param income is gross salary earned
/// @param donations is the tax deductable donations
/// @return tax owed
/// -----------------------------------------------------------------------
double grossIncomeTax(double income, double donations) {
    // variable declaraition
    double taxable;         // taxable income
    double tax_owed;        // the final answer [income tax]
    // standard deductions
    taxable = income - away - donations;

    // Tax table assuming the input is clean and there is no negative input
    if (taxable <= 9950 && taxable >= 0) {
        tax_owed = getTax(0, 0.1, taxable, 0);
    } else if (taxable <= 40525 && taxable >= 9951) {
        tax_owed = getTax(995, 0.12, taxable, 9950);
    } else if (taxable <= 86375 && taxable >= 40526) {
        tax_owed = getTax(4664, 0.22, taxable, 40525);
    } else if (taxable <= 164925 && taxable >= 86376) {
        tax_owed = getTax(14751, 0.24, taxable, 86375);
    } else if (taxable <= 209425 && taxable >= 164926) {
        tax_owed = getTax(33603, 0.32, taxable, 164925);
    } else if (taxable <= 523600 && taxable >= 209426) {
        tax_owed = getTax(47843, 0.35, taxable, 209425);
    } else {
        tax_owed = getTax(157804.25, 0.37, taxable, 523600);
    }

    // return the tax owed to the IRS
    return tax_owed;
}


/// -----------------------------------------------------------------------
/// prints a horizontal dashed line for the report
/// -----------------------------------------------------------------------
void printLine() {
    // print 79 dashes
    cout << string(79, '-');
}


/// -----------------------------------------------------------------------
/// prints the heading for the report
/// -----------------------------------------------------------------------
void printHeading() {
    // print the first line of headng
    cout << right;
    cout
            << setw(45) << "Gross"
            << setw(18) << "Income"
            << setw(8) << "Net"
            << setw(8) << "Income" << endl;

    // the second line
    cout << left
         << setw(7)  << " Name" << right
         << setw(15) << "ID"
         << setw(13) << "Dept"
         << setw(10) << "Salary"
         << setw(8)  << "Giving"
         << setw(10) << "Tax"
         << setw(8)  << "Salary"
         << setw(8)  << "Tax %";

    cout << endl;
}


/// -----------------------------------------------------------------------
/// prints the records in the report, calculating data as needed
/// -----------------------------------------------------------------------
void printReport(const employee_t list[]) {
    // variable delcaratiion
    double incometax = 0;       // income tax
    double netsalary = 0;       // to cal the net salary

    // print the heading
    printHeading();
    cout << endl;
    // print the ---- line
    printLine();
    cout << endl;
    // print the data of each employee and repeat it 50 times

    for (int i = 0; i < SIZE; i++) {

        // calculation
        incometax = grossIncomeTax(list[i].salary, list[i].giving);
        netsalary = list[i].salary - incometax;

        // print each of the compartments
        cout << left;
        cout << setw(19) << list[i].firstName + " " + list[i].lastName;

        cout    << right << setprecision(0) << fixed;
        cout
                << setw(10) << list[i].personID
                << setw(6)  << list[i].deptID
                << setw(10) << list[i].salary
                << setw(8)  << list[i].giving
                << setw(10) << round(incometax)
                << setw(8)  << netsalary
                << setw(8)  << round(100 - ((list[i].salary - incometax) /
                                            list[i].salary * 100))
                << endl;
    }
}



void printHeading_Save(const string& output) {
    
    ofstream fout;
    fout.open(output);

        // print the first line of headng
        fout << right;
        fout
                << setw(45) << "Gross"
                << setw(18) << "Income"
                << setw(8) << "Net"
                << setw(8) << "Income" << endl;

        // the second line
        fout << left
            << setw(7)  << " Name" << right
            << setw(15) << "ID"
            << setw(13) << "Dept"
            << setw(10) << "Salary"
            << setw(8)  << "Giving"
            << setw(10) << "Tax"
            << setw(8)  << "Salary"
            << setw(8)  << "Tax %";

        fout << endl;
        fout << string(79, '-');
        fout << endl;
        fout.close();
}





void saveReport(const string inputDataFile,
                const string inputDonationsFile, const string outputFile) {

    // create an empty employee data set
    employee_t employees[SIZE];

    // populate the data set with employee data
    readEmployeeData(employees, inputDataFile);

    // add employee donation information to the employee records
    readEmployeeDonations(employees, inputDonationsFile);

    printSave(employees, outputFile);
}

void printSave(employee_t list[], const string outputfile) {
    
    printHeading_Save(outputfile);

    ofstream fout;
    fout.open(outputfile);

    // variable delcaratiion
    double incometax = 0;       // income tax
    double netsalary = 0;       // to cal the net salary


    if (fout.is_open()) {
    // print the data of each employee and repeat it 50 times
        for (int i = 0; i < SIZE; i++) {

            // calculation
            incometax = grossIncomeTax(list[i].salary, list[i].giving);
            netsalary = list[i].salary - incometax;

            // print each of the compartments
            fout << left;
            fout << setw(19) << list[i].firstName + " " + list[i].lastName;

            fout    << right << setprecision(0) << fixed;
            fout
                    << setw(10) << list[i].personID
                    << setw(6)  << list[i].deptID
                    << setw(10) << list[i].salary
                    << setw(8)  << list[i].giving
                    << setw(10) << round(incometax)
                    << setw(8)  << netsalary
                    << setw(8)  << round(100 - ((list[i].salary - incometax) /
                                                list[i].salary * 100))
                    << endl;
        }

        fout << endl;
        fout.close(); 
    }
}

/*
SAMPLE INTERACTION
                                        Gross            Income     Net  Income
 Name              ID         Dept     Salary  Giving       Tax  Salary   Tax %
-------------------------------------------------------------------------------
Cara Hines         822668548  1006      95184    9518      9095   86089      10
Aleah Mccann       486229863  1002      55044    5504      2746   52298       5
Kiera Silva        963334433  1003      81948    8195      6474   75474       8
Paula Ball         953300891  1003     106536   10654     11343   95193      11
Aliana Ali         146897162  1000      72264    7226      4606   67658       6
Noemi Melendez     985884810  1005     110664   11066     12160   98504      11
Lily Farley        685256803  1005      40644    4064      1191   39453       3
Tyler Barnett      552026759  1005      68004    6800      4146   63858       6
Marcel Huber       611228167  1006      67248    6725      4064   63184       6
Janiah Hodge       632872144  1003     108624   10862     11756   96868      11
June Huber         317609995  1005      47580    4758      1940   45640       4
Kyla Avila         551834716  1000     640188   64019    168005  472183      26
Bianca Day         651393707  1005      83952    8395      6871   77081       8
Hailee Turner      918946452  1005      81936    8194      6472   75464       8
Lyla Bean          641385513  1003      99360    9936      9922   89438      10
Selena Beard       860400116  1005      43224    4322      1469   41755       3
Reagan Rivers      748597749  1005      44676    4468      1626   43050       4
Kristin Coffey     609089154  1004      47460    4746      1927   45533       4
Anna Cook          450441910  1006      94464    9446      8952   85512       9
Quinton Frank      458119667  1006     100752   10075     10197   90555      10
Aarav Sloan        816766736  1000      54132    5413      2647   51485       5
Ireland Vaughn     621172820  1004      69816    6982      4341   65475       6
Sebastian Decker   225748204  1002      64512    6451      3768   60744       6
Randall Solomon    477529455  1004     106800   10680     11395   95405      11
Adalyn Hendrix     688213620  1003      97848    9785      9622   88226      10
Yaretzi Trujillo   571629638  1005     105828   10583     11202   94626      11
Michaela Newman    306889471  1004      84612    8461      7002   77610       8
Morgan Nicholson   979714719  1004      75852    7585      5267   70585       7
Arianna Cooke      617980112  1003      58944    5894      3167   55777       5
Aliya Barrera      922922925  1000     117636   11764     13540  104096      12
Laylah Booker      138571710  1005      74472    7447      4994   69478       7
Carlo Hoover       569129703  1006      52248    5225      2444   49804       5
Donovan Spence     718944492  1001      43392    4339      1487   41905       3
Mckenzie Waters    616470223  1002      73788    7379      4858   68930       7
Adriana Lucas      233183215  1003      79188    7919      5928   73260       7
Deanna Benton      307772035  1000      43212    4321      1468   41744       3
Zaiden Hampton     439235114  1004      45204    4520      1683   43521       4
Reed Duffy         204435797  1002      50112    5011      2213   47899       4
Zackary Blackwell  340086211  1003      80196    8020      6127   74069       8
Lauren Gonzales    946638656  1000     204000   20400     43089  160911      21
Jason Pugh         506471355  1005      65376    6538      3862   61514       6
Sadie Oneill       113387281  1000     399252   39925     91559  307693      23
Celeste Powell     337293245  1000     403584   40358     92923  310661      23
Shawn Bray         757624552  1000     570240   57024    145420  424820      26
Saniyah Bradshaw   784649946  1001      91716    9172      8408   83308       9
Mackenzie Ballard  519661375  1006     107736   10774     11580   96156      11
Janae Holland      507485567  1006      81684    8168      6422   75262       8
Carlo Nichols      353505571  1006      86676    8668      7410   79266       9
Iris Miller        180833192  1001      79188    7919      5928   73260       7
Chelsea Mann       320429173  1000      45636    4564      1730   43906       4


Tax rate	Taxable income bracket	Tax owed
10%	        $0 to $9,950	        10% of taxable income
12%	        $9,951 to $40,525	    $995 plus 12% of the amount over $9,950
22%	        $40,526 to $86,375	    $4,664 plus 22% of the amount over $40,525
24%	        $86,376 to $164,925	    $14,751 plus 24% of the amount over $86,375
32%	        $164,926 to $209,425	$33,603 plus 32% of the amount over $164,925
35%	        $209,426 to $523,600	$47,843 plus 35% of the amount over $209,425
37%     	$523,601 or more	    $157,804.25 plus 37% of the amount over $523,600

*/

/// @note ./pa09 donations.csv employeeData.csv
