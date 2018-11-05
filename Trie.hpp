#ifndef __TRIE__
#define __TRIE__

#include <iostream>
#include "TrieNode.hpp"
#include "List.h"

template <class T>
class Trie {
	private:
		TrieNode<T> *root;
		List* str;
	public:
		Trie ();
		int insert(char*, T*);
		T* find(char*);
		void print();
		virtual ~Trie ();
};

template <class T>
Trie<T>::Trie () {
	root = new TrieNode<T>('\0');
}

template <class T>
int Trie<T>::insert(char* s, T* leaf_data) {
	int l = strlen(s);
	int i = 0;
	TrieNode<T> *cur = root, *node;
	//we check if the current character is in a child of the current node
	while (i < l) {
		node = cur->findChildNode(s[i]);
		if (node != NULL) { //if we found the character it means we'll look in the children of the node we found
			cur = node;
			i++;
		} else { //if no child was found we insert our character as the child of current node
			break;
		}
	}

	cur->insert(s, i, l, leaf_data);
	return 0;
}

template <class T>
T* Trie<T>::find(char* s) {
	int l = strlen(s);
	int i = 0;
	TrieNode<T> *cur = root, *node;
	for (i = 0; i < l; i++) { //for each of the word we are searching we check the children of current node
		node = cur->findChildNode(s[i]);
		if (node != NULL) { //if the current letter was found we move in the next
			cur = node;
		} else { //else it was not found
			return NULL;
		}
	}

	return cur->getLeafData();
}

template <class T>
void Trie<T>::print () {
	str = new List();
	if (root != NULL) {
		root->print(*str);
	}
	delete str;
}

template <class T>
Trie<T>::~Trie() {
	delete root;
}

#endif
