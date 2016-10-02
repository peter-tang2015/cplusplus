#include "stdafx.h"

#include "DictionaryTrie_internal.h"

#include <stack>
#include <stdlib.h>
#include <string.h>

void InitDictionaryTrie(DictionaryTrie** dtriePtr)
{
	if (!dtriePtr) {
		*dtriePtr = static_cast<DictionaryTrie*> (malloc(sizeof(dtriePtr)));
		(*dtriePtr)->str = 0;
		for (int i = 0; i < NUMBER_OF_LETTERS; ++ i) {
			(*dtriePtr)->children[i] = 0;
		}
	}
}

DictionaryTrie* AddWord(DictionaryTrie* root, const char* word)
{
	if (!root || !word) {
		return NULL;
	}

	DictionaryTrie* tempPtr = root;
	int size_str = 0;
	while (*(word + size_str) != '\0') {
		if (!tempPtr->children[*(word + size_str) - 'a']) {
			tempPtr->children[*(word + size_str) - 'a'] = new DictionaryTrie();
		}
		tempPtr = tempPtr->children[*(word + size_str) - 'a'];
		++size_str;
	}

	if (!tempPtr->str) {
		tempPtr->str = static_cast<char*>(malloc(size_str + 1));
		strncpy(tempPtr->str, word, size_str);
		*(tempPtr->str + size_str) = '\0';
        return tempPtr;
	}

    return NULL;
}

void RemoveWord(DictionaryTrie* root, const char* word)
{
	DictionaryTrie* tempPtr = LocateWord(root, word);
	if (tempPtr) {
		if (tempPtr->str) {
			free(tempPtr->str);
			tempPtr->str = 0;
		}

		if (EmptyTrieNode(tempPtr)) {
			DestoryDictionaryTrie(tempPtr);
		}
	}
}

void QueryWord(DictionaryTrie* root, const char* word, char** result)
{
	DictionaryTrie* wordFound = LocateWord(root, word);
	if (wordFound) {
		TraverseDictionaryTrie(wordFound, result);
	}
}

void QueryWord(DictionaryTrie* root, const char* word, std::vector<std::string>& result)
{
	DictionaryTrie* wordFound = LocateWord(root, word);
	if (wordFound) {
		TraverseDictionaryTrie(wordFound, result);
	}
}

bool FindWord(DictionaryTrie* root, const char* word)
{
	DictionaryTrie* tempPtr = LocateWord(root, word);
	return !tempPtr && !tempPtr->str;
}

DictionaryTrie* FindPath(DictionaryTrie *parent, const char key)
{
    if (parent) {
        return parent->children[key - 'a'];
    }

    return  NULL;
}

void TraverseDictionaryTrie(DictionaryTrie* root, char** result)
{
	DictionaryTrie* tempPtr = root;
	if(tempPtr) {
		if (tempPtr->str) {
			// copy the pointer rather than the string
			*(result++) = tempPtr->str;
		}
		for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
			TraverseDictionaryTrie(tempPtr->children[i], result);
		}
	}
}

void TraverseDictionaryTrie(DictionaryTrie* root, std::vector<std::string>& result)
{
	DictionaryTrie* tempPtr = root;
	if (tempPtr) {
		if (tempPtr->str) {
			result.push_back(tempPtr->str);
		}
		for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
			TraverseDictionaryTrie(tempPtr->children[i], result);
		}
	}
}

void DestoryDictionaryTrie(DictionaryTrie* root)
{
	DictionaryTrie* tempPtr = root;
	if (tempPtr) {
		if (tempPtr->str) {
			free(tempPtr->str);
			tempPtr->str = 0;
		}

		for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
			DestoryDictionaryTrie(tempPtr->children[i]);
		}
		delete tempPtr;
	}
}

/*
 * this verison use a lot of mem
 */
/*
void DestoryDictionaryTrie(DictionaryTrie* root)
{
	if(!root) {
		return;
	}

	std::stack<DictionaryTrie*> stackDtriePtr;
	stackDtriePtr.push(root);
	DictionaryTrie* tempPtr;
	while (!stackDtriePtr.empty()) {
		tempPtr = stackDtriePtr.top();
		stackDtriePtr.pop();
		if (tempPtr->str) {
			free(tempPtr->str);
		}
		for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
			if (!tempPtr->children[i]) {
				stackDtriePtr.push(tempPtr->children[i]);
			}
		}

		free(tempPtr);
	}
}
*/

DictionaryTrie* LocateWord(DictionaryTrie* root, const char* word)
{
	if (!root || !word) {
		return nullptr;
	}

	DictionaryTrie* tempPtr = root;
	while (*word != '\0' && tempPtr) {
		tempPtr = tempPtr->children[*word - 'a'];
		++word;
	}

	return tempPtr;
}

DictionaryTrie* LocateChar(DictionaryTrie* root, char const ch)
{
    if (!root || ch < 'a' || ch > 'z') {
        return nullptr;
    }

    return root->children[ch - 'a'];
}

bool EmptyTrieNode(DictionaryTrie* node)
{
	if (node->str) {
		return false;
	}

	for (int i = 0; i < NUMBER_OF_LETTERS; ++i) {
		if (node->children[i]) {
			return false;
		}
	}

	return true;
}