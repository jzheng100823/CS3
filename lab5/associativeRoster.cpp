//Jerry Zheng 
//lab5 
//roster and their classes using maps
//the students arse sorted lexograhpically by their last name
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <list>
#include <fstream>

using std::cout; using std::endl;
using std::string; using std::map;
using std::list; using std::ifstream;

class Student {
public:
    Student(string firstName, string lastName) :
        firstName_(firstName), lastName_(lastName) {}


    // force generation of default copy constructor
    Student(const Student& org) = default;

    string print() const { return firstName_ + ' ' + lastName_; }

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

private:
    string firstName_;
    string lastName_;
};

void readRoster(map<Student,list<string>>& roster, string fileName);

// printing a list out
void printRoster(const map < Student , list<string>> roster );

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last"
            << endl; exit(1);
    }
    map<Student,list<string>> roster;

    //prints  out the roster with the classes they are enrolled in
    for (int i = 1; i < argc - 1; i++) {
        readRoster(roster, argv[i]); //reading in the files
    }
    printRoster(roster);
}
void readRoster(map<Student, list<string>>& roster, string fileName) {
    ifstream course(fileName); //gets input stream
    string courseName = fileName; //sets the name of file to string
    courseName.erase(courseName.end() - 4, courseName.end()); //remove the txt to get the name of the class 

    string first, last; //these will hold the first and last name
    list<string> listClass; // creating a list to store the name of the classes
    listClass.push_back(courseName); //pushes the name of the class into a list which will then be added to the map
    while (course >> first >> last) { //while it keeps reading
        bool check = false;   //this will keep track of whether the student has a record already
        for (auto& name : roster) {
            if (name.first == Student(first, last)) { //of there is a record
                bool check = true; //set it to true
                name.second.push_back(courseName); //just add the course name;
                break;
            }
        }
        if (check == false) { //if there is no student entry
            roster.emplace(Student(first, last),listClass); //this will add the first and last name along with the list of classes to the map
        }
    }

}
//prints out the roster
void printRoster( const map < Student, list<string>> roster) {
    for ( const auto& course : roster) {
        cout << course.first.print() << " ";
        for (const auto& courseName : course.second) {
            cout << courseName<<" ";
        }
        cout << endl;
    }
}
