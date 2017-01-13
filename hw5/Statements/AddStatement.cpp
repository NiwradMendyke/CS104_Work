// AddStatement.cpp:
#include "../Statement_headers/AddStatement.h"
#include <cstring>
using namespace std;

// constructor
AddStatement::AddStatement(string var1, string var2)
	: m_variable1(var1), m_variable2(var2) {
}	

// Checks if the second parameter is a number or a variable name
// Adds the two and places the value in the first variable
void AddStatement::execute(ProgramState * state) {
	int value = state->get_var_value(m_variable2);

	state->setVar(m_variable1, state->getVar(m_variable1) + value);
	state->setCounter(state->getCounter() + 1);
}

