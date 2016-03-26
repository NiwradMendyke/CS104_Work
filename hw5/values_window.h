// Darwin Mendyke
// CS 104 / Spring 2016
//
// debugger.cpp
//
// The ValuesWindow class is the secondary window that the debuggerwindow opens.
// Shows the various variables at the current line in the Facile program. 
// Contains a display showing the variables and their values, two buttons, and four radiobuttons
//
// the close window button just hides the ValueWindow
// 
// update button updates the variables in the display to the current list of variables
//
// the radiobuttons allow the user to toggle different sorting types to sort the variable display


#include <QWidget>
#include <QListWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QListWidget>
#include <QApplication>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

#include "Statement_headers/Statement.h"
#include "Statement_headers/ProgramState.h"

using namespace std;

// functor struct to compare variable string names in ascending order
struct ascNameComp {
	bool operator()(const FacileVar& lhs, const FacileVar& rhs) {
		return lhs.name < rhs.name;
	}
};

// functor struct to compare variable string names in descending order
struct descNameComp {
	bool operator()(const FacileVar& lhs, const FacileVar& rhs) {
		return lhs.name > rhs.name;
	}
};

// functor struct to compare variable values in increasing order
struct incrNumComp {
	bool operator()(const FacileVar& lhs, const FacileVar& rhs) {
		return lhs.value < rhs.value;
	}
};

// functor struct to compare variable values in decreasing order
struct decrNumComp {
	bool operator()(const FacileVar& lhs, const FacileVar& rhs) {
		return lhs.value > rhs.value;
	}
};

class ValuesWindow : public QWidget {
	Q_OBJECT

	public:
		// constructor
		ValuesWindow(ProgramState * the_state);

		// deconstructor
		~ValuesWindow();

		// displays the variables in program state
		void show_vars();

	private slots:
		// calls show_vars()
		void slot_show(); 

		// sorts A -> Z
		void ascending_sort();

		// sorts Z - > A
		void descending_sort();

		// sorts in increasing order
		void increasing_sort();

		// sorts in decreasing order
		void decreasing_sort();

		// allows program to quit 
		void close_window(); 

	private:
		ProgramState * state;
		//bool var_window_open; // boolean flag to indicate if 
		int which_sort; // indicates which comparison functor to use

		QGridLayout* mainWindow; // layout object for the loadscreen

		QListWidget* display; // displays the variables

		QPushButton* closeB; // closes the valuewindow
		QPushButton* updateB; // updates the variable display

		QRadioButton* ascending_name; // change sort to ascending alphanumeric sort
		QRadioButton* descending_name; // change sort to descending alphanumeric sort
		QRadioButton* increasing_value; // change sort to increasing numerical sort
		QRadioButton* decreasing_value; // change sort to decreasing numerical sort

		// various functor comparison objects
		ascNameComp comp0; 
		descNameComp comp1;
		incrNumComp comp2;
		decrNumComp comp3;

		// creates the error messagebox popup
		void show_error(string error_type);

		// sorts and outputs the variables to the display
		void display_vars(vector<FacileVar> variables);
};


