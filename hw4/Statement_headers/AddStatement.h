// AddStatement.h
//
// CS 104 / Spring 2016
//
// The AddStatement class encapsulates an Add statement in a Facile program.
// An Add statement looks like this:
//
//     ADD A B
//
// Primarily, it consists of two things: a variable name (denoted by a single
// character) and another variable name. The program then adds the two variables.
// Then places the resulting sum in the first variable.


#ifndef ADD_STATEMENT_INCLUDED
#define ADD_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class AddStatement: public Statement {
private:
	std::string m_variable1, m_variable2; // variables for the operation

public:
	// constructor
	AddStatement(std::string var1, std::string var2);

	// execute statement
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif