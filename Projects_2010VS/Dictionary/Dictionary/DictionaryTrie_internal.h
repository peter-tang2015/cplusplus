#ifndef DICTIONARY_TRIE_INTERNAL_H
#define DICTIONARY_TRIE_INTERNAL_H

#include "DictionaryTrie.h"

DictionaryTrie* LocateWord(DictionaryTrie* root, const char* word);
bool EmptyTrieNode(DictionaryTrie* node);

#endif
