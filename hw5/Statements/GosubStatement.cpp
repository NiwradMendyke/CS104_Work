// GosubStatement.cpp:
#include "../Statement_headers/GosubStatement.h"
#include <stdexcept>
using namespace std;

// constructor
GosubStatement::GosubStatement(int new_line)
	: m_new_line(new_line) { }	

// checks if the new line is an appropriate line to jump to
// adds the current line to the programstate stack
// then sets the program counter to that line
void GosubStatement::execute(ProgramState * state) {
	if (m_new_line > state->getNum() || m_new_line <= 0)
		throw out_of_range("illegal jump instruction");
	state->gosub();
	state->setCounter(m_new_line);
}