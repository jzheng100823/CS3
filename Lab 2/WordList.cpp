#include "WordList.hpp"
// class WordOccurrence

//default constructor
WordOccurrence::WordOccurrence(const std::string& word, int num) {
	word_ = word;
	num_ = num;
}
//checks to seee if the new word matches
bool WordOccurrence::matchWord(const std::string& word) {  //checks to see if word is the same. nword stands for new word
	return word == word_;
}
//increments occurrences
void WordOccurrence::increment() { 
	num_++;
}

std::string WordOccurrence::getWord() const { //gets the word
	return word_;
}

int WordOccurrence::getNum() const {  //get the number of occurrences
	return num_;
}

// class WordList

//default constructor
WordList::WordList() {
	size_ = 0;
	wordArray_ = new WordOccurrence[size_];
}

//copy constructor
WordList::WordList(const WordList& rhs) { //copy constructor
	size_ = rhs.size_;
	wordArray_ = size_ > 0 ? new WordOccurrence[size_] : nullptr;
	std::copy(rhs.wordArray_, rhs.wordArray_ + size_, wordArray_);
}

//overloaded asignment using swap idiom
WordList& WordList::operator=(WordList rhs) { 
	swap(*this, rhs);
	return *this;
}

//swap idiom for the overloading assignment
void swap(WordList& one, WordList& two) { 
	std::swap(one.size_, two.size_);
	std::swap(one.wordArray_, two.wordArray_);
}

//destructor
WordList::~WordList() { 
	delete[] wordArray_;
}

bool equal(const WordList& first, const WordList& second) { // compares two objects to see if they are equal

	if (first.size_ != second.size_) {  // if same size it will return true or it will return false
		return false;
	}
	else {

		for (int i = 0; i < second.size_; i++) { // if same size compare to see if the objects are the same
			if (first.wordArray_[i].getWord() != second.wordArray_[i].getWord()) {
				return false;
			}
			if (first.wordArray_[i].getNum() != second.wordArray_[i].getNum()) {
				return false;
			}
		}
	}
	return true;
}

void WordList::addWord(const std::string& word) { // adds word
	bool matched = false;
	//check if word as already in array
	for (int i = 0; i < size_; i++) {
		if (wordArray_[i].matchWord(word)) {
			wordArray_[i].increment();
			matched = true; // if it matches, match will turn to true
		}
	}

	if (matched == false) { // if the word doest match we then add  
		WordOccurrence* tmp = wordArray_;
		wordArray_ = new WordOccurrence[size_ + 1];    //enlarge array using tmp array
		for (int i = 0; i < size_; i++) {
			wordArray_[i] = tmp[i];
		}
		wordArray_[size_] = word;  // adds new word into new dynamically allocated space
		wordArray_[size_].increment();  //increments the word count after adding word
		delete[] tmp; //calling destructor
		size_++;
	}
}

void WordList::print() {

	std::cout << "Word Count Program" << std::endl;
	std::cout << "Word:" << " \t " <<"Count:" << std::endl;

	for (int i = 0; i < size_; i++) { //for loop to sort the number counts
		for (int j = i + 1; j < size_; j++) {//second for loop used to compare the num_ countd
			if (wordArray_[j].getNum() < wordArray_[i].getNum()) { //checks to see which one has more occurrences
				std::swap(wordArray_[j], wordArray_[i]);  //swap them
			}
		}
	}

	for (int i = 0; i < size_; i++) { //print array

		std::cout << wordArray_[i].getWord() << " \t" <<"\t"<< wordArray_[i].getNum() << std::endl;
	}
}
