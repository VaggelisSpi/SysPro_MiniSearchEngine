#ifndef __POSTING_LIST__
#define __POSTING_LIST__ value

class PostListNode {
private:
	int id;
	int frq;
	PostListNode* next;
public:
	PostListNode ();
	PostListNode (int, int);
	int getId();
	int getFrq();
	void setFrq(int);
	void incFrq();
	PostListNode* getNext();
	void setNext(PostListNode*);
	virtual ~PostListNode ();
};

class PostingList {
private:
	PostListNode* list;
	PostListNode* cur;
	long df;
	int size;
public:
	PostingList ();
	PostListNode* findId(int);
	int insert(int, int);
	int getDF();
	int add(int);
	int getLastId();
	int getLastFrq();
	int getFrq(int);
	int setLastFrq(int);
	int incLastFrq();
	void first();
	bool hasNext();
	void goToNext();
	int getCurDoc();
	int getCurFrq();
	void print();
	virtual ~PostingList ();
};

#endif
