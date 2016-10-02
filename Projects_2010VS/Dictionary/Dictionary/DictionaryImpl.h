#ifndef DICTIONARY_IMPL_H
#define DICTIONARY_IMPL_H

#pragma once

#include <string>
#include <vector>

struct DictionaryTrie;

class DictionaryImpl
{
public:
	DictionaryImpl();
	~DictionaryImpl();

	void Add(const std::string& word);
	void Query(const std::string& word, std::vector<std::string>& words);
	void Query(const std::string& word, char** words);
	void Remove(const std::string& word);
	void RetrieveAll(std::vector<std::string>& words);
	void RetrieveAll(char** words);

private:
	DictionaryTrie* const m_DictRoot;
};

#endif

