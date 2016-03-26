// Darwin Mendyke
// CS 104 / Spring 2016
//
// facile.cpp
// 
// The facile class takes a file input and converts it into a vector of Statement points


#include <string>
#include <vector>
#include <sstream> 

#include "Statement_headers/Statement.h"
#include "Statement_headers/ProgramState.h"

class Facile {

	public:
		// constructor
		Facile();

		// deconstructor
		~Facile(); 

		// executes one line of the Facile program
		void execute_line(ProgramState* state);

		// opens the Facile program from the text file
		vector<string> parseProgram(istream& inf);

		vector<Statement *> program; // vector containing list of program statements
		vector<bool> breaks; // vector containing list of breakpoints

	private:
		// reads a single line of the Facile
		Statement* parseLine(string line);

		// deletes the Statements*
		void cleanUp();
};