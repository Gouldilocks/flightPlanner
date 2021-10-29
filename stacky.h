//
// Created by Christian Gould on 10/20/20.
//

#ifndef INC_20F_FLT_PLN_STACKY_H
#define INC_20F_FLT_PLN_STACKY_H
#include <iostream>
#include "LinkyList.h"
using namespace std;
template <class t>
class stacky{
public:
	/* Constructors */
	stacky<t>() = default;
	stacky<t>(t input){
		stacker.push_back(input);
	}
	stacky<t>(const stacky<t>& st){
		this-> stacker = st.stacker;
	}
	/* Destructor */
	~stacky() = default;
	/* Functions */
	void stack(t input){
		stacker.push_front (input);
	}
	// returns a copy of the element to be unstacked
	t unstack(){
		if(this->stacker.getSize () == 0) throw exception();
		t returnMe = t(stacker[0]);
		stacker.remove (0);
		return returnMe;
	}
	int getSize() const{
		return stacker.getSize();
	}
	bool isEmpty(){
		return stacker.getSize() == 0;
	}
	t peek() const{
		return stacker[0];
	}
	void reverse(){
		LinkyList<t> reversed = stacker;
		for(int i = stacker.getSize()-1, j = 0; i>=0; i--, j++){
			stacker[j] = reversed[i];
		}
	}
	void printAll(){
		cout << "printing all" << endl;
		for(int i = 0; i < stacker.getSize(); i++){
			cout << stacker[i] << endl;
		}
	}
	/* Operators */
	stacky& operator= (const stacky<t>& rhs){
		stacker = rhs.stacker;
	}
private:
	// in this linked list, the front of the list is the top of the stack.
	LinkyList<t> stacker;
};
#endif //INC_20F_FLT_PLN_STACKY_H
