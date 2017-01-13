/*
* Darwin Mendyke
* CSCI 104: Spring 2016
* 4/30/16
*
* Main function for Homework 8 
* Determines zipf districution of words in a text file.
*
* Uses splaytree and hashtable to compare runtimes of each.
*
* Takes two inputs, an int indicating which data structure to use and a filename
*/



#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <algorithm>

#include "bin/splaybst.h"
#include "bin/hashtable.h"


using namespace std;

int main(int argc, char* argv[]) {
	clock_t start;
	double duration;

	start = clock(); // starts timer

	// start of algorithm
	int alg_selection; // stores int indicating which data structure to use
	Map *structure; // Map pointer
	SplayTree splaytree;
	HashTable hashtable;

	if(argc < 3){
    	cerr << "Please provide a text file." << endl;
    	return 1;
  	}

  	ifstream input(argv[2]);
	// able to open file? 
	if (input.fail()) {
		cerr << "Couldn't open file" << endl; 
		return 1;
	}

  	stringstream ss; 
  	ss << argv[1];
  	ss >> alg_selection; // gets which data structure to use

  	if (alg_selection == 4)
  		structure = &splaytree;
  	else if (alg_selection == 5)
  		structure = &hashtable;
  	else {
  		cerr << "please enter an appropriate integer" << endl;
  		return 0;
  	}

  	string temp; // placeholder for the current word

  	while (input >> temp) {
   	transform(temp.begin(), temp.end(), temp.begin(), ::tolower); // converts to lowercase
   	//cerr << "current word: " << temp << endl; // debug

  		structure->add(temp); // adds to the data structure
  	}

  	structure->reportAll(cout); // outputs words

  	input.close();
  	// end of algorithm

	duration = ( clock() - start ) / (double) CLOCKS_PER_SEC; // stops the timer

	cout << duration << endl;
}

