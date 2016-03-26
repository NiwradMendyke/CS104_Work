// LetStatement.cpp:
#include "../Statement_headers/LetStatement.h"
using namespace std;

// constructor
LetStatement::LetStatement(std::string variableName, int value)
	: m_variableName(variableName), m_value(value) {
}	

// set the value of the appropriate variable
// increment the program counter
void LetStatement::execute(ProgramState * state, ostream &outf) {
	state->setVar(m_variableName, m_value);
	state->setCounter(state->getCounter() + 1);
}


