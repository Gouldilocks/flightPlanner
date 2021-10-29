//
// Created by Christian Gould on 10/20/20.
//

#ifndef INC_20F_FLT_PLN_FLIGHTPLANNER_H
#define INC_20F_FLT_PLN_FLIGHTPLANNER_H
#include <iostream>
#include "adjacencyListy.h"
#include "destinationCity.h"
#include "city.h"
#include "stacky.h"
#include "flight.h"
using namespace std;
class flightPlanner{
public:
	/* Constructors */
	flightPlanner();
	flightPlanner(const flightPlanner& copy);
	/* Destructor */
	/* Functions */
	void determineFlights(ifstream& flightPlans,ifstream& f,ofstream& o);
	void iterativeBacktracking();
	void takeInput(ifstream& flightPlans, ifstream& reqFlights);
	void output_Result(ofstream& output);
	void printCombos();
	bool nameContains(stacky<destinationCity>& st, const Stringy& stringy);
	/* Operators */

private:
	// this is an adjacency list of all the different places a flight can go
adjacencyListy<city,destinationCity> flightPlans;
	// this is an adjacency list of all the start and stops planned to travel
Vecty<pair<Stringy,Stringy>> begAndEnds;
Vecty<char> sorts;
// this is a vector of vector of flights which represents all the possible combinations
Vecty<Vecty<flight>> combinations;
};
#endif //INC_20F_FLT_PLN_FLIGHTPLANNER_H
