#ifndef __TRIE_HEAP_NODE__
#define __TRIE_HEAP_NODE__

#include <iostream>
#include "List.h"

template <class T>
class TrieNode {
	private:
		TrieNode<T> *child;
		TrieNode<T> *next;
		T* leaf_data;
		char data;
	public:
		TrieNode ();
		TrieNode (char);
		int insert(char*, T*);
		int insert(char*, int, int, T*);
		T* find(char*);
		TrieNode<T>* findChildNode(char);
		char getChar();
		T* getLeafData();
		TrieNode<T> *getNext();
		TrieNode<T> *getChild();
		void print();
		void print (List& str);
		virtual ~TrieNode ();
};

template <class T>
TrieNode<T>::TrieNode () {
	child = NULL;
	next = NULL;
	leaf_data = NULL;
}

template <class T>
TrieNode<T>::TrieNode (char c) {
	child = NULL;
	next = NULL;
	leaf_data = NULL;
	data = c;
}

template <class T>
int TrieNode<T>::insert(char* s, T* leaf_data) {
	TrieNode<T>* cur = child, *new_node, *prev = NULL;
	char* s2;
	int l = strlen(s);
	if (l == 0) { //if no more to insert then the
		this->leaf_data = leaf_data;
	} else {
		while (cur != NULL && s[0] > cur->getChar()) { //find the proper position in its children
			prev = cur;
			cur = cur->next;
		}
		new_node = new TrieNode<T>(s[0]);
		new_node->next = cur;
		if (prev != NULL) {
			prev->next = new_node;
		} else { //if new node would be at the beginning we change the child pointer
			child = new_node;
		}
		s2 = new char[l];
		strncpy(s2, &(s[1]), l);
		new_node->insert(s2, leaf_data); //insert the rest of the string in the children of the new node
	}
	return 0;
}

template <class T>
int TrieNode<T>::insert(char* s, int ind, int l, T* leaf_data) {
	TrieNode<T>* cur = child, *new_node, *prev = NULL;
	if (ind == l) {  //if no more of the word remains then we add the leaf
		this->leaf_data = leaf_data;
	} else {
		while (cur != NULL && s[ind] > cur->getChar()) { //find the proper position in its children
			prev = cur;
			cur = cur->next;
		}
		new_node = new TrieNode<T>(s[ind]);
		new_node->next = cur;
		if (prev != NULL) {
			prev->next = new_node;
		} else { //if new node would be at the beginning we change the child pointer
			child = new_node;
		}
		new_node->insert(s, ind+1, l, leaf_data); //insert the rest of the string in the children of the new node
	}
	return 0;
}

template <typename T>
TrieNode<T>* TrieNode<T>::findChildNode(char c) {
	TrieNode<T>* cur = child;
	if (child == NULL) return NULL;
	//check if c is in one of its children
	while (cur != NULL) {
		if (c == cur->getChar()) {
			return cur;
		} else {
			cur = cur->getNext();
		}
	}
	return NULL;
}

template <class T>
char TrieNode<T>::getChar() { return data; }

template <class T>
T* TrieNode<T>::getLeafData() { return leaf_data; }


template <class T>
TrieNode<T>* TrieNode<T>::getNext() { return next; }

template <class T>
TrieNode<T>* TrieNode<T>::getChild() { return child; }

template <class T>
void TrieNode<T>::print () {
	if (leaf_data != NULL)
		leaf_data->print();
	if (child != NULL)
		child->print();
	if (next != NULL)
		next->print();
}

template <class T>
void TrieNode<T>::print (List& str) {
	if (data != '\0')
		str.insert(data);
	if (leaf_data != NULL) {
		str.print();
		leaf_data->print();
	}
	if (child != NULL) {
		child->print(str);
		str.removeLast();
	}
	if (next != NULL) {
		str.removeLast();
		next->print(str);
	}
}

template <class T>
TrieNode<T>::~TrieNode () {
	if (leaf_data != NULL) {
		delete leaf_data;
		leaf_data = NULL;
	}
	if (child != NULL)
		delete child;
	if (next != NULL)
		delete next;
}

#endif
