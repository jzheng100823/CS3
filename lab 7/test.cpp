#include "hashmap.hpp"
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main() {
    hashmap<int, int> myHash;
    myHash.insert(pair<int, int>(9, 60));
    myHash.insert(pair<int, int>(4, 40));
    myHash.insert(pair<int, int>(60, 9));
    myHash.insert(pair<int, int>(80, 85));

    auto safe_insert = myHash.insert(pair<int, int>(20, 40));

    if (safe_insert.second) {
        cout << "pair" << "<" << safe_insert.first->first << "," << safe_insert.first->second << ">" << " was succesfully inserted" << endl;
    }
    else {
        cout << "pair" << "<" << safe_insert.first->first << "," << safe_insert.first->second << "insertion was unsuccessful" << endl;
    }

    auto safe_insert_2 = myHash.insert(pair<int, int>(100, 100));


    if (safe_insert_2.second) {
        cout << "pair" << "<" << safe_insert_2.first->first << "," << safe_insert_2.first->second << ">" << " was succesfully inserted" << endl;
    }
    else {
        cout << "pair" << "<" << safe_insert_2.first->first << "," << safe_insert_2.first->second << "insertion was unsuccessful" << endl;
    }

    auto safe_insert_3 = myHash.insert(pair<int, int>(1, 1));

    if (safe_insert_3.second) {
        cout << "pair" << "<" << safe_insert_3.first->first << "," << safe_insert_3.first->second << ">" << " was succesfully inserted" << endl;
    }
    else {
        cout << "pair" << "<" << safe_insert_3.first->first << "," << safe_insert_3.first->second << "insertion was unsuccessful" << endl;
    }

    myHash.erase(4);

    auto safe_delete = myHash.erase(80);


    if (safe_delete.second) {
        cout << "removed key 80 safely" << endl;

    }
    else {
        cout << "Either key 7 is not found or it is not removed" << endl;
    }

    auto safe_delete_2 = myHash.erase(1000);

    if (safe_delete_2.second) {
        cout << "removed key 1000  safely" << endl;
    }
    else {
        cout << "Either key 1000 is not found or it is not removed" << endl;
    }


    auto x2 = myHash.find(4);
    if (x2 != nullptr)
        cout << "4 maps to " << x2->second << endl;
    else
        cout << "cannot find 4 in map" << endl;

    myHash[4] = 60;
    myHash.rehash(20);
    myHash.rehash(1);

    /*
    auto x3 = myHash.find(4);
    if (x3 != nullptr)
        cout << "4 maps to " << x3->second << endl;
    else
        cout << "cannot find 4 in map" << endl;

    hashmap<int, string> employees;

    // entering entries with indexing operator
    employees[123] = "Mike";
    employees[345] = "Charlie";
    employees[192] = "Joe";
    employees[752] = "Paul";
    employees[328] = "Peter";

    cout << "Enter new employee number: "; int num; cin >> num;
    cout << "Enter new employee name: "; string name; cin >> name;

    employees[num] = name; // "unsafe" insert

    // searching map
    cout << "Enter employee number to look for: "; cin >> num;
    auto it = employees.find(num);
    if (it != nullptr)
        cout << it->first << ":" << it->second << endl;
    else
        cout << "employee not found" << endl;

    // removing from a map
    cout << "Enter employee number to fire: "; cin >> num;
    employees.erase(num);
    // check if not there
    auto removed = employees.find(num);
    if (removed == nullptr)
        cout << "Employee removed successfully" << endl;
    */
}
