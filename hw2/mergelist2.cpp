#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
	int value;
	Node *next;
	Node (int val, Node *point) {value = val; next = point;}
};

Node* merge(Node*& first, Node*& second);

void print_list(Node* list);

int main() {
	Node *L16 = new Node(11, NULL);
	Node *L15 = new Node(9, L16);
	Node *L14 = new Node(7, L15);
	Node *L13 = new Node(5, L14);
	Node *L12 = new Node(3, L13);
	Node *L11 = new Node(1, L12);

	Node *L24 = new Node(8, NULL);
	Node *L23 = new Node(6, L24);
	Node *L22 = new Node(4, L23);
	Node *L21 = new Node(2, L22);

	Node *merged = merge(L11, L21);

	cout << "merged list: ";
	print_list(merged);
	print_list(L11);
	print_list(L21);

	while (merged != NULL) {
		Node *temp = merged->next;
		delete merged;
		merged = temp;
	}

	cout << "merged list after deleting: ";
	print_list(merged);
	//print_list(L14);
	//print_list(L22);*/

	return 0;
}

Node* merge(Node*& first, Node*& second) {
	if ((first == NULL) && (second == NULL))
		return NULL;
	if (first == NULL)
		return second;
	if (second == NULL)
		return first;
	if (first->value >= second->value) {
		second->next = merge(first, second->next); // recursive call
		//cout << "first,second" << endl; // debug
		Node *temp = second;
		//print_list(first); // debug
		//print_list(second); // debug
		first = NULL;
		second = NULL;
		return temp;
	}
	else {
		first->next = merge(first->next, second);  // recursive call
		//cout << "second,first" << endl; // debug
		Node *temp = first;
		//print_list(first); // debug
		//print_list(second); // debug
		first = NULL;
		second = NULL;
		return temp;
	}
}

// test function to output values of a linked list
void print_list(Node* list) {
	if (list == NULL)
		cout << "list is empty" << endl;
	else if (list->next == NULL)
		cout << list->value << endl;
	else {
		while (list != NULL) {
			cout << list->value << " ";
			list = list->next;
		}
		cout << endl;
	}
}