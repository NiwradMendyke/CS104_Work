/*
* 	Darwin Mendyke
* 	mendyke@usc.edu
* 	3/21/19
*
* 	msort.h
* 	
*	Templated function to mergesort a vector of any type.
*	Uses a passed functor that specifies the comparison desired.
*	Sort function based off this example: 
*	http://vh216602.truman.edu/agarvey/jins319/sort.html
*
*	spoke with Shindler regarding use of this source on 12:25 3/22/16
*	he allowed use of this as a reference
*/

#include <vector>
#include <math.h>
#include <iostream>

#include "Statement_headers/ProgramState.h"

using namespace std;

/*
// debug method used to output the values of a vector
template <class T>
void print_array (vector<T>& myArray, int l, int r) {
	for (int i = l; i < r; i++)
		cout << myArray[i] << " ";
	cout << endl;
}
*/

// helper function used as part of mergesort
// does the merging between two seperatly sorted parts of a parent vector
template <class T, class Comparator>
void merge (vector<T>& myArray, int leftPos, int rightPos, int rightEnd, Comparator comp) {
	//cout << "called merge with " << leftPos << " to " << rightPos << " to " << rightEnd << endl; // debug
	
	int leftEnd = rightPos - 1; // end of left side of the list
   int tmpPos = leftPos; // iterates through a temporary vector object
   int numElements = rightEnd - leftPos + 1;
   vector<T> temp(myArray.size()); // temporary list to hold sorted values
	
	// iterates through both halves of the list segement
	// adds each element to temporary list in sorted order
	while(leftPos <= leftEnd && rightPos <= rightEnd) {
		if (comp(myArray[leftPos], myArray[rightPos])) // uses the comparison functor
         temp[tmpPos++] = myArray[leftPos++];
      else
         temp[tmpPos++] = myArray[rightPos++];
	}

	while(leftPos <= leftEnd) {   // Copy rest of first half
      temp[tmpPos++] = myArray[leftPos++];
   }

   while(rightPos <= rightEnd) {  // Copy rest of right half
      temp[tmpPos++] = myArray[rightPos++];
   }

   for(int i = 0; i < numElements; i++, rightEnd--) // Copy tmpArray back
      myArray[rightEnd] = temp[rightEnd];
}

// helper function used as part of mergesort
// does the recursive call and separates the list into smaller elements
template <class T, class Comparator>
void mergeSort (vector<T>& myArray, int l, int r, Comparator comp) {
	//cout << "called binSort with l = " << l << " and r = " << r << endl; // debug

	if (l < r) {
		int m = floor((l + r)/2); // defines the middle
		mergeSort(myArray, l, m, comp); // recursive sorts the left half
		mergeSort(myArray, (m + 1), r, comp); // recursive sorts the right half
		merge(myArray, l, (m + 1), r, comp); // merges the two sides
	}
}

// the merge function called by main
template <class T, class Comparator>
void mergeSort (vector<T>& myArray, Comparator comp) {
	mergeSort(myArray, 0, (myArray.size() - 1), comp);
}


