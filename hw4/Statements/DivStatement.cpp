// DivStatement.cpp:
#include "../Statement_headers/DivStatement.h"
#include <cstring>
#include <stdexcept>
using namespace std;

// constructor
DivStatement::DivStatement(string var1, string var2)
	: m_variable1( var1 ), m_variable2( var2 ) {
}	

// Checks if the second parameter is a number or a variable name
// Divides the two and places the value in the first variable
void DivStatement::execute(ProgramState * state, ostream &outf) {
	int value = state->get_var_value(m_variable2);

	if (value == 0) // checks if there's a divide by zero problem
		throw domain_error("domain error");

	state->setVar(m_variable1, state->getVar(m_variable1) / value);
	state->setCounter(state->getCounter() + 1);
}

