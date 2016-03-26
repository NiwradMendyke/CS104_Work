// Darwin Mendyke
// CS 104 / Spring 2016
//
// load_window.cpp


#include <fstream>

#include "load_window.h"

using namespace std;

// constructor
LoadWindow::LoadWindow() {
	file = false;
	debugger_window = new Debugger(); // creates the hidden debugger window

	// title
	setWindowTitle("Loading");

	// main layout
	mainWindow = new QGridLayout();

	// labels
	prompt = new QLabel("Please enter a Facile filename");
	mainWindow->addWidget(prompt, 0, 0, 1, 2);

	// text input
	fileInput = new QLineEdit();
	mainWindow->addWidget(fileInput, 1, 0, 1, 2);

	// buttons
	quitButton = new QPushButton("Quit");
	connect(quitButton, SIGNAL(clicked()), this, SLOT(quitProgram()));
	mainWindow->addWidget(quitButton, 3, 0, 1, 1);

	loadButton = new QPushButton("Load file");
	connect(loadButton, SIGNAL(clicked()), this, SLOT(get_file()));
	mainWindow->addWidget(loadButton, 3, 1, 1, 1);

	// Set overall layout
	setLayout(mainWindow);
}

// deconstructor
LoadWindow::~LoadWindow() {
	delete debugger_window;

	delete loadButton;
	delete quitButton;
	delete fileInput;
	delete prompt;

	delete mainWindow;
}

// function to capture a key press from the user
// if user hits "enter", gets the file from the input
void LoadWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) // checks the key
		get_file();
}

// slot function to collect the text from user input
// used by the load button
void LoadWindow::get_file() {
	// error popup if user left input blank
	if(fileInput->text().isEmpty()) {
		show_error("You didn't enter anything");
		return;
	}

	file_name = fileInput->text().toStdString();

	ifstream infile(file_name.c_str()); // opens the input stream

	if (!infile) { // if program cannot open the file
		show_error("Not a real file");
		return;
	}

	file = true;

	infile.close();

	close(); // closes the load window

	debugger_window->set_file(file_name); // passes filename to debugger window
	debugger_window->show(); // displays the debugger window
}

// slot function to quit program
void LoadWindow::quitProgram() {
	QApplication::quit();
}


// displays and error with the passed string message
void LoadWindow::show_error(string error_type) {
	// Create message box
	QMessageBox msgBox;

	// Set message box text values
	msgBox.setWindowTitle("Error");
	msgBox.setText(QString::fromStdString(error_type)); // converts to QString

	msgBox.exec();
}

