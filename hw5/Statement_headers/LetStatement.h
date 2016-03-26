// LetStatement.h
//
// CS 104 / Spring 2016
//
// The LetStatement class encapsulates a LET statement in a Facile program.
// A LET statement looks like this:
//
//     LET A 3
//
// Primarily, it consists of two things: a variable name (denoted by a single
// character) and an integer value.  So, a LetStatement object contains a
// character and an integer, which is the important information contained in
// a LET statement.


#ifndef LET_STATEMENT_INCLUDED
#define LET_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class LetStatement: public Statement {
private:
	std::string m_variableName; // name of the new variable
	int m_value; // value of the new variable

public:
	// constructor
	LetStatement(std::string variableName, int value);
	
	// execute statement
	void execute(ProgramState * state, std::ostream &outf);
};

#endif



