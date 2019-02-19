#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function
		int hash(T const &) const;

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	delete[] array;
	delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size;
}

template<typename T >
bool DoubleHashTable<T >::empty() const {
	return count == 0;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	int hash = static_cast<int>(obj) % array_size;
	if (hash < 0) hash += array_size;
	return hash;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	int hash = (static_cast<int>(obj) / array_size) % array_size;
	if (hash % 2 == 0) {
		hash++;
	}
	if (hash < 0) hash += array_size;
	return hash;
}

template<typename T >
bool DoubleHashTable<T >::member(T const &obj) const {
	return hash(obj) != -1;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
	return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	if (count == array_size) throw overflow();
	int offset = h2(obj);
	int index = h1(obj);
	while (array_state[index] == OCCUPIED) {
		index = (index + offset) % array_size;
	}
	array[index] = obj;
	array_state[index] = OCCUPIED;
	count++;
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	if (!member(obj)) return false;
	int index = hash(obj);
	array_state[index] = DELETED;
	count--;
	return true;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	for (int i = 0; i < array_size; i++) {
		array_state[i] = EMPTY;
	}
	count = 0;
}
    
//Print function won't be tested
template<typename T >
void DoubleHashTable<T >::print() const {
	for (int i = 0; i < array_size; i++) {
		if (array_state[i] == OCCUPIED) {
			std::cout << i << " " << array[i] << std::endl;
		}
	}
}

template<typename T >
int DoubleHashTable<T >::hash(T const &obj) const {
	int index = h1(obj);
	int offset = h2(obj);
	int counter = 0;
	while (array_state[index] != EMPTY && !(array[index] == obj && array_state[index] == OCCUPIED) && counter < array_size) {
		index = (index + offset) % array_size;
		counter++;
	}
	if (counter == array_size || array_state[index] == EMPTY) {
		return -1;
	}
	else {
		return index;
	}
}

#endif
