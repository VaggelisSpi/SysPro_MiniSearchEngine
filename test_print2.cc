#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

//Spears seeks aborted tour payment  Singer Britney Spears is suing eight insurance companies that have refused to reimburse her for cancelling her 2004 world tour.

int main(int argc, char const *argv[]) {
	struct winsize ws;
	ioctl( STDOUT_FILENO, TIOCGWINSZ, &ws );

	int i, wc = 5, clm, k, l, width, cur_doc_l, s, tok_start, sub_l, beg, tok_l, spaces, spcs;
	char* doc, *words[5], *cur_doc, *cur_str, *sub_str, *tok_str;
	double score = 10.23456789;
	bool first, first_line = true;

	// doc = new char[22];
	// strncpy(doc, "abcde \t jkl ghi\tglk a\0", 22);
	doc = new char[500];
	// strncpy(doc, "Spears seeks aborted tour payment  \0", 269);
	strncpy(doc, "Spears seeks aborted tour payment  Singer Britney \t\t\tSpears is suing\t eight insurance companies eight that have refused to reimburse her for cancelling eight her 2004 world tour .\0", 500);

	words[0] = new char[7];
	strncpy(words[0], "Spears\0", 7);

	words[1] = new char[6];
	strncpy(words[1], "eight\0", 6);

	words[2] = new char[5];
	strncpy(words[2], "tour\0", 5);

	words[3] = new char[4];
	strncpy(words[3], "jkl\0", 4);

	words[4] = new char[6];
	strncpy(words[4], "seeks\0", 6);

	//START OF PRINTING
	l = strlen(doc);
	k = 0;
	cur_doc = doc;
	int doc_start = 0;
	while(k < l) {
		//cur_doc will be what remains from doc
		cur_doc = new char[l - k + 1];
		strncpy(cur_doc, &doc[k], l - k);
		strncpy(&cur_doc[l - k], "\0", 1);
		width = 24; //standar spaces below the scores and the ids etc
		for(k = doc_start; k < l; k++) {  //from the current position of doc unitl it's end check the width
			if (doc[k] == '\t') {   //if a tab is found we need to move in the next tab stop
				width += 8 - clm%8;
			} else
				width++;  //if no tab is found we move only one position
			if (width >= ws.ws_col) {  //if we moved past the end of the terminal width we need to split doc into multiple lines
				k -= 8; //in order to avoid spliting in tabs adnd messing up the print format we will move k8 positions back
				while (!isspace(doc[k])) {  //if we split in the middle of a word we will move the whole word below
					k--;
				}
				cur_doc = new char[k - doc_start + 1];  //cur_doc will hold only the part of the doc that fits in a whole line
				strncpy(cur_doc, &doc[doc_start], k - doc_start);
				strncpy(&cur_doc[k - doc_start], "\0", 1);
				doc_start = k;
				break;
			}
		}
		if (first_line == true) {  //if we are in the first line we print the numbers
			printf("%4d.(%4d)[%10.5f] %s\n", 0, 0, score, cur_doc);
			first_line = false;
		} else {  //else only spaces and then the doc
			for (i = 0; i < 23; i++) {
				std::cout << " ";
				clm++;
			}
			std::cout << " " << cur_doc << '\n';
		}
		//print the spaces below the numbers in the begining
		clm = 0;
		for (i = 0; i < 24; i++) {
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
					if (sub_l == cur_doc_l) {
						if ( !isspace(sub_str[strlen(words[i])])) //if after thw subst there is no space or tab we didn't find the word
							continue;
					} else if (sub_str[strlen(words[i])] == '\0') {
						if (!isspace(sub_str[-1]) )  //if after thw subst there is no space or tab we didn't find the word
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
	}

	delete[] doc;
	delete[] words[0];
	delete[] words[1];
	delete[] words[2];
	delete[] words[3];
	delete[] words[4];

	return 0;
}
