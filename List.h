#ifndef __LIST__
#define __LIST__

class ListNode {
private:
	char c;
	ListNode* next;
	ListNode* prev;
public:
	ListNode (char ch);
	char getChar();
	ListNode* getNext();
	ListNode* getPrev();
	void setNext(ListNode* n);
	void setPrev(ListNode* n);
	virtual ~ListNode ();
};

class List {
private:
	ListNode* first;
	ListNode* last;
public:
	List ();
	void insert(char c);
	void print();
	void removeLast();
	virtual ~List ();
};

#endif
