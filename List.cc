#include <cstdlib>
#include "List.h"
#include <iostream>

ListNode::ListNode (char ch): c(ch), next(NULL), prev(NULL) {}

char ListNode::getChar() { return c; }

ListNode* ListNode::getNext() { return next; }

ListNode* ListNode::getPrev() { return prev; }

void ListNode::setNext(ListNode* n) { next = n; }

void ListNode::setPrev(ListNode* n) { prev = n; }

ListNode::~ListNode () { if (next != NULL) delete next; }


List::List (): first(NULL), last(NULL) {}

void List::insert(char c) {
	if (first == NULL) {
		ListNode* n = new ListNode(c);
		first = n;
		last = n;
		n->setNext(NULL);
		n->setPrev(NULL);
	} else {
		ListNode* n = new ListNode(c);
		n->setPrev(last);
		last->setNext(n);
		last = n;
	}
}

void List::print() {
	ListNode* cur = first;
	while (cur != NULL) {
		std::cout << cur->getChar();
		cur = cur->getNext();
	}
}

void List::removeLast() {
	if (last != NULL) {
		ListNode* cur = last;
		if (last == first) {
			first = NULL;
		} else
			cur->getPrev()->setNext(NULL);
		last = last->getPrev();
		delete cur;
	}
}

List::~List () {
	if (first != NULL)
		delete first;
}
