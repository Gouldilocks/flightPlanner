//
// Created by loggityloglog on 10/21/20.
//
#include "city.h"

city::city (const Stringy &home) {
	this-> startPoint = home;
}

city::city (const city &copy) {
	this-> startPoint = copy.startPoint;
}

Stringy city::getStartPoint () const {
	return this-> startPoint;
}

void city::setStartPoint (const Stringy &set) {
	this-> startPoint = set;
}

bool operator== (const city &lhs, const city &rhs) {
	return (lhs.startPoint == rhs.startPoint);
}

bool operator< (const city &lhs, const city &rhs) {
	return (lhs.startPoint < rhs.startPoint);
}

city &city::operator= (const city &rhs) {
	if (*this == rhs) return *this;
	else{
		this-> startPoint = rhs.startPoint;
		return *this;
	}
}

ostream &operator<< (ostream &OS, const city &S) {
	OS << S.startPoint;
	return OS;
}

bool operator!= (const city& lhs, const city& rhs){
	return (lhs.startPoint != rhs.startPoint);
}

