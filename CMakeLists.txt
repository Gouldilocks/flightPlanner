cmake_minimum_required(VERSION 3.14)
project(20f-flt-pln)
set (EXE_NAME flight_planner)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

set (input01 "flightPlans.csv")
set (input02 "requestedFlights.csv")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS_DEBUG "-O3")
add_executable(${EXE_NAME} main.cpp flightPlanner.h flightPlanner.cpp stacky.h adjacencyListy.h catch.hpp LinkyList.h LinkyListIter.h LinkyListTests.cpp List.h Nody.h Stringy.cpp Stringy.h StringyTests.cpp Vecty.h VectyIter.h VectyTests.cpp stackyTests.cpp adjacencyListyTests.cpp keyCode.h flight.h flight.cpp city.cpp city.h destinationCity.h)

