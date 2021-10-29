//
// Created by Christian Gould on 9/15/20.
//
/*
 * Insertion sort adapted from professor Gabrielson's lecture materials
 */
#ifndef INC_20F_AUTO_IDX_VECTY_H
#define INC_20F_AUTO_IDX_VECTY_H
#define debug true
#include "List.h"
#include "VectyIter.h"
#include <iostream>
using namespace std;

template <class t>
class Vecty : public List<t> {
public:
	/* iterator */
// returns the first element in the yvector
vectyIter<t> begin() {
	return vectyIter<t>(this-> yvector, 0);
}
// returns the theoretical next element after the last
vectyIter<t> end(){
	return vectyIter<t>(this->yvector + this->size, -1);
}

	/* constructors */
	// default constructor
	Vecty()  : List <t>(){
		this->size = 0;
		this-> yvector = nullptr;
	}
	// copy constructor
	Vecty(const Vecty& v) : List <t>(){
		this-> size = v.size;
		this-> yvector = new t[this->size];
		for(int i = 0; i < this->size; i++){
			this-> yvector[i] = v.yvector[i];
		}
	}
	// constructor given one element t
	Vecty(const t& addMe) : List <t>(){
		this-> yvector = new t[1];
		this->yvector[1] = addMe;
		this->size = 1;
	}
	/* destructor */
	~Vecty () {
		delete []this-> yvector;
	}
	/* functions */
	void push_back(const t& pushMe){
		// make temp variable, and copy the old elements into it
		t old[this->size];
		for(int i = 0; i < this->size; i++){
			old[i] = yvector[i];
		}
		++this-> size;
		delete []this-> yvector;
		this-> yvector = new t[this->size];
		// copy each of the old elements into the new resized array
		for(int i = 0; i < this->size-1; i++){
			this->yvector[i] = old[i];
		}
		// add the new element
		this->yvector[this->size-1] = pushMe;
	}
	void remove(int remMe) {
		// copy the old elements into this array
		t old[this->size];
		for(int i = 0; i < this->size; i++){
			old[i] = this-> yvector[i];
		}
		--this->size;
		delete []this->yvector;
		this->yvector = new t[this->size];
		// will change i, and skip the index that needs to be put in.
		// ex.) if remMe == 2, then it will skip adding yvector[i].
		for(int i = 0; i < this->size; i++){
			if(i == remMe) break;
			this-> yvector[i] = old[i];
		}
		for (int i = remMe; i < this->size; i++){
			this-> yvector[i] = old[i+1];
		}
	}
	// function has incorrect input handling: If findMe exceeds the array, then it will return final element
	t& at(int findMe){
		if (findMe >= this-> size){
#ifdef DEBUG_MODE
			{cout << "exceeded bounds of vector" << endl;}
#endif
			return this-> yvector[this->size-1];
		} else {
			return this-> yvector[findMe];
		}
	}
	void insertionSort(){
		int thisSizey = this->getSize ();
		// this integer is a counter for each element in the array
		int i;
		// this integer is a counter for the index of the current element being sorted
		int j;
		// temporary variable to swap
		t temp;

		for (i = 1; i < thisSizey; ++i) {
			j = i;
			// Insert yvector[i] into sorted part
			// stopping once yvector[i] in correct position
			while (j > 0 && yvector[j] < yvector[j - 1]) {

				// switch yvector [j] and yvector[j-1]
				temp = yvector[j];
				yvector[j] = yvector[j - 1];
				yvector[j - 1] = temp;
				--j;
			}
		}
		this->sorted = true;
	}
	// returns an iterator to the given parameter in the vector, and if not found, returns .end()
	vectyIter<t> find(t findMe){
		vectyIter<t> returnMe = this->begin();
		for(returnMe; returnMe != this->end(); ++returnMe){
			if(*returnMe == findMe) break;
		}
		// return the iterator
		return returnMe;
	}
	/* operators */
	Vecty& operator=(const Vecty& rhs){
		if(this != &rhs) {
			delete[] yvector;
			this->size = rhs.size;
			this->yvector = new t[this->size];
			for (int i = 0; i < this->size; i++) {
				this->yvector[ i ] = rhs.yvector[ i ];
			}
			return *this;
		}
	}
	// returns an element without bound protection
	t& operator[] (const int ret)const {
	return yvector[ret];
	}
	/* Operators */
	bool operator==(const Vecty<t>& rhs) const {
		// if they are the same size, execute comparison
		if(rhs.getSize() == this->getSize ()){
			// loop through all the elements
			for(int i = 0; i < this->size; i++){
				// if the elements are not the same, return false
				if(this->operator[] (i) != rhs[i]) return false;
			}
			return true;
			// if they are not the same size, return false
		} else return false;
	}
	// checks if every element in this vector is less than the ones in the right hand side
	bool operator< (const Vecty<t>& rhs){
		for(int i=0, j = 0; i < this->size && j < rhs.size; i++,j++){
			if (!((*this)[i] < rhs[j]))return false;
		}
		return true;
	}

private:
	t* yvector;
};
#endif //INC_20F_AUTO_IDX_VECTY_H
