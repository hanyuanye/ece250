/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
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

#ifndef DYNAMIC_STACK_AS_ARRAY_H
#define DYNAMIC_STACK_AS_ARRAY_H

#ifndef nullptr
#define nullptr 0
#endif

#include <algorithm>
#include "Exception.h"

class Dynamic_range_stack {
private:
	int entry_count;
	int max_count;
	int min_count;
	int initial_capacity;
	int current_capacity;

	int *stack_array;
	int *maximum_array;
	int *minimum_array;

	// You may wish to include a number of helper functions
	// in order to abstract out some operations

	void increaseCapacity();


public:
	Dynamic_range_stack(int = 10);
	~Dynamic_range_stack();

	int top() const;
	int size() const;
	bool empty() const;
	int capacity() const;

	int maximum() const;
	int minimum() const;


	void push(int const &);
	int pop();
	void clear();


	// Friends

	friend std::ostream &operator<<(std::ostream &, Dynamic_range_stack const &);
};

Dynamic_range_stack::Dynamic_range_stack(int n) :
	entry_count(0),
	min_count(0),
	max_count(0),
	initial_capacity(std::max(1, n)),
	current_capacity(initial_capacity),
	stack_array(new int[current_capacity]),
	maximum_array(new int[current_capacity]),
	minimum_array(new int[current_capacity]) {
	// empty constructor
}

Dynamic_range_stack::~Dynamic_range_stack() {
	delete[]stack_array;
	delete[]minimum_array;
	delete[]maximum_array;

}

int Dynamic_range_stack::top() const {
	if (entry_count == 0) throw underflow();
	return stack_array[entry_count - 1];
}

int Dynamic_range_stack::maximum() const {
	if (max_count == 0) throw underflow();
	return maximum_array[max_count - 1];
}

int Dynamic_range_stack::minimum() const {
	if (min_count == 0) throw underflow();
	return minimum_array[min_count - 1];
}

int Dynamic_range_stack::size() const {
	return entry_count;
}

bool Dynamic_range_stack::empty() const {
	return entry_count == 0;
}

int Dynamic_range_stack::capacity() const {
	return current_capacity;
}



void Dynamic_range_stack::push(int const &obj) {
	if (entry_count == current_capacity) {
		increaseCapacity();
	}

	if (max_count == 0 || obj >= maximum()) {
		maximum_array[max_count] = obj;
		max_count++;
	}

	if (min_count == 0 || obj <=	 minimum()) {
		minimum_array[min_count] = obj;
		min_count++;
	}

	stack_array[entry_count] = obj;
	entry_count++;
}

int Dynamic_range_stack::pop() {
	auto topEntry = top();
	if (maximum_array[max_count - 1] == topEntry) {
		maximum_array[max_count - 1] == 0;
		max_count--;
	}

	if (minimum_array[min_count - 1] == topEntry) {
		minimum_array[min_count - 1] == 0;
		min_count--;
	}
	stack_array[entry_count] = 0;
	entry_count--;
	return topEntry;
}

void Dynamic_range_stack::clear() {
	delete []stack_array;
	delete []maximum_array;
	delete []minimum_array;
	stack_array = new int[initial_capacity];
	maximum_array = new int[initial_capacity];
	minimum_array = new int[initial_capacity];
	entry_count = 0;
	max_count = 0;
	min_count = 0;
}

void Dynamic_range_stack::increaseCapacity() {
	current_capacity = current_capacity * 2;

	int *new_stack_array = new int[current_capacity];
	for (int i = 0; i < entry_count; i++) {
		new_stack_array[i] = stack_array[i];
	}
	delete []stack_array;
	stack_array = new_stack_array;

	int *new_max_array = new int[current_capacity];
	for (int i = 0; i < max_count; i++) {
		new_max_array[i] = maximum_array[i];
	}
	delete []maximum_array;
	maximum_array = new_max_array;

	int *new_min_array = new int[current_capacity];
	for (int i = 0; i < min_count; i++) {
		new_min_array[i] = minimum_array[i];
	}
	delete []minimum_array;
	minimum_array = new_min_array;
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<(std::ostream &out, Dynamic_range_stack const &stack) {
	// Print out your stacks

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif