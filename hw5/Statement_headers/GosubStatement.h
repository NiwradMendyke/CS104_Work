// GosubStatement.h
//
// CS 104 / Spring 2016
//
// The GosubStatement class allows the user to jump to a particular line in the program
// then return to the original location upon a subsequent Return statement
//
//     GOSUB 3
//
// It primarily consists of a int value, which represents the new line.
// This is the new value the program will advance to.


#ifndef GOSUB_STATEMENT_INCLUDED
#define GOSUB_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class GosubStatement: public Statement {
private:
	int m_new_line; // the new line to go to

public:
	// constructor
	GosubStatement(int m_new_line);

	// execute statement
	virtual void execute(ProgramState * state, std::ostream &outf);
};

#endif
