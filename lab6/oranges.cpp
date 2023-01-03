//Jerry Zheng 
//cs3 lab 6
//Select certain colors of oranges only 


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>


using std::cin; using std::cout; using std::endl;
using std::string;
using std::make_pair;
using std::vector;
using std::multimap;

enum class Variety { orange, pear, apple };
vector<string> colors = { "red", "green", "yellow" };

struct Fruit {
    Variety v;
    string color; // red, green or orange
};


int main() {
    srand(time(nullptr));
    multimap<Variety, string> tree;
    // random fruit and color selection
    int size = rand() % 100 + 1;//generates a random size 
    for (int i = 0; i < size; ++i) {
        tree.emplace(make_pair(static_cast<Variety>(rand() % 3), colors[rand() % 3]));//inserts the colors to the the map
       
    }


    // printing colors of oranges
    cout << "Colors of the oranges: " << endl;
    for (auto it = tree.lower_bound(Variety::orange);it!=tree.upper_bound(Variety::orange);++it)
        cout << it->second << endl; //prints out only the color

}
