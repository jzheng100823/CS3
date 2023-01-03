//main file for lab 2
//Jerry zheng

#include "WordList.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>

using std::cout; using std::string;using std::endl;

int main(int  argc, char* argv[]) {
    //if user does not enter a file prompts them to 
    if (argc < 2) {
        cout << "Please Enter at least a  File to be Read" << endl;
        return 0;
    }
    //makes an object of word Class
    WordList list;


    //creates a string and for get to read 
    string file = argv[1];
    std::ifstream get(file);
    string words;

    //checks to see if the word is a character
    bool ischar = true;

    //reads int the word
    while (get >> words) {
        for (int i = 0;i < words.length();i++) {
            char x = words[i];

            //uses the isalpha function to check to see if it alphabetic letter and if it is
            //sets to true
            if (isalpha(x)) {
                ischar = true;
            }
            else
                ischar = false;
        }
        //if it is a alphabetic letter then we add it to the wordlist
        if (ischar == true) {
            list.addWord(words);
        }
    }

    //prints the wordlist and closes the files
    list.print();
    get.close();
}
