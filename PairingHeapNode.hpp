#ifndef __PAIRING_HEAP_NODE__
#define __PAIRING_HEAP_NODE__

template <class C, class T>
class PairingHeapNode {
private:
	C cost;
	T elem;
	PairingHeapNode<C,T>* child;
	PairingHeapNode<C,T>* next;
public:
	PairingHeapNode();
	PairingHeapNode(C, T);
	T getElem();
	C getCost();
	PairingHeapNode<C,T>* getNext();
	PairingHeapNode<C,T>* getChild();
	void setNext(PairingHeapNode<C,T>*);
	void setChild(PairingHeapNode<C,T>*);
	void addChild(PairingHeapNode<C,T>*);
	virtual ~PairingHeapNode ();
};

template <class C, class T>
PairingHeapNode<C,T>::PairingHeapNode () {
	cost = NULL;
	elem = NULL;
	child = NULL;
	next = NULL;
}

template <class C, class T>
PairingHeapNode<C,T>::PairingHeapNode (C c, T t) {
	cost = c;
	elem = t;
	child = NULL;
	next = NULL;
}

template <class C, class T>
T PairingHeapNode<C,T>::getElem() { return elem; }

template <class C, class T>
C PairingHeapNode<C,T>::getCost() { return cost; }

template <class C, class T>
PairingHeapNode<C,T>* PairingHeapNode<C,T>::getNext() { return next; }

template <class C, class T>
PairingHeapNode<C,T>* PairingHeapNode<C,T>::getChild() {return child; }

template <class C, class T>
void PairingHeapNode<C,T>::setNext(PairingHeapNode<C,T>* n) { next = n;}

template <class C, class T>
void PairingHeapNode<C,T>::setChild(PairingHeapNode<C,T>* n) { child = n; }

template <class C, class T>
void PairingHeapNode<C,T>::addChild(PairingHeapNode<C,T>* node) {
	if (child == NULL)
		child = node;
	else {
		node->next = child;
		child = node;
	}
}

template <class C, class T>
PairingHeapNode<C,T>::~PairingHeapNode() {
	if (child != NULL)
		delete child;
	if (next != NULL)
		delete next;
}

#endif
