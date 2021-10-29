//
// Created by Christian Gould on 9/15/20.
//
/*
* Insertion sort adapted from professor Gabrielson's lecture materials
*/
 #ifndef INC_20F_AUTO_IDX_LINKYLIST_H
#define INC_20F_AUTO_IDX_LINKYLIST_H
#define debug false
#include "List.h"
#include "Nody.h"
#include "LinkyListIter.h"
using namespace std;

template<class t>
// default will set the head and tail to null
class LinkyList : public List<t> {
private:
	Nody<t> *head;
	Nody<t> *tail;
public:
	/* Iterator */
	LinkyIter<t> begin () const {
		return LinkyIter<t> (this->head,0);
	}

	LinkyIter<t> end () const {
		return LinkyIter<t> (this->tail->getNext (),-1);
	}

	// default constructor makes sure the head and tail are null
	LinkyList () : List<t> () {
		this->head = nullptr;
		this->tail = nullptr;
		this->size = 0;
	}

	// this will make a deep copy of the head and tail of given LinkyList
	LinkyList (const LinkyList<t> &newGuy) : List<t> () {
		if (newGuy.head == nullptr && newGuy.tail == nullptr) {
			this->head = this->tail = nullptr;
			this-> size = newGuy.size;
		} else {
			for(int i = 0; i < newGuy.size; i++){
				this->push_back(newGuy[i]);
			}
		}
	}
	// is using the above constructor when I want to use this one below. This is because it is actually a LinkyList<t> which I am trying to call constructor of
	LinkyList (const t& firstElem) : List<t> (){
		this-> head = nullptr;
		this-> tail = nullptr;
		this-> size = 0;
		this-> push_back (firstElem);
	}
	// makes a deep copy using the = operator
	LinkyList& operator= (const LinkyList &newGuy){
		// check if they are the same object
		if(*this != newGuy) {
			if (newGuy.head == nullptr && newGuy.tail == nullptr) {
				this->head = this->tail = nullptr;
				this-> size = 0;
				return *this;
			} else {
				if (this->head != nullptr){
					delete this;
				}
				this->head = nullptr;
				this->tail = nullptr;
				this->size = 0;
				for(int i = 0; i < newGuy.size; i++){
					this->push_back(newGuy[i]);
				}
				return *this;
			}
		}
}

	// destructor
	~LinkyList (){
		// set the current to head
		Nody<t>* current = head;
		// while the current pointer is not nullptr / 0
		while( current != 0) {
			// store the next pointer into the next variable
			Nody<t>* next = current->getNext();
			// delete current
			delete current;
			// store that next pointer into the current variable
			current = next;
		}
		head = 0;
	}

	// will put the given element into the back of the linked list
	void push_back (const t& pushMe){
		// if there are no elements set head to tail to the only element
		if (this-> size == 0) {
			head = tail = new Nody<t> (pushMe);
			this->size = 1;
		} else {
			// if there are elements, add it at the end
			tail->setNext (new Nody<t> (pushMe));
			tail->getNext()->setPrev (tail);
			this-> tail = tail->getNext ();
			this->size++;
		}
	}
	void push_front (const t& pushMe){
		// if there are not elements, make it the only element
		if (head == nullptr){
			head =tail = new Nody<t> (pushMe);
			this-> size = 1;
		} else {
			// if there are elements, add it to the front
			Nody<t>* temp = head;
			this-> head = new Nody<t> (pushMe);
			head->setNext(temp);
			temp->setPrev (head);
			this-> size++;
		}
	}
	// returns an iterator to the given parameter in the vector, and if not found, returns .end()
	LinkyIter<t> find(t findMe){
		LinkyIter<t> returnMe = this->begin();
		for(returnMe; returnMe != this->end(); ++returnMe){
			if(*returnMe == findMe) break;
		}
		// return the iterator
		return returnMe;
	}
	// will return the payload of the wanted element in the list
	t& operator[] (int iWant) const{
		int incrementor = 0;
		Nody<t> *temp = this->head;
		while (incrementor < iWant && temp != this->tail) {
			temp = temp->getNext ();
			incrementor++;
		}
		return temp->getPayload ();
	}
	Nody<t>* findNode(int find) const {
		Nody<t>* current = this-> head;
		int counter = 0;
		while(counter < find && current != tail){
			current = current->getNext();
			counter++;
		}
		return current;
	}
	// this will remove the given element in the list
	void remove (int removeMe) {
		if(debug)cout << "size before removal: " << this-> size << endl;
// removing from the beginnning
		if (removeMe == 0) {
			// if there are more than 2 elements
			if (this->size > 2) {
				Nody<t>* deleteMe = this->head;
				this->head = this->head->getNext ();
				delete deleteMe;
				// if there is only 1 element
			} else if (this->size == 1) {
				delete this-> head;
				this->head = this->tail = nullptr;
				// if there is 2 elements
			} else if (this->size == 2) {
				Nody<t>* gone = this->head;
				this->head = this->head->getNext ();
				this->tail = this->head;
				this-> head->setPrev (nullptr);
				this->tail->setPrev (nullptr);
				delete gone;
			}
		} else
// removing from the middle
		if (removeMe > 0 && removeMe < this->size - 1) {
			Nody<t>* currptr = head;
			int i = 0;
			while (currptr != tail && i < removeMe - 1) {
				currptr = currptr->getNext ();
				i++;
			}
			// prev is the element before the one being removed.
			Nody<t> *prev = currptr;
			Nody<t> *toDelete = currptr->getNext ();
			Nody<t> *next = toDelete->getNext ();
			prev->setNext (next);
			next->setPrev (prev);
			delete toDelete;
		} else
// removing from the end
		if (removeMe == this->size - 1) {
			if(this->size <= 1){ this->head = this->tail = nullptr; return;}
			Nody<t> *currptr = head;
			delete tail;
			tail = tail->getPrev ();
			tail->setNext (nullptr);
		}
	// reduce size by one because we have removed an element
	this->size--;
		if(debug)cout << "size after removal: " << this-> size << endl;
	}

	// this will return the size of the linked list
//	int getSize () const {
//		return this->size;
//	}
	// function which will find the size of the linked list if there are problems
	int findSize() const {
		//		// if there are no elements in the list
		if (this->head == nullptr) {
			return 0;
		}
		// if there is only one element in the list
		if (this->head == this->tail) return 1;
		// if there is more than one element in the list
		Nody<t> *temp = this->head;
		int size = 1;
		while (temp != this->tail) {
			temp = temp->getNext ();
			size++;
		}
		return this->size;
	}
	// replaces one element in the Linked list
	void replace (int toRepl, t newGuy){
		int i = 0;
		Nody<t>* temp = head;
		// get the element to be replaced
		while(i < toRepl && temp != tail){
		temp = temp->getNext ();
		i++;
		}
		delete temp->getPayloadptr ();
		temp->setPayload (new t(newGuy));
	}
	void insertionSort(){
		int thisSizey = this->size ;
		// this integer is a counter for each element in the array
		int i;
		// this integer is a counter for the index of the current element being sorted
		int j;
		// temporary variables to swap
		t temp;
		t tempmin;
		for (i = 1; i < thisSizey; ++i) {
			// set the index to be checked to i
			j = i;
			// Insert yvector[i] into sorted part
			// stopping once yvector[i] in correct position
			while (j > 0 && (this->operator[] (j)) < (this->operator[](j - 1))) {
				Nody<t>* nodeJ = this->findNode(j);
				Nody<t>* nodeJmin = this->findNode (j-1);
				temp = nodeJ->getPayload();
				tempmin = nodeJmin->getPayload();
				delete nodeJ->getPayloadptr ();
				delete nodeJmin->getPayloadptr();
				nodeJ->setPayload (tempmin);
				nodeJmin->setPayload (temp);
				--j;
			}
		}
		this->sorted = true;
	}
/* Operators */
	bool operator==(const LinkyList<t>& rhs) const{
		LinkyIter<t> leftIter = begin();
		LinkyIter<t> rightIter = rhs.begin();
		// if the sizes are the same
		if(this->size == rhs.size){
			// loop through all the elements
			while(leftIter != end()){
				// if they are not the same, then return false
				if(*leftIter != *rightIter) {
					if(debug) cout << "wrong by wrong thing" << endl;
					return false;
				}
				if(debug)cout << "left: " << *leftIter << endl;
				if(debug)cout << "right: " << *rightIter << endl;
				++leftIter;
				++rightIter;
			}
			return true;
		}
		// if they are not the same size, return false

		else {
			if(debug)cout << "wrong by size" << endl;
			return false;
		}
	}
	friend bool operator<(const LinkyList<t>& lhs, const LinkyList<t>& rhs){
		return lhs.size < rhs.size;
	}
	bool operator != (const LinkyList<t>& rhs){
		return !((*this) == rhs);
	}
	friend ostream& operator<< (ostream& OS, const LinkyList<t>& rhs){
		for(int i = 0; i < rhs.size; i++){
			OS << (rhs)[i] << " ";
		}
	}
};
#endif //INC_20F_AUTO_IDX_LINKYLIST_H
