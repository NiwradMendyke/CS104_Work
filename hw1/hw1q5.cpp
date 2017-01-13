/*
*	Darwin Mendyke
* 	mendyke@usc.edu
*
*	Program to read a text file and output the text in reverse
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring> 

using namespace std;

// recursive function to read and output text from a file
void output(ifstream &ifile) {
	string out;
	ifile >> out; // gets next word

	if (!ifile.fail()) // checks for base case
		output(ifile);

	if (out != "") // ensures program doesn't output an empty space at the end
		cout << out << endl;
}

// main function of program
int main(int argc, char* argv[]) {
	int temp;

  if(argc < 2) {
    cerr << "Please provide a file name." << endl;
    return 1;
  }

	ifstream myFile (argv[1]);

	if(myFile.fail() ) { // able to open file? 
		cerr << "Couldn't open file" << endl; 
		return 1;
	}

	myFile >> temp;

	output(myFile);

	myFile.close();

	return 0;
}