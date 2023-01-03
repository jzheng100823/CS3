// jamming peaches
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 9/30/2021


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::remove_copy_if; 

struct Peaches {
    double weight; // oz
    string ripe;  // ripe or not
    void print() const { cout << ripe<< ", " << weight << endl; }
};



int main() {
    srand(time(nullptr));
    const double minWeight = 8.;
    const double maxWeight = 3.;

    cout << "Input basket size: ";
    int size;
    cin >> size;

    vector <Peaches> basket(size);

    // assign random weight and ripeness peaches in the basket
    // replace with generate()
    /*
    for (auto it = basket.begin(); it != basket.end(); ++it) {
        it->weight = minWeight +
            static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        it->ripe = rand() % 2;
    }
    */
    //fills the basket with peaches with random sizes and random ripeness
    generate(basket.begin(), basket.end(), [minWeight, maxWeight] {
        Peaches peach;
        peach.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        peach.ripe = rand() % 2 == 1 ? "ripe" : "green";
        return peach;
        });



    // for_each() possibly
    /*
    cout << "all peaches" << endl;
    for (const auto& e : basket) {
        e.print();
    }
    */
    //prints out all the peaches in the basket
    cout << "all peaches" << endl;
    for_each(basket.begin(), basket.end(), [](Peaches peach) {peach.print();});

    // moving all the ripe peaches from basket to peck
    // remove_copy_if() with back_inserter()/front_inserter() or equivalents
    /*
    deque<Peaches> peck;
    for (auto it = basket.begin(); it != basket.end();)
        if (it->ripe) {
            peck.push_front(std::move(*it));
            it = basket.erase(it);
        }
        else
            ++it;
            */
    //deque to store the ripe peaches
    deque<Peaches> peck(size);
    //copies all the green and puts it basket adn removes all the ripe peaches and inserts it into the peck 
    remove_copy_if(basket.begin(), basket.end(), std::front_inserter(peck), [=](Peaches peach) {return peach.ripe != "ripe";});
    //removes all the ripe peaches that was moved in the basket 
    basket.erase(remove_if(basket.begin(), basket.end(), [=](Peaches peach) {return peach.ripe == "ripe";}), basket.end());



    // for_each() possibly
    cout << "peaches remaining in the basket" << endl;
    for_each(basket.begin(), basket.end(), [](Peaches& peach) {peach.print();});
    /*
    cout << "peaches remainng in the basket" << endl;
    for (const auto& e : basket) {
        e.print();
    }
    */
    cout << endl;

    // for_each() possibly
    cout << "peaches moved to the peck" << endl;
    //this will only print if there is a peach with a weight
    for_each(peck.begin(), peck.end(), [=](Peaches peach) {if(peach.weight!=0)peach.print();});
    /*
    cout << "peaches moved to the peck" << endl;
    for (const auto& e : peck) {
        e.print();
    }
    */


    // prints every "space" peach in the peck
    // 
    /*
    const int space = 3;
    cout << "\nevery " << space << "\'d peach in the peck" << endl;

    // replace with advance()/next()/distance()
    // no iterator arithmetic
    auto it = peck.cbegin(); int i = 0;
    while (it != peck.cend()) {
        if (i == space) {
            it->print();
            i = 0;
        }
        ++i;
        ++it;
    }
    */
    const int space = 3;
    int peach = 1;
    cout << " every " << space << " peach in the peck " << endl;
    auto i = peck.begin();
    while (i != peck.end()) {
        //modulo so that if peach %3 == 0 then it will print it out
        if (peach % space == 0 && i->weight != 0) {
            i->print();
        }
        //advance is similar to increment 
        advance(i, 1);
        peach++;
    }

    // putting all small ripe peaches in a jam
    // use a binder to create a functor with configurable max weight
    // accumulate() or count_if() then remove_if()
    /*
    const double weightToJam = 10.0;
    double jamWeight = 0;
    for (auto it = peck.begin(); it != peck.end();)
        if (it->weight < weightToJam) {
            jamWeight += it->weight;
            it = peck.erase(it);
        }
        else
            ++it;

    cout << "Weight of jam is: " << jamWeight << endl;
    */
    //functor class
    class functor {
    public:
        functor() { jamWeight = 0; };//initializes the wight to 0
        double operator() (vector<Peaches> peck, double maxJam) {
            for (auto &peach : peck) {
                if (peach.weight < maxJam) { //configurable max weight
                    jamWeight += peach.weight;//adds all the wights 
                }
            }
            return jamWeight;
        }


    private:
        double jamWeight;
    };
    const double weightToJam = 10.0;
    functor peachJam;
    auto jam = std::bind(peachJam, basket, weightToJam);//using bind function  
    cout << " Weight of jam is " << jam();
}
