/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  h43ye@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Winter 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

//#ifndef nullptr
//#define nullptr 0
//#endif

#include "Exception.h"
#include <iostream>

template <typename Type>
class Single_node {
public:
	Type       element;
	Single_node *next_node;

	Single_node(Type const &e = Type(), Single_node *n = 0);
	Type retrieve() const;
	Single_node *next() const;
};

template <typename Type>
class Sorted_single_list {
public:

	Sorted_single_list();
	~Sorted_single_list();

	// Accessors

	int size() const;
	bool empty() const;

	Type front() const;
	Type back() const;

	Single_node<Type> *head() const;
	Single_node<Type> *tail() const;

	int count(Type const &) const;

	// Mutators


	void insert(Type const &);

	Type pop_front();

	int erase(Type const &);

private:
	Single_node<Type> *list_head;
	Single_node<Type> *list_tail;
	int list_size;
};

template <typename Type>
Single_node<Type>::Single_node(Type const &e, Single_node<Type> *n) :
	element(e),
	next_node(n) {
	// empty constructor
}

template <typename Type>
Type Single_node<Type>::retrieve() const {
	return element;
}

template <typename Type>
Single_node<Type>* Single_node<Type>::next() const {
	return next_node;
}

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////
template <typename Type>
Sorted_single_list<Type>::Sorted_single_list() :
	list_head(nullptr),
	list_tail(nullptr),
	list_size(0) {
	// empty constructor
}



template <typename Type>
Sorted_single_list<Type>::~Sorted_single_list() {
	// enter your implementation here
	auto curr = list_head;
	while (curr) {
		auto prev = curr;
		curr = curr->next_node;
		delete prev;
	}
}

template <typename Type>
int Sorted_single_list<Type>::size() const {
	// enter your implementation here
	return list_size;
}

template <typename Type>
bool Sorted_single_list<Type>::empty() const {
	return list_size == 0;
}

template <typename Type>
Type Sorted_single_list<Type>::front() const {
	if (!list_head) {
		throw underflow();
	}
	return list_head->element;
}

template <typename Type>
Type Sorted_single_list<Type>::back() const {
	if (!list_tail) {
		throw underflow();
	}
	return list_tail->element;
}

template <typename Type>
Single_node<Type> *Sorted_single_list<Type>::head() const {
	return list_head;
}

template <typename Type>
Single_node<Type> *Sorted_single_list<Type>::tail() const {
	return list_tail;
}

template <typename Type>
int Sorted_single_list<Type>::count(Type const &obj) const {
	auto curr = list_head;
	int count = 0;
	while (curr) {
		if (curr->element == obj) {
			count++;
		}
		curr = curr->next_node;
	}
	return count;
}

template <typename Type>
void Sorted_single_list<Type>::insert(Type const &obj) {
	auto curr = list_head;
	Single_node<Type> *prev = nullptr;
	bool inserted = false;
	while (curr) {
		if (curr->element > obj) {
			Single_node<Type>* node = new Single_node<Type>(obj, curr);
			if (prev) {
				prev->next_node = node;
			}
			if (curr == list_head) {
				list_tail = list_head;
				list_head = node;
			}
			inserted = true;
			break;
		}
		prev = curr;
		curr = curr->next_node;
	}
	if (!inserted) {
		Single_node<Type>* node = new Single_node<Type>(obj, curr);
		if (list_tail) {
			list_tail->next_node = node;
			list_tail = list_tail->next_node;
		}
		else if (!list_head) {
			list_head = node;
		}
		else {
			list_tail = node;
		}
	}
	list_size++;
}

template <typename Type>
Type Sorted_single_list<Type>::pop_front() {
	if (!list_head) {
		throw underflow();
	}
	auto next = list_head->next_node;
	Type obj = list_head->element;
	delete list_head;
	list_head = next;
	std::cout << list_head << std::endl;
	return obj;
}

template <typename Type>
int Sorted_single_list<Type>::erase(Type const &obj) {
	auto curr = list_head;
	Single_node<Type> *prev = nullptr;
	int counter = 0;
	while (curr) {
		if (curr->element == obj) {
			if (curr == list_head) {
				list_head = list_head->next_node;
				delete curr;
				curr = list_head;
			}
			else if (curr == list_tail) {
				list_tail = prev;
				delete curr;
			}
			else {
				prev->next_node = curr->next_node;
				delete curr;
				curr = prev->next_node;
			}
			counter++;
		}
		prev = curr;
		curr = curr->next_node;
	}
	list_size -= counter;
	return counter;
}


#endif