 #include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "DocMap.h"
#include <fstream>
#include "HelperFunctions.h"
#include <iostream>
#include "PairingHeap.hpp"
#include "PostingList.h"
#include "Trie.hpp"

int countlines(FILE* file, int* lines, int* non_empty) {
	(*lines) = 0;
	(*non_empty) = 0;
	size_t s;
	char* line;
	while (!feof(file)) {
		//whle we are not in the end of the file get a line and increase counter
		line = NULL;
		s = 0;
		getline(&line, &s, file);
		if (feof(file)) { //stop if we reached the end. This is so we won't calcuate an extra line
			fseek(file, 0, SEEK_SET);
			free(line);
			return 0;
		}
		(*lines)++;
		if (!strcmp(line, "\n")) {  //if the line was empty we move in the next one
			free(line);
			continue;
		}
		(*non_empty)++;
		free(line);
	}
	fseek(file, 0, SEEK_SET); //go back to the beginning of the file
	return 0;
}

char* ignoreWhiteAtStart(char* s) {
	int l = strlen(s), i;
	char* new_s;

	for (i = 0; i < l; i++) {  //we skip all the digits and spaces in the beginning of a doc so we'kkep only the doc
		if (!isspace(s[i]) && !isdigit(s[i])) break;
	}
	new_s = new char[l-i + 1];
	strncpy(new_s, &s[i], l-i+1);

	delete[] s;
	return new_s;
}

char* ignoreWhiteAtEnd(char* s) {
	int l = strlen(s), i;
	char* new_s;

	for (i = l - 1; i >= 0; i--) { //we ignore all the white spaces in the end of a doc
		if (!isspace(s[i]) && s[i] != '\n') break;
	}

	new_s = new char[i+2];
	strncpy(new_s, s, i+1);
	strncpy(&new_s[i+1], "\0", 1);
	delete[] s;
	return new_s;
}

DocMap* makeStructs(int lines, int non_empty, FILE* doc, DocMap* doc_map, Trie<PostingList>* trie, int* all_words) {
	size_t s = 0;
	char* line, *d_line, *token;
	int i, id, id2, l, j, wc;
	doc_map = new DocMap(non_empty);
	PostingList* psl = NULL;
	j = 0;
	(*all_words) = 0;
	for (i = 0; i < lines; i++) {
		wc = 0;
		line = NULL;
		getline(&line, &s, doc);
		if (feof(doc)) {
			free(line);
			return doc_map;
		}
		//if line is empty move on the next line
		if (!strcmp(line, "\n")) {
			free(line);
			continue;
		}
		l = strlen(line);
		d_line = new char[l+1];
		strncpy(d_line, line, l+1);

		//if ids are not in order error
		id = atoi(strtok(line, " \t"));
		if (id != j) {
			std::cout << "Ids are not in order" << '\n';
			delete[] d_line;
			free(line);
			exit(1);
		}
		j++;
		//insert the words in the trie
		while (1) {
			token = strtok(NULL, " \t\n");
			if (token == NULL) {
				break;
			}
			wc++;
			psl = trie->find(token);
			(*all_words)++;
			//if the word wasn't in the trie add it
			if (psl == NULL) {
				psl = new PostingList();
				psl->insert(id, 1);
				trie->insert(token, psl);
			} else {
				id2 = psl->getLastId();
				//check if the last doc the word added is the same as the one we check now
				//if yes just increase its frequency for the doc
				if (id == id2) {
					psl->incLastFrq();
				} else {
					//if not we need to add another doc to the posting list
					psl->insert(id, 1);
				}
			}
		}
		//keep only the sentnce in the line without white spaces in the beginning and in the end
		d_line = ignoreWhiteAtStart(d_line);
		d_line = ignoreWhiteAtEnd(d_line);

		doc_map->insert(d_line, wc);
		delete[] d_line;
		free(line);
	}
	return doc_map;
}
