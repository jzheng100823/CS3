//Basic Coffee shack using decorator pattern 
//Jerry Zheng
//11/16/2022

#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::cin;

enum class DrinkType { small, medium, large };
//component
class Drink {
public:
    Drink(DrinkType type = DrinkType::small, int price = 0) :
        type_(type), price_(price) {}
    virtual int getPrice() const {return price_;}
    virtual string getName() const {
        string size;
        if (type_ == DrinkType::small) {
            size = "small";
        }
        else if (type_ == DrinkType::medium) {
            size = "medium";
        }
        else
        {
            size = "large";
        }
        return size + " drink with: ";

    };
private:
    int price_;
    DrinkType type_;
};
//sugar decorator class
class Sugar :public Drink {
public:
    Sugar(const Drink* wrapped) :wrapped_(wrapped) {}
    int getPrice()const { 
        return wrapped_->getPrice() + 1; 
    }
    string getName()const { 
        return wrapped_->getName() + "Sugar ,"; //returns sugar
    }
private:
    const Drink* wrapped_;
};
//cream decorator class
class Cream :public Drink {
public:
    Cream(const Drink* wrapped) :wrapped_(wrapped) {}
    int getPrice()const {
        return wrapped_->getPrice() + 2;
    }
    string getName()const {
        return wrapped_->getName() + "Cream , ";
    }
private:
    const Drink* wrapped_;

};
//milk foam decorator class
class Foam :public Drink {
public:
    Foam(const Drink* wrapped) :wrapped_(wrapped) {}
    int getPrice()const {
        return wrapped_->getPrice() + 3;
    }
    string getName() const {
        return wrapped_->getName() + "Milk Foam ,";
    }

private:
    const Drink* wrapped_;

};
int main() {
    //variables for user input 
    char sml, toppings;
    DrinkType size;
    int price;
    string name;
    Drink* drink;
    cout << "Hi what is Your Name";
    cin >> name;
    cout << "Hello " << name << " Can i get you a [s]mall, [m]edium, or [l]arge drink today";
    cin >> sml;

    switch (sml) {
    case 's':
        size = DrinkType::small;
        price = 5;
        break;
    case'm':
        size = DrinkType::medium;
        price = 7;
        break;
    case'l':
        size = DrinkType::large;
        price = 10;
        break;
    }
    drink=new Drink(size, price); //makes a new drink based on the size and price
   
    do //i used do while because it need to run one time in case to ask for toppings
    {
       cout << "Would you like to add [s]ugar,[c]ream, milk [f]oam, or [d]one ? ";
       cin >> toppings;
       switch (toppings) { //switch statements to add new toppings based on user input
       case's':
           drink = new Sugar(drink); //adds the toppings to the object
           break;
       case'c':
           drink = new Cream(drink);
           break;
       case'f':
           drink = new Foam(drink);
           break;
       }

    } while (toppings != 'd');
    cout << name << " your " << drink->getName() << " is ready It will be $" << drink->getPrice() << " please";
    
}
