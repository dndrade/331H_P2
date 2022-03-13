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
void Stack<T>::Top(T&) {
	items.back();
}

template <class T>
void Stack<T>::copy(const Stack<T>&) {

}

template <class T>
const Stack<T>& Stack<T>::operator=(const Stack<T>& other) {

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