#include <stdio.h>
#include "Stack.h"

void prnMenu() {
	cout << "*******************************************\n";
	cout << "* 1. Insert    2. Delete    3. Print   4. Exit *\n";
	cout << "*******************************************\n";
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
			cout << tmpItem << " is inserted.\n";
			break;

		case 2:
			if (p->Delete(tmpItem) == true)
				cout << tmpItem << " is deleted.\n";

			else cout << "Data is empty\n";
			break;

		case 3:
			cout << "Size of data: " << p->GetSize() << '\n';
			p->Print();
			break;

		case 4:
			flag = true;     break;

		default:
			cout << "Error: Input is not correct.\n";
			break;

		}

		if (flag) break;

	} while (1);

	return 0;
}

