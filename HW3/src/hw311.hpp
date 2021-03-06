//  hw311.hpp

#ifndef CS263_PROB_3_11
#define CS263_PROB_3_11
#include <iostream>
#include "gvsu_alloc.hpp"

namespace gvsu {
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
	Node* reverse(Node* temp);
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
	if (head != nullptr) {
		Node* prev;
		Node* current = head;
		while (current != nullptr) {
			prev = current;
			current = current->next;
			delete prev;
		}
	}
}

/*
 3.11 (a) return the size of the linked list
 */
template<class E>
int LinkedList<E>::size() const {
	int sum = 0;
	if (head != nullptr) {
		Node* next = head;
		while (next != nullptr) {
			sum++;
			next = next->next;
		}
	}
	return sum;
}

/*
 3.11 (b) print the linked list
 */
template<class E>
void LinkedList<E>::print(ostream& output) const {
	if (head != nullptr) {
		Node* next = head;
		while (next != nullptr) {
			output << next->data << endl;
			next = next->next;
		}
	}
}

/*
 3.11 (c) test if a value is contained in the linked list
 */
template<class E>
bool LinkedList<E>::contains(const E &value) const {
	if (head != nullptr) {
		Node* next = head;
		while (next != nullptr) {
			if (next->data == value)
				return true;
			next = next->next;
		}
	}
	return false;
}

/* 3.11 (d) insert new_data at the end of the list (if it is not already
 in the list). Return true if the item is inserted, false otherwise */
template<class E>
bool LinkedList<E>::add(const E& value) {
	if (!contains(value)) {
		Node* insert = new Node();
		insert->data = value;
		insert->next = nullptr;
		Node* next;
		Node* prev;
		next = head;
		while (next != nullptr) {
			prev = next;
			next = next->next;
		}
		if (head != nullptr)
			prev->next = insert;
		else
			head = insert;
		return true;
	} else
		return false;
}

/* 3.11 (d) insert new_data at the end of the list (if it is not already
 in the list). Return true if the item is inserted, false otherwise */
template<class E>
bool LinkedList<E>::remove(const E& value) {
	/* TODO: complete this function */
	if (head != nullptr) {
		Node* next = head;
		Node* prev;
		Node* end;
		while (next != nullptr) {
			if (next->data == value) {
				end = next->next;
				if (end != nullptr)
					prev->next = end;
				else
					prev->next = nullptr;
				if (next == head)
					head = end;
				delete next;
				return true;
			}
			prev = next;
			next = next->next;
		}
	}
	return false;
}

/*
 3.11 (b) print the linked list
 */
template<class E>
ostream& operator<<(ostream& os, const LinkedList<E>& theList) {
	theList.print(os);
	return os;
}

template<class E>
typename LinkedList<E>::Node* LinkedList<E>::reverse(Node* temp) {
	Node* next;
	Node* prev = nullptr;
	Node* current = temp;
	while (current != nullptr) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return prev;
}

/* Prob 3.29: print the list in reverse, using only O(1) extra memory space */
template<class E>
void LinkedList<E>::print_reverse(ostream &os) {
	/* TODO: complete this function */
	if (head != nullptr) {
		head = this->reverse(head);
		this->print(os);
		head = this->reverse(head);
	}
}

}
#endif
