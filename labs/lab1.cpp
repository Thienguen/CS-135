#include <iostream>
#include <iomanip>

using namespace std;

//declairing a struct to be refrenced with function calls 

struct studentType
{
	string Fname;
	string Lname;
	int    grade; 
	char   Lgrade;
};

// Function prototypes
void   getStudentData(studentType&);
void   getLetterGrade(studentType&);
void printStudentData(studentType&);

//Initiliazed program 
int main(){
	
	//StructData 
	studentType printout;
	
	// Call to the fuctions 
	getStudentData(printout);
	getLetterGrade(printout);
	printStudentData(printout);
	return 0;
}

void getStudentData(studentType& printout){
		//declair variables inside the function
		int    gradeIn = 0;
		string Fname;
		string Lname;
  
		//get entered user First Name 
		cout << "Enter a first name\n" << "**";
  
		cin >> Fname;
		
    printout.Fname = Fname;
		
    cout << endl;
		
		//get entered user First Name 
		cout << "Enter a lastname name\n" << "**"; 
		
    cin >> Lname;
		
    printout.Lname = Lname;
		
    cout << endl;

		// entering in a Grade
		cout << "Enter a grade\n" << "**";
  
    cin >> gradeIn;
    
    cout << endl;

		while(gradeIn < 0 || gradeIn > 4 || cin.fail())
    {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error: Invalid grade" << endl;
			cout << "Enter a grade"        << endl << "**";
			
      cin >> gradeIn;
      cout << endl;
		}

		  printout.grade = gradeIn;
	
	}


void getLetterGrade(studentType& printout){

	if      (printout.grade == 4) printout.Lgrade = 'A';
	else if (printout.grade == 3) printout.Lgrade = 'B';
	else if (printout.grade == 2) printout.Lgrade = 'C';
	else if (printout.grade == 1) printout.Lgrade = 'D';
	else if (printout.grade == 0) printout.Lgrade = 'F';

}

void printStudentData(studentType& printout)
{
	cout  << "Data Entered"      << endl;
	cout  << right << setw(19)   << "Student.firstName" 
        << setw(5) << " = "    << printout.Fname        << endl
        << right   << setw(18) << "Student.lastname"    << right 
        << setw(6) << " = "    << printout.Lname        << endl
        << right   << setw(15) << "Student.grade"       << right 
        << setw(9) << " = "    << printout.grade        << endl
        << right   << setw(21) << "Student.letterGrade" << right 
        << setw(1) << " = "    << printout.Lgrade       << endl;
}
