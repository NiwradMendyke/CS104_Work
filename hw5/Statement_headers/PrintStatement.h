// PrintStatement.h
//
// CS 104 / Spring 2016
//
// The PrintStatement class encapsulates an Print statement in a Facile program.
// A Print statement looks like this:
//
//     PRINT A
//
// Primarily, it consists of a variable name, which denotes the variable whose value
// the program will output to the outstream. If the variable 

#ifndef PRINT_STATEMENT_INCLUDED
#define PRINT_STATEMENT_INCLUDED

#include "Statement.h"
#include <iostream>

class PrintStatement: public Statement
{
private:
	std::string m_variableName; // the name of the variable to output
	
public:
	// constructor
	PrintStatement(std::string variableName);

	// execute statement
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif

