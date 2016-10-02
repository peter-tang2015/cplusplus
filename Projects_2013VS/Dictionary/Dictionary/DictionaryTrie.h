#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <string>
#include <vector>

#define NUMBER_OF_LETTERS 26
struct DictionaryTrie {
	char* str;
	DictionaryTrie* children[NUMBER_OF_LETTERS];
	DictionaryTrie() {
		str = NULL;
		for (int i = 0; i != NUMBER_OF_LETTERS; ++i) {
			children[i] = NULL;
		}
	}
};

void InitDictionaryTrie(DictionaryTrie** dtriePtr);
DictionaryTrie* AddWord(DictionaryTrie* root, const char* word);
void RemoveWord(DictionaryTrie* root, const char* word);
void QueryWord(DictionaryTrie* root, const char* word, char** result);
void QueryWord(DictionaryTrie* root, const char* word, std::vector<std::string>& result);
bool FindWord(DictionaryTrie* root, const char* word);
DictionaryTrie* FindPath(DictionaryTrie *parent, const char key);
void TraverseDictionaryTrie(DictionaryTrie* root, char** result);
void TraverseDictionaryTrie(DictionaryTrie* root, std::vector<std::string>& result);
void DestoryDictionaryTrie(DictionaryTrie* root);
bool EmptyTrieNode(DictionaryTrie* node);

#endif
