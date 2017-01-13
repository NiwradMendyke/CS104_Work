#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// node object used for the list
struct Node {
	int value;
	Node *next;
	Node (int val, Node *point) {value = val; next = point;}
};

Node* merge(Node*& first, Node*& second);

// recursive function to merge two ordered lists
Node* merge(Node*& first, Node*& second) {
	if ((first == NULL) && (second == NULL)) // checks if two lists are empty
		return NULL;
	if (first == NULL) // if end of 1st list reached
		return second;
	if (second == NULL) // if end of 2nd list reached
		return first;
	// advances the pointer pointing to the lesser value
	if (first->value >= second->value) {
		second->next = merge(first, second->next); // recursive call
		Node *temp = second;

		// cleans the original pointers
		first = NULL;
		second = NULL;
		return temp;
	}
	// advances the pointer pointing to the lesser value
	else {
		first->next = merge(first->next, second);  // recursive call
		Node *temp = first;

		// cleans the original pointers
		first = NULL;
		second = NULL;
		return temp;
	}
}