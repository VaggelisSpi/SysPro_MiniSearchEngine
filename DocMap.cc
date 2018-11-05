#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "DocMap.h"
#include <fstream>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

DocMap::DocMap (int size): size(size), cur_add(0) {
	this->map = new char*[size];
	this->words = new int[size];
}

char* DocMap::getDoc(int i) {
	if (i < 0 || i >= size)
		return NULL;
	else {
		return map[i];
	}
}

int DocMap::getSize() { return size; }

int DocMap::getWords(int i) {
	if (i < 0 || i >= size)
		return -1;
	else {
		return words[i];
	}

}

int DocMap::insert(char* s, int w) {
	int l;
	if (cur_add < size) {
		l = strlen(s);
		map[cur_add] = new char[l + 1];
		strncpy(map[cur_add], s, l);
		strncpy(map[cur_add] + l, "\0", 1);
		words[cur_add] = w;
		cur_add++;
		return 0;
	} //else for realoc if full map
	return -1;
}

void DocMap::print(int doc_ind, char *words[], int wc, float score) {
	char* doc = map[doc_ind];
	struct winsize ws;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws );

	int i, clm, k, l, width, cur_doc_l, s, tok_start, sub_l, beg, tok_l, spaces, spcs, std_spcs = 20;
	char *cur_doc, *cur_str, *sub_str, *tok_str;
	bool first, first_line = true;

	l = strlen(doc);
	k = 0;  //k points to where we are left at doc so far
	cur_doc = doc;
	int doc_start = 0;
	while(k < l) {
		//cur_doc will be what remains from doc
		cur_doc = new char[l - k + 1];
		strncpy(cur_doc, &doc[k], l - k);
		strncpy(&cur_doc[l - k], "\0", 1);
		width = std_spcs; //standar spaces below the scores and the ids etc
		for(k = doc_start; k < l; k++) {  //from the current position of doc unitl its end check the width
			if (doc[k] == '\t') {   //if a tab is found we need to move in the next tab stop
				width += 8 - clm%8;
			} else
				width++;  //if no tab is found we move only one position
			if (width >= ws.ws_col) {  //if we moved past the end of the terminal width we need to split doc into multiple lines
				k -= 8; //in order to avoid spliting in tabs and messing up the print format we will move k 8 positions back
				while (!isspace(doc[k])) {  //if we split in the middle of a word we will move the whole word below
					k--;
				}
				delete[] cur_doc;
				cur_doc = new char[k - doc_start + 1];  //cur_doc will hold only the part of the doc that fits in a whole line
				strncpy(cur_doc, &doc[doc_start], k - doc_start);
				strncpy(&cur_doc[k - doc_start], "\0", 1);
				doc_start = k;
				break;
			}
		}
		if (first_line == true) {  //if we are in the first line we print the numbers
			printf("(%4d) [%10.5f] %s\n", doc_ind, score, cur_doc);
			first_line = false;
		} else {  //else only spaces and then the doc
			for (i = 0; i < std_spcs - 1; i++) {
				std::cout << " ";
				clm++;
			}
			std::cout << " " << cur_doc << '\n';
		}
		//print the spaces below the numbers in the begining
		clm = 0;
		for (i = 0; i < std_spcs; i++) {
			std::cout << " ";
			clm++;
		}

		beg = 0; //beg indicates from where we will start to print spaces
		tok_l = -1; //tok_l indicates how many ^ we'll write
		cur_str = cur_doc; //cur_str is a string from the start of the remaining doc unitl the end of the doc
		cur_doc_l = strlen(cur_doc);
		s = 0;
		tok_start = cur_doc_l; //tok_start shows from where we will satrt to print ^, if no word will be found we will write spaces below all the text
		while (cur_str != NULL) {  //while we have more to print
			first = true;
			tok_str = NULL;
			for (i = 0; i < wc; i++) {  //find first appearence of each word
				sub_str = strstr(cur_str, words[i]);
				if (sub_str != NULL) {    //if a word was found sub_str points to the beginning of the word
					sub_l = strlen(sub_str);
					//if before or after the sub_str there is no space or tab we didn't find the word since it's part of anotehr word
					if (sub_l == cur_doc_l) {
						if ( !isspace(sub_str[strlen(words[i])]))
							continue;
					} else if (sub_str[strlen(words[i])] == '\0') {
						if (!isspace(sub_str[-1]) )
							continue;
					} else {
						if ( !isspace(sub_str[strlen(words[i])]) || !isspace(sub_str[-1]) )  //if after thw subst there is no space or tab we didn't find the word
							continue;
					}
					if (first == true) {   //if it's the first word we found then token will start at the point the word starts
						tok_start = cur_doc_l - sub_l;
						tok_str = sub_str;
						tok_l = strlen(words[i]);
						first = false;
					} else { //otherwise we check if it's before the first word
						if (cur_doc_l - sub_l < tok_start) {
							tok_start = cur_doc_l - sub_l;
							tok_str = sub_str;
							tok_l = strlen(words[i]);
						}
					}
				}
			}
			spaces = tok_start - beg;
			for (i = 0; i < spaces; i++) {
				if (cur_doc[beg + i] == '\t') { //if we find a tab we need to print spaces until the next tab stop
					spcs = clm%8;
					for (int j = 0; j < 8 - spcs; j++) {
						std::cout << " ";
						s++;
						clm++;
					}
					continue;
				}
				std::cout << " ";
				s++;
				clm++;
			}
			for (i = 0; i < tok_l; i++) {
				std::cout << "^";
				s++;
				clm++;
			}
			if (tok_str == NULL) {
				break;
			}
			if (tok_start + tok_l > cur_doc_l)  //if the word is in the end of the doc there is nothing more to print
				cur_str = NULL;
			else
				cur_str = &cur_doc[tok_start] + tok_l; //else check the rest
			beg = tok_start + tok_l;
			tok_start = cur_doc_l; //if we won't find any other word print only spaces
			tok_l = -1;   //tok_l is set to -1 so we won't print any ^ if no word will be found
		}

		for (i = s; i < cur_doc_l; i++) {  //print the rest spaces
			std::cout << " ";
		}
		std::cout << '\n';
		delete[] cur_doc;
	}
}

DocMap::~DocMap () {
	for (int i = 0; i < size; i++) {
		delete[] map[i];
	}
	delete[] map;
	delete [] words;
}
