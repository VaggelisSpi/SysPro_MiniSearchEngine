#include <iostream>
#include <cstdlib>
#include <cstring>
#include "PostingList.h"

//-------------POSTING LIST NODE-------------------------//
PostListNode::PostListNode () {
	next = NULL;
}

PostListNode::PostListNode (int id, int frq) {
	this->id = id;
	this->frq = frq;
	next = NULL;
}

PostListNode* PostListNode::getNext() { return next; }

int PostListNode::getId() { return id; }

int PostListNode::getFrq() { return frq; }

void PostListNode::setFrq(int n) {
	frq = n;
}

void PostListNode::incFrq() { frq++; }

void PostListNode::setNext(PostListNode* n) { next = n; }

PostListNode::~PostListNode () {}



//-------------POSTING LIST-------------------------//
PostingList::PostingList (): list(NULL), cur(NULL), df(0), size(0)  {}

PostListNode* PostingList::findId(int id) {
	PostListNode* cur = list;
	while (cur != NULL) {
		if (id == cur->getId()) {
			return cur;
		} else {
			cur = cur->getNext();
		}
	}
	return cur;
}

int PostingList::insert(int id, int frq) {
	PostListNode* new_node;
	if (list == NULL) {
		list = new PostListNode(id, frq);
		cur = list;
	} else {
		new_node = new PostListNode(id, frq);
		new_node->setNext(list);
		list = new_node;
	}
	df++;
	return 0;
}

int PostingList::getDF() { return df; }

//it's used to increase the frequency of a word in the last doc it was found
int PostingList::add(int x) {
	if (list != NULL) {
		list->setFrq(list->getFrq() + x);
		return 0;
	}
	return 1;
}

int PostingList::getLastId() {
	if (list != NULL)
		return list->getId();
	return -1;
}

int PostingList::getLastFrq() {
	if (list != NULL)
		return list->getFrq();
	return -1;
}

int PostingList::getFrq(int id) {
	PostListNode* cur = list;
	while (cur != NULL) {
		if (cur->getId() == id)
			return cur->getFrq();
		cur = cur->getNext();
	}
	return 0;
}

int PostingList::setLastFrq(int frq) {
	if (list != NULL) {
		list->setFrq(frq);
		return 1;
	}
	return -1;
}

int PostingList::incLastFrq() {
	if (list != NULL) {
		list->incFrq();
		return 1;
	}
	return -1;
}

void PostingList::print() {
	std::cout << " " << df << '\n';
}

void PostingList::first() { cur = list; }

bool PostingList::hasNext() {
	if (cur != NULL) return true;
	return false;
}

void PostingList::goToNext() {
	if (cur != NULL)
		cur = cur->getNext();
}

int PostingList::getCurDoc() {
	if (cur != NULL)
		return cur->getId();
	return -1;
}

int PostingList::getCurFrq() {
	if (cur != NULL)
		return cur->getFrq();
	return -1;
}


PostingList::~PostingList () {
	PostListNode* cur, *next;
	cur = list;
	while (cur != NULL) {
		next = cur->getNext();
		delete cur;
		cur = next;
	}
}
