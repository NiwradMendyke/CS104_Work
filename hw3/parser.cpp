/*
*	Darwin Mendyke
*	mendyke@usc.edu
* CS170
*
* Program to read in and solve arithmetic expressions.
* Uses a StackInt class to store int values and operands.
* Then performs the operations as it reads values back out of the stack.
*
* To run with make, use "make parser", then execute it with "make parse"
*/

#include "stackint.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <stdexcept>

using namespace std;

// converting the required symbols to int values
const int OPEN_PAREN = -1;
const int CLOSE_PAREN = -2;
const int ADD = -3;
const int MULTIPLY = -4;
const int SHIFT_LEFT = -5;
const int SHIFT_RIGHT = -6;

int convert_to_int(char in);
int sum_of_ints(vector<int> ints, int num);
int product_of_ints(vector<int> ints, int num);

// main function that reads input and loops through it
int main(int argc, char* argv[]) {
	if (argc < 2) { // checks if right number of arguements
    cerr << "Please provide an input file." << endl;
    return 1;
  }

  ifstream input(argv[1]);

  if (input.fail()) { // checks if can read file
  	cerr << "Cannot read input file" << endl;
  	return 1;
  }

  StackInt stack = StackInt(); // main stack for use in the program
  string curr; // captures the line of text

  while(getline(input, curr)) {
  	//cerr << curr << endl;
  	vector<int> ints; // stores the integer values
  	bool malformed = false; // flag to track if line is malformed
  	bool operand = false; // flag to track if line has '+' or '*'
  	int digit; // keeps track of which digit the number being inputed is on
  	int num_open = 0; // number of open parenthesis
  	int num_close = 0; // number of closing parenthesis
  	int result = 0; // the result of a line of arithmetic
  	int operation = 0; // keeps track of which operand to use

  	const char* cur = curr.c_str();

  	for (int i = 0; i < strlen(cur); i++) { // iterates through each char on a line
  		//cerr << "iterating through the line" << endl;
  		
  		if (cur[i] != ' ') { // checks if line is empty space
  			stack.push(convert_to_int(cur[i])); // otherwise converts to int and pushes onto stack

  			// records number of each type of parenthesis
  			if (stack.top() == -1)
	  			num_open++;
	  		if (stack.top() == -2)
	  			num_close++;
  		}

  		// checks if ')' '+' or '*' is at the start of the line
  		if (i == 0 && ((stack.top() != OPEN_PAREN) && ((stack.top() > -5) && (stack.top() < 0)))) {
  			malformed = true;
  			//cerr << "first value is not acceptable" << endl;
  			break;
  		}

  		// checks if '(' '*' '+' '<' '>' is at the end of the line
  		if (i == (strlen(cur) - 1) && ((stack.top() != CLOSE_PAREN) && (stack.top() < 0))) {
  			malformed = true;
  			//cerr << "last value must be parenthesis or number" << endl;
  			break;
  		}

  		// checks if line has an operand
  		if ((stack.top() == ADD) || (stack.top() == MULTIPLY))
  			operand = true;

  		// if a closing loop is found on an operand statement
  		if ((stack.top() == CLOSE_PAREN) && operand) {
  			ints.push_back(0);
  			int num_ints = 0; // records number of integer values in an operation
  			digit = 0;
  			operation = 0;
  			stack.pop();

  			while (stack.top() != OPEN_PAREN) { // iterates until an opening parenthesis is found
  				//cerr << "looking for the open_paren" << endl;

  				int top = stack.top();
  				if (top == -10) {
  					malformed = true;
  					break;
  				}
  				else if (top < 0) {
  					if (digit == 0) { // if a symbol is found directly before closing parenthesis
  						malformed = true;
  						//cerr << "can't end expression with operand" << endl;
  						break;
  					}
  					else if (top == SHIFT_RIGHT) {
  						ints[num_ints] = ints[num_ints] / 2;
  					}
  					else if (top == SHIFT_LEFT) {
  						ints[num_ints] = ints[num_ints] * 2;
  					}
  					// if a single statement has different operand types
  					else if (((operation != 0) && (operation != 1)) && (top != operation)) {
  						malformed = true;
  						//cerr << "operands don't match" << endl;
  						break;
  					}
  					else { // if the symbol is another of the same operand type
  						operation = top;
  						ints.push_back(0);
  						num_ints++;
  						digit = 0;	
  					}
  				}
  				else { // if the character is a integer digit
  					ints[num_ints] += (top * pow(10, digit));
  					digit++;
  				}
  				stack.pop();

  				if (stack.empty()) { // if a closing parenthesis is found w/o an opening parenthesis
						malformed = true;
						//cerr << "can't find opening parenthesis" << endl;
						break;
					}
  			}
  			
  			if (malformed)
  				break;

  			stack.pop();

  			if (digit == 0) { // if the parenthesis statement begins with an operand
  				malformed = true;
  				//cerr << "can't start expression with operand" << endl;
  				break;
  			}

  			/*cerr << ints[0]; // debug to output values of int values
  			for (int i = 1; i <= num_ints; i++)
  				cerr << " " << operation << " " << ints[i];
  			cerr << endl;*/

  			result = ints[0];

  			switch (operation) { // performs the operation
  				case ADD:
  					result = sum_of_ints(ints, num_ints);
  					break;
  				case MULTIPLY:
  					result = product_of_ints(ints, num_ints);
  					break;
  			}

  			while (!stack.empty()) { // checks if there are any shift symbols
  				if (stack.top() <= -5) {
  					if (stack.top() == SHIFT_RIGHT) {
  						result = result / 2;
  						stack.pop();
  					}
  					else {
  						result = result * 2;
  						stack.pop();
  					}
  				}
  				else if (stack.top() >= 0) { // a number follows an opening parenthesis in the stack
  					malformed = true;
  					//cerr << "can't have number right after parenthesis" << endl;
  					break;
  				}
  				else {
  					break;
  				}
  			}

  			stack.push(result);
  			ints.clear();
  		}
  	}

  	if (num_close != num_open) { // checks if number of parenthesis match
  		malformed = true;
  		//cerr << "unequal nnumber of parenthesis" << endl;
  	}

  	if (!operand) { // if statement has no operand values
  		bool is_empty = true; // checks if there are number values in the expression

  		if (stack.top() <= -3) { // line cannot end with shift symbol
  			malformed = true;
  			//cerr << "can't start with shift or operand key" << endl;
  		}
  		else {
  			digit = 0;

				while (!stack.empty()) {
					int top = stack.top();

					if (stack.top() >= 0) { // if the character is an integer digit
						if (is_empty)
							is_empty = false;
						if (digit == -1) { // if there is already another integer digit
							malformed = true;
							//cerr << "can't have mulitple values in a not-operand" << endl;
							break;
						}
						result += (top * pow(10, digit)); // adds to result
						digit++;
					}
					else if (top == SHIFT_RIGHT) {
						result = result / 2;
						digit = -1;
					}
					else if (top == SHIFT_LEFT) {
						result = result * 2;
						digit = -1;
					}
					else if ((top == OPEN_PAREN) || (top == CLOSE_PAREN)) {

					}
					else {
						malformed = true;
						//cerr << "not an operand and not an acceptable value" << endl;
						break;
					}

					stack.pop();
				}	

				if (is_empty) { // if no integer values in expression
					malformed = true;
					//cerr << "not an operand and empty" << endl;
				}
				else 
					stack.push(result);
  		}			
		}

  	if (malformed) {
  		ints.clear();
  		cerr << "malformed" << endl;
  	}
  	else {
  		cout << result << endl;
  		stack.pop();
  	}

  	while (!stack.empty()) 
  		stack.pop();
  }

  input.close();

  return 0;
}

// function to convert a char input value into an int to place on the stackint object
int convert_to_int(char in) {
	int a = in;
	if (a >= 48 && a <= 57)
		return a - 48;
	else {
		switch (in) {
			case '(':
				return OPEN_PAREN;
			case ')':
				return CLOSE_PAREN;
			case '+':
				return ADD;
			case '*':
				return MULTIPLY;
			case '>':
				return SHIFT_RIGHT;
			case '<':
				return SHIFT_LEFT;
		}
	}

	return -10;
}

// sums the values of a vector of integers
int sum_of_ints(vector<int> ints, int num) {
	int sum = 0;

	for (int i = 0; i <= num; i++)
		sum += ints[i];

	return sum;
}

// multiplies the values of a vector of integers 
int product_of_ints(vector<int> ints, int num) {
	int product = 1;

	for (int i = 0; i <= num; i++)
		product *= ints[i];

	return product;
}

