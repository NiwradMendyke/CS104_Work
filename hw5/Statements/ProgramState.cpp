// ProgramState.cpp:
#include "../Statement_headers/ProgramState.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

// constructor
ProgramState::ProgramState(int numLines)
	: m_numLines(numLines) {
	counter = 1;
	endLine = false;
	stack = StackInt();
	variables = std::map<std::string, int>();
}

// returns total number of lines
int ProgramState::getNum() {
	return m_numLines;
}

// returns current line number
int ProgramState::getCounter() {
	return counter;
}

// allows changes to the current line number
void ProgramState::setCounter(int line) {
	counter = line;
}

// sets flag to end program
void ProgramState::endProgram() {
	endLine = true;
}

// adds line number to the stack
void ProgramState::gosub() {
	//std::cout << "pushing " << counter << std::endl;
	stack.push(counter);
}
	
// gets top line number from the stack
// othersie is stack is empty, just increments the program counter
void ProgramState::return_() {
	if (!stack.empty()) { // if there are items on top of stack
		counter = stack.top() + 1;
		stack.pop();
	}
	else // otherwise increments program normally
		counter++;
}

// checks if program should terminate
bool ProgramState::is_end() {
	return endLine;
}

// checks if the variable exists in the map
bool ProgramState::is_var(std::string name) {
	std::map<std::string, int>::iterator it = variables.find(name); // map iterator
	if (it != variables.end())
		return true;
	return false;
}

// gets the variable from the map
// if it doesn't actually exist, initializes the variable as zero and returns
int ProgramState::getVar(std::string name) {
	std::map<std::string, int>::iterator it = variables.find(name);
	if (it != variables.end())
		return it->second;
	else {
		variables.insert(std::make_pair(name, 0));
		return 0;
	}
}

// allows changes to a variable
// if it doesn't actually exist, adds a new variable with the given value
void ProgramState::setVar(std::string name, int value) {
	std::map<std::string, int>::iterator it = variables.find(name);
	if (it != variables.end())
		it->second = value;
	else
		variables.insert(std::make_pair(name, value));
}

// outputs every variable
void ProgramState::print_Vars() {
	std::map<std::string, int>::iterator it;
	for (it = variables.begin(); it != variables.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
}

// called by the arithmetic expression statements. 
// this function determines whether a parameter variable is a value or a variable name
// then returns the appropriate value. 
// used by the arithmetic operation statements
int ProgramState::get_var_value(std::string name) {
	if (is_var(name)) // if it's a variable
		return getVar(name);
	else { // if it's not a variable
		return atoi(name.c_str());
	}
}

// returns whether or not the stack is empty
// represents if the Facile program is in a GoSub statement
// used by the "next" button in the debugger
bool ProgramState::empty_stack() {
	return stack.empty();
}

// returns a list of all the variables in the map
// used by the values window to output all the variables in the program
const vector<FacileVar> ProgramState::get_Vars() {
	vector<FacileVar> list; // creates a list of string, int structs

	std::map<std::string, int>::iterator it; // iterates through the map
	for (it = variables.begin(); it != variables.end(); it++)
		list.push_back(FacileVar(it->first, it->second));

	return list;
}



