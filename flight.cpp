//
// Created by Christian Gould on 10/21/20.
//
#include "flight.h"

ostream& operator<< (ostream &OS, const flight &S) {
	if(S.possible) {
		OS << S.visited[ 0 ].getDestination ();
		OS << "(" << S.visited[ 0 ].getAirline() << ")";
		for (int i = 1; i < S.visited.getSize (); i++) {
			OS << " -> " << S.visited[ i ].getDestination ();
			OS << "(" << S.visited[ i ].getAirline() << ")";
		}
		OS << ". Time: " << S.totalTime () << " Cost: " << S.totalCost () << endl;
	}
	else {
		OS << S.original << endl;
	}
	return OS;
}

flight::flight (){
	this->possible = true;
	this-> original = "nah fam";
}

flight::flight (const flight &copy) {
this-> visited = copy.visited;
this-> orderedBy = copy.orderedBy;
	this-> possible = copy.possible;
}
flight::flight(const destinationCity& stop){
	visited.push_back(stop);
}
flight::~flight () = default;

double flight::totalCost () const {
	//cout << "inside : " << this->getOrigin () << endl;
	double totalC = 0;
	Stringy currAir = visited[1].getAirline();
	//cout << "curr airline: " << currAir << endl;
	//calculate the number of layovers
	// subtract the beginning flight and the end flight
	int numLayovers = visited.getSize() -2;
	totalC += (19*numLayovers);
	for(int i = 1; i < visited.getSize(); i++){
		//cout << "adding " << visited[i].getCost() << endl;
		totalC+= visited[i].getCost ();
			// if there is not another airline after
//		if(visited[i].getAirline() == currAir) {
//			continue;
//		}
//		else{
//			currAir = visited[i].getAirline();
//			totalC+= 19;
//		}
	}
	//cout << "total cost: " << totalC << endl;
	return totalC;
}

double flight::totalTime () const {
	double totalT = 0;
	Stringy currAir = visited[1].getAirline();
	//cout << "curr airline: " << currAir << endl;
	int numLayovers = visited.getSize() -2;
	totalT += 43*numLayovers;
	for(int i = 1; i < visited.getSize(); i++){
		// add layover time and flight time
		totalT+= visited[i].getNumMinutes();
		// add the layover time if there is another flight after this one
		//if(i != visited.getSize()-1) totalT += 43;
		// if there is not another airline after
//		else break;
		//totalT+= 43;
		if(visited[i].getAirline() == currAir) {
			continue;
		}
		// if the company is not the same, add additional 22 minutes to layover
		else{
			currAir = visited[i].getAirline();
			totalT+= 22;
		}
	}
	return totalT;
}

void flight::addstop (const destinationCity &stop) {
visited.push_back(stop);
}

flight &flight::operator= (const flight &rhs) {
	this-> visited = rhs.visited;
	this-> orderedBy = rhs.orderedBy;
	this-> possible = rhs.possible;
	this->original = rhs.original;
	return *this;
}

bool flight::operator< (const flight &rhs) {
	if(orderedBy == 'T'){
		return totalTime () < rhs.totalTime();
	}
	else if(orderedBy == 'C'){
		return totalCost () < rhs.totalCost();
	}
	else throw logic_error("Operator < flight, orderedBy is not T or C");
}

bool flight::operator== (const flight &rhs) {
	if(orderedBy == 'T'){
		return totalTime () == rhs.totalTime();
	}
	else if(orderedBy == 'C'){
		return totalCost () == rhs.totalCost();
	}
	else throw logic_error("Operator == flight, orderedBy is not T or C");
}

Stringy flight::getOrigin () const {
	if(possible) {
		return this->visited[ 0 ].getDestination ();
	}
	else return visited[0].getDestination();
}
Stringy flight::getDestination() {
	if (possible) {
		return this->visited[ visited.getSize () - 1 ].getDestination ();
	}
	else return visited[1].getDestination();
}

Stringy flight::getOrderedBy () {
	if(orderedBy == 'T'){
		return Stringy("(Time)");
	}
	else if(orderedBy == 'C') return Stringy("(Cost)");
	else cout << "orderedby happens to be " << orderedBy << endl;
}

flight::flight (stacky<destinationCity> stacky,char ord) {
	this-> possible = true;
	this-> orderedBy = ord;
cout << "this stack: ************" << endl;
//stacky.printAll();
//cout << "flight constructor ordered by: " << orderedBy << endl;
stacky.reverse ();
//cout << "reversed: ********** " << endl;
stacky.printAll();
//cout << "**********" << endl;
cout << "the stack size is : " << stacky.getSize() << endl;
int run = stacky.getSize();
for(int i = 0; i < run; i++){
	cout << "i is " << i << " and size is " << stacky.getSize() << endl;
	this->visited.push_back(stacky.unstack());
}
cout << "this visited size is: " << this->visited.getSize() << endl;
cout << "**************" << endl;
}

flight::flight (bool able) {
	this-> possible = able;
	this->original = Stringy("impossible");
	this->orderedBy = 'N';
}

bool flight::getPossible () {
	return this-> possible;
}

flight::flight (const Stringy &start, const Stringy &stop, char ord) {
this-> original = "Flight from " + start + " to " + stop + " is not possible, no paths shown.";
this-> possible = false;
this->visited.push_back(destinationCity(start,0,0,"none"));
this->visited.push_back(destinationCity(stop,0,0,"none"));
this->orderedBy = ord;
}
