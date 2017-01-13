// ReturnStatement.h
//
// CS 104 / Spring 2016
//
// The ReturnStatement class allows the user to return to a particular line in the program.
// Pulls the location from the top of the stack
//
//     RETURN
//
// The program will advance to the line pulled from the top of the stack.


#ifndef RETURN_STATEMENT_INCLUDED
#define RETURN_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class ReturnStatement: public Statement {
public:
	ReturnStatement();
	virtual void execute(ProgramState * state);
};

#endif
