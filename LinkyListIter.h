//
// Created by Christian Gould on 9/24/20.
//
/* references
 * https://stackoverflow.com/questions/21569483/c-overloading-dereference-operators
 * used to find out how to change dereference operators
 *
 * https://users.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html
 * used to find how to make a basic iterator class
 * */
#ifndef INC_20F_AUTO_IDX_LINKYLISTITER_H
#define INC_20F_AUTO_IDX_LINKYLISTITER_H
using namespace std;
#include "Nody.h"
template <class t>
class LinkyIter{
private:
	Nody<t>* payload;
	int position;
public:
	LinkyIter<t>(){
		this-> payload = nullptr;
		this-> position = 0;
	}
	LinkyIter(Nody<t>* newLoad){
		this-> payload = newLoad;
	}
	LinkyIter(Nody<t>* newLoad, const int& pos){
		this-> payload = newLoad;
		this-> position = pos;
	}
	LinkyIter& operator++(){
		payload = payload->getNext();
		position++;
	}
	LinkyIter& operator++(int){
		payload = payload->getNext();
		position++;
	}
	LinkyIter& operator--(){
		payload = payload->getPrev();
		position--;
	}
	LinkyIter& operator--(int){
		payload = payload->getPrev();
		position--;
	}
	LinkyIter& operator=(const LinkyIter& rhs){
		this-> payload = rhs.payload;
		this->position = rhs.position;
	}
	t operator->(){
		return payload->getPayload();
	}
	t& operator*(){
		// if the node is end() payload will be nullptr
		if (this-> payload == nullptr) throw exception(invalid_argument("tried to dereference a linkyList iterator and failed"));
		// otherwise return the payload
		return payload->getPayload();
	}
	int getPos(){
		return this-> position;
	}
	friend bool operator == (const LinkyIter<t>& lhs, const LinkyIter<t>& rhs){
		return lhs.payload == rhs.payload && lhs.position == rhs.position;
	}
	bool operator !=(const LinkyIter<t>& rhs){
		return payload != rhs.payload && this->position != rhs.position;
	}
};
#endif //INC_20F_AUTO_IDX_LINKYLISTITER_H
