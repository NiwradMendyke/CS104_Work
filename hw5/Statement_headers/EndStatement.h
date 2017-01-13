// EndStatement.h
//
// CS 104 / Spring 2016
//
// The EndStatement class encapsulates a END statement in a Facile program.
// And END statement serves to indicate the end for a Facile program.


#ifndef END_STATEMENT_INCLUDED
#define END_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class EndStatement: public Statement {

public:
	EndStatement();
	virtual void execute(ProgramState * state);
};

#endif