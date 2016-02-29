// ReturnStatement.cpp:
#include "../Statement_headers/ReturnStatement.h"
#include <stdexcept>
using namespace std;

ReturnStatement::ReturnStatement() { }	

// set the value of the appropriate variable
// increment the program counter
void ReturnStatement::execute(ProgramState * state, ostream &outf) {
	state->return_();
}