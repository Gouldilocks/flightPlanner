//
// Created by Christian Gould on 10/20/20.
//
#include "catch.hpp"
#include "adjacencyListy.h"
#include "Stringy.h"
#include "city.h"
#include "destinationCity.h"
using namespace std;
TEST_CASE("adjacency List tests" "[adjacencyListy]"){
Stringy one = "one";
Stringy two = "two";
Stringy three = "three";
Stringy mapOne = "mapOne";
Stringy mapTwo = "mapTwo";
Stringy mapThree = "mapThree";
adjacencyListy<Stringy,Stringy> strings;
strings.addEdge(one,mapOne);
strings.addEdge(two,mapTwo);
strings.addEdge(three,mapThree);
strings.addEdge(one,"second");
strings.addEdge(one, "third edge");
strings.addEdge(two,"secondMap");
CHECK(strings.at(one,0) == mapOne);
CHECK(strings.at(one,1) == "second");
CHECK(strings.at(one,2) == "third edge");
CHECK(strings.at(two,0) == mapTwo);
CHECK(strings.at(two,1) == "secondMap");
CHECK(strings.at(three,0) == mapThree);
//strings.printAll();
SECTION("city tests"){
	destinationCity end("destination",11.00,15.00,"American");
		destinationCity end2("destination2",12.00,15.00,"American");
		destinationCity end3("destination3",13.00,15.00,"American");
		destinationCity end4("destination4",14.00,15.00,"American");
		city start("location");
		city start2("location2");
		city start3("location3");
		city start4("location4");
		adjacencyListy<city, destinationCity> a;
	a.addEdge(start,end);
	a.addEdge(start,end2);

	a.addEdge(start2,end2);
	a.addEdge(start2,end3);

	a.addEdge(start3,end3);
	a.addEdge(start3,end4);

	a.addEdge(start4,end4);
	a.addEdge(start4,end);

SECTION("where, peek, right, left, up, down functionality") {
			CHECK(a.where () == start);
			CHECK(a.peek () == end);
			CHECK(a.currDown() == 0);
			CHECK(a.right () == end2);
			CHECK(a.currRight() == 1);
			CHECK(a.currDown() == 0);
			CHECK(a.left() == end);
			CHECK(a.currRight() == 0);
			CHECK(a.down() == start2);
			CHECK(a.currDown() == 1);
			CHECK(a.where() == start2);
			CHECK(a.peek() == end2);
			CHECK(a.right() == end3);
			CHECK(a.currRight() == 1);
			CHECK(a.left() == end2);
			CHECK(a.currRight() == 0);
			CHECK(a.down() == start3);
			CHECK(a.currDown() == 2);
			CHECK(a.where() == start3);
			CHECK(a.peek() == end3);
			CHECK(a.right() == end4);
			CHECK(a.left() == end3);
			CHECK(a.down() == start4);
			CHECK(a.currDown() == 3);
			CHECK(a.where() == start4);
			CHECK(a.right() == end4);
			CHECK(a.left() == end);
			CHECK(a.up() == start3);
			CHECK(a.currDown() == 2);
		}
		SECTION("maxRight and maxDown functionality"){
		CHECK(a.downMax() == 4);
		a.iterateStart();
		for(int i = 0; i < a.downMax(); i++){
			CHECK(a.rightMax() == 2);
		}
		}
}
}