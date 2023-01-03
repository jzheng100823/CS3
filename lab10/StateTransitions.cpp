//Lab10 State Transitions
//Jerry Zheng 

#include <iostream>
#include <string>

using std::cin; using std::cout;
using std::endl; using std::string;

//forward class declaration
class State;

//context class
class Process {
public:
	Process();
	void create();
	void suspend();
	void exit();
	void dispatch();
	void unblock();
	void block();
	string report();

	void changeState(State* state) { state_ = state; }
private:
	State* state_;
	static int nextIdentifier;
	int id;//which process

};
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
	cout << "Process " << id << " " << state_->report() << endl;
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
int Process::nextIdentifier = 1;//sets the process id to be 1 since its the first process 
Process::Process() {
	id = nextIdentifier;
	++nextIdentifier;
	state_ = Ready::instance();//this will always set the process to be in the ready state when created;
}
int main() {
	Process process1;
	process1.create();
	process1.report();

	process1.dispatch();
	process1.report();

	process1.dispatch();
	process1.report();

	process1.block();
	process1.report();

	process1.unblock();
	process1.report();

	Process process2;
	process2.create();
	process2.report();

	process2.dispatch();
	process2.report();

	process2.exit();
	process2.report();

	Process process3;
	process3.create();
	process3.report();

	process3.dispatch();
	process3.report();

	process3.suspend();
	process3.report();

	process3.dispatch();
	process3.report();


	process3.exit();
	process3.report();

}