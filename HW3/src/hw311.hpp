//  hw311.hpp

#ifndef CS263_PROB_3_11
#define CS263_PROB_3_11
#include <iostream>
#include "gvsu_alloc.hpp"

namespace gvsu {
/* don't write any code above this line */
using namespace std;

template<class E>
class LinkedList {
	static GVSU_Allocator<E>* node_alloc;

	/* DO NOT EDIT the Node class below */
	class Node { /* inner class of Linked List */
	private:
	public:
		E data; /* store the data item */
		Node* next; /* pointer to the next node */

		/* override new and delete to use our own allocator */
		void* operator new(size_t s) {
			return node_alloc->allocate(s);
		}
		void operator delete(void * ptr) {
			node_alloc->deallocate(static_cast<E*>(ptr));
		}
	};

private:
	/* We know that the design choice used by this class is NOT EFFICIENT,
	 * but you are NOT ALLOWED to add any other instance variable besides
	 * the head pointer below in your attempt make the design more efficient.
	 */
	Node *head; /* pointer to the first element */

	/* You may add PRIVATE HELPER FUNCTIONS */

public:

	LinkedList();
	~LinkedList();
	int size() const;  // part (a) return the size of the linked list
	void print(ostream&) const;  // part (b) print the linked list
	bool contains(const E& value) const; // part (c) test if the item is in the list
	bool add(const E& value); // part (d)
	bool remove(const E& value); // part (e) remove a value

	void print_reverse(ostream&);  // prob 3.29
};

template<class E>
LinkedList<E>::LinkedList() {
	head = nullptr;
}

template<class E>
LinkedList<E>::~LinkedList() {
	/* TODO: complete this function */
}

/*
 3.11 (a) return the size of the linked list
 */
template<class E>
int LinkedList<E>::size() const {
	/* TODO: complete this function */
	return 0;
}

/*
 3.11 (b) print the linked list
 */
template<class E>
void LinkedList<E>::print(ostream& output) const {
	/* TODO: complete this function */
}

/*
 3.11 (c) test if a value is contained in the linked list
 */
template<class E>
bool LinkedList<E>::contains(const E &value) const {
	/* TODO: complete this function */
	return false;
}

/* 3.11 (d) insert new_data at the end of the list (if it is not already
 in the list). Return true if the item is inserted, false otherwise */
template<class E>
bool LinkedList<E>::add(const E& value) {
	/* TODO: complete this function */
	return false;
}

/* 3.11 (d) insert new_data at the end of the list (if it is not already
 in the list). Return true if the item is inserted, false otherwise */
template<class E>
bool LinkedList<E>::remove(const E& value) {
	/* TODO: complete this function */
	return false;
}

/*
 3.11 (b) print the linked list
 */
template<class E>
ostream& operator<<(ostream& os, const LinkedList<E>& theList) {
	/* TODO: complete this function. Hint: just need one line of code */
	return os;
}

/* Prob 3.29: print the list in reverse, using only O(1) extra space */
template<class E>
void LinkedList<E>::print_reverse(ostream &os) {
	/* TODO: complete this function */
	//Make a recursive helper function?
}

} /* end of namespace, don't write any code below this line */
#endif