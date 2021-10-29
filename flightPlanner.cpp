//
// Created by Christian Gould on 10/20/20.
//

#include "flightPlanner.h"
#include <sstream>
#define debug true
#define debugTakeInput false
flightPlanner::flightPlanner () = default;
flightPlanner::flightPlanner (const flightPlanner &copy) {
this-> flightPlans = copy.flightPlans;
this-> begAndEnds = copy.begAndEnds;
this-> sorts = copy.sorts;
this-> combinations = copy.combinations;
}

void flightPlanner::determineFlights (ifstream& flightPlans, ifstream& suggested, ofstream& outputFile) {
takeInput (flightPlans,suggested);
iterativeBacktracking ();
output_Result (outputFile);
}

void flightPlanner::takeInput (ifstream& flightData, ifstream& reqFlights) {
char buffer[50000];
int numinputs;
flightData.getline(buffer, 49999);
numinputs = Stringy(buffer).toInt();
memset(buffer,0,50000);
for(int i = 0; i < numinputs; i++){
	flightData.getline(buffer, 49999);
		stringstream k(buffer);
	// fill buffer with the home city
	k.getline(buffer,49999,'|');
	Stringy homeCity(buffer);
	// fill buffer with the destination city
	k.getline(buffer,49999,'|');
	Stringy destination(buffer);
	// fill buffer with the price
	memset(buffer,0,50000);
	k.getline(buffer,49999,'|');
	stringstream ss(buffer);
	double price;
	ss >> price;
	// fill buffer with the time
	memset(buffer,0,50000);
	k.getline(buffer,49999,'|');
	stringstream s2(buffer);
	double time;
	s2 >> time;
	// fill buffer with the airline
	memset(buffer,0,50000);
	k.getline(buffer,49999,'|');
	Stringy airline(buffer);

	if(debugTakeInput)cout << "loop: " << i << " homeCity: " << homeCity << endl;
	// add the edge, and it can go either way so make it reversible
	this->flightPlans.addEdge(city(homeCity),destinationCity(destination,price,time,airline));
	this->flightPlans.addEdge(city(destination),destinationCity(homeCity,price,time,airline));
	memset(buffer,0,50000);
	}
	if(debug) flightPlans.printAll();
	/* requested flight plans */
	memset(buffer,0,50000);
	reqFlights.getline(buffer,49999);
	numinputs = Stringy(buffer).toInt();
	memset(buffer,0,50000);
	for(int i = 0; i < numinputs; i++){
		reqFlights.getline(buffer,49999,'|');
		Stringy beg(buffer);
		memset(buffer,0,50000);
		reqFlights.getline(buffer,49999,'|');
		Stringy end(buffer);
		begAndEnds.push_back(pair<Stringy,Stringy>(beg,end));
		memset(buffer,0,50000);
		reqFlights.getline(buffer,49999);
		sorts.push_back(buffer[0]);
		memset(buffer,0,50000);
	}
	if(debug){
		for(int i = 0; i < sorts.getSize(); i++){
			cout << sorts[i] << endl;
		}
	}
}

void flightPlanner::output_Result(ofstream &output) {
for(int i = 0; i < combinations.getSize(); i++) {
	cout << "i = " << i << endl;
	cout << "getpossible of " << combinations[i][0].getDestination() << " is " << this->combinations[i][0].getPossible() << endl;
	if (this->combinations[ i ][0].getPossible ()) {
		output << "Flight " << i + 1 << ": " << combinations[ i ][ 0 ].getOrigin () << " -> "
		       << combinations[ i ][ 0 ].getDestination () << combinations[ i ][ 0 ].getOrderedBy () << endl;
		flightPlans.mvDown ();
		combinations[ i ].insertionSort ();
		for (int x = 0; x < combinations[ i ].getSize () && x < 3; x++) {
			output << "Path " << x + 1 << ": ";
			output << combinations[ i ][ x ] << endl;
		}
	}
	// if the flight path is not possible
	else{
		// output the flight path that was originally destined to print
		output << "Flight " << i + 1 << ": " << combinations[ i ][ 0 ].getOrigin () << " -> "
		       << combinations[ i ][ 0 ].getDestination () << combinations[ i ][ 0 ].getOrderedBy () << endl;
		// output error message
		output << combinations[i][0] << endl;
		continue;
	}
}
}

void flightPlanner::iterativeBacktracking () {
	flightPlans.iterateStart();
	vectyIter<char> sortsIt = sorts.begin();
	vectyIter<pair<Stringy,Stringy>> begAndEndIt = begAndEnds.begin();
	for(int i = 0; i < sorts.getSize(); i++, ++sortsIt, ++begAndEndIt) {
		Vecty<flight> pushToCombinations;
		Stringy start = (*begAndEndIt).first;
		Stringy finish = (*begAndEndIt).second;
		cout << "start is : " << start << endl;
		cout << "end is : " << finish << endl;
		char sortBy = (*sortsIt);
		// stack the beginning city into the stack
		stacky<destinationCity> stacker;
		city beginCity(start);
		flightPlans.mvToFirst_Elem(beginCity);
		stacker.stack(destinationCity(start,0,0,"begin"));
		destinationCity lastOne("firstIteration",-1,-1,"firstIteration");
		while(!(stacker.isEmpty())) {
			cout << "current stacker: " << endl;
			stacker.printAll();
			//cout << "stacker size: " << stacker.getSize () << endl;
			//if(stacker.getSize() > 10) break;
			//cout << "stacker peek: " << stacker.peek() << endl;
			// for each of the possibilities of a node
			// if the node is the end node, stack and then go back one
			if(flightPlans.peek().getDestination () == finish && !(nameContains(stacker,flightPlans.peek().getDestination ()))){
				cout << "flightplans peek == finish, and is not already stacked" << endl;
				cout << flightPlans.peek ().getDestination () << " == " << finish << endl;
				//cout << "flightPlans.peek().getDestination == finish" << endl;
				stacker.stack (flightPlans.peek());
				cout << "current stacker: " << endl;
				stacker.printAll();
				cout << "PUSHING BACK: " << flight(stacker,sortBy)  << endl;
				pushToCombinations.push_back(flight(stacker,sortBy));
				cout << "lastone = " << stacker.peek () << endl;
				lastOne = stacker.unstack ();
				//cout << "lastOne currently is: " << lastOne.getDestination() << endl;
				// move right if there is another node to move to
				if(flightPlans.currRight() < flightPlans.rightMax ()-1) {
					flightPlans.mvRight ();
					cout << "there is space to move right, moving to " << flightPlans.peek ().getDestination () << endl;
				}
				else {
					cout << "there is no space to move right when at " << flightPlans.peek().getDestination () << endl;
					while(true) {
						//cout << "begin loop" << endl;
						cout << "lastone = " << stacker.peek() << endl;
						lastOne = stacker.unstack ();
						if (stacker.isEmpty ()) {
							cout << "empty" << endl;
							break;
						}
						//cout << "mover" << endl;
						flightPlans.mvToFirst_Elem (city (stacker.peek ().getDestination ()));
						while(flightPlans.peek() != lastOne){
							//cout << "nested while" << endl;
							flightPlans.mvRight();
						}
						//cout << "if statement" << endl;
						if(flightPlans.currRight() < flightPlans.rightMax ()-1) {
							flightPlans.mvRight();
							cout << "room to move right, moving to " << flightPlans.peek().getDestination () << endl;
							break;
						}
						else continue;
					}
					if(stacker.isEmpty()) break;
				}
				// if the stack is empty, we have done all combinations
				if(stacker.isEmpty()) break;
				else continue;
			}
			// if the node is not the end node, stack and go to the next one
			else if(!(flightPlans.peek().getDestination () == finish)){
				cout << "not the correct element." << endl;
				cout << flightPlans.peek().getDestination() << " != " << finish << endl;
				// if the peek has children, and is not in the stack already, stack it and move the list
				cout << flightPlans.peek().getDestination () << "haschildren?: " << flightPlans.hasChildren() << endl;
				cout << flightPlans.peek().getDestination () << "is in stack?: " << nameContains(stacker,flightPlans.peek().getDestination ()) << endl;
				if(flightPlans.hasChildren() && !(nameContains(stacker,flightPlans.peek().getDestination ()))) {
					cout << flightPlans.peek().getDestination () << " has children and stack does not already have it" << endl;
					stacker.stack (flightPlans.peek ());
					cout << "stacking " << stacker.peek().getDestination() << endl;
					// move the adjacency list to the newly stacked element
					flightPlans.mvToFirst_Elem(city(flightPlans.peek().getDestination()));
					continue;
				}
				// if the current peek does not have children
				else {
					if(flightPlans.currRight() < flightPlans.rightMax ()-1){
						flightPlans.mvRight();
						continue;
					}
					lastOne = stacker.unstack();
					if(stacker.isEmpty())break;
					flightPlans.mvToFirst_Elem(city(stacker.peek().getDestination()));
					// search for the element
					while(flightPlans.peek() != lastOne){
						flightPlans.mvRight();
					}
					// once the element is found, update once to get the new element
					if(flightPlans.currRight() < flightPlans.rightMax ()-1) flightPlans.mvRight();
					// if the element is found, but is the last element of its subtree
					else {
						while(true) {
							lastOne = stacker.unstack ();
							if (stacker.isEmpty ()) {
								break;
							}
							flightPlans.mvToFirst_Elem (city (stacker.peek ().getDestination ()));
							while(flightPlans.peek() != lastOne){
								flightPlans.mvRight();
							}
							if(flightPlans.currRight() < flightPlans.rightMax ()-1){
								flightPlans.mvRight();
								break;
							}
							else continue;
						}
						if(stacker.isEmpty()) break;
					}
					continue;
				}
			}
		}
		cout << "printToCombinations Size: " << pushToCombinations.getSize() << endl;

		if(pushToCombinations.getSize() == 0){
			pushToCombinations.push_back(flight(start,finish,(*sortsIt)));
		}
		combinations.push_back(pushToCombinations);
	}
//printCombos ();
}
void flightPlanner:: printCombos(){
	for(int i = 0; i < combinations.getSize(); i++){
		for(int x = 0; x < combinations[i].getSize(); x++){
			cout << combinations[i][x] << endl;
		}
	}
}
bool flightPlanner:: nameContains(stacky<destinationCity>& st, const Stringy& stringy){
	stacky<destinationCity> ok = st;
	int k = ok.getSize();
	for(int i = 0; i < k; i++){
		if(ok.unstack().getDestination() == stringy)
			return true;
		else continue;
	}
	return false;
}