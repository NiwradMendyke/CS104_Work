// GotoStatement.h
//
// CS 104 / Spring 2016
//
// The GotoStatement class allows the user to jump to a particular line in the program
//
//     GOTO 3
//
// It primarily consists of a int value, which represents the new line.
// This is the new value the program will advance to.


#ifndef GOTO_STATEMENT_INCLUDED
#define GOTO_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class GotoStatement: public Statement
{
private:
	int m_new_line; // the new line to go to

public:
	// constructor
	GotoStatement(int m_new_line);

	// execute statement
	virtual void execute(ProgramState * state);
};

#endif
