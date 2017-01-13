// GotoStatement.cpp:
#include "../Statement_headers/GotoStatement.h"
#include <stdexcept>
using namespace std;

// constructor
GotoStatement::GotoStatement(int new_line) {
	m_new_line = new_line;
}	

// checks if the new line is an appropriate line to jump to
// then sets the program counter to that line
void GotoStatement::execute(ProgramState * state) {
	if (m_new_line > state->getNum() || m_new_line <= 0)
		throw out_of_range("illegal jump instruction");
	state->setCounter(m_new_line);
}