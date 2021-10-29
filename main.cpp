// created by Christian Gould on 10/12/20
#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.hpp"
#include "flightPlanner.h"
using namespace std;
#define debug false
int main(int argc, char** argv) {
	// if no arguments passed, run catch for debugging
	if(argc == 1){
			Catch:: Session().run();
			return 0;
	}
	auto* runMe = new flightPlanner();
	ifstream O_and_D_Data(argv[1]);
	ifstream req_Flights(argv[2]);
	ofstream output(argv[3]);
	cout << "putting output in: " << argv[3] << endl;
	runMe-> determineFlights(O_and_D_Data,req_Flights,output);
	delete runMe;
	cout << "Done" << endl;
	return 0;
}
