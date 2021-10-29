//
// Created by loggityloglog on 10/21/20.
//

#ifndef INC_20F_FLT_PLN_DESTINATIONCITY_H
#define INC_20F_FLT_PLN_DESTINATIONCITY_H
#include "city.h"
#include "Stringy.h"
class destinationCity : public city {
public:
	/* Constructors */
	destinationCity() : city(){

	}
	destinationCity(Stringy destination, double cost, double numMinutes, Stringy airline) : city() {
		this-> destination = destination;
		this-> cost = cost;
		this-> numMinutes = numMinutes;
		this-> airline = airline;
	}
	destinationCity(const destinationCity& copy) : city(){
		this-> destination = copy.destination;
		this-> cost = copy.cost;
		this-> numMinutes = copy.numMinutes;
		this-> airline = copy.airline;
	}
	/* Destructor */
	~destinationCity () = default;
	/* Functions */
	Stringy& getDestination(){
		return this-> destination;
	}
	void setDestination(const Stringy& set){
		this-> destination = set;
	}
	double& getCost(){
		return this-> cost;
	}
	void setCost(const double& set){
		this-> cost = set;
	}
	double getNumMinutes(){
		return this-> numMinutes;
	}
	void setNumMinutes(const double& set){
		this-> numMinutes = set;
	}
	Stringy& getAirline(){
		return this-> airline;
	}
	void setAirline(const Stringy& set){
		this-> airline = set;
	}
	/* Operators */
	bool operator== (const destinationCity& rhs){
		return (this-> destination == rhs.destination && this-> cost == rhs.cost && this-> numMinutes == rhs.numMinutes && this-> airline == rhs.airline);
	}
	bool operator!= (const destinationCity& rhs){
		return !((*this) == rhs);
	}
	bool operator< (const destinationCity& rhs){
		return (this-> destination < rhs.destination);
	}
	destinationCity& operator= ( const destinationCity& rhs){
		if(*this == rhs) return *this;
		else {
			this-> destination = rhs.destination;
			this-> cost = rhs.cost;
			this-> numMinutes = rhs.numMinutes;
			this-> airline = rhs.airline;
		}
		return *this;
	}
	friend ostream& operator<< (ostream &OS, const destinationCity &S) {
		OS << S.destination << " " << S.cost << " " << S.numMinutes << " " << S.airline;
		return OS;
	}
	bool operator ==(const city& rhs){
		return (this->destination == rhs.getStartPoint());
	}
private:
	Stringy destination;
	double cost;
	double numMinutes;
	Stringy airline;
};
#endif //INC_20F_FLT_PLN_DESTINATIONCITY_H
