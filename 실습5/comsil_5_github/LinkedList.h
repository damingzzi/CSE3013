#ifndef __LINKEDLIST__
#define __LINKEDLIST__

#include <iostream>
using namespace std;

template <class T>
class Node {
public:
	T data;
	Node* link; //다음 node를 가리키는 pointer
	Node(T element) {
		data = element;
		link = 0;
	}
};

template <class T>
class LinkedList {
protected:
	Node<T>* first; //가장 마지막에 들어온 node를 first로 한다.
	int current_size;
public:
	LinkedList() { //생성자는 first와 current_size를 모두 0으로한다.
		first = 0;
		current_size = 0;
	};

	int GetSize() { return current_size; };

	void Insert(T element);

	virtual bool Delete(T& element);

	void Print();
};


template <class T>
void LinkedList<T>::Insert(T element) { 
	Node<T>* newnode = new Node<T>(element);

	newnode->link = first; //insert하면 first를 변경시켜준다.
	first = newnode;
	current_size++; //current_size를 증가시키는 것을 잊지말자.
}

template <class T>
bool LinkedList<T>::Delete(T& element) {

	if (first == 0)	return false;

	Node<T>* current = first;
	Node<T>* previous = 0;

	while (1) {
		if (current->link == 0) { //linked list에서 가장 첫번째로 들어온 요소를 삭제한다.
					//따라서 current가 가리키는 곳이 null pointer이도록 끝까지 탐색한다.
			if (previous)
				previous->link = current->link;
			else
				first = first->link;
			break;
		}
		previous = current;
		current = current->link;
	}
	element = current->data;
	delete current;
	current_size--;

	return true;
}

template <class T>
void LinkedList<T>::Print() {
	Node<T>* i;
	int index = 1;

	if (current_size != 0) {
		for (i = first; i != NULL; i = i->link) {
			if (index == current_size) {
				cout << "[" << index << "|";
				cout << i->data << "]";
			}

			else {
				cout << "[" << index << "|";
				cout << i->data << "]->";
				index++;
			}
		}
		cout << '\n';
	}
}


#endif

