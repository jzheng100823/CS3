#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>


using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::generate;using std::for_each;
using std::transform; using std::remove_if;

struct Apples {
    double weight; // oz
    string color;  // red or green
    void print() const { cout << color << ", " << weight << endl; }
};



int main() {
    srand(time(nullptr));
    const double minWeight = 8.;
    const double maxWeight = 3.;

    cout << "Input crate size: ";
    int size;
    cin >> size;

    vector <Apples> crate(size);

    // assign random weight and color to apples in the crate
    // replace with generate()
    /*
    for (auto it = crate.begin(); it != crate.end(); ++it) {
        it->weight = minWeight +
            static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        it->color = rand() % 2 == 1 ? "green" : "red";
    }
    */
    //this fill the container with random apple weights of the color red and green
    generate(crate.begin(), crate.end(), [minWeight, maxWeight] {
        Apples apple;
        apple.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        apple.color = rand() % 2 == 1 ? "green" : "red";
        return apple;
        });


    // for_each() possibly

    //prints all the apples out 
    for_each(crate.begin(), crate.end(), [=](Apples& apple) {apple.print(); });

    /*
     cout << "all appleas" << endl;
     for (const auto& e : crate) {
         e.print();
     }
    */

    cout << "Enter weight to find: ";
    double toFind;
    cin >> toFind;

    // count_if()
    //find all the weights that are greater we capture the user input
    int cnt = count_if(crate.begin(), crate.end(), [toFind](Apples& apple) {return apple.weight > toFind;});
    /*
    for (auto it = crate.cbegin(); it != crate.cend(); ++it)
        if (it->weight > toFind) ++cnt;
        */

    cout << "There are " << cnt << " apples heavier than "
        << toFind << " oz" << endl;

    // find_if()
    //finds the positions of the apple that are greater
    auto it = find_if(crate.begin(), crate.end(), [toFind](Apples& apples) {return apples.weight > toFind; });
    if (it != crate.end()) {
        cout << "at postions";
        while (it != crate.end()) {
            cout <<" "<< it - crate.begin() << " ";
            it = find_if(++it, crate.end(), [toFind](Apples apple) {return apple.weight > toFind;});
        }
    }
    cout << endl;


        /*
cout << "at positions ";
for (int i = 0; i < size; ++i)
    if (crate[i].weight > toFind)
        cout << i << ", ";
cout << endl;
*/

/*
// max_element()
        double heaviest = crate[0].weight;
    for (int i = 1; i < size; ++i)
        if (crate[i].weight > heaviest) heaviest = crate[i].weight;
    cout << "Heaviest apple weighs: " << heaviest << " oz" << endl;
    */

        //finds the heaviest apple of them all 
        it = max_element(crate.begin(), crate.end(), [](Apples s, Apples b) {return s.weight < b.weight;});
        cout << "The heaviest Apple is" <<" "<< it->weight;
        cout << endl;

        /*
        // for_each() or accumulate()
        double sum = 0;
        for (int i = 0; i < size; ++i)
            sum += crate[i].weight;
        cout << "Total apple weight is: " << sum << " oz" << endl;
        */
        double total_weight = 0;
        //adds all the weight of the apples
        for_each(crate.begin(), crate.end(), [&total_weight](Apples apple) {return total_weight += apple.weight;});
        cout << "The total apple weight is " << total_weight << " oz ";

        // transform();

        
        
        cout << "How much should they grow: ";
        double toGrow;
        cin >> toGrow;

        //adds the user input to all the weights
        transform(crate.begin(), crate.end(),crate.begin(),[=](Apples apple) {
            Apples a;
            a.weight = apple.weight + toGrow;
            a.color = apple.color;
            return a;
            });
        /*
        for (int i = 0; i < crate.size(); ++i)
            crate[i].weight += toGrow;
         */
        // remove_if()
        cout << "Input minimum acceptable weight: ";
        double minAccept;
        cin >> minAccept;


        // removing small apples
        // nested loops, replace with a single loop modification idiom

        //removes all the apples that dont meet the weight
        crate.erase(remove_if(crate.begin(), crate.end(), [minAccept](Apples &apple) {return apple.weight < minAccept;}), crate.end());
        /*
        bool removed;
        do {
            removed = false;
            for (auto it = crate.begin(); it != crate.end(); ++it)
                if (it->weight < minAccept) {
                    crate.erase(it);
                    removed = true;
                    break;
                }
        } while (removed);
        */
        cout << "removed " << size - crate.size() << " elements" << endl;


        // bubble sort, replace with sort()
        //the sort function sorts the apples by their respected weight
        sort(crate.begin(), crate.end(), [=](Apples apple1, Apples apple2) {return apple1.weight < apple2.weight;});
       /*
        bool swapped;
        do {
            swapped = false;
            for (int i = 0; i < crate.size() - 1; ++i)
                if (crate[i].weight > crate[i + 1].weight) {
                    std::swap(crate[i], crate[i + 1]);
                    swapped = true;
                }
        } while (swapped);
       */

        // for_each() possibly
        /*
        cout << "sorted remaining apples" << endl;
        for (const auto& e : crate) {
            e.print();
        }
        */

        //prints out remaining sorted apples 
        cout << "sorted remaining apples by weight are" << endl;
        for_each(crate.begin(), crate.end(), [=](Apples apple) {apple.print();});

    }