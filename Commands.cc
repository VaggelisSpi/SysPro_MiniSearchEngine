#include "Commands.h"

float calcIdf(int df, int n) {
	return log10((n - df + 0.5)/(df + 0.5));
}

int search(char* rest, Trie<PostingList> *trie, DocMap* doc_map, int all_words, int k) {
	int wc = 0, i, n = doc_map->getSize(), doc, doc_words, frq;
	float score, kl = 1.2, b = 0.75, avg = all_words/n, idf;
	bool first = true;
	char* words[10];
	PostingList* psl;
	PairingHeap<float, int> *score_heap = new PairingHeap<float, int>();

	float *doc_scores = new float[n]; //hold the score of each doc for the current query
	bool *doc_flg = new bool[n];  //shows which docs participated in the query and need to be added in the heap

	for (i = 0; i < n; i++) {
		doc_scores[i] = 0;
		doc_flg[i] = false;
	}

	//get the first 10 words, or less if less were given
	for (wc = 0; wc < 10; wc++) {
		//need special case for first word since we haven't used strtok to rest yet
		if (first == true) {
			words[wc] = strtok(rest, " \t\n");
			first = false;
		} else
			words[wc] = strtok(NULL, " \t\n");
		if (words[wc] == NULL) {  //if there are no more words check if there was at least one and proceed
			if (wc == 0) {
				std::cout << "Please run this command as \"search q1 q2...q10\"" << "\n\n";
				return -1;
			}
			break;
		}
		psl = trie->find(words[wc]);
		if (psl != NULL) {
			psl->first();
			idf = calcIdf(psl->getDF(), n);
			while (psl->hasNext()) { //for each doc caclucate the score for the curretn word
				doc = psl->getCurDoc();
				doc_words = doc_map->getWords(doc);
				frq = psl->getCurFrq();
				doc_scores[doc] += idf*( (frq*(kl + 1)) / (frq + kl * (1 - b + b*(doc_words/avg))));
				doc_flg[doc] = true;
				psl->goToNext();
			}
		}
	}

	for (i = 0; i < n; i++) { //insert all the scores of the relevant docs in the heap
		if (doc_flg[i] == true) {
			score_heap->insert(doc_scores[i], i);
		}
	}
	//remove unecessary memory
	delete[] doc_scores;
	delete[] doc_flg;

	i = 0;
	while (i < k && !score_heap->empty()) { //print the top k scores or less if there are less than k docs
		doc = score_heap->top();
		score = score_heap->topCost();
		doc_map->print(doc, words, wc, score);
		score_heap->pop();
		while (!score_heap->empty() && doc == score_heap->top()) { //ignore duplicate docs at the the heap
			score_heap->pop();
		}
		i++;
	}

	delete score_heap;
	return 0;
}

int df(char* promt, Trie<PostingList>* trie) {
	PostingList* psl = NULL;
	char* rest = strtok(promt, " \t\n");
	if (rest == NULL)  //if df was given without an argument print everything
		trie->print();
	else {
		while (rest != NULL) {  //get each argument of df and make print it out
			psl = trie->find(rest);
			if (psl != NULL) {
				std::cout << rest;
				psl->print();
			} else {
				std::cout << rest << " 0" << '\n';
			}
			rest = strtok(NULL, " \t\n");
		}
	}
	return 0;
}

int tf(char* rest, Trie<PostingList>* trie) {
	PostingList* psl = NULL;
	char* word;
	int id;
	//check if the tf was given with proper arguments
	if (rest == NULL) {
		std::cout << "Pleas run this command as \"tf id word\" where id is a non negative integer" << "\n\n";
		return -1;
	}
	if (!isdigit(rest[0])) {
		std::cout << "Pleas run this command as \"tf id word\" where id is a non negative integer" << "\n\n";
		return -1;
	}
	id = atoi(rest);
	if (id < 0) {
		std::cout << "Please run this command as \"tf id word\" where id is a non negative integer" << "\n\n";
		return -1;
	}
	word = strtok(NULL, " \t\n");
	if (word == NULL) {
		std::cout << "Please run this command as \"tf id word\" where id is a non negative integer" << "\n\n";
		return -1;
	}
	//find the word in the trie and then find the respective doc and print
	psl = trie->find(word);
	rest = strtok(NULL, " \t\n");
	if (rest != NULL) {
		std::cout << "Please run this command as \"tf id word\" where id is a non negative integer" << "\n\n";
		return -1;
	}

	if (psl != NULL)
		std::cout << id << " " << word << " " << psl->getFrq(id) << '\n';
	else   //if there is no post list for this word then it has 0 frequency at the respective doc
		std::cout << id << " " << word << " 0" << '\n';

	return 0;
}

//just a helping function
void man() {
	std::cerr << "Command list:" << '\n';
	std::cout << "    search q1 q2 q3 q4 ... q10" << '\n';
	std::cout << "    df" << '\n';
	std::cout << "    df word(s)" << '\n';
	std::cout << "    tf id word" << '\n';
	std::cout << "    exit" << '\n';
	std::cout << "Run your commands with \\ or / in the beginning" << '\n';
}
