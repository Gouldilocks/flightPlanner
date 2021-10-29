//
// Created by Christian Gould on 10/20/20.
//

#ifndef INC_20F_FLT_PLN_ADJACENCYLISTY_H
#define INC_20F_FLT_PLN_ADJACENCYLISTY_H
#include <iostream>
#include "LinkyList.h"
#include "Vecty.h"
#include "keyCode.h"
#include <exception>
#define debugAdj false
using namespace std;
template <class t, class p>
class adjacencyListy {
public:
	adjacencyListy<t,p>(){
		this-> iterating = false;
	}
void addEdge(t first, p second){
		iterating = false;
	if(debugAdj)cout << "size of key: " << key.getSize() << endl;
	if(debugAdj)cout << "size of adj: " << adj.getSize () << endl;
	// check for the first element in the key
	int keyFind = key.binarySearch(keyCode<t>(first),0, key.getSize()-1);
	// if the element was found in the key vector
	if(keyFind != -1){
		adj[key[keyFind].pos].push_back (second);
		adj[key[keyFind].pos].insertionSort ();
		return;
		// if the first element was never found
	} else {
		if(debugAdj)cout << "Not found in Key. Adding: " << first << " to key" << endl;
		// if the first was never found in any of the elements, add it
		key.push_back(keyCode<t>(first,key.getSize()));
		key.insertionSort();
		// add element and sort
		adj.push_back (LinkyList<p>(second));
		// sort the new list which was added(just to fix sorted variable)
		adj[ adj.getSize () - 1 ].insertionSort ();
	}
	iterateStart ();
}
// returns the first value from the list after val, and returns val if not found.
p& at(t val, int at){
	int search = key.binarySearch((keyCode<t>(val)),0,key.getSize()-1);
	if(search == -1){
		//cout << "out of bounds or not found" << endl;
		throw out_of_range("binary search error, adjacency list");
	} else {
		return adj[key[search].pos][at];
	}
}
void printAll(){
	for(int i = 0; i < key.getSize (); i++){
		cout << "Left Side: ";
		cout << key[i] << endl;
		int keyd = key[i].pos;
		if(debugAdj)cout << "In list number: " << keyd << endl;
		for(int x = 0; x < adj[keyd].getSize (); x++){
			cout << adj[keyd][x] << endl;
		}
		cout << endl;
	}
}
void iterateStart(){
		keyiter = key.begin();
		adjiter = adj[(*keyiter).pos].begin ();
		iterating = true;
	}
	p& right(){
		if(!iterating) iterateStart ();
		mvRight ();
		return *adjiter;
	}
	void mvRight(){
		if(!iterating) iterateStart ();
		++adjiter;
	}
	p& left(){
		if(!iterating) iterateStart ();
		mvLeft ();
		return *adjiter;
	}
	void mvLeft(){
		if(!iterating) iterateStart ();
		--adjiter;
	}
	t& down(){
		if(!iterating) iterateStart ();
		mvDown ();
		return (*keyiter).firsty;
	}
	// this will move down without returning
	void mvDown(){
		if(!iterating) iterateStart ();
		++keyiter;
		adjiter = adj[(*keyiter).pos].begin();
	}
	// this will move the pointer up and return the value
	t& up(){
		if(!iterating) iterateStart ();
		mvUp();
		return (*keyiter).firsty;
	}
	// this will move the pointer up without returning the value
	void mvUp(){
		if(!iterating) iterateStart ();
		--keyiter;
		adjiter = adj[(*keyiter).pos].begin();
	}
	// this will return the current destination
	p& peek(){
		if(!iterating) iterateStart ();
		return *adjiter;
	}
	// returns the maximum number of right steps there are to make
	int rightMax(){
		return adj[(*keyiter).pos].getSize ();
	}
	// this will return the current y position of the list
	int currRight(){
		return adjiter.getPos ();
	}
	// returns the maximum number of down steps there are to make
	int downMax(){
		return this-> key.getSize ();
	}
	// this will return the current x position of the list
	int currDown(){
		return (*keyiter).pos;
	}
	// this will return the current starting point
	t& where(){
		if(!iterating) iterateStart();
		return (*keyiter).firsty;
	}
	adjacencyListy<t,p>& operator=(const adjacencyListy<t,p>& rhs){
		if(*this == rhs) return *this;
		this-> adj = rhs.adj;
		this-> key = rhs.key;
		this-> keyiter = rhs.keyiter;
		this-> adjiter = rhs.adjiter;
		this-> iterating = rhs.iterating;
	}
	bool operator== (const adjacencyListy<t,p>& rhs){
		return (this-> adj == rhs.adj && this-> key == rhs.key && this-> keyiter == rhs.keyiter && this-> adjiter == rhs.adjiter && this-> iterating == rhs.iterating);
	}
	p& operator[](int find){
		if(find == 0){
			iterateStart ();
			return peek ();
		}
		else{
			find--;
			if(find < this->downMax ()){
			mvDown ();
			(*this)[find];
			} else return peek();
		}
	}
	void mvToFirst_Elem(const t& findMe){
		iterateStart();
		if(debugAdj)cout << "FIRST ELEM\n-------------" << endl;
		if(debugAdj)cout << "iterator w/ dereference: " << *keyiter << endl;
		if(debugAdj)cout << "iterator w/ dereference and .firsty: " << (*keyiter).firsty << endl;
		if(debugAdj)cout << "findMe: " << findMe << endl;
		int counter = 0;
		while((findMe != (*keyiter).getFirsty ()) && (counter < downMax ()-1)){
			counter++;
			//cout << "downMax-1 = " << downMax()-1 << endl;
			//cout << "looping: " << counter <<  endl;
			mvDown ();
		}
	}
	// returns a bool of whether or not the current city has children
	bool hasChildren(){
		for(int i = 0; i < key.getSize(); i++){
			if((*adjiter) == key[i].getFirsty()) {
				cout << "true children method" << endl;
				cout << (*adjiter).getDestination() << " == " << key[i] << endl;
				return true;
			}
		}
		return false;
	}
private:
	LinkyList<LinkyList<p>> adj;
	Vecty<keyCode<t>> key;
	vectyIter<keyCode<t>> keyiter;
	LinkyIter<p> adjiter;
	bool iterating;
};
#endif //INC_20F_FLT_PLN_ADJACENCYLISTY_H
