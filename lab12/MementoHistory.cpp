//Jerry Zheng modified memento with history
//lab12
//11/28/2022


#include <iostream>
#include <vector>
#include <string>
#include <stack>

using std::vector; using std::string;
using std::cout; using std::cin; using std::endl;
using std::stack;

// receiver
class Document {
public:

    Document(const vector <string>& lines = {}) : lines_(lines) {}

    // actions
    void insert(int line, const string& str) {
        const int index = line - 1;
        if (index <= lines_.size())
            lines_.insert(lines_.begin() + index, str);
        else
            cout << "line out of range" << endl;
    }

    string remove(int line) {
        const int index = line - 1;
        string deletedLine = "";
        if (index < lines_.size()) {
            deletedLine = lines_[index];
            lines_.erase(lines_.begin() + index);
        }
        else
            cout << "line out of range" << endl;
        return deletedLine;
    }

    void show() {
        for (int i = 0; i < lines_.size(); ++i)
            cout << i + 1 << ". " << lines_[i] << endl;
    }

private:
    vector<string> lines_;
};

// abstract command
class Command {
public:
    Command(Document* doc) : doc_(doc) {}
    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual ~Command() {}
    virtual void show() = 0;
protected:
    Document* doc_;
};

// two concrete commands
class InsertCommand : public Command {
public:
    InsertCommand(Document* doc, int line, const string& str) :
        Command(doc), line_(line), str_(str) {}
    void execute() override { doc_->insert(line_, str_); }
    void unexecute() override { doc_->remove(line_); }
    void show()override { cout << "inserted" << " " << str_ << " at line " << line_ << endl;; }
private:
    int line_;
    string str_;
};


class EraseCommand : public Command {
public:
    EraseCommand(Document* doc, int line) :
        Command(doc), line_(line), str_("") {}
    void execute() override { str_ = doc_->remove(line_); }
    void unexecute() override { doc_->insert(line_, str_); }
    void show()override { cout << "Erase line " << line_ << endl; }
private:
    int line_;
    string str_;
};

// client
class DocumentWithHistory {
public:
    DocumentWithHistory(const vector<string>& text = {}) : doc_(text) {}

    void insert(int line, string str) {
        Command* com = new InsertCommand(&doc_, line, str);
        com->execute();
        doneCommands_.push(com);
    }

    void erase(int line) {
        Command* com = new EraseCommand(&doc_, line);
        com->execute();
        doneCommands_.push(com);
    }

    void undo() {
        if (doneCommands_.size() != 0) {
            Command* com = doneCommands_.top();
            doneCommands_.pop();
            com->unexecute();
            delete com; // don't forget to delete command
        }
        else
            cout << "no commands to undo" << endl;
    }

    void show() { doc_.show(); }
    void History() {
        cout << "History" << endl;
        stack<Command*> temp;
        int commands = 0;
        int i = 0;//keep track of command number
        while (!doneCommands_.empty()) { //while the command stack is not empty
            ++i;
            ++commands; //we iterate the commands
            Command* currentCommand = doneCommands_.top();//we call top to get the command
            doneCommands_.pop(); //pops it off/
            cout << i << " ";
            currentCommand->show();//prints it out
            temp.push(currentCommand);//pushes the command onto the temp stack
        }
        while (!temp.empty()) {
            Command* currentCommand = temp.top();
            temp.pop();
            doneCommands_.push(currentCommand);

        }
    }

    void redo(int command) {
        if (doneCommands_.size() != 0 && command < doneCommands_.size()) {//if there is at least one command to do redo
            Command* currentCommand;
            stack<Command*>temp;
            for (int i = 0;i < command;i++) {
                currentCommand = doneCommands_.top();
                doneCommands_.pop();//pops that command off the stack
                temp.push(currentCommand);//push that command to the temp stack
            }
            currentCommand->execute();//execute that command
            for (int i = 0;i < command - 1;i++) {
                doneCommands_.push(temp.top());
                temp.pop();
            }
            doneCommands_.push(currentCommand);
        }
        else {
            cout << "No commands to redo" << endl;
        }
    }
    class Memento* createMemento() const;
    void rollBack(class Memento*);


private:
    Document doc_;
    std::stack<Command*> doneCommands_;
};
class Memento {
public:
    Memento(const DocumentWithHistory& doc) : doc_(doc) {}
    const DocumentWithHistory& getState() const { return doc_; }
private:
    const DocumentWithHistory doc_;
};

Memento* DocumentWithHistory::createMemento() const {
    return new Memento(*this); // copying the Document itself
}

void DocumentWithHistory::rollBack(Memento* mem) {
    *this = mem->getState();  // copying back
}
int main() {
    DocumentWithHistory his({
      "Lorem Ipsum is simply dummy text of the printing and typesetting",
      "industry. Lorem Ipsum has been the industry's standard dummy text",
      "ever since the 1500s, when an unknown printer took a galley of",
      "type and scrambled it to make a type specimen book. It has",
      "survived five centuries." });

    char option;
    Memento* checkpoint = nullptr;
    do {
        his.show();
        cout << endl;

        cout << "Enter option (i)nsert line, (e)rase line, (u)ndo last command,(c)heckpoint,roll(b)ack,(h)istory,(r)edo command: ";
        cin >> option;

        int line; string str;
        switch (option) {
        case 'i':
            cout << "line number to insert: ";
            cin >> line;
            cout << "line to insert: ";
            cin.get(); // removes end-of-line character so getline() works correctly
            getline(cin, str);
            his.insert(line, str);
            break;

        case 'e':
            cout << "line number to remove: ";
            cin >> line;
            his.erase(line);
            break;

        case 'u':
            his.undo();
            break;
        case 'c':
            his.createMemento();
            break;
        case'b':
            if (checkpoint != nullptr) {
                his.rollBack(checkpoint);
                delete checkpoint;
            }
            break;
        case'h':
            his.History();
            break;
        case'r':
            his.History();
            cout << "redo which command:";
            cin >> line;
            his.redo(line);
            break;
        }


    } while (option == 'i' || option == 'e' || option == 'u' || option == 'c' || option == 'b' || option == 'h' || option == 'r');
}

