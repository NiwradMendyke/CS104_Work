/*
* Darwin Mendyke
* CSCI 104: Spring 2016
* 4/30/16
*
* Hashtable data structure which stores a list of words from a given input.
* Uses a hash function to convert each word into a specific vector index
* Resizes if needed.
*
* Can store up to 40,961 words if needed. 
*/



#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <string>

#include "Map.h"


class HashTable : public Map  {
	public:
		HashTable();

		~HashTable();

		// virtual function inherited from map, adds a word to the hashtable
		void add(const std::string& word);

		// virtual function inherited from map, outputs all words in the table to an output
		void reportAll(std::ostream& output);

	protected:
		int stored, num_indices, num_resizes; // various integers to keep track of different values
		std::vector<std::pair<std::string, int>* > hash_list; // vector used to store the words


		// when the load factor is greater than 0.5, doubles vector size
		void resize();

		// converts a word into a vector index
		int hash(const std::string& word);

		// helper function to get an vector index
		int get_index(int hash_int, int counter);
};

#endif


