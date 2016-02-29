// SubStatement.h
//
// CS 104 / Spring 2016
//
// The SubStatement class encapsulates an Sub statement in a Facile program.
// An Sub statement looks like this:
//
//     SUB A B
//
// Primarily, it consists of two things: a variable name (denoted by a single
// character) and another variable name. The program then subtracts the two variables.
// Then places the resulting value in the first variable.


#ifndef SUB_STATEMENT_INCLUDED
#define SUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class SubStatement: public Statement {
private:
	std::string m_variable1, m_variable2; // variables for the operation

public:
	// constructor
	SubStatement(std::string var1, std::string var2);

	// execute statement
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif