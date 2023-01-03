//lab 9 bridge design pattern
//Jerry Zheng 


#include <iostream>
#include <vector>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill {
public:
    Fill(char fillChar,char fillBorder) : fillChar_(fillChar), borderChar_(fillBorder) {}
    virtual char getBorder() { return borderChar_; };
    virtual char getInternal() { return fillChar_; }
    virtual ~Fill() {}
protected:
    char fillChar_;
    char borderChar_;
};

// concrete body
class Hollow : public Fill {
public:
    Hollow(char fillBorder) :Fill(' ',fillBorder) {}
    char getBorder() override { return borderChar_; }
    char getInternal() override { return ' '; }
    ~Hollow() override {}
};


// another concrete body
class Filled : public Fill {
public:
    Filled(char fillChar) :Fill(fillChar,fillChar) {}
    char getBorder() override { return fillChar_; }
    char getInternal() override { return fillChar_; }
    ~Filled() override {}
};

class FullyFilled :public Fill {
public:
    FullyFilled(char fillChar, char fillBorder) :Fill(fillChar, fillBorder) {}
    char getBorder() override { return borderChar_; }//gets border character
    char getInternal() override { return fillChar_; } //gets internal character
    ~FullyFilled() override {} //destructor

};
class RandomFilled : public Fill {
public:
    RandomFilled(char fillChar, char fillBorder) :Fill(fillChar, fillBorder) {}
    char getBorder() override { 
        int getChar = rand() % 2; //generates random characters based on the random number generated
        if (getChar == 1) {
            return borderChar_;
        }
        else {
            return fillChar_;
        }
    }
    char getInternal() override {
        int getChar = rand() % 2;//generates random characters based on the random number generated
        if (getChar == 1) {
            return fillChar_;
        }
        else {
            return borderChar_;
        }
    }
    ~RandomFilled() override {}//destructor
};

// abstract handle
class Figure {
public:
    Figure(int size, Fill* fill) : size_(size), fill_(fill) {}
    virtual void draw() = 0;
    virtual ~Figure() {}
protected:
    int size_;
    Fill* fill_;
};

// concrete handle
class Square : public Figure {
public:
    Square(int size, Fill* fill) : Figure(size, fill) {}
    void draw() override;

};


void Square::draw() {
    for (int i = 0; i < size_; ++i) {
        for (int j = 0; j < size_; ++j)
            if (i == 0 || j == 0 || i == size_ - 1 || j == size_ - 1)
                cout << fill_->getBorder();
            else
                cout << fill_->getInternal();
        cout << endl;
    }
}

int main() {
    Fill* hollow = new Hollow('Z');
    Fill* filled = new Filled('*');
    Fill* fullyFilled = new FullyFilled('J', 'Z');
    Fill* randomFilled = new RandomFilled('J', 'Y');

    Figure* box1 = new Square(10, hollow);
    Figure* box2 = new Square(6, filled);
    Figure* box3 = new Square(7, fullyFilled);
    Figure* box4 = new Square(8, randomFilled);


    box1->draw();
    cout << endl;
    box2->draw();
    cout << endl;
    box3->draw();
    cout << endl;
    box4->draw();
    cout << endl;
   

}