#ifndef __HELPER__
#define __HELPER__

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "DocMap.h"
#include <fstream>
#include <iostream>
#include "PairingHeap.hpp"
#include "PostingList.h"
#include "Trie.hpp"

int countlines(FILE* file, int* lines, int* non_empty);

char* ignoreWhiteAtStart(char* s);

char* ignoreWhiteAtEnd(char* s);

DocMap* makeStructs(int lines, int non_empty, FILE* doc, DocMap* doc_map, Trie<PostingList>* trie, int* all_words);

#endif
