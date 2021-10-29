//
// Created by Christian Gould on 10/20/20.
//
#include "catch.hpp"
#include "Stringy.h"
#include "stacky.h"
TEST_CASE("stacky tests" "[stacky]"){
	Stringy one = "One";
	Stringy two = "Two";
	Stringy three = "Three";
	Stringy four = "Four";
	Stringy five = "Five";
	stacky<int> ints;
	stacky<Stringy> strings;
	SECTION("stack basic functionality"){
		for(int i = 0; i < 10; i++){
			ints.stack(i);
		}
		strings.stack(one);
		strings.stack(two);
		strings.stack(three);
		strings.stack(four);
		strings.stack(five);
		SECTION("unstack function") {
			CHECK(strings.unstack () == "Five");
			CHECK(strings.unstack () == "Four");
			CHECK(strings.unstack () == "Three");
			CHECK(strings.unstack () == "Two");
			CHECK(strings.unstack () == "One");
			for(int i = 0; i < 10; i++){
				CHECK(9-i == ints.unstack());
			}
		}
		SECTION("isEmpty function"){
			for(int i = 0; i < 5; i++){
				strings.unstack();
			}
		CHECK(strings.isEmpty ());
		strings.stack("Hello");
		CHECK(!strings.isEmpty ());
		}
		SECTION("size function"){
		CHECK(strings.getSize() == 5);
			for(int i = 0; i < 5; i++){
				strings.unstack();
			}
			strings.stack("hello");
		CHECK(strings.getSize() == 1);
		strings.stack("ok");
		CHECK(strings.getSize() == 2);
		strings.unstack();
		CHECK(strings.getSize() == 1);
		}
	}
	SECTION("Operators"){
		SECTION("Assignment operator"){
			stacky<Stringy> left;
			stacky<Stringy> right;
			right.stack(one);
			right.stack(two);
			right.stack(three);
			left = right;
			CHECK(left.unstack() == three);
			CHECK(left.unstack() == two);
			CHECK(left.unstack() == one);
		}
	}
	SECTION("Constructors"){
		SECTION("One elements constructor") {
			stacky<Stringy> testy ("One");
			stacky<Stringy> testyTwo (one);
			CHECK(testy.unstack() == "One");
			CHECK(testyTwo.unstack() == one);
		}
	}
	SECTION("reverse,peek, and contains functions"){
		stacky<Stringy> forwards;
		forwards.stack(one);
		forwards.stack(two);
		forwards.stack(three);
		forwards.stack(four);
		forwards.stack(five);
		forwards.reverse();
		CHECK(forwards.peek() == five);
		CHECK(forwards.unstack() == five);
		CHECK(forwards.peek() == four);
		CHECK(forwards.unstack() == four);
		CHECK(forwards.peek() == three);
		CHECK(forwards.unstack() == three);
		CHECK(forwards.peek() == two);
		CHECK(forwards.unstack() == two);
		CHECK(forwards.peek() == one);
		CHECK(forwards.unstack() == one);
	}
}
