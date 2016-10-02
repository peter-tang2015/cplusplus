#include "stdafx.h"
#include "PermutationDetector.h"

#include "DictionaryTrie.h"

#include <queue>

#include <cassert>

PermutationDetector::PermutationDetector()
    : m_DictRoot(nullptr)
{
}

PermutationDetector::PermutationDetector(const std::vector<std::string> &words)
    : m_DictRoot(nullptr)
{
    ConstructDict(words, false);
}

PermutationDetector::~PermutationDetector()
{
    if (m_DictRoot) {
        DestoryDictionaryTrie(m_DictRoot);
        m_DictRoot = nullptr;
    }
}

void PermutationDetector::ConstructDict(const std::vector<std::string> &words,
                                        const bool appendMode)
{
    if (!appendMode && m_DictRoot) {
        DestoryDictionaryTrie(m_DictRoot);
        m_DictRoot = nullptr;
    }
    if (!m_DictRoot) {
        m_DictRoot = new DictionaryTrie();
    }

    assert(m_DictRoot != nullptr);

    auto&& itEnd = words.rend();
    for (auto&& it = words.rbegin(); it != itEnd; ++it) {
        AddWord(m_DictRoot, it->c_str());
    }
}

bool PermutationDetector::IsPermutation_R(const std::string &word,
                                        std::queue<size_t> &nextSearch) const
{
    if (nextSearch.empty()) {
        return false;
    }

    const size_t startSearchIndex = nextSearch.front();
    const char *startSearchPtr = word.c_str() + startSearchIndex;
    nextSearch.pop();

    DictionaryTrie *tempPtr = m_DictRoot;
    size_t searchedLen = 1;
    while (*startSearchPtr != '\0' && tempPtr) {
        tempPtr = tempPtr->children[*startSearchPtr - 'a'];
        if (tempPtr && tempPtr->str) {
            nextSearch.push(startSearchIndex + searchedLen);
        }
        ++searchedLen;
        ++startSearchPtr;
    }

    if (*startSearchPtr == '\0' && tempPtr && tempPtr->str) {
        return true;
    }

    return IsPermutation_R(word, nextSearch);
}

bool PermutationDetector::IsPermutation_R(const std::string &word) const
{
    if (word.empty()) {
        return false;
    }

    std::queue<size_t> nextSearch;
    nextSearch.push(0);
    return IsPermutation_R(word, nextSearch);
}

bool PermutationDetector::IsPermutation(const std::string &word) const
{
    if (word.empty()) {
        return false;
    }

    std::queue<size_t> nextSearch;
    nextSearch.push(0);
    while (!nextSearch.empty()) {
        size_t startSearchIndex = nextSearch.front();
        nextSearch.pop();
        const char *searchStartPtr = word.c_str() + startSearchIndex;
        DictionaryTrie *tempPtr = m_DictRoot;
        ++startSearchIndex;
        while (*searchStartPtr != '\0' && tempPtr) {
            tempPtr = tempPtr->children[*searchStartPtr - 'a'];
            if (tempPtr && tempPtr->str) {
                nextSearch.push(startSearchIndex);
            }
            ++startSearchIndex;
            ++searchStartPtr;
        }
        
        if (*searchStartPtr == '\0' && tempPtr && tempPtr->str) {
            return true;
        }
    }

    return false;
}
