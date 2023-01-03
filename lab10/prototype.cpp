//Lab10 State Transitions
//Jerry Zheng 

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <queue>


using std::cin; using std::cout;
using std::endl; using std::string;
using std::queue;

//forward class declaration
class State;

//context class
class Process {
public:
	Process();
	Process(State* state) :state_(state) {
		nextIdentifier++;
		id = nextIdentifier;
	}
		
	void create();
	void suspend();
	void exit();
	void dispatch();
	void unblock();
	void block();
	string report();
	int getId()const { return id; }
	 Process* clone(){
		 return new Process(state_);
	}
	

	void changeState(State* state) { state_ = state; }
private:
	State* state_;
	static int nextIdentifier;
	int id;//which process
};
int Process::nextIdentifier = 0;
//abstract state class
class State {
public:
	virtual void create(Process*) {}
	virtual void suspend(Process*) {}
	virtual void exit(Process*) {}
	virtual void dispatch(Process*) {}
	virtual void unblock(Process*) {}
	virtual void block(Process*) {}

	virtual string report() = 0;
	void changeState(Process* process, State* state) {
		process->changeState(state);
	}
private:
};
//class for ready state
class Ready : public State {
public:
	static State* instance() {
		static State* onlyInstance = new Ready;
		return onlyInstance;
	}
	void dispatch(Process* n)override;
	string report() override {
		return "Ready";
	}
private:
};
//class for running state
class Running :public State {
public:
	static State* instance() {
		static State* onlyInstance = new Running;
		return onlyInstance;
	}
	void suspend(Process* n) override;
	void exit(Process* n) override;
	void block(Process* n)override;
	string report() override {
		return "runnning";
	}
private:
};
//class for blocked state;
class Blocked :public State {
public:
	static State* instance() {
		static State* onlyInstance = new Blocked;
		return onlyInstance;
	}
	void unblock(Process* n)override;

	string report()override {
		return  "blocked";
	}
private:
};
//class for exit or terminate;
class Exit :public State {
public:
	static State* instance() {
		static State* onlyInstance = new Exit;
		return onlyInstance;
	}
	string report()override {
		return "Exited";
	}
private:
};

//handels/behavior of the processes
void Process::create() { state_->create(this); }
void Process::dispatch() { state_->dispatch(this); }
void Process::suspend() { state_->suspend(this); }
void Process::exit() { state_->exit(this); }
void Process::block() { state_->block(this); }
void Process::unblock() { state_->unblock(this); }



//state transitions member functions
string Process::report() {
	cout<< state_->report()<<" ";
	return state_->report();
}
void Ready::dispatch(Process* z) {
	changeState(z, Running::instance());
}
void Running::exit(Process* z) {
	changeState(z, Exit::instance());
}
void Running::block(Process* z) {
	changeState(z, Blocked::instance());
}
void Running::suspend(Process* z) {
	changeState(z, Ready::instance());
}

void Blocked::unblock(Process* z) {
	changeState(z, Ready::instance());
}
Process::Process(){
	state_ = Ready::instance();
}
int main() {
	srand(time(nullptr));
	Process prototype;
	queue<Process*> rQueue;//ready queue
	queue<Process*>bQueue;//blocked queue;

	for (int i = 1;i < 5;++i) { //generate 4 process and 
		rQueue.push(prototype.clone());
		cout << "Pid " << i << " is in state: " << rQueue.front()->report() << endl;
	}

	cout << "-----------------------------------------------------------" << endl;
	while (!rQueue.empty() && bQueue.empty()) {
		if (!rQueue.empty()) {
			int probability = rand() % 3;//we generate 3 because we want it to be 33% chance
			switch (probability) { //i used switch statement to switch between the different outcomes
			case 0:
				rQueue.front()->block();//blocks
				bQueue.push(rQueue.front());
				cout << "Process" << rQueue.front()->getId() << " has been blocked" << endl ;
				rQueue.pop();
				break;
			case 1:
				rQueue.front()->exit(); //changes to exit
				cout << "Process" << rQueue.front()->getId() << " has exited" << endl;
				rQueue.pop();
				break;
			case 2:
				rQueue.front()->suspend(); //suspends 
				cout << "Process" << rQueue.front()->getId() << " has been suspended" <<endl;
				rQueue.push(rQueue.front());
				rQueue.pop();
				break;
			default:
				cout << "cant decide" << endl;

			}

		}
		int probability = rand() % 2 ; //it is a 50% chance of it being unblocked
		if (!bQueue.empty()&& probability==0) {
				bQueue.front()->unblock(); //change to unblock
				rQueue.push(bQueue.front());//pushes the process back into the ready queue from the blocked queue
				cout << "Process" << rQueue.front()->getId() << " is " << rQueue.front()->report() << endl;
				bQueue.pop();
		}

	}

}