//
// Created by loggityloglog on 10/21/20.
//
/*
 * The city object was originally made in order to differentiate
 * between different types of cities, being cities which were the starting
 * location, and the inherited class destination city was
 * going to be all the cities which were visited. This ended up being a little
 * bit of an annoyance, and in retrospect, it would have been simpler and more
 * elegant to implement just one city class.
 */
#ifndef INC_20F_FLT_PLN_CITY_H
#define INC_20F_FLT_PLN_CITY_H
#include <iostream>
#include "Stringy.h"

using namespace std;
class city{
public:
	/* Constructors */
	city() = default;
	city(const Stringy& home);
	city(const city& copy);
	/* Destructor */
	~city() = default;
	/* Function */
	Stringy getStartPoint() const;
	void setStartPoint(const Stringy& set);
	/* Operators */
	friend bool operator== (const city& lhs, const city& rhs);
	friend bool operator< (const city& lhs,const city& rhs);
	city& operator= (const city& rhs);
	friend ostream& operator<< (ostream &OS, const city &S);
	friend bool operator!= (const city& lhs, const city& rhs);
protected:
	Stringy startPoint;
};
#endif //INC_20F_FLT_PLN_CITY_H
