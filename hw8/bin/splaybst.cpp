#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include "splaybst.h"

using namespace std;

/**
 * Empty constructor 
 */
SplayTree::SplayTree() { }

/**
 * Empty constructor 
 */
SplayTree::~SplayTree() { }

/**
 * Function to add a new word to a splaytree. 
 *
 * Uses the add_helper to get pointer to the new node, then decides how to rotate to top 
 */
void SplayTree::add(const string& word) 
{
	//cerr << "adding \"" << word << "\" to tree" << endl; // debug

	if (this->root == NULL) { // if no existing nodes
     this->root = new Node<string, int>(word, 1, NULL); // creates new node
     return;
   }

   Node<string, int> *new_node = add_helper(word, this->root); // gets pointer to new node

   while (new_node->getParent() != NULL) { // rotates until new node is at the top
   	//print();

   	if (new_node->getParent()->getParent() == NULL) {
   		zig(new_node);
   	}
   	else if (new_node->getKey() < new_node->getParent()->getKey() 
   		&& new_node->getKey() < new_node->getParent()->getParent()->getKey()) {
   		zzig(new_node);
   	}
   	else if (new_node->getKey() > new_node->getParent()->getKey() 
   		&& new_node->getKey() > new_node->getParent()->getParent()->getKey()) {
   		zzig(new_node);
   	}
   	else {
   		zzag(new_node);
   	}
   }
}

/**
 * Function to output each word in the splaytree to an output stream
 */
void SplayTree::reportAll(ostream& output) 
{
	if (root != NULL) {
		BinarySearchTree<string, int>::iterator it = this->begin();
		while (it != this->end()) {
			output << it->first << " " << it->second << endl;
			it = ++it;
		}
	}
}

/**
 * Recursive helper function to add the new node
 *
 * Iterates recursively through the binary tree until it finds a place to add the new node.
 * Also checks if the word is already in the tree.
 */
Node<string, int> *SplayTree::add_helper(const string& word, Node<string, int> *curr)
{
	// finds where to place the new value
   if (word == curr->getKey()) { // if word already exists in the tree
     curr->setValue(curr->getValue() + 1); // updates the count value
     return curr;
   } 
   else if (word < curr->getKey()) {
     if (curr->getLeft() == NULL) { // places new node to the left of parent
       curr->setLeft(new Node<string, int>(word, 1, curr));
       return curr->getLeft();
     }
     else { // recursive call to the left
       return add_helper(word, curr->getLeft());
     }
   } 
   else {
     if (curr->getRight() == NULL) { // places new node to the right of parent
       curr->setRight(new Node<string, int>(word, 1, curr));
       return curr->getRight();
     }
     else { // recursive call to the right
       return add_helper(word, curr->getRight());
     }
   }
}

/**
 * Moves a node up one.
 * Then updates pointer values of child nodes and parent nodes
 */
void SplayTree::zig(Node<string, int> *curr)
{
	Node<string, int> *old_root = curr->getParent(); // gets temp pointer to parent

	if (curr->getKey() < old_root->getKey()) { // zig from the left
		Node<string, int> *T1 = curr->getRight();

		curr->setRight(old_root); // replaces parent with child
		old_root->setParent(curr);

		old_root->setLeft(T1); // adds children of curr to the former parent
		if (T1 != NULL)
			T1->setParent(old_root);
	}
	else { // zig from the right
		Node<string, int> *T1 = curr->getLeft();

		curr->setLeft(old_root); // replaces parent with child
		old_root->setParent(curr);

		old_root->setRight(T1); // adds children of curr to the former parent
		if (T1 != NULL)
			T1->setParent(old_root);
	}

	curr->setParent(NULL);
	this->root = curr;
}

/**
 * Moves a node up two either left-left or right-right.
 * Then updates pointer values of child nodes and parent nodes
 */
void SplayTree::zzig(Node<string, int> *curr)
{
	Node<string, int> *parent = curr->getParent(); // gets temp pointer to parent
	Node<string, int> *grandparent = parent->getParent(); // gets temp pointer to grandparent
		
	if (curr->getKey() < grandparent->getKey()) { // if left-left zzig
		Node<string, int> *T1 = curr->getRight();
		Node<string, int> *T2 = parent->getRight();

		curr->setParent(grandparent->getParent());
		curr->setRight(parent);
		parent->setParent(curr);

		parent->setLeft(T1);
		if (T1 != NULL)
			T1->setParent(parent);

		parent->setRight(grandparent);
		grandparent->setParent(parent);

		grandparent->setLeft(T2);
		if (T2 != NULL)
			T2->setParent(grandparent);
	}
	else { // if right-right zzig
		Node<string, int> *T1 = curr->getLeft();
		Node<string, int> *T2 = parent->getLeft();

		curr->setParent(grandparent->getParent());
		curr->setLeft(parent);
		parent->setParent(curr);

		parent->setRight(T1);
		if (T1 != NULL)
			T1->setParent(parent);

		parent->setLeft(grandparent);
		grandparent->setParent(parent);

		grandparent->setRight(T2);
		if (T2 != NULL)
			T2->setParent(grandparent);
	}

	this->root = curr;
}

/**
 * Moves a node up two either left-right or right-left.
 * Then updates pointer values of child nodes and parent nodes
 */
void SplayTree::zzag(Node<string, int> *curr)
{
	Node<string, int> *parent = curr->getParent(); // gets temp pointer to parent
	Node<string, int> *grandparent = parent->getParent(); // gets temp pointer to grandparent
	
	if (curr->getKey() < grandparent->getKey()) { // if left-right zzag
		Node<string, int> *T1 = curr->getLeft();
		Node<string, int> *T2 = curr->getRight();

		curr->setParent(grandparent->getParent());
		curr->setLeft(parent);
		parent->setParent(curr);
		curr->setRight(grandparent);
		grandparent->setParent(curr);

		parent->setRight(T1);
		if (T1 != NULL)
			T1->setParent(parent);

		grandparent->setLeft(T2);
		if (T2 != NULL)
			T2->setParent(grandparent);
	}
	else { // if right-left zzag
		Node<string, int> *T1 = curr->getLeft();
		Node<string, int> *T2 = curr->getRight();

		curr->setParent(grandparent->getParent());
		curr->setRight(parent);
		parent->setParent(curr);
		curr->setLeft(grandparent);
		grandparent->setParent(curr);

		parent->setLeft(T2);
		if (T2 != NULL)
			T2->setParent(parent);

		grandparent->setRight(T1);
		if (T1 != NULL)
			T1->setParent(grandparent);
	}

	this->root = curr;
}

