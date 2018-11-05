#ifndef __COMMANDS__
#define __COMMANDS__

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

int search(char* rest, Trie<PostingList> *trie, DocMap* doc_map, int all_words, int k);

int df(char* promt, Trie<PostingList>* trie);

int tf(char* promt, Trie<PostingList>* trie);

void man();

#endif
