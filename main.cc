#include <cmath>
#include "Commands.h"
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
#include <ctime>

int main(int argc, char const *argv[]) {
	int k = 10, lines, i, non_empty, ret;
	FILE* doc = NULL;
	DocMap* doc_map = NULL;
	Trie<PostingList>* trie = new Trie<PostingList>();
	char* promt, *rest;
	size_t s;
	bool f = false; //flag to check if a file was found and oppened

	//check if the arguments are correct
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-i")) {
			f = true;
			if (i == (argc - 1)) {
				std::cerr << "Invalid arguments. Please run as \"./minisearch -i docfile -k K\"" << '\n';
				exit(1);
			}
			doc = fopen(argv[i+1], "r");
			if (doc == NULL) {
				std::cerr << "Could not open docfile " << argv[i+1] << '\n';
				exit(1);
			}
			i++;
		} else if (!strcmp(argv[i], "-k")) {
			if (i == (argc - 1)) {
				std::cerr << "Invalid arguments. Please run as \"./minisearch -i docfile -k K\"" << '\n';
				exit(1);
			}
			k = atoi(argv[i+1]);
			if (k <= 0) {
				std::cerr << "The parameter for flag -k should be a positive integer. Please try again" << '\n';
				exit(1);
			}
			i++;
		} else {
			std::cerr << "Invalid arguments. Please run as \"./minisearch -i docfile -k K\"" << '\n';
			exit(1);
		}
	}

	if (f == false) {
		std::cerr << "Invalid arguments. No input file specified. Please run as \"./minisearch -i docfile -k K\"" << '\n';
		exit(1);
	}

	int all_words = 0;
	countlines(doc, &lines, &non_empty);
	doc_map = makeStructs(lines, non_empty, doc, doc_map, trie, &all_words);

	//while loop to run the commands given as input from user unitl exit is given for termination
	//all the commands are implemented with one function each
	while (1) {
		std::cout << "$:";  //start of command line
		promt = NULL;
		s = 0;
		getline(&promt, &s, stdin);
		promt = strtok(promt, " \t\n");
		if (promt == NULL) { //case user typed enter and no other input was given
			std::cout << "Please give a valid command. Run \\man or /man to see all the commands" << '\n';
		} else if (!strcmp(promt, "\\exit") || !strcmp(promt, "/exit")) {  //if exit is given clear all memory and terminate the program
			free(promt);
			fclose(doc);
			delete doc_map;
			delete trie;
			return 0;

		} else if (!strcmp(promt, "\\search") || !strcmp(promt, "/search")) {
			rest = strtok(NULL, "\n");
			ret = search(rest, trie, doc_map, all_words, k);
			if (ret != 0) {
				free(promt);
				continue;
			}

		} else if (!strcmp(promt, "\\df") || !strcmp(promt, "/df")) {
			rest = strtok(NULL, "\n");
			df(rest, trie);

		} else if (!strcmp(promt, "\\tf") || !strcmp(promt, "/tf")) {
			rest = strtok(NULL, " \n");
			ret = tf(rest, trie);
			//if an error occured at tf free the memory and go on the next command
			if (ret != 0) {
				free(promt);
				continue;
			}

		} else if (!strcmp(promt, "\\man") || !strcmp(promt, "/man")) { //jut a command to show the existing commands and help the user
			man();
		} else {
			//in case a command that does not exist was given print a message
			std::cout << "This command does not exist. Try something else. Use \\man or /man for the existing commands" << '\n';
		}
		free(promt);
		std::cout << '\n';
	}

	//should never reach here but just in case
	fclose(doc);
	delete doc_map;
	delete trie;
	return 0;

}
