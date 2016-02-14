#include "../llistint.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

void output(LListInt &list) {
	for (int i = 0; i < list.size(); i++)
		cout << list[i] << " ";
	cout << endl;
}

int main() {
	cout << "main function" << endl;
	
	/*LListInt list1 = LListInt();
	list1.insert(0, 5);
	list1.insert(0, 4);
	list1.insert(0, 1);
	list1.insert(0, 2);
	list1.insert(0, 2);*/

	LListInt list2 = LListInt();
	list2.insert(0, 3);
	list2.insert(0, 1);

	LListInt list3 = LListInt();
	cout << "new LListInt" << endl;
	list3.insert(0, 3);
	list3.insert(0, 3);
	list3.insert(0, 3);

	//output(list2);

	//(list2) = (list1);

	//output(list2);

	(list2) = ((list2) + (list3));

	return 0;
}