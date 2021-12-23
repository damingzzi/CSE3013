#include <stdio.h>
#include "Stack.h"

void prnMenu() {
	cout << "*******************************************" << endl;
	cout << "* 1. Insert    2. Delete    3. Print   4. Exit *" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
	cout << "Choose menu: ";
}

int main() {
	int mode, selectNumber, tmpItem;
	LinkedList<int>* p;
	bool flag = false;

	cout << "Choose Data Structure(1: Stack, Other: Linked List): ";
	cin >> mode;

	if (mode == 1)
		p = new Stack<int>();    //Stack for integer
	else
		p = new LinkedList<int>();

	do {
		prnMenu();
		cin >> selectNumber;

		switch (selectNumber) {
		case 1:
			cout << "Enter an Integer to insert: ";
			cin >> tmpItem;    p->Insert(tmpItem);
			cout << tmpItem << " is inserted." << endl;
			break;

		case 2:
			if (p->Delete(tmpItem) == true)
				cout << tmpItem << " is deleted." << endl;

			else cout << "Data is empty" << endl;
			break;

		case 3:
			cout << "Size of data: " << p->GetSize() << endl;
			p->Print();
			break;

		case 4:
			flag = true;     break;

		default:
			cout << "Error: Input is not correct." << endl;
			break;

		}

		if (flag) break;

	} while (1);

	return 0;
}

