// DivStatement.h
//
// CS 104 / Spring 2016
//
// The DivStatement class encapsulates an Div statement in a Facile program.
// A Div statement looks like this:
//
//     Div A B
//
// Primarily, it consists of two things: a variable name (denoted by a single
// character) and another variable name. The program then divides the two variables.
// Then places the resulting value in the first variable.


#ifndef DIV_STATEMENT_INCLUDED
#define DIV_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class DivStatement: public Statement {
private:
	std::string m_variable1, m_variable2; // variables for the operation

public:
	// constructor 
	DivStatement(std::string var1, std::string var2);

	// execute statement
	virtual void execute(ProgramState * state);
};

#endif