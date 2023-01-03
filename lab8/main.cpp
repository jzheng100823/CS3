//using the meyers singleton 
//logger
#include <iostream>
#include <fstream>
#include <string>
using std::string;
using namespace std;
class Logger {
public:
    static Logger& instance() {
        static Logger s;
        return s;
    }
    void report(const string& s) {
        fout << s << endl;

    }
    ~Logger() { //destructor
        fout.close();
    }
private:
    Logger() {
        fout.open("test.txt", std::fstream::out | std::fstream::app);
    }
    Logger(const Logger&);
    Logger& operator=(const Logger&) {};
    std::ofstream fout;

};

//another function 
void myFunc() {
    Logger::instance().report("!!!");
}

int main() {
	Logger& s = Logger::instance();
    s.report("HELLO");
    Logger::instance().report("WORLD");
    myFunc();
}