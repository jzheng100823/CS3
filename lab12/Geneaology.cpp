// traversing genealogical tree using Composite and Visitors with Geneaology
// Jerry Zheng
// 12/2/2022

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string;
using std::vector;
using std::cin;

class Person { // component
public:
    Person(string firstName, Person* spouse, Person* father, Person* mother) :
        firstName_(firstName), spouse_(spouse), father_(father), mother_(mother) {}
    const string& getFirstName() { return firstName_; }
    Person* getSpouse() { return spouse_; }
    void setSpouse(Person* spouse) { spouse_ = spouse; }
    Person* getFather() { return father_; }
    Person* getMother() { return mother_; }
    Person* getChild() { return children_; }

    virtual string getFullName() = 0;

    virtual void accept(class PersonVisitor*) = 0;
    virtual ~Person() {}
private:
    const string firstName_;
    Person* spouse_;
    Person* father_;
    Person* mother_;
    Person* children_;
};


// leaf
// man has a last name 
class Man : public Person {
public:
    Man(string lastName, string firstName, Person* spouse,
        Person* father, Person* mother) :
        lastName_(lastName),
        Person(firstName, spouse, father, mother) {}
    const string& getLastName() const { return lastName_; }
    void accept(class PersonVisitor* visitor) override;
    string getFullName()override { return getFirstName() + " " + getLastName(); }
private:
    const string lastName_;
};

// composite
// woman has a list of children
class Woman : public Person {
public:
    Woman(vector<Person*> children,
        string firstName,
        Person* spouse,
        Person* father, Person* mother) :
        children_(children),
        Person(firstName, spouse, father, mother) {}
    const vector<Person*>& getChildren() const { return children_; }
    void setChildren(const vector<Person*>& children) { children_ = children; }
    void accept(class PersonVisitor* visitor) override;
    string getFullName()override {
        string name = "";
        name = getFirstName();
        if (getSpouse() != nullptr)
            return name = name + " " + static_cast<Man*>(getSpouse())->getLastName();
        else if (getFather() != nullptr)
            return name = +" " + static_cast<Man*> (getFather())->getLastName();
        else
            cout << "Doe";
        cout << endl;
    }
private:
    vector<Person*> children_;
};

// abstract visitor
class PersonVisitor {
public:
    virtual void visit(Man*) = 0;
    virtual void visit(Woman*) = 0;
    virtual ~PersonVisitor() {}
};

// composite methods that define traversal
void Man::accept(PersonVisitor* visitor) {
    visitor->visit(this);
}

void Woman::accept(PersonVisitor* visitor) {
    // children traversal through mother only
    // father's children are not traversed so as not 
    // to traverse them twice: for mother and father

    visitor->visit(this);

    // traversing descendants
    for (auto child : children_)
        child->accept(visitor);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter : public PersonVisitor {
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << " " << m->getLastName() << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << " ";
        if (w->getSpouse() != nullptr)
            cout << static_cast<Man*>(w->getSpouse())->getLastName();
        else if (w->getFather() != nullptr)
            cout << static_cast<Man*> (w->getFather())->getLastName();
        else
            cout << "Doe";
        cout << endl;
    }
};


class ChildrenPrinter : public PersonVisitor {
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << ": ";
        Woman* spouse = static_cast<Woman*>(m->getSpouse());
        if (spouse != nullptr)
            printNames(spouse->getChildren());
        cout << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << ": ";
        printNames(w->getChildren());
        cout << endl;
    }
private:
    void printNames(const vector<Person*>& children) {
        for (const auto c : children)
            cout << c->getFirstName() << ", ";
    }
};
class Relative :public PersonVisitor {
public:
    Relative(string name1, string name2) :person1(name1), person2(name2) {}
    void visit(Man* m)override {
        if (m->getFullName() == person1) {
            found = true;//we have located the canidate in the tree
            canidate1 = m; //sets the man to candidate 1
        }
        if (m->getFullName() == person2) {
            found = true; //we have located canidate 2 
            canidate2 = m;//sets the man to canidate 2
        }
    }

    void visit(Woman* w)override {
        string woman_last;//stores the womans last name as string cause we dont know yet
        if (w->getFullName() == person1) {
            found = true; //we have have found the canidate;
            canidate1 = w; //set the woman to canidate 1
        }
        if (w->getFirstName() == person2) {
            found = true; //we have have found the canidate;
            canidate2 = w; //set the woman to canidate 1

        }
    }


    bool Related() {
        if (found) {//if the canidates are found in the tree then 
            if (canidate1 == canidate2) { //the two canidates are the same people
                return true;
            }
            //parent 
            if (canidate1->getMother() == canidate2 || canidate1->getFather() == canidate2) {
                return true; //returns true since canidate 2 is the father or mother of canidate 1
            }
            if (canidate2->getMother() == canidate1 || canidate2->getFather() == canidate1) {
                return true; //returns true since canidate 1 is the father or mother of candidate 2
            }
            if (canidate1->getMother() == canidate2->getMother()) {
                return true;//since they have the same mother then they are brothers and sisters 
            }

            if (canidate1->getMother() != nullptr) {

                if (canidate1 == canidate2->getMother()->getMother()->getChild()) {
                    return true; //if the are aunt/uncle relationship then they are also related
                }
                if (canidate2 == canidate1->getMother()->getMother()->getChild()) {
                    return true;
                }
            }
        }
    }

private:
    string person1;
    string person2;
    bool found = false;//checks to see if the person is found or not set to false initially 
    Person* canidate1;
    Person* canidate2;
};

// demonstrating the operation
int main() {

    // setting up the genealogical tree      
    // the tree is as follows
    //    
    //
    //       James Smith  <--spouse-->   Mary 
    //	                                  |
    //	                                 children -------------------------
    //	                                  |              |                |
    //	                                  |              |                |
    //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
    //	                                  |
    //	                                 children------------
    //	                                  |                 |
    //                                     |                 |
    //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
    //	       |
    //	     children
    //	       |
    //          |
    //	     Susan


    // first generation
    Man* js = new Man("Smith", "James", nullptr, nullptr, nullptr);
    Woman* ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
    ms->setSpouse(js); js->setSpouse(ms);

    // second generation
    Woman* ps = new Woman({}, "Patricia", nullptr, js, ms);
    Man* wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
    ps->setSpouse(wj); wj->setSpouse(ps);

    vector<Person*> marysKids = { ps,
                       new Man("Smith", "Robert", nullptr, js, ms),
                       new Woman({}, "Linda", nullptr, js, ms) };
    ms->setChildren(marysKids);

    // third generation
    Man* mj = new Man("Johnson", "Michael", nullptr, wj, ps);
    vector<Person*> patsKids = { mj, new Woman({}, "Barbara", nullptr, wj, ps) };
    ps->setChildren(patsKids);

    Woman* jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
    vector<Person*> jensKids = { new Woman({}, "Susan", nullptr, mj ,jj) };

    jj->setSpouse(mj); mj->setSpouse(jj);
    jj->setChildren(jensKids);


    // defining two visitors
    ChildrenPrinter* cp = new ChildrenPrinter;
    NamePrinter* np = new NamePrinter;

    // executing the traversal with the composite
    // and the specific visitor

    /*
    cout << "\nNAME LIST\n";
    ms->accept(np);
    cout << endl << endl;


    cout << "CHILDREN LIST\n";
    ms->accept(cp);
    */
    /*
    cout << "\nJAMES' CHILDREN\n";
    js->accept(cp);
    */

    string candidate1;
    string canidate2;
    cout << "Enter Name of Canidate 1";
    std::getline(cin, candidate1);
    cout << "Enter Name of Canidate2";
    std::getline(cin, canidate2);


    Relative* check = new Relative(candidate1, canidate2);

    ms->accept(check);
    if (check->Related() == true) {
        cout << "they are close relatives";
    }
    else {
        cout << "They are just friends";
    }


}