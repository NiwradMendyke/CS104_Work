/*
* Darwin Mendyke
* CSCI 104: Spring 2016
* 4/30/16
*
* SplayTree data structure to store a list of words from a given input.
*
* Functions by storing the words in an implemented binary search tree.
* Newest words added are rotated to the top.
* Rotations are formed by a combination of zigs, zigzigs, and zigzags. 
*/



#ifndef SPLAYBST_H
#define SPLAYBST_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <string>

#include "bst.h"
#include "Map.h"


class SplayTree : public BinarySearchTree<std::string, int>, public Map  {
	public:
		SplayTree();

		~SplayTree();

		// virtual function inherited from map, adds a word to the hashtable
		void add(const std::string& word);

		// virtual function inherited from map, outputs all words in the table to an output
		void reportAll(std::ostream& output);

	protected:
		// recursive helper function to find the location in the tree to add the new word
		Node<std::string, int> *add_helper(const std::string& word, Node<std::string, int> *curr);

		// moves a word up one node
		void zig(Node<std::string, int> *curr);

		// moves a word up two nodes in the same direction
		void zzig(Node<std::string, int> *curr);

		// moves a word up two nodes in two directions
		void zzag(Node<std::string, int> *curr);

};

#endif