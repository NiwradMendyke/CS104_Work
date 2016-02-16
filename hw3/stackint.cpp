#include "stackint.h"
#include "llistint.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

StackInt::StackInt() {
	list = LListInt();
}

StackInt::~StackInt() {
	list.clear();
}

// Returns true if the stack is empty, false otherwise
bool StackInt::empty() const {
	return (list.size() == 0);
}

// Pushes a new value, val, onto the top of the stack
void StackInt::push(const int& val) {
	list.insert(0, val);
}


// Returns the top value on the stack
int const &  StackInt::top() const {
	return list.get(0);
}

// Removes the top element on the stack
void StackInt::pop() {
	list.remove(0);
}