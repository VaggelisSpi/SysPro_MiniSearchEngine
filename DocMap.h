#ifndef __DOC_MAP__
#define __DOC_MAP__

class DocMap {
	private:
		int size;
		char** map;
		int* words;
		int cur_add;
	public:
		DocMap (int);
		char* getDoc(int);
		int getSize();
		int getWords(int);
		int insert(char*, int);
		void print(int, char *words[], int, float);
		virtual ~DocMap ();
};

#endif
