// Coffee Shack with Chain of Responsibility
// Jerry Zheng
// 11/7/2022

#include <string>
#include <iostream>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::cin;

enum class DrinkType { small, medium, large };
//component
class Drink {
public:
    Drink(DrinkType type = DrinkType::small, int price = 0) :
        type_(type), price_(price) {}
    virtual int getPrice() const { return price_; }
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
//abstract handler
class Barista {
public:
    Barista(Barista* successor = nullptr) :successor_(successor) {}
    virtual Drink* handleRequest(char Toppings, Drink* drink) { return successor_->handleRequest(Toppings, drink); }

private:
    Barista* successor_;
};
class JuniorBarista :public Barista {
public:
    JuniorBarista(Barista* successor = nullptr) :Barista(successor) {}
    Drink* handleRequest(char Toppings, Drink* drink)override {

        cout << "Can i get you a [s]mall, [m]edium, or [l]arge drink today";
        DrinkType size;
        char sml;
        int price;
        cin >> sml;
        switch (sml) {
        case's'://switch statement to decide the size of the drink
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
        //drink with the size and price 
        drink = new Drink(size, price);

        //asks user for drink toppings
        cout << "Would you like to add [s]ugar,[c]ream, milk [f]oam, or [d]one ? ";
        cin >> Toppings;
        if (Toppings == 'd') { //junior barista handles drink with no ingredients
            cout << "Junior Barista made your drink" << endl; //states that the drink is made by junior barista
            return drink; //returns the drink 
        }
        else {
            return Barista::handleRequest(Toppings, drink);//if the junior barista cant handle the toppings goes to next barista
        }
    }



private:
};
class SeniorBarista :public Barista {
public:
    SeniorBarista(Barista* successor = nullptr) :Barista(successor) {}
    Drink* handleRequest(char Toppings, Drink* drink)override {
        while (Toppings != 'f') { //senior barista cannot handle cold foam
            cout << " The Junior Barista cannot make your drink so the Senior Barista will make your drink " << endl; //states who made the drink

            switch (Toppings) {
            case's':
                drink = new Sugar(drink);
                break;
            case 'c':
                drink = new Cream(drink);
                break;
            case 'd':
                return drink;
                break;
            }
            cout << "Would you like to add[s]ugar, [c]ream, milk[f]oam, or [d]one ? ";
            cin >> Toppings;
        }
        return Barista::handleRequest(Toppings, drink); //if the senior barista cant handle the drink either

    }
private:
};

class Manager :public Barista {
public:
    Manager(Barista* successor = nullptr) :Barista(successor) {}
    Drink* handleRequest(char Toppings, Drink* drink)override {
        while (Toppings != 'd') { //while the user keeps selecting the toppings then manager will make it 
            cout << "Senior and Junior Barista cannot make your drink the Manager will make your drink" << endl;
            switch (Toppings) {
            case's':
                drink = new Sugar(drink);
                break;
            case'c':
                drink = new Cream(drink);
                break;
            case'f':
                drink = new Foam(drink);
                break;
            }
            //continue to ask user for toppings
            cout << "Would you like to add[s]ugar, [c]ream, milk[f]oam, or [d]one ? ";
            cin >> Toppings;

        }
        //returns the drink
        return drink;
    }

private:
};
int main() {
    char Toppings;
    Drink* drink;
    string name;
    cout << "Hi What is your name";
    cin >> name;
    //
    Barista* john = new JuniorBarista(new SeniorBarista(new Manager));//makes barista object john
    drink = john->handleRequest(Toppings, drink);//how it handles request of the toppings
    cout << name << " your " << drink->getName() << " is ready It will be $" << drink->getPrice() << " please";

}
