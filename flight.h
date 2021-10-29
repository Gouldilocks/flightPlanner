//
// Created by Christian Gould on 10/21/20.
//

#ifndef INC_20F_FLT_PLN_FLIGHT_H
#define INC_20F_FLT_PLN_FLIGHT_H
#include <iostream>
#include "Vecty.h"
#include "Stringy.h"
#include "destinationCity.h"
#include "stacky.h"

using namespace std;
class flight{
public:
	/* Constructors */
	flight();
	flight(bool able);
	flight(const flight& copy);
	flight(const destinationCity& stopOne);
	flight(stacky<destinationCity> stacky,char ord);
	// impossible flight constructor
	flight(const Stringy& start, const Stringy& stop, char ord);
	/* Destructor */
	~flight();
	/* Functions */
	// returns whether the flight is possible or not
	bool getPossible();
	// returns the name of the starting city
	Stringy getOrigin() const;
	// returns the name of the ending destination
	Stringy getDestination();
	// returns the way in which the flight will be organized
	Stringy getOrderedBy();
	// returns the total cost of the flight including layover fees
	double totalCost() const;
	// returns the total time of the flight path including layovers
	double totalTime() const;
	// adds an airline stop pair to the list
	void addstop(const destinationCity& stop);
	/* Operators */
	friend ostream &operator<< (ostream &OS, const flight &S);
	flight& operator= (const flight& rhs);
	bool operator< (const flight& rhs);
	bool operator==(const flight& rhs);
private:
	Stringy original;
	Vecty<destinationCity> visited;
	char orderedBy;
	bool possible;
};
#endif //INC_20F_FLT_PLN_FLIGHT_H
