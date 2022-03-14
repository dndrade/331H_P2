#include "Stack.h"

template <class T>
Stack<T>::Stack() {

}

template <class T>
Stack<T>::Stack(const Stack<T>& other) {
	copy(other);
}
template <class T>
Stack<T>::~Stack() {
}

template <class T>
void Stack<T>::push(T item) {
	items.push_back(item);
}
template <class T>
void Stack<T>::pop() {
	if (isEmpty()) {
		std::cout << "\nStack Underflow."; // list is empty
	}
	else {
		items.pop_back(); // remove top element
	}
}

template <class T>
T Stack<T>::Top() {
	if (isEmpty()) {
		std::cout << "\nStack Underflow."; // list is empty
		return NULL;
	}
	return items.back(); // should change it to return
}

template <class T>
void Stack<T>::copy(const Stack<T>& other) {
	//items.reserve(other.items.size());
	/*for (std::size_t i = 0; i < other.size(); i++) {
		items.push_back(new Stack<T>(*other.[i]));
	}*/
}

template <class T>
const Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
	copy();
}


template <class T>
bool Stack<T>::isEmpty() {
	return items.size() == -1;
}

template <class T>
void Stack<T>::print() {
	for (int i : items) {
		std::cout << i << "\n";
	}
}

template <class T>
int Stack<T>::size() {
	return items.size();
}