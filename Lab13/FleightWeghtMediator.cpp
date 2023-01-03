//Jerry Zheng 
//Mediator with Flyweight
//12/7/2022

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <map>

// for timed sleep
#include <thread>
#include <chrono>

enum class airline{Delta,United,JetBlue,AirFrance,KLM,Aeroflot,Lufthansa};

using std::cout; using std::cin; using std::endl;
using std::string;
using std::map;

//abstract flyweight
class Logo {
public:
	virtual string image() = 0;
private:
};

//concrete flyweights
// Boeing Delta", "United", "JetBlue

class Delta :public Logo {
public:
	string image()override { return "DELTA"; }
private:
};

class United :public Logo {
public:
	string image()override { return "UNITED"; }
private:
};
class JetBlue :public Logo {
public:
	string image()override { return "JETBLUE"; }
private:
};
//concrete flyweights
// Airbus flights "AirFrance", "KLM", "Aeroflot", "Lufthansa"
class AirFrance :public Logo {
public:
	string image() override { return "AIRFRANCE"; }
private:
};
class KLM :public Logo {
public:
	string image() override { return "KLM"; }
private:
};
class Aeroflot :public Logo {
public:
	string image() override { return "Aeroflot"; }
private:
};
class Lufthansa :public Logo {
public:
	string image() override { return "LUFTHANSA"; }
private:
};

class AirlineFactory {
public:
	static Logo* makeLogo(airline a) {
		if (airlines_.find(a) == airlines_.end())
			switch (a) {// Delta, United, JetBlue, Airfrance, KLM, Aeroflot, Lufthansa };
			case airline::Delta:
				airlines_[a] = new Delta;break;
			case airline::United:
				airlines_[a] = new United; break;
			case airline::JetBlue:
				airlines_[a] = new JetBlue;break;
			case airline::AirFrance:
				airlines_[a] = new AirFrance;break;
			case airline::KLM:
				airlines_[a] = new KLM;break;
			case airline::Aeroflot:
				airlines_[a] = new Aeroflot;break;
			case airline::Lufthansa:
				airlines_[a] = new Lufthansa;break;
			}
		return airlines_[a];
	}
private:
	static std::map<airline, Logo*>airlines_;
};
std::map<airline, Logo*>AirlineFactory::airlines_;
// abstract mediator
class Controller {
public:
	virtual void join(class Flight*) = 0;
	virtual void leave(class Flight*) = 0;
	virtual void broadcast() = 0;
	virtual void observe() = 0;
};

//concrete flyweights
// Airbus "AirFrance", "KLM", "Aeroflot", "Lufthansa"


//client class
class Airplane {
public:
	Airplane(airline a) {
		logo_ = AirlineFactory::makeLogo(a);
	}
	string report()const {
		return logo_->image();
	}
private:
	const string flight_;
	Logo* logo_;
};

// concrete mediator
// tower, runway clearance
class Tower : public Controller {
public:
	void join(class Flight*) override;
	void leave(class Flight*) override;
	void broadcast() override;
	void observe() override;
private:
	std::set<class Flight*> waiting_;
};


// abstract colleague
class Flight {
public:
	Flight(Controller* controller) :controller_(controller), status_(Status::waiting) {
		task_ = rand() % 2 ? Task::taxiing : Task::approaching;
		controller_->join(this);
	}
	void receive(const string& msg) {
		if (msg.find(flightNo_) != string::npos || msg.find("all") != string::npos) {
			if (msg.find("clear") != string::npos) {
				cout << flightNo_ << " roger that, ";
				cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
				//determines if the plane is lands or takes off for Delta
			if (flightNo_.find("Delta")!=string::npos) {
				Airplane* logo = new Airplane(airline::Delta);
				string planeLogo = logo->report()+planeNum;
				cout << "....." << planeLogo << " ";
				cout<<(task_ == Task::taxiing ? "takes off" : "lands") <<"....." <<endl;
				delete logo;
			}
			//determines for united
			else if (flightNo_.find("United") != string::npos) {
				Airplane* logo = new Airplane( airline::United);
				string planeLogo = logo->report()+planeNum;
				cout << "....." << planeLogo << " "; //returns name of airline
				cout << (task_ == Task::taxiing ? "takes off" : "lands") << "....." << endl;
				delete logo;
			}
			//determines for Jetblue
			else if (flightNo_.find("JetBlue") != string::npos) {
				Airplane* logo = new Airplane(airline::JetBlue);
				string planeLogo = logo->report()+planeNum;
				cout << "....." << planeLogo << " ";//returns name of airline
				cout << (task_ == Task::taxiing ? "takes off" : "lands") << "....." << endl;
				delete logo;
			}
			//determines for Airfrance
			else if (flightNo_.find("AirFrance") != string::npos) {
				Airplane* logo = new Airplane(airline::AirFrance);
				string planeLogo = logo->report()+planeNum;
				cout << "....." << planeLogo << " ";//returns name of airline
				cout << (task_ == Task::taxiing ? "takes off" : "lands") << "....." << endl;
				delete logo;
			}
			//determines for KLM
			else if (flightNo_.find("KLM") != string::npos) {
				Airplane* logo = new Airplane(airline::KLM);
				string planeLogo = logo->report()+planeNum;
				cout << "....." << planeLogo << " ";//returns name  of airline
				cout << (task_ == Task::taxiing ? "takes off" : "lands") << "....." << endl;
				delete logo;
			}
			//determines for Aeroflot
			else if (flightNo_.find("Aeroflot") != string::npos) {
				Airplane* logo = new Airplane(airline::Aeroflot);
				string planeLogo = logo->report()+planeNum;
				cout << "....." << planeLogo << " "; //reports name of airline
				cout << (task_ == Task::taxiing ? "takes off" : "lands") << "....." << endl;
				delete logo;
			}
			//determines for Lufthansa
			else if (flightNo_.find("Lufthansa") != string::npos) {
				Airplane* logo = new Airplane( airline::Lufthansa);
				string planeLogo = logo->report()+planeNum;
				cout << "....." << planeLogo << " "; //reports name of airline
				cout << (task_ == Task::taxiing ? "takes off" : "lands") << "....." << endl;
				delete logo;
			}

				status_ = Status::cleared;
			}
			else if (msg.find("status") != string::npos) {
				cout << flightNo_
					<< (status_ == Status::waiting ? " waiting to " : " cleared to ")
					<< (task_ == Task::taxiing ? "take off" : "land") << endl;
			}
			else
				cout << "Tower, this is " << flightNo_ << " please repeat." << endl;
		}
	}
	bool isCleared() const { return status_ == Status::cleared; }
	void proceed() {
		std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1)); // wait a while    
		cout << flightNo_
			<< (task_ == Task::taxiing ? " took off" : " landed")
			<< ". Have a good day!" << endl;
		controller_->leave(this);
	}

protected:
	string flightNo_;
	string airline;
	string planeNum;
	Controller* controller_;
	enum class Task { taxiing, approaching };  Task task_;
	enum class Status { waiting, cleared };    Status status_;
};

// concrete colleagues
class Airbus : public Flight {
public:
	Airbus(Tower* tower) : Flight(tower) {
		static const std::vector<string> companies =
		{ "AirFrance", "KLM", "Aeroflot", "Lufthansa" };
		planeNum = std::to_string(rand() % 1000); //holds the value of the plane number
		airline= companies[rand() % companies.size()];//holds the name of the airline
		flightNo_ = airline + planeNum;//holds the name of the airline and plane number
		cout << flightNo_ << " requesting "
			<< (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
	}
};

class Boeing : public Flight {
public:
	Boeing(Tower* tower) : Flight(tower) {
		static const std::vector<string> companies =
		{ "Delta", "United", "JetBlue" };
		planeNum = std::to_string(rand() % 1000);//holds the plane number
		airline = companies[rand() % companies.size()]; //holds the name of the airline
		flightNo_ = airline + planeNum;//hold the name of the airline and number
		
		cout << flightNo_ << " requesting "
			<< (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
	}
};


// member functions for Tower
void Tower::broadcast() {
	cout << "Tower: ";
	string msg;
	getline(cin, msg);
	if (!msg.empty())
		for (auto f : waiting_) f->receive(msg);
}


void Tower::observe() {
	auto findCleared = [](Flight* f) {return f->isCleared(); };

	auto toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);

	while (toProceed != waiting_.end()) { // found a cleared flight
		(*toProceed)->proceed();
		toProceed = std::find_if(waiting_.begin(), waiting_.end(), findCleared);
		if (toProceed != waiting_.end())
			cout << "MAYDAY! MAYDAY! MAYDAY! " << endl; // more than a single flight cleared
	}
}


void Tower::join(Flight* f) {
	waiting_.insert(f);
}


void Tower::leave(Flight* f) {
	waiting_.erase(f);
	delete f;
}

int main() {
	srand(time(nullptr));
	Tower jfk;

	new Boeing(&jfk);
	new Airbus(&jfk);
	new Boeing(&jfk);
	new Airbus(&jfk);

	while (true) {
		jfk.broadcast();
		jfk.observe();
		if (rand() % 2) {
			if (rand() % 2)
				new Boeing(&jfk);
			else
				new Airbus(&jfk);
		}
	}
}





