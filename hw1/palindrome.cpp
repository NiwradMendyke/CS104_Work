/*
*	Darwin Mendyke
* 	mendyke@usc.edu
*
*	Program to identify a palindrome
*/

#include <iostream>
#include <sstream>
#include <cstring> 

using namespace std;

// Recursive function to compare characters of a string
bool helper(stringstream &input, int len)
{
	char prev, next;

	if (len == 0) return true; // if we are at the midpoint of the string, return true.

	input >> prev; // gets previous character in string

	if (len == 1) return true; // if at midpoint of the string, return true

	bool val = helper(input, len-2); // recursive call

	input >> next; // gets next character in string

	//cout << prev << " " << next << endl; // debug

	// if previous pair are equal, checks the next pair of characters
	if (val) 
		return prev == next;

	return false;
}

// Main function, calls the recursive function
int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a string of characters." << endl;
    return 1;
  }

  stringstream ss;

  ss << argv[1]; 

  // calls the recursion
  if(helper(ss, strlen(argv[1])))
	  cout << "Palindrome" << endl;

  else cout << "Not a Palindrome" << endl;
  
  return 0;
}
