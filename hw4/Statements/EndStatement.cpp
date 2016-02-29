// EndStatement.cpp
#include "../Statement_headers/EndStatement.h"

EndStatement::EndStatement() { }

// changes a variable in programState to indicate an end to program execution
void EndStatement::execute(ProgramState * state, std::ostream &outf) {
	state->endProgram();
}