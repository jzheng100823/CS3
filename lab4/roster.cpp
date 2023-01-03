#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <algorithm>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;
using std::sort;

// reading a list from a fileName
void readRoster(vector<list<string>>& roster, string fileName);

// printing a list out
void printRoster(const vector<list<string>>& roster);

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cout << "usage: " << argv[0]
            << " list of courses, dropouts last"
            << endl; exit(1);
    }
    vector<list<string>> roster;
    
    for (int i = 1; i < argc - 1; i++) {
        readRoster(roster, argv[i]);
    }
    printRoster(roster);

    cout<<"students sorted and dropouts removed"<<endl;

}
void readRoster(vector<list<string>>& roster, string fileName) {
  ifstream course(fileName); //creates file stream
  string courseName = fileName; //course name will obtaied from file name
  courseName.erase(courseName.begin()+3 , courseName.end());//removes the txt from file

    string first,last;
    while (course >> first >> last) {
        bool check = false;
        for (auto i = roster.begin(); i != roster.end();++ i) { //loops through list of strings
	  if (i->front() == first && *(++(i->begin())) == last) { //if the names match an student entry is already made
                check = true;
                i->push_back(courseName); //pushes the course name
                break;
            }
        }
        if (!check) { //if the student entry is not there we add it 
            list<string> name;
            name.push_back(first); //pushes the first name
            name.push_back(last); //pushes last name
            name.push_back(courseName); //adds the course name
            roster.push_back(move(name)); //moves the student entry into the container
        }
    }
    course.close();
}
void printRoster(const vector<list<string>>& roster) {
    for (auto i = roster.begin();i != roster.end();++i) {
        for (auto& student : *i) {
	  cout << student<<" ";
        }
	cout<<endl;
    }
}





