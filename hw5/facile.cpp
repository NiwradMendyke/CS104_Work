// Darwin Mendyke
// CS 104 / Spring 2016
//
// facile.cpp


#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <stdio.h>

#include "facile.h"
#include "Statement_headers/Statement.h"
#include "Statement_headers/LetStatement.h"
#include "Statement_headers/PrintStatement.h"
#include "Statement_headers/PrintallStatement.h"
#include "Statement_headers/AddStatement.h"
#include "Statement_headers/SubStatement.h"
#include "Statement_headers/MultStatement.h"
#include "Statement_headers/DivStatement.h"
#include "Statement_headers/IfStatement.h"
#include "Statement_headers/GotoStatement.h"
#include "Statement_headers/GosubStatement.h"
#include "Statement_headers/ReturnStatement.h"
#include "Statement_headers/EndStatement.h"
#include "Statement_headers/ProgramState.h"

using namespace std;

Facile::Facile() {

}

Facile::~Facile() {
	cleanUp();
}

// executes one line of the facile program
// catches for potential errors in the program
void Facile::execute_line(ProgramState * state) {
	program[state->getCounter()]->execute(state, cout); // executes each statement
}

// takes a line of text input from the file and converts it to a Facile Statement
// used by the parseProgram() function to read through the file
Statement * Facile::parseLine(string line) {
	Statement * statement = NULL; // placeholder for the statement object
	stringstream ss; // stringstream to parse out individual characters in the string
	string type; // contains the first command of the line
	string var, var1, op; // placeholders for any string values in the line
	int val; // placeholder for any int values in the line

	ss << line;
	ss >> type;
	
	if (type == "LET") { // creates a new variable
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal Facile program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}
	if (type == "PRINT") { // prints out a variable value
		ss >> var;
		statement = new PrintStatement(var);
	}
	if (type == "PRINTALL") { // prints out value of all variables
		statement = new PrintallStatement();
	}
	if (type == "ADD") { // adds value of the two variables
		ss >> var;
		ss >> var1;
		statement = new AddStatement(var, var1);
	}
	if (type == "SUB") { // subtracts value of the two variables
		ss >> var;
		ss >> var1;
		statement = new SubStatement(var, var1);
	}
	if (type == "MULT") { // multiplies value of the two variables
		ss >> var;
		ss >> var1;
		statement = new MultStatement(var, var1);
	}
	if (type == "DIV") { // divides value of the two variables
		ss >> var;
		ss >> var1;
		statement = new DivStatement(var, var1);
	}
	if (type == "IF") { // conditional goto statement
		ss >> var;
		ss >> op;
		ss >> var1;
		ss >> type;
		ss >> val;
		statement = new IfStatement(var, var1, op, val);
	}
	if (type == "GOTO") { // goto statement
		ss >> val;
		statement = new GotoStatement(val);
	}
	if (type == "GOSUB") { // goto function call
		ss >> val;
		statement = new GosubStatement(val);
	}
	if (type == "RETURN") { // returns to original counter after a gosub call
		statement = new ReturnStatement();
	}
	if (type == "END" || type == ".") { // ends the program
		statement = new EndStatement();
	}
		
	return statement;
}

// takes a Facile file and converts it to a list of Statement* that the prgram can use
vector<string> Facile::parseProgram(istream &inf) {
	program.push_back(NULL); // puts NULL in 0th element of the vector
	vector<string> lines_text;
	
	string line;

	while( ! inf.eof() ) { // loops through each line in the input
		getline(inf, line);

		lines_text.push_back(line);
		program.push_back(parseLine(line));
	}

	return lines_text;
}

void Facile::cleanUp() {
	int program_size = program.size();

	for (int i = 1; i < program_size; i++) { // deletes each statement in the vector
		delete program[i];
	}
}

