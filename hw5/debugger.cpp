// Darwin Mendyke
// CS 104 / Spring 2016
//
// debugger.cpp


#include <fstream>
#include <string>
#include <stdio.h>
#include <QFont>
#include <QModelIndex>
#include <QListWidgetItem>
#include <QItemSelectionModel>

#include "debugger.h"
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

using namespace std;

// constructor
Debugger::Debugger() {
	breaks.push_back(NULL);

	// title
	setWindowTitle("Debugger");

	// main layout
	mainWindow = new QGridLayout();

	// display for the program
	display = new QListWidget(this);
	mainWindow->addWidget(display, 0, 0, 6, 1); 

	// buttons
	breakB = new QPushButton("Breakpoint");
	connect(breakB, SIGNAL(clicked()), this, SLOT(new_break()));
	mainWindow->addWidget(breakB, 0, 1, 1, 1);

	continueB = new QPushButton("Continue");
	connect(continueB, SIGNAL(clicked()), this, SLOT(run_program()));
	mainWindow->addWidget(continueB, 1, 1, 1, 1);

	stepB = new QPushButton("Step");
	connect(stepB, SIGNAL(clicked()), this, SLOT(step_program()));
	mainWindow->addWidget(stepB, 2, 1, 1, 1);

	nextB = new QPushButton("Next");
	connect(nextB, SIGNAL(clicked()), this, SLOT(next_step()));
	mainWindow->addWidget(nextB, 3, 1, 1, 1);

	inspectB = new QPushButton("Inspect");
	connect(inspectB, SIGNAL(clicked()), this, SLOT(show_values()));
	mainWindow->addWidget(inspectB, 4, 1, 1, 1);

	quitB = new QPushButton("Quit");
	connect(quitB, SIGNAL(clicked()), this, SLOT(quitProgram()));
	mainWindow->addWidget(quitB, 5, 1, 1, 1);

	// Set overall layout
	setLayout(mainWindow);
}

// deconstructor
Debugger::~Debugger() {
	delete valueswindow;

	delete display;

	delete breakB;
	delete continueB;
	delete stepB;
	delete nextB;
	delete inspectB;
	delete quitB;

	delete state;

	delete mainWindow;
}

// accesses the Facile program from the file with the given filename
// called by the loadwindow class
void Debugger::set_file(string file) {
	ifstream infile(file.c_str()); // opens the input stream

	facile = new Facile();
	// goes through file input and creates the program
	vector<string> lines_text = facile->parseProgram(infile);

	for (unsigned int i = 0; i < lines_text.size(); i++) {
		stringstream ss;
		ss << (i + 1);

		new QListWidgetItem(QString::fromStdString(ss.str() + "\t" + lines_text[i]), display);
		breaks.push_back(false);
	}

	if (lines_text.size() > 1000) {
		show_error("Can't have more than 1000 lines");
	}
	
	state = new ProgramState(lines_text.size()); // creates the programstate

	valueswindow = new ValuesWindow(state); // creates the value window

	advance(0, 0); // creates '-->' at the first line
}

// slot function to create or delete a break point at the selected line
// if no line is selected, creates the break point at the current line in the program
// if the line already has a breakpoint, deletes it
// breakpoint is represented by '*' at the end of the line
void Debugger::new_break() {
	int selected_row = display->currentRow() + 1; // gets the current selected row
	string line = display->item(selected_row - 1)->text().toStdString(); // gets the text at that row

	if (!breaks[selected_row]) { // if no breakpoint currenlty exists there
		display->insertItem(selected_row, QString::fromStdString(line + "*")); // adds a new line with that breakpoint
		delete display->item(selected_row - 1); // removes the old line
	
		breaks[selected_row] = true; // updates the break vector
	}
	else { // if there's already a breakpoint there
		display->insertItem(selected_row, QString::fromStdString(line.substr(0, line.size() - 1)));
		delete display->item(selected_row - 1); // removes the old line

		breaks[selected_row] = false; // updates the break vector
	}
}


// slot function to run through the entire program
// stops if it reaches a line with a breakpoint
// moves the '-->' cursor from the starting line to the ending line
void Debugger::run_program() {
	int start_line = state->getCounter(); // gets start line

	// needs to set the bool flag to false to allow function to execute past a breakpoint
	bool temp = breaks[start_line];
	breaks[start_line] = 0;

	// iterates through program until reaches a breakpoint, or it reaches the end
	while (!state->is_end() && !breaks[state->getCounter()]) {
		facile->execute_line(state);
	}

	if (state->is_end()) { // resets the programstate if it reaches the end
		reset_state();
	}

	// restores the bool flag at a breakpoint line
	breaks[start_line] = temp;

	advance(start_line - 1, state->getCounter() - 1); // moves the '-->' cursor
	display->item(state->getCounter() - 1)->setSelected(true); // sets the selected row to the current row in the program
}

// slot function to step through one line of the program
// moves the '-->' cursor to the next line
void Debugger::step_program() {
	int start_line = state->getCounter() - 1; // gets the start line

	facile->execute_line(state); // executes the next line

	if (state->is_end()) // resets the programstate if it reaches the end
		reset_state();

	advance(start_line, state->getCounter() - 1); // moves the '-->' cursor
	display->item(state->getCounter() - 1)->setSelected(true); // sets the selected row to the current row in the program
}

// slot function to step through one line of the program
// if it hits a GoSub function, iterates through the GoSub until program returns
// moves the '-->' cursor to the next line
void Debugger::next_step() {
	int start_line = state->getCounter(); // gets the start line

	// needs to set the bool flag to false to allow function to execute past a breakpoint
	bool temp = breaks[start_line];
	breaks[start_line] = 0;

	facile->execute_line(state); // executes the next line
	while (!state->is_end() && !state->empty_stack() && !breaks[state->getCounter()]) {
		// if the programstate stack isn't empty, keeps executing until a RETURN statement is reached
		facile->execute_line(state);
	}

	if (state->is_end()) // resets the programstate if it reaches the end
		reset_state();

	// restores the bool flag at a breakpoint line
	breaks[start_line] = temp;

	advance(start_line - 1, state->getCounter() - 1); // moves the '-->' cursor
	display->item(state->getCounter() - 1)->setSelected(true); // sets the selected row to the current row in the program
}

// slot function to display the values window
void Debugger::show_values() {
	valueswindow->show();
	valueswindow->show_vars(); // updates the variables if pressed again
}

// slot function to quit program
void Debugger::quitProgram() {
	QApplication::quit();
}

// displays and error with the passed string message
void Debugger::show_error(string error_type) {
	// Create message box
	QMessageBox msgBox;

	// Set message box text values
	msgBox.setWindowTitle("Error");
	msgBox.setText(QString::fromStdString(error_type));

	msgBox.exec();
}

// advances the cursor from line prev to line next
// QListWidget doesn't allow modification of a line, so the function must insert then delete
void Debugger::advance(int prev, int next) {
	string previous = display->item(prev)->text().toStdString(); // gets the text from previous line
	
	if (previous.substr(0, 3) == "-->") // removes the cursor if it exists
		previous = previous.substr(3);
		
	display->insertItem(prev, QString::fromStdString(previous)); // displays the cursor-free line
	delete display->item(prev + 1); // deletes the old one

	string next_item = display->item(next)->text().toStdString(); // gets text from next line
	display->insertItem(next, QString::fromStdString("-->" + next_item)); // displays new line with the cursor
	delete display->item(next + 1); // deletes the old one
}

// executes one line of the facile program
// catches for potential errors in the program
void Debugger::execute_line(ProgramState * state) {
	try { // trys to interpret the program
		facile->execute_line(state); // executes each statement
  	}
  	catch (domain_error& e) { // if user tries to divide by zero
  		show_error("divide by zero exception"); // shows error message
		state->endProgram();
	}
  	catch (out_of_range& e) { // if user tries to goto bad location
  		show_error("invalid location error"); // shows error message
 		state->endProgram();
  	}
}

// resets the programstate so that the interpreter can start over
// used by all the program-advancing buttons
void Debugger::reset_state() {
	int temp_size = state->getNum();
	ProgramState * tempState = state; // shallow copy to tempState

	delete tempState;
	state = new ProgramState(temp_size); // assigns the pointer to a new ProgramState
}



