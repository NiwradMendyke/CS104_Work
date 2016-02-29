// MultStatement.h
//
// CS 104 / Spring 2016
//
// The MultStatement class encapsulates an MULT statement in a Facile program.
// A Mult statement looks like this:
//
//     ADD A B
//
// Primarily, it consists of two things: a variable name (denoted by a single
// character) and another variable name. The program then multiplies the two variables.
// Then places the resulting product in the first variable.


#ifndef MULT_STATEMENT_INCLUDED
#define MULT_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class MultStatement: public Statement {
private:
	std::string m_variable1, m_variable2; // variables for the operation

public:
	// constructor
	MultStatement(std::string var1, std::string var2);

	// execute statement
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif