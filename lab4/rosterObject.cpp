#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;


class Student {
public:
    Student(string firstName, string lastName, string className) :
        firstName_(firstName), lastName_(lastName) {
        students_.push_back(className);
    }

    // force generation of default copy constructor
    Student(const Student& org) = default;

    string print() const { return firstName_ + ' ' + lastName_; }

    // needed for unique() and for remove()
    friend bool operator== (Student left, Student right) {
        return left.lastName_ == right.lastName_ &&
            left.firstName_ == right.firstName_;
    }

    // needed for sort()
    friend bool operator< (Student left, Student right) {
        return left.lastName_ < right.lastName_ ||
            (left.lastName_ == right.lastName_ &&
                left.firstName_ < right.firstName_);
    }
    string get_firstName_() const { return firstName_;} //constant function to return the students first name
    string get_lastName_() const { return lastName_;} //constant function to return the last name

    //prints out the the name the of students
    void print_list_students() {
        for (auto roster : students_) {
            cout << roster << " ";
        }
    }
    //function to add the course to the list
    void add_course(const string filename) {
        students_.push_back(filename);
    }


private:
    string firstName_;
    string lastName_;
    list<string> students_; //a list of the students 
};
void printRoster(const list<Student>& roster);
void readRoster( list<Student>& roster, string fileName);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last"
            << endl; exit(1);
    }
    list<Student> roster;

    for (int i = 1; i < argc - 1; i++) {
        readRoster(roster, argv[i]);
    }
    printRoster(roster);
}
//prints out the names of the students as a list
void printRoster(const list<Student>& roster) {
    for (auto list : roster) { //auto for loop 
        cout << list.print()<<" ";
        list.print_list_students();
        cout << endl;
    }
}
void readRoster(list<Student>& roster, string fileName) {
    ifstream course(fileName); //creates a file string
    string courseName = fileName; //sets the file string to a string
    courseName.erase(courseName.begin() + 3, courseName.end()); //removes the .txt from the cs files 

    string first, last; //creates strings for the first and last names respectively 
    while (course >> first >> last) { //while we are reading in the first an last names
        bool check = false;  //checks to see if the students name is already there
        for (auto& name : roster) {
            if (name.get_firstName_() == first && name.get_lastName_() == last) { //checks to see if an student is in the list or not
                name.add_course(courseName);//if the student is in the list then we just add the cs course
                check = true; //the student is already in the list
                break;
            }
        }
        if (!check) //if the student is not in the list 
            roster.push_back(Student(first, last, courseName)); //we add the first name last name and course to the list
    }
    course.close(); //close the file
}
