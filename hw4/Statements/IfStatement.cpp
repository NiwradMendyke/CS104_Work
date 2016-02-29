// IfStatement.cpp:
#include "../Statement_headers/IfStatement.h"
#include <stdexcept>
using namespace std;

// constructor
IfStatement::IfStatement(std::string var1, std::string var2, std::string op, int next_line)
	: m_variable1( var1 ), m_variable2( var2 ), operation(op), m_new_line(next_line) {
	result = false;
}	

// checks if the new_line value is in range of appropriate line calls
// then gets the value of both variables from ProgramState
// and performs the appropriate boolean operand based on the value of operation
void IfStatement::execute(ProgramState * state, ostream &outf) {
	if (m_new_line > state->getNum() || m_new_line <= 0)
		throw out_of_range("out of range");

	//outf << "IF " << m_variable1 << " " << operation << " " << m_variable2 << " THEN " << m_next_line << endl;
	int val1 = state->getVar(m_variable1);
	int val2 = state->get_var_value(m_variable2);

	// checks the operation type
	if (operation == "<")
		result = (val1 < val2);
	if (operation == "<=")
		result = (val1 <= val2);
	if (operation == ">")
		result = (val1 > val2);
	if (operation == ">=")
		result = (val1 >= val2);
	if (operation == "=")
		result = (val1 == val2);
	if (operation == "<>")
		result = (val1 != val2);

	if (result) // moves counter to new line if true
		state->setCounter(m_new_line);
	else // otherwise keeps advancing normally through program
		state->setCounter(state->getCounter() + 1);
}
