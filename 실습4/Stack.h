#include "LinkedList.h"

template <class T>
class Stack : public LinkedList<T> {
public:
	bool Delete(T& element) {
		if (this->first == NULL) {
			return false; 
		}

		Node<T>* temp = this->first; 
		this->first = this->first->link;
		delete temp;
		this->current_size--;

		return true;
	}
};
