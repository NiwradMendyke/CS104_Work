// Darwin Mendyke
// CS 104 / Spring 2016
//
// debugger.h
//
// The DebuggerWindow class is the main window for the QT graphical debugger
// Contains a display showing the lines from the Facile file, and six buttons.
// "*" represents a breakpoint and "-->" represents the current line of the program
// 
// Break button creates and removes breakpoint at the selected line.
//
// Continue button executes each line of the program until the program either finishes
// or it reaches a breakpoint
// 
// Step button executes an individual line of the program.
//
// Next button functions like the step button, except it completely executes a GoSub function
//
// Inpsect button creates the value window which shows the values of each variable at the current line.
// Pressing inspect again while the value window is open simply updates the values
//
// Quit button exits the program


#include <QWidget>
#include <QListWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include <QApplication>
#include <QKeyEvent>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream> 
#include <fstream>
#include <cstdlib>

#include "facile.h"
#include "values_window.h"
#include "Statement_headers/Statement.h"
#include "Statement_headers/ProgramState.h"

using namespace std;

class Debugger : public QWidget {
	Q_OBJECT

	public:
		// constructor
		Debugger();

		// deconstructor
		~Debugger(); 

		// allows the loadwindow to pass the file to the debugger
		void set_file(string file);

	private slots:
		// creates or deletes a breakpoint
		void new_break();

		// runs through the program
		void run_program();

		// steps to the next line
		void step_program();

		// like step, but advances through a GoSub function
		void next_step(); 

		// shows the value window
		void show_values();

		// allows program to quit
		void quitProgram();

	private:
		//vector<Statement *> program; // vector containing list of program statements
		vector<bool> breaks; // vector containing list of breakpoints
		Facile* facile; // facile program interpreter
		ProgramState* state; // represents current state of the program

		ValuesWindow* valueswindow; // the value window

		QGridLayout* mainWindow; // layout object for the loadscreen

		QListWidget* display; // displays the facile lines

		QPushButton* breakB; // creates breakpoint
		QPushButton* continueB; // continues through program
		QPushButton* stepB; // steps to next line
		QPushButton* nextB; // steps to next line unless its a GoSub function
		QPushButton* inspectB; // opens value window
		QPushButton* quitB; // quits program

		// creates the error messagebox popup
		void show_error(string error_type);

		// moves the '-->' cursor from one line to another
		void advance(int prev, int next);

		// executes one line of the Facile program
		void execute_line(ProgramState* state);

		// resets the programstate
		void reset_state();
};
