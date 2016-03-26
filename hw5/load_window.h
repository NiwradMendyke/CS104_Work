// Darwin Mendyke
// CS 104 / Spring 2016
//
// load_window.h
//
// The LoadWindow class represents the first window presented to the users in the QT debugger
// Presents the user with a text input and two buttons.
//
// The text input allows the user to enter a file name. 
// Then the window checks if the file is valid, if not, outputs an error message.
// Otherwise uses filename to create the main debugger window
//
// The close button allows the user to quit.
//
// The load button closes the load screen and displays the debugger window


#ifndef LOAD_WINDOW_H
#define LOAD_WINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include <QApplication>
#include <QKeyEvent>

#include <string>
#include <vector>

#include "debugger.h"

using namespace std;

class LoadWindow : public QWidget {
	Q_OBJECT

	public:
		// constructor
		LoadWindow();

		// deconstructor
		~LoadWindow();

	protected:
		// calls the load button if user hits "enter"
		void keyPressEvent(QKeyEvent *event);

	private slots:
		// gets the inputted filename
		void get_file();

		// allows program to quit
		void quitProgram();

	private:
		string file_name; // name of the Facile file

		QGridLayout* mainWindow; // layout object for the loadscreen
		Debugger* debugger_window; // the debugger window

		QLabel* prompt; // user text input box

		QLineEdit* fileInput; // the place user inputs file name

		QPushButton* quitButton; // quits the program
		QPushButton* loadButton; // loads the file and opens the debugger window

		bool file; // flag to indicate if window has a valid file

		void show_error(string error_type); // creates the error messagebox popup
};

#endif