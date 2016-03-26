// Darwin Mendyke
// CS 104 / Spring 2016
//
// values_window.cpp


#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <QFont>
#include <QMessageBox>
#include <QModelIndex>
#include <QListWidgetItem>

#include "msort.h"
#include "values_window.h"
#include "Statement_headers/Statement.h"
#include "Statement_headers/ProgramState.h"

using namespace std;


// constructor
// takes the programstate pointer as a parameter
ValuesWindow::ValuesWindow(ProgramState * the_state) : state(the_state) {
	//var_window_open = false;

	// title
	setWindowTitle("Variable values");

	// main layout
	mainWindow = new QGridLayout();

	// display for the program
	display = new QListWidget(this);
	mainWindow->addWidget(display, 0, 0, 3, 2); 

	// buttons
	closeB = new QPushButton("Close window");
	connect(closeB, SIGNAL(clicked()), this, SLOT(close_window()));
	mainWindow->addWidget(closeB, 3, 0, 1, 1);

	updateB = new QPushButton("Update");
	connect(updateB, SIGNAL(clicked()), this, SLOT(slot_show()));
	mainWindow->addWidget(updateB, 3, 1, 1, 1);

	// radiobuttons
	ascending_name = new QRadioButton("Sort A -> Z", this);
	connect(ascending_name, SIGNAL(clicked()), this, SLOT(ascending_sort()));
	mainWindow->addWidget(ascending_name, 0, 3, 1, 1);
	ascending_name->setChecked(true);

	descending_name = new QRadioButton("Sort Z -> A", this);
	connect(descending_name, SIGNAL(clicked()), this, SLOT(descending_sort()));
	mainWindow->addWidget(descending_name, 1, 3, 1, 1);

	increasing_value = new QRadioButton("Sort increasing", this);
	connect(increasing_value, SIGNAL(clicked()), this, SLOT(increasing_sort()));
	mainWindow->addWidget(increasing_value, 2, 3, 1, 1);

	decreasing_value = new QRadioButton("Sort decreasing", this);
	connect(decreasing_value, SIGNAL(clicked()), this, SLOT(decreasing_sort()));
	mainWindow->addWidget(decreasing_value, 3, 3, 1, 1);

	// Set overall layout
	setLayout(mainWindow);

	which_sort = 0; // sets ascending_name comparison functor as the initial sort
}

// deconstructor
ValuesWindow::~ValuesWindow() {
	delete display;

	delete closeB;
	delete updateB;
	delete ascending_name;
	delete descending_name;
	delete increasing_value;
	delete decreasing_value;

	delete mainWindow;
}

// clears the display then updates it with latest variable values from the Facile program
// called by both the update slot function and the debugger window
void ValuesWindow::show_vars() {
	display->clear();
	display_vars(state->get_Vars());
}

// slot function that calls show_vars()
void ValuesWindow::slot_show() {
	show_vars();
}

// sorts A -> Z
void ValuesWindow::ascending_sort() {
	which_sort = 0;
}

// sorts Z -> A
void ValuesWindow::descending_sort() {
	which_sort = 1;
}

// sorts in increasing numeric order
void ValuesWindow::increasing_sort() {
	which_sort = 2;
}

// sorts in decreasing numeric order
void ValuesWindow::decreasing_sort() {
	which_sort = 3;
}

// slot function to close the window
void ValuesWindow::close_window() {
	this->close();
}

// displays and error with the passed string message
void ValuesWindow::show_error(string error_type) {
	// Create message box
	QMessageBox msgBox;

	// Set message box text values
	msgBox.setWindowTitle("Error");
	msgBox.setText(QString::fromStdString(error_type));

	msgBox.exec();
}

// takes a list of variable structs and outputs it to the display
// determines which sort to use
// then sorts the list with the mergesort templated function using the appropriate functor
void ValuesWindow::display_vars(vector<FacileVar> variables) {
	switch (which_sort) { // examines which_sort to determine which sort to use
		case 0:
			mergeSort(variables, comp0);
			break;
		case 1:
			mergeSort(variables, comp1);
			break;
		case 2:
			mergeSort(variables, comp2);
			break;
		case 3:
			mergeSort(variables, comp3);
			break;
	}

	// iterates through the list and adds to the ListWidget object
	for (unsigned int i = 0; i < variables.size(); i++) {
		stringstream ss;
		ss << variables[i].value; // adds the integer value to stringstream

		// creates a new ListWidgetItem
		new QListWidgetItem(QString::fromStdString(variables[i].name + "\t" + ss.str()), display);
	}
}


