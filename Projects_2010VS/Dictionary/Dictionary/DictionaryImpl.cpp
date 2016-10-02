#include "StdAfx.h"
#include "DictionaryImpl.h"

#include "DictionaryTrie.h"

DictionaryImpl::DictionaryImpl()
	: m_DictRoot(new DictionaryTrie())
{
}


DictionaryImpl::~DictionaryImpl()
{
	DestoryDictionaryTrie(m_DictRoot);
}

void DictionaryImpl::Add(const std::string& word)
{
	AddWord(m_DictRoot, word.c_str());
}

void DictionaryImpl::Query(const std::string& word, std::vector<std::string>& words)
{
	std::vector<std::string>().swap(words);
	QueryWord(m_DictRoot, word.c_str(), words);
}

void DictionaryImpl::Query(const std::string& word, char** words)
{
	QueryWord(m_DictRoot, word.c_str(), words);
}

void DictionaryImpl::Remove(const std::string& word)
{
	RemoveWord(m_DictRoot, word.c_str());
}

void DictionaryImpl::RetrieveAll(std::vector<std::string>& words)
{
	std::vector<std::string>().swap(words);
	TraverseDictionaryTrie(m_DictRoot, words);
}

void DictionaryImpl::RetrieveAll(char** words)
{
	TraverseDictionaryTrie(m_DictRoot, words);
}
