/*
Tester class for the linked list object.
Specifically, test Insert() and Remove() functions
*/

#include "../llistint.h"
#include <iostream>

using namespace std;

int main() {
  LListInt * list = new LListInt();

  // Check if the list is initially empty.
  if (list->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }

  // Remove an item from an empty list
  //list->remove(0);

  // Insert an item from invalid location
  //list->insert(-1, 1);
  //list->insert(3, 3);

  // Insert an item at the head.
  list->insert(0, 3);

  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after one insertion." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }


  // Insert an item from invalid location
  //list->insert(3, 3);

  // Insert an item to the end of an existing list
  list->insert(1, 2);
  list->insert(2, 1);

  if (list->size() == 3) {
    cout << "SUCCESS: List has size 3 after three insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after three insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Check if the value is correct.
  if (list->get(1) == 2) {
    cout << "SUCCESS: 2 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 2 is not at the 1st index of the list, " << list->get(2);
    cout << " is instead." << endl;
  }

  // Check if the value is correct.
  if (list->get(2) == 1) {
    cout << "SUCCESS: 1 is at the 2nd index of the list." << endl;
  } else {
    cout << "FAIL: 1 is not at the 2nd index of the list, " << list->get(2);
    cout << " is instead." << endl;
  }

  // Insert an item into middle of an existing list
  list->insert(1, 3);
  list->insert(0, 10);

  if (list->size() == 5) {
    cout << "SUCCESS: List has size 5 after five insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after five insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 10) {
    cout << "SUCCESS: 10 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 10 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Check if the value is correct.
  if (list->get(1) == 3) {
    cout << "SUCCESS: 3 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 1st index of the list, " << list->get(1);
    cout << " is instead." << endl;
  }

  // Check if the value is correct.
  if (list->get(2) == 3) {
    cout << "SUCCESS: 3 is at the 2nd index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 2nd index of the list, " << list->get(2);
    cout << " is instead." << endl;
  }


  // Remove item from invalid location
  //list->remove(-1);
  //list->remove(6);

  // Remove item from ends of the list
  list->remove(0);
  list->remove(3);

  if (list->size() == 3) {
    cout << "SUCCESS: List has size 3 after two removals." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after two removals.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3) {
    cout << "SUCCESS: 3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }

  // Check if the value is correct.
  if (list->get(2) == 2) {
    cout << "SUCCESS: 2 is at the 3rd index of the list." << endl;
  } else {
    cout << "FAIL: 2 is not at the 3rd index of the list, " << list->get(2);
    cout << " is instead." << endl;
  }

  // Remove item from middle of an array
  list->remove(1); 

  if (list->size() == 2) {
    cout << "SUCCESS: List has size 2 after three removals." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after three removals.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(1) == 2) {
    cout << "SUCCESS: 2 is at the 1st index of the list." << endl;
  } else {
    cout << "FAIL: 2 is not at the 1st index of the list, " << list->get(1);
    cout << " is instead." << endl;
  }  

  // Clean list
  list->clear();

  if (list->empty()) {
    cout << "SUCCESS: List is empty after clear()." << endl;
  } else {
    cout << "FAIL: List is not empty after clear() when it should be." << endl;
  }


  // Clean up memory.
  delete list;
}
