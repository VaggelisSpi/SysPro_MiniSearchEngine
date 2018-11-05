#ifndef __PAIRING_HEAP__
#define __PAIRING_HEAP__

#include "PairingHeapNode.hpp"

template <class C, class T>
class PairingHeap {
private:
	PairingHeapNode<C,T>* root;
	PairingHeapNode<C,T>* mergePairs(PairingHeapNode<C,T>*);
public:
	PairingHeap();
	PairingHeap(C, T);
	PairingHeap(PairingHeapNode<C,T>*);
	bool empty();
	T top();
	C topCost();
	void pop();
	void insert(C, T);
	void merge(PairingHeap*);
	virtual ~PairingHeap ();
};

template <class C, class T>
PairingHeap<C,T>::PairingHeap() {
	root = NULL;
}

template <class C, class T>
PairingHeap<C,T>::PairingHeap(C c, T t) {
	root = new PairingHeapNode<C,T>(c, t);
}

template <class C, class T>
PairingHeap<C,T>::PairingHeap(PairingHeapNode<C,T>* n) {
	root = n;
}

template <class C, class T>
bool PairingHeap<C,T>::empty() {
	if (root == NULL)
		return true;
	return false;
}

template <class C, class T>
T PairingHeap<C,T>::top() {
	return root->getElem();
}

template <class C, class T>
C PairingHeap<C,T>::topCost() { return root->getCost(); }


template <class C, class T>
//Merge pairs is used to merge each node with its next and then merge that new heap with the result of
//merge pairs for the rest of the next nodes. It is used in order to to keep the heap ordred after we pop
//an element
PairingHeapNode<C,T>* PairingHeap<C,T>::mergePairs(PairingHeapNode<C,T>* node) {
	if (node == NULL || node->getNext() == NULL)
		return node;
	else {
		PairingHeapNode<C,T>* ret;
		PairingHeap<C,T> *A, *B, *newNode;
		A = new PairingHeap<C,T>(node);
		B = new PairingHeap<C,T>(node->getNext());
		newNode = new PairingHeap<C,T>(node->getNext()->getNext());

		A->root->setNext(NULL);
		B->root->setNext(NULL);

		A->merge(B);
		A->merge(new PairingHeap<C,T>(mergePairs(newNode->root)));

		ret = A->root;
		A->root = NULL;
		newNode->root = NULL;
		delete A;
		delete newNode;
		return ret;
	}
}

template <class C, class T>
void PairingHeap<C,T>::pop() {
	if (root == NULL) return;
	else {
		PairingHeapNode<C,T>* old_root = root;
		root = mergePairs(root->getChild());  //we will merge each pair of root's children and
			//then merge the results together and so on, so forth since a whole heap would be constructed
		old_root->setNext(NULL);
		old_root->setChild(NULL);
		delete old_root;
	}
}

template <class C, class T>
void PairingHeap<C,T>::insert(C c, T t) {
	merge(new PairingHeap<C,T>(c,t));
}

template <class C, class T>
//Merges 2 heaps
//in case one of the heaps is emtpy we keep the non empty one as the new heap
//if both have elements then the one with the root with lower cost will be the new root
//and the other one will become its child
void PairingHeap<C,T>::merge(PairingHeap<C,T>* heap2) {
	PairingHeapNode<C,T>* A = root, *B = heap2->root;
	if (empty()) {
		root = B;
		heap2->root = NULL;
		delete heap2;
	} else if (heap2->empty()) {
		delete heap2;
		return;
	} else if (A->getCost() > B->getCost()) {
		heap2->root = NULL;
		delete heap2;
		A->addChild(B);
	} else if (A->getCost() < B->getCost()){
		heap2->root = NULL;
		delete heap2;
		B->addChild(A);
		root = B;
	} else {
		//if both root costs are equal then we order them by their elemnt value
		T elem = heap2->top();
		heap2->root = NULL;
		delete heap2;
		if (elem > root->getElem()) {
			B->addChild(A);
			root = B;
		} else {
			A->addChild(B);
		}
	}
}

template <class C, class T>
PairingHeap<C,T>::~PairingHeap() {
	if (root != NULL)
		delete root;
}

#endif
