// Facile.cpp
#include "Statement_headers/Statement.h"
#include "Statement_headers/LetStatement.h"
#include "Statement_headers/PrintStatement.h"
#include "Statement_headers/PrintallStatement.h"
#include "Statement_headers/AddStatement.h"
#include "Statement_headers/SubStatement.h"
#include "Statement_headers/MultStatement.h"
#include "Statement_headers/DivStatement.h"
#include "Statement_headers/IfStatement.h"
#include "Statement_headers/GotoStatement.h"
#include "Statement_headers/GosubStatement.h"
#include "Statement_headers/ReturnStatement.h"
#include "Statement_headers/EndStatement.h"
#include "Statement_headers/ProgramState.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream> 
#include <fstream>
#include <cstdlib>

using namespace std; 

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement *> & program);


// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement * parseLine(string line);


// method to delete allocated memory used for the statements and the programstate
// called before any return statement
void cleanUp(vector<Statement *> & program, ProgramState * programstate);


// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);


// the main function, gets a file and interprets input
// also includes try/catch statement to account for errors
int main() {
	cout << "Enter Facile program file name: "; // gets the file name from user
  string filename;
  getline(cin, filename);
  ifstream infile(filename.c_str()); // opens the input stream

  if (!infile) { // if program cannot open the file
    cout << "Cannot open " << filename << "!";
    return 1;
  }

  interpretProgram(infile, cout);

  infile.close();

  return 1;
}


void parseProgram(istream &inf, vector<Statement *> & program) {
	program.push_back(NULL); // puts NULL in 0th element of the vector
	
	string line;
	while( ! inf.eof() ) { // loops through each line in the input
		getline(inf, line);
		program.push_back(parseLine(line));
	}
}


Statement * parseLine(string line) {
	Statement * statement; // placeholder for the statement object
	stringstream ss; // stringstream to parse out individual characters in the string
	string type; // contains the first command of the line
	string var, var1, op; // placeholders for any string values in the line
	int val; // placeholder for any int values in the line

	ss << line;
	ss >> type;
	
	if (type == "LET") { // creates a new variable
		ss >> var;
		ss >> val;
		// Note:  Because the project spec states that we can assume the file
		//	  contains a syntactically legal Facile program, we know that
		//	  any line that begins with "LET" will be followed by a space
		//	  and then a variable and then an integer value.
		statement = new LetStatement(var, val);
	}
	if (type == "PRINT") { // prints out a variable value
		ss >> var;
		statement = new PrintStatement(var);
	}
	if (type == "PRINTALL") { // prints out value of all variables
		statement = new PrintallStatement();
	}
	if (type == "ADD") { // adds value of the two variables
		ss >> var;
		ss >> var1;
		statement = new AddStatement(var, var1);
	}
	if (type == "SUB") { // subtracts value of the two variables
		ss >> var;
		ss >> var1;
		statement = new SubStatement(var, var1);
	}
	if (type == "MULT") { // multiplies value of the two variables
		ss >> var;
		ss >> var1;
		statement = new MultStatement(var, var1);
	}
	if (type == "DIV") { // divides value of the two variables
		ss >> var;
		ss >> var1;
		statement = new DivStatement(var, var1);
	}
	if (type == "IF") { // conditional goto statement
		ss >> var;
		ss >> op;
		ss >> var1;
		ss >> type;
		ss >> val;
		statement = new IfStatement(var, var1, op, val);
	}
	if (type == "GOTO") { // goto statement
		ss >> val;
		statement = new GotoStatement(val);
	}
	if (type == "GOSUB") { // goto function call
		ss >> val;
		statement = new GosubStatement(val);
	}
	if (type == "RETURN") { // returns to original counter after a gosub call
		statement = new ReturnStatement();
	}
	if (type == "END" || type == ".") { // ends the program
		statement = new EndStatement();
	}
		
	cout << "statement created" << endl;
	return statement;
}


void cleanUp(vector<Statement *> & program, ProgramState * programstate) {
	cout << "cleanUp called" << endl;
	int program_size = program.size();

	//cout << program_size << endl;
	for (int i = 1; i < program_size; i++) { // deletes each statement in the vector
		delete program[i];
		cout << "statement deleted" << endl;
	}

	delete programstate; // deletes the programstate
	cout << "programstate delete" << endl;
}


void interpretProgram(istream& inf, ostream& outf) {
	vector<Statement *> program; // vector containing list of program statements
	parseProgram( inf, program );
	
	ProgramState * state = new ProgramState(program.size()); // creates the programstate
	cout << "programstate created" << endl;

	if (program.size() > 1000) {
		cout << "program may not exceed 1000 lines" << endl;
	 	state->endProgram();
	}

	while (state->getCounter() < state->getNum() && !state->is_end()) { // iterates through the program
		try { // trys to interpret the program
			program[state->getCounter()]->execute(state, outf); // executes each statement
	  }
	  catch (domain_error) { // if user tries to divide by zero
	  	cout << "divide by zero exception" << endl;
	 		state->endProgram();
	  }
	  catch (out_of_range) { // if user tries to goto bad location
	  	cout << "illegal jump instruction" << endl;
	 		state->endProgram();
	  }
	}

  cleanUp(program, state);
}

