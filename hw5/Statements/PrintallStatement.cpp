// PrintallStatement.cpp
#include "../Statement_headers/PrintallStatement.h"

// constructor
PrintallStatement::PrintallStatement() { }

// prints all the variables currently in the programstate map
// increments the program counter
void PrintallStatement::execute(ProgramState * state) {
	state->print_Vars();
	state->setCounter(state->getCounter() + 1);
}