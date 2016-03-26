// ProgramState.h
//
// CS 104 / Spring 2016
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a Facile program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// Also contains a number of methods related to the functionality of each.


#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include "../StackInt/stackint.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

// the struct object to pass a variable representation to another class
struct FacileVar {
	FacileVar() { } // empty constructor
	FacileVar(string var_name, int var_value) : name(var_name), value(var_value) { }
	string name;
	int value;
};

class ProgramState {
	public:
		// constructor
		ProgramState(int numLines);

		// returns total number of lines
		int getNum();

		// returns current line number
		int getCounter();

		// allows changes to the current line number
		void setCounter(int line);

		// sets flag to end program
		void endProgram();

		// adds line number to the stack
		void gosub();

		// gets top line number from the stack
		void return_();

		// checks if program should terminate
		bool is_end();

		// checks if variable exists in the map
		bool is_var(std::string name);

		// gets the variable
		int getVar(std::string name);

		// allows changes to variable
		void setVar(std::string name, int value);

		// outputs every variable
		void print_Vars();

		// gets the value of input parameter
		int get_var_value(std::string name);

		// tells user if Facile is in a GoSub function
		bool empty_stack();

		// returns a list of all variables in the map
		const vector<FacileVar> get_Vars(); 

	private:
		int m_numLines; // total number of lines
		int counter; // current line
		bool endLine; // flag to indicate whether program should end
		StackInt stack; // stack to hold line number to return to after a gosub call
		std::map<std::string, int> variables; // map containing variables for the program
};

#endif



