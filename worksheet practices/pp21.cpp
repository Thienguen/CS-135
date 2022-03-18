/// @note Thien Nguyen revision on 3/17/2022
/* 
    This program utilizes a struct to save data of variable studenType
    and outputs the data given.

    The expected input: First name, last name, grade

    The expected output: First name, last name, and grade.
*/
#include <iostream>
using namespace std;

// declare a struct called studentType
struct studentType { 
    string firstName;
    string lastName;
    int grade;
};

// pass the struct and student into functions
void getStudentData(studentType& student) { 
    // need variables to save the data into
    string first, last; 
    int num;
    cout << "First name: ";
    cin >> first;
    // save the input into the first part of the struct
    student.firstName = first; 
    cout << "Lastname: ";
    cin >> last;
    // save the input into the second part of the struct
    student.lastName = last; 
    cout << "Grade: ";
    cin >> num;
    // save the input into the third part of the struct
    student.grade = num; 

    // output all data
    cout << "\nData entered\n" 
         << student.firstName << " " << student.lastName << " " << student.grade << endl;

}

int main() {
    studentType student;
    // calling the function
    getStudentData(student); 
}
