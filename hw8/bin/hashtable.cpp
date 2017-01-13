#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cmath>

#include "hashtable.h"

using namespace std;

/**
 * Constructor to set initial values for variables
 */
HashTable::HashTable() 
{ 
	stored = 0;
	num_indices = 11; // initial size of 11
	num_resizes = 0;

	for (int i = 0; i < num_indices; i++) // fills hashtable with empty values
		hash_list.push_back(NULL);
}

/**
 * Deconstructor
 */
HashTable::~HashTable() 
{ 
	for (int i = 0; i < num_indices; i++) {
		if (hash_list[i] != NULL) {
			delete hash_list[i];
		}
	}
}

/**
 * Function to add a word to the hashtable.
 * Uses a hashfunction to get an index for the vector.
 *
 * Also checks if the vector needs to be resized, and if the word is already in the vector
 */
void HashTable::add(const std::string& word)
{
	if ((stored * 2) >= num_indices) { // checks load factor
		resize(); // doubles vector size
	}

	int hash_int, i = 0;

	try {
		hash_int = hash(word); // gets the hash-integer
		//cerr << "|" << word << "| returns hash int " << hash_int << endl; // debug
	}
   catch (std::exception& e) {
		//cout << e.what() << endl;
	}

	// loop to implement quadratic probing and find appropriate index
	while ((hash_list[get_index(hash_int, i)] != NULL) && (pow(i, 2) < num_indices)) {
		if (hash_list[get_index(hash_int, i)]->first == word) { // if the word is already in the table
			hash_list[get_index(hash_int, i)]->second = hash_list[get_index(hash_int, i)]->second + 1;
			return;
		}

		i++; 
	}

	hash_list[get_index(hash_int, i)] = new std::pair<std::string, int>(word, 1); // otherwise adds word to hashtable
	//cerr << word << " was stored in hash_list[" << get_index(hash_int, i) << "]" << endl; // debug
	stored++;
}

/**
 * Function to output each word in the hashtable to an output stream
 */
void HashTable::reportAll(std::ostream& output)
{
	for (int i = 0; i < num_indices; i++) {
		if (hash_list[i] != NULL) {
			output << hash_list[i]->first << " " << hash_list[i]->second << endl;
		}
	}
}

/**
 * Function to double the size of the hashtable vector.
 *
 * Then adds every word in the original vector to the new updated vector
 */
void HashTable::resize()
{
	int sizes[14] = {11, 23, 41, 83, 163, 331, 641, 1283, 2579, 5147, 10243, 20483, 40961, 81923};
	
	stored = 0;
	num_resizes++; // updates which value of sizes[] to use
	
	vector<pair<string, int> > temp; // to hold the existing words in the vector

	for (int i = 0; i < num_indices; i++) { // moves existing words into temp
		if (hash_list[i] != NULL) {
			temp.push_back(pair<string, int>(hash_list[i]->first, hash_list[i]->second));
		}
	}

	num_indices = sizes[num_resizes];

	for (int i = 0; i < sizes[num_resizes - 1]; i++) { // deletes words from original vector
		if (hash_list[i] != NULL) {
			delete hash_list[i];
		}
	}
	hash_list.clear();
	for (int i = 0; i < sizes[num_resizes]; i++) {
		hash_list.push_back(NULL);
	}
	for (unsigned int i = 0; i < temp.size(); i++) { // adds the existing words back into the updated vector
		for (int j = 0; j < temp[i].second; j++)
			add(temp[i].first);
	}
}

/**
 * Function to convert a given word into an array index using a complicated algorithm
 *
 * Also checks if word is over 28 characters and if it's a valid ascii value.
 * Otherwise it throws a domain_error
 */
int HashTable::hash(const std::string& word)
{
	if (word.length() > 28) { // checks word length
		throw std::domain_error("word is too long: " + word);
	}

	char char_word[28]; // char buffer to store chars in the word
	int base_40961[14];
	int randoms[14] = {34394, 36706, 38074, 16351, 2623, 10174, 22339, 27779, 36642, 19250, 36216, 33514, 24019, 5552};
	strcpy(char_word, word.c_str()); // copies word into the char buffer
	int i = word.length() - 1, k = 13;;

	while (i >= 0) { // iterates through the word
		int j = 0;
		long long step1 = 0, a = 1;

		while (j < 8 && i >= 0) { // loops through every 8 characters and converts to a long long
			//cerr << "iterating through " << i << "th char in the string " << char_word[i] << endl; // debug
			//cerr << a << " * " << (int) char_word[i] << endl; // debug
			int b = (int) char_word[i]; // casts the character into an int

			if (b < 0) {
				throw std::domain_error("invalid character: " + word);
			}

			step1 += a * b; // adds to the long long
			a = a * 128;
			j++;
			i--;
		}

		while (step1 != 0) { // converts the long long into a base 40,961 number
			//cerr << "value of step1 is " << step1 << endl; // debug
			base_40961[k] = step1 % 40961;
			//cerr << "added " << base_40961[k] << " to 14-digit value" << endl; // debug
			step1 = step1 / 40961;
			k--;
		}
		while (k >= 0) { // fills remaining empty spaces in the char buffer with 0
			base_40961[k] = 0;
			k--;
		}
	}

	long long return_value= 0;
	for (int b = 0; b < 14; b++) { 
		return_value += randoms[b] * base_40961[b];
	} 

	return return_value % num_indices; // returns the hash-integer
}

/**
 * Shortcut function to shorten lines of code.
 *
 * Returns a vector index given a hash_int and a counter
 */
int HashTable::get_index(int hash_int, int counter)
{
	return (hash_int + (counter * counter)) % num_indices;
}

