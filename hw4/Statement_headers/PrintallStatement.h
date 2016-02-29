// PrintallStatement.h
//
// CS 104 / Spring 2016
//
// The PrintallStatement class prints all the current variables in a Facile program.
// Outputs each variable so that there is one per line. 
// Prints the name of the variable followed by the value.


#ifndef PRINTALL_STATEMENT_INCLUDED
#define PRINTALL_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class PrintallStatement: public Statement {

public:
	// constructor
	PrintallStatement();

	// execute statement
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif