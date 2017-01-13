// SubStatement.cpp:
#include "../Statement_headers/SubStatement.h"
using namespace std;

// constructor
SubStatement::SubStatement(std::string var1, std::string var2)
	: m_variable1( var1 ), m_variable2( var2 ) {
}	

// Checks if the second parameter is a number or a variable name
// Subtracts the two and places the value in the first variable
void SubStatement::execute(ProgramState * state) {
	int value = state->get_var_value(m_variable2);

	state->setVar(m_variable1, state->getVar(m_variable1) - value);
	state->setCounter(state->getCounter() + 1);
}

