// PrintStatement.cpp:
#include "../Statement_headers/PrintStatement.h"
using namespace std;

// constructor
PrintStatement::PrintStatement(std::string variableName)
	: m_variableName( variableName ) {
	m_variableName = variableName;
}

// prints the value of the appropriate variable
// increment the program counter
void PrintStatement::execute(ProgramState * state) {
	cout << state->getVar(m_variableName) << std::endl;
	state->setCounter(state->getCounter() + 1);
}


