//Jerry Zheng
//Template Class and its definitions

#ifndef TEMPLATELIST_HPP
#define TEMPLATELIST_HPP

#include <iostream>
using std::cout; using std::endl;

// template class for node
template <typename T>
class node {
public:
	node() : next_(nullptr) {}
	T getData() const { return data_; }
	void setData(const T& data) { data_ = data; }
	node<T>* getNext()const;
	void setNext(node<T>* const);

private:
	T data_;
	node<T>* next_;
};
//return the next node
template <typename T>
node<T>* node<T>::getNext() const {
	return next_;
}
// sets the  node to point to whatever position 
template <typename T>
void node<T>::setNext(node<T>* const next) {
	next_ = next;
}

//template class for collection
template <typename T>
class Collection {
public:
	Collection() : head(nullptr) {};
	void add(const T&);
	void remove(const T&);
	void print();
	T last();
	template<typename U>
	friend bool equal(const Collection<U>&, const Collection<U>&);
private:
	node<T>* head;// private pointer of node class to point to the next head

};
//add data type to the list
template <typename T>
void Collection<T>::add(const T& data) {
	node<T>* next = new node<T>(); //create a new node to add the data

	next->setData(data); //sets the data to point at the element
	next->setNext(head);//sets the pointer to the head 
	head = next;//points to the next space
}


template <typename T>
void Collection<T>::print() {
	node<T>* i = new node<T>();
	cout << "Your List" << endl;
	i = head;                    //make the node i point to the head
	while (i!= nullptr) {        // while the list is not empty 
		cout << i->getData() << endl; //points to the element and print it out
		i = i->getNext();          //pointer now points to the next element
	}
}

template<typename T>
T Collection<T>::last() {
	return head->getData(); //returns the last element addes
}
template<typename T>
void Collection<T>::remove(const T& data) {
	node<T>* tmp;
	node<T>* h;
	h= head;
	while (head->getData() == data) { //while the element pointer matches the data 
		head = head->getNext();       // it will skip over that element and point to next one
	}

 	while (h->getNext() != nullptr) { //while the next element is not a nullptr
		if (h->getNext()->getData() == data) { //if the next element and the data match
			tmp = h->getNext();               //then we store the position in the tmp variable
			h->setNext(h->getNext()->getNext());// we skip the next element and move to the next
			delete tmp; //remove the element
			
		}
		else {  // if the data does not match the element 
			tmp = h; // we set the position to head
			h = h->getNext(); //we move forward to next element
		}
	}
}
template <typename U>
bool equal(const Collection<U>& l, const Collection<U>& r) {
	node<U>* left;
	node<U>* right;
	left = l.head;
	right = r.head;
	if (left == nullptr && right == nullptr) { // if both list are empty then we can say they are both empty 
		return true;
	}
	if (left == nullptr && right != nullptr || left != nullptr && right == nullptr) { //if a one list is shorter than another
		return false;
	}
	while (left != nullptr && right != nullptr) { //while both list are not empty
		if (left->getData() != right->getData()) { //if the pointer that is pointing to both elements are not the same 
			return false;
		}
		left = left->getNext();//move to next element
		right = right->getNext();//move to next element
	}
	return true; //if both elements are the same

}


#endif


