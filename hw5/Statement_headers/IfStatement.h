// IfStatement.h
//
// CS 104 / Spring 2016
//
// The IfStatement class encapsulates an If statement in a Facile program.
// An if statement looks like this:
//
//     IF A < B THEN 5
//
// Primarily, it consists of four things: a variable name (denoted by a single
// character), an integer value, a comparison operation and a line number to advance to
// if the statement is true


#ifndef IF_STATEMENT_INCLUDED
#define IF_STATEMENT_INCLUDED

#include "Statement.h"
#include "ProgramState.h"

class IfStatement: public Statement {
private:
	std::string m_variable1, m_variable2, operation; // the variables and the operand
	int m_new_line; // which line to jump to if statement is true
	bool result; // bool value whether statement is true or not

public:
	// constructor
	IfStatement(std::string var1, std::string var2, std::string op, int next_line);

	// execute statement
	virtual void execute(ProgramState * state);
};

#endif



