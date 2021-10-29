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
#ifndef INC_20F_AUTO_IDX_VECTYITER_H
#define INC_20F_AUTO_IDX_VECTYITER_H
using namespace std;
template <class t>
class vectyIter{
private:
	t* payload;
	int position;
public:
	vectyIter<t> (){
		this->payload = nullptr;
		this-> position = 0;
	}
	vectyIter(t* newLoad){
		this-> payload = newLoad;
	}
	vectyIter(t* newLoad, const int& position){
		this-> payload = newLoad;
		this-> position = position;
	}
	vectyIter& operator++(){
	++payload;
	++position;
	}
	vectyIter& operator++(int){
		++payload;
		++position;
	}
	vectyIter& operator--(){
	--payload;
	--position;
	}
	vectyIter& operator--(int){
		--payload;
		--position;
	}
	vectyIter& operator=(const vectyIter& rhs){
		this-> payload = rhs.payload;
		this-> position = rhs.position;
	}
	t operator->(){
		return *payload;
	}
	t& operator*(){
		return *payload;
	}
	friend bool operator == (const vectyIter<t>& lhs, const vectyIter<t>& rhs){
		return lhs.payload == rhs.payload && lhs.position == rhs.position;
	}
	bool operator !=(const vectyIter<t>& rhs){
		return payload != rhs.payload && position != rhs.position;
	}
	int getPos(){
		return position;
	}
};
#endif //INC_20F_AUTO_IDX_VECTYITER_H
