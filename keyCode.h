//
// Created by loggityloglog on 10/21/20.
//

#ifndef INC_20F_FLT_PLN_KEYCODE_H
#define INC_20F_FLT_PLN_KEYCODE_H
template <class t>
class keyCode {
public:
	int pos;
	t firsty;
	keyCode(){
		pos = 0;
		firsty = t();
	}
	keyCode(t first, int position = 0){
		firsty = first;
		pos = position;
	}
	t getFirsty(){
		return this-> firsty;
	}
	friend bool operator< (const keyCode& lhs, const keyCode& rhs){
		return lhs.firsty < rhs.firsty;
	}
	friend ostream& operator<< (ostream &OS, const keyCode &S) {
		OS << S.firsty;
		return OS;
	}
	friend bool operator== (const keyCode& lhs, const keyCode& rhs){
		return lhs.firsty == rhs.firsty;
	}
	bool operator!=(const keyCode& rhs){
		return !((*this) == rhs);
	}
};
#endif //INC_20F_FLT_PLN_KEYCODE_H
