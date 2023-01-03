//Jerry Zheng 
//cs44001
//lab5 reading roster using set
//the students are sorted by their last name


#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <set>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;using std::set;


class Student {
public:
    Student(string firstName, string lastName) :
        firstName_(firstName), lastName_(lastName) {}

    // move constructor, not really needed, generated automatically
    Student(Student && org) :
        firstName_(move(org.firstName_)),
        lastName_(move(org.lastName_))
    {}

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
private:
    string firstName_;
    string lastName_;
};




// reading a list from a fileName
void readRoster(set<Student>& roster, string fileName);
// printing a list out
void printRoster(const set<Student>& roster);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last" << endl; exit(1);
    }

    // vector of courses of students
    set<Student> roster;

    for (int i = 1; i < argc - 1; ++i) {
        readRoster(roster, argv[i]);//reads in the file 
    }
    printRoster(roster); //printst out the roster
}

    


void readRoster(set<Student>& roster, string fileName) {
    ifstream course(fileName); //creates a ifstream for the file 
    string first, last; //creates a string for first and last name
    while (course >> first >> last) {
        bool check = false; //used to check if the name is in the file
        for (auto& name : roster) {
            if (name == Student(first, last)) { //if there is an entry then
                check = true; //set it to true
                break;//breaks out of the loop
            }
        }
        if (check == false) { //if there is no student entry 
            roster.insert(Student(first, last)); // add the student entry 
        }
    }
    course.close();//close the file 
}
    
 

// printing a list out
void printRoster(const set<Student>& roster) {
    for (const auto& student : roster)
        cout << student.print() << endl;
}