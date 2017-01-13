/*
*	Darwin Mendyke
* mendyke@usc.edu
*
*	Program to simulate a resident hall with floors, residents, and belongings
*/

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// main function of the program
int main(int argc, char* argv[]) {	
	// checks for appropriate number of command line arguments
  if(argc < 3){
    cerr << "Please provide an input and output file." << endl;
    return 1;
  }

  // opens file read/write streams
  ifstream input(argv[1]);
  ofstream output(argv[2]);

  // able to open file? 
  if (input.fail()) {
		cout << "Couldn't open file" << endl; 
		return 1;
	}

  int floors;
  int *floorsizes;
  string ***trojans;	// main data object of the program
  string curr;	// contains strings in the current line

  input >> floors; // gets number of floors
  trojans = new string**[floors]; // creates string[][][]
  cerr << "new string**[] created" << endl; // debug 

  floorsizes = new int[floors]; // records residents per floor
  cerr << "new int[] created" << endl; // debug

  // fills elements from 0 to floors-1 with 0 and NULL
  for (int i = 0; i < floors; i++) {
	  floorsizes[i] = 0;
	  trojans[i] = NULL;
  }

  // main loop of the program
  while(getline(input, curr)) {
	  stringstream ss;
	  ss << curr;
	  ss >> curr;

	  // Creates a floor and some residents
	  if (curr == "MOVEIN") {
		  int i,k;
		  ss >> i; // which floor?
		  ss >> k; // how many residents?

		  if (ss.fail()) {
			  output << "Error - incorrect command" << endl;
		  }
		  else {
		  	if (i > floors)
		  		output << "Error - floor " << i << " does not exist" << endl;
		  	else if (trojans[i-1] != NULL)
		  		output << "Error - floor " << i << " is not empty" << endl;
		  	else {
		  		floorsizes[i-1] = k; // gets number of residents
		  		trojans[i-1] = new string*[k]; // creates string[][]
		  		cerr << "new string*[] created" << endl; // debug

		  		// sets all elements in the new array to NULL
		  		for (int a = 0; a < k; a++)
		  			trojans[i-1][a] = NULL;

		  		cerr << "floor " << i << " has " << k << " people" << endl; // debug
		  	}
		  }
	  }
	  // deletes a floor of residents
	  else if (curr == "MOVEOUT") {
	  	if (ss.fail()) {
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else {
	  		int i;
		  	ss >> i; // which floor?

		  	if (i > floors)
			  	output << "Error - floor " << i << " does not exist" << endl;
			  else if (trojans[i-1] == NULL)
			  	output << "Error - floor " << i << " is already empty" << endl;
				else {
		  		//cerr << i-1 << " " << floorsizes[i-1] << endl; // debug

					// deletes each resident on the floor array
	  			for (int j = 0; j < floorsizes[i-1]; j++)
	  				delete [ ] trojans[i-1][j]; // deletes string[]
	  	
	  			// sets the floor to NULL
	  			trojans[i-1] = NULL;

	  			cerr << "deleted everything on floor " << i << endl; // debug
		  	}
	  	}
	  }
	  // adds a list of possessions to a resident
	  else if (curr == "OBTAIN") {
	  	if (ss.fail()) {
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else {
	  		//cerr << "OBTAIN called" << endl; // debug
		  	int i, j, k;
		  	ss >> i; // which floor?
		  	ss >> j; // which resident?
		  	ss >> k; // how many possessions?

		  	if (i > floors)
			  	output << "Error - floor " << i << " does not exist" << endl;
			  else if (floorsizes[i-1] < j)
			  	output << "Error - floor " << i << " does not have " << j << " students" << endl;
			  else if (trojans[i-1][j-1] != NULL)
			  	output << "Error - student " << j << " already has possessions" << endl;
			  else {
			  	trojans[i-1][j-1] = new string[k+1]; // makes new string[]
			  	trojans[i-1][j-1][0] = to_string(k); // stores number of possessions in first element
			  	cerr << "new string[] created" << endl; // debug

			  	// stores possessions into the array
			  	for (int a = 0; a < k; a++) {
			  		ss >> trojans[i-1][j-1][a+1];
			  	}
			  }
	  	}
	  }
	  // outputs the possessions of a particular user
	  else if (curr == "OUTPUT") {
	  	if (ss.fail()) {
	  		output << "Error - incorrect command" << endl;
	  	}
	  	else {
	  		int i, j, k;
		  	ss >> i; // which floor?
		  	ss >> j; // which resident?
			 
				if (i > floors)
			  	output << "Error - floor " << i << " does not exist" << endl;
			  else if (floorsizes[i-1] < j)
			  	output << "Error - floor " << i << " does not have " << j << " students" << endl;
			  else if (trojans[i-1][j-1] == NULL)
			  	output << "Error - student " << j << " has no possessions" << endl;
			  else {
			  	// gets the number of possessions from the first element of the array
			  	k = atoi(trojans[i-1][j-1][0].c_str());

			  	cerr << "Student " << j << " on floor " << i << " has:" << endl; // debug

			  	// prints possessions to the file
			  	for (int a = 0; a < k; a++) {
			  		cerr << trojans[i-1][j-1][a+1] << endl;	// debug
			  		output << trojans[i-1][j-1][a+1] << endl; // outputs
			  	}
			  }
	  	}
	  }
	  else {
	  	if (curr != "")
	  		output << "Error - incorrect command (" << curr << ")" << endl;
	  }
  }

  cerr << "finished reading file" << endl; // debug

  input.close();
  output.close();

  // iterates through floors to delete each one
  for (int i = 0; i < floors; i++) {
  	if (trojans[i] != NULL) {
  		// iterates through each resident and deletes them
  		for (int j = 0; j < floorsizes[i]; j++) {
  			if (trojans[i][j] != NULL) {
  				delete [ ] trojans[i][j]; // deletes string[]
  				cerr << "deleted string[]" << endl; // debug
  			}
  		}

  		cerr << "deleted everything in trojans[" << i << "]" << endl; // debug

  		delete [ ] trojans[i]; // deletes string[][]
  		cerr << "deleted string[][]" << endl; // debug
  	}
  }

  delete [ ] trojans; // deletes string[][][]
  cerr << "deleted string[][][]" << endl; // debug

  delete [ ] floorsizes; // deletes int[]
  cerr << "deleted int[]" << endl; // debug

  return 0;
}
