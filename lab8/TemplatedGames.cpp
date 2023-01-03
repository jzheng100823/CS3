//template Dice game
//lab 8
//Jerry Zheng


#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game {
public:
    Game() :playersCount_(0), movesCount_(0), playerWon_(noWinner) {}

    // template method
    void playGame(const int playersCount = 0) {
        playersCount_ = playersCount;
        movesCount_ = 0;

        initializeGame();

        for (int i = 0; !endOfGame(); i = (i + 1) % playersCount_) {
            makeMove(i);
            if (i == playersCount_ - 1)
                ++movesCount_;
        }
        printWinner();
    }

    virtual ~Game() {}

protected:
    // primitive operations
    virtual void initializeGame() = 0;
    virtual void makeMove(int player) = 0;
    virtual void printWinner() = 0;
    virtual bool endOfGame() { return playerWon_ != noWinner; } // this is a hook
                    // returns true if winner is decided
    static const int noWinner = -1;

    int playersCount_;
    int movesCount_;
    int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly : public Game {
public:
    // implementing concrete methods
    void initializeGame() {
        playersCount_ = rand() % numPlayers_ + 1; // initialize players
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) {
            const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
            if (chance < movesCount_) playerWon_ = player;
        }
    }

    void printWinner() {
        cout << "Monopoly, player " << playerWon_ << " won in "
            << movesCount_ << " moves." << endl;
    }

private:
    static const int numPlayers_ = 8; // max number of players
    static const int minMoves_ = 20; // nobody wins before minMoves_
    static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
// primitive operations
class Chess : public Game {
public:
    void initializeGame() {
        playersCount_ = numPlayers_; // initalize players
        for (int i = 0; i < numPlayers_; ++i)
            experience_[i] = rand() % maxExperience_ + 1;
    }

    void makeMove(int player) {
        if (movesCount_ > minMoves_) {
            const int chance = (rand() % maxMoves_) / experience_[player];
            if (chance < movesCount_) playerWon_ = player;
        }
    }

    void printWinner() {
        cout << "Chess, player " << playerWon_
            << " with experience " << experience_[playerWon_]
            << " won in " << movesCount_ << " moves over"
            << " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
            << endl;
    }

private:
    static const int numPlayers_ = 2;
    static const int minMoves_ = 2; // nobody wins before minMoves_
    static const int maxMoves_ = 100; // somebody wins before maxMoves_
    static const int maxExperience_ = 5; // player's experience
                               // the higher, the greater probability of winning
    int experience_[numPlayers_];
};
class Dice :public Game {
public:
    void initializeGame() {
        playersCount_ = numPlayer_;
    }
    void makeMove(int player) {
        if (movesCount_ < maxMoves_) {

            //computer turn to roll the dice 
            if (cpuMove_ == true && player == 0) {
                int cpu_Total = 0;
                cout<<"Round "<<++round<<":"<< "computer Rolled ";
                for (int i = 0;i < 5;++i) {
                    int roll = rand() % 6 + 1; //generate number form 1-6
                    cout << roll << " ";
                    cpu_Total += roll; //adds all the numbers 
                }
                cout << "= " << cpu_Total;
                if (cpu_Total > cpu_Max) { //checks to see if the current score is higher than the max or not
                    cpu_Max = cpu_Total; //if it is then we set it as the max 
                }
                cout << " computers highest score is:" << cpu_Max << endl;

                if (movesCount_ < maxMoves_ - 1) {
                    int again = rand() % 11 + 1;
                    if (again >= 6) {
                        cpuMove_ = false;
                        
                    }
                }
            }
            else if (cpuMove_ == false && player == 0) {
                cout <<"Round "<<++round<<":"<< "computer rolled: passed computer highest score is " << cpu_Max << endl;
                cpuMove_ = true;

                if (movesCount_ < maxMoves_ - 1) {
                    int again = rand() % 11 + 1; //this will generate some random values to see if the computer will roll or pass
                    if (again >= 6) { //if the number generated is more than 6 than the computer will pass
                        cpuMove_ = false;
                    }
                }
            }
            if (humanMove_ == true && player == 1) {
                int human_Total = 0;
                cout << "you rolled"<<" ";
                for (int i = 0; i < 5;++i) {
                    int roll = rand() % 6 + 1; //generates randomn numbers from 1-6
                    cout << roll << " ";
                    human_Total += roll; //adds them all together
                }
                cout << "= " << human_Total;
                if (human_Total > human_Max) { //checks to see if the current score is higher than the max 
                    human_Max = human_Total; //if it is then it will be the new max score 
                }
                cout << " your highest score is " << human_Max << endl;
                if (movesCount_ < maxMoves_ - 1) {
                    char roll_again;
                    cout << "Roll Again[y/n]";
                    std::cin >> roll_again;
                    if (roll_again == 'n') {
                        humanMove_ = false;
                    }
                }
            }
            //if the user does not want to roll again 
            else if (humanMove_ == false && player == 1) {
                cout << "You rolled: passed, your highest score = " << human_Max << endl;
                humanMove_ = true;
                if (movesCount_ < maxMoves_ - 1) { //next move 
                    char roll_again;
                    cout << "Roll Again[y/n]";
                    std::cin >> roll_again; //ask for user input
                    if (roll_again == 'n') {
                        humanMove_ = false; //sets the next move to false;

                    }
                }
            }
        }
        else {
            if (cpu_Max > human_Max) {//if your score is less than the computers score
                playerWon_ = 1;
            }
            if (human_Max>cpu_Max) { //if your score is more than the computers score
                playerWon_ = 2;
            }
            if (cpu_Max == human_Max) {//if your score is tied with the computers score
                playerWon_ = 3;
            }
        }
    }
    //these print either if you win lose or tie
    void printWinner(){
    
        if (playerWon_ == 1) {
            cout << "you lose";
        }
        if (playerWon_ == 2) {
            cout << "you win";
        }
        if (playerWon_ == 3) {
            cout << "it is a tie ";
        }

    }
private:
    static const int numPlayer_ = 2;
    static const int minMoves_ = 1;
    static const int maxMoves_ = 3;
    int cpu_Max = 0;
    int human_Max = 0;
    bool cpuMove_ = true;
    bool humanMove_ = true;
    int round = 0;



};

int main() {
    srand(time(nullptr));

    Game* gp = nullptr;
    /*
    // play chess 8 times
    for (int i = 0; i < 8; ++i) {
        gp = new Chess;
        gp->playGame();
        delete gp;
    }


    // play monopoly 8 times
    for (int i = 0; i < 8; ++i) {
        gp = new Monopoly;
        gp->playGame();
        delete gp;
    }
    */

        gp = new Dice;
        gp->playGame();
        delete gp;
   
}