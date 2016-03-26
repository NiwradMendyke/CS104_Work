// MultStatement.cpp:
#include "../Statement_headers/MultStatement.h"
#include <cstring>
using namespace std;

// constructor
MultStatement::MultStatement(string var1, string var2)
	: m_variable1( var1 ), m_variable2( var2 ) {
}	

// Checks if the second parameter is a number or a variable name
// Multiplies the two and places the product in the first variable
void MultStatement::execute(ProgramState * state, ostream &outf) {
	int value = state->get_var_value(m_variable2);

	state->setVar(m_variable1, state->getVar(m_variable1) * value);
	state->setCounter(state->getCounter() + 1);
}

