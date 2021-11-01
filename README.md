<div id="top"></div>

# Fall 2020 - Flight Planner 

## Important Information

Project handout:  [Click Here](https://drive.google.com/file/d/1lEFdwiFRgI_5ZH0uhJCJEEJw4yJH_LlT/view?usp=sharing)

## Implementation Details:

### The creation of this project entailed a few key aspects:
* The creation of a custom Linked List class
    * with the creation of Linked list iterator in the style of std::iterators
* The creation of a custom Vector class
    * With the creation of Vector iterator in the style of std::iterators
* The creation of a custom String class
* The creation of a custom, templated, Adjacency list class
* The creation of a custom Stack class
* Implementation of iterative backtracking


<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

#### Step 1: You will need to have cmake installed and a compiler for c++.

#### Step 2: You will need to create two files for input:

Origination and Destination Data – This file will contain a sequence of city pairs representing
0-stop flights that can be used in preparing a flight plan. For each of these, the file will also
contain a dollar cost for that leg and a time to travel. For each pair in the file, it is assumed
that it is possible to fly both directions.

Example (Taken from flightPlans.csv in this repo):
```
6
Dallas|Austin|101|47|Spirit
Dallas|Austin|1000|59|American
Dallas|Austin|50|2|Spirit
Austin|Houston|95|39|United
Dallas|Houston|101|51|Spirit
Dallas|Chicago|144|192|American
```

Requested Flights – This file will contain a sequence of origin/destination city pairs. For each
pair, your program will determine if the flight is or is not possible. If it is possible, it will output
to a file the flight plan with the total cost for the flight. If it is not possible, then a suitable
message will be written to the output file.

Example (Taken from requestedFlights.csv in this repo):
```
3
Dallas|Houston|T
Dallas|Austin|C
Dallas|Illinois|T
```

<p align="right">(<a href="#top">back to top</a>)</p>


<!-- USAGE EXAMPLES -->
## Usage
To run this program, simple clone the repo with this command in your terminal:

```
git clone https://github.com/Gouldilocks/flightPlanner.git
```
And then run these commands from inside the repository's directory
```
cmake .
make
./flight_planner <FlightDataFile> <PathsToCalculateFile> <OutputFile>
```


<p align="right">(<a href="#top">back to top</a>)</p>


