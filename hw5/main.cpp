// Darwin Mendyke
// CS 104 / Spring 2016
//
// main.cpp
//
// The main function for the project pt2 program
// Creates a LoadWindow object and starts the QT application


#include "load_window.h"

#include <QApplication>

// main function
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	LoadWindow loadwindow;
	loadwindow.show();

	return app.exec();
}