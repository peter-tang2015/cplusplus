#pragma once

#include <queue>
#include <string>
#include <vector>

struct DictionaryTrie;

class PermutationDetector
{
public:
    PermutationDetector();
    PermutationDetector(const std::vector<std::string> &words);
    ~PermutationDetector();

    void ConstructDict(const std::vector<std::string> &words, const bool appendMode);
    bool IsPermutation_R(const std::string &word) const;
    bool IsPermutation(const std::string &word) const;
private:
    bool IsPermutation_R(const std::string &word, std::queue<size_t> &nextSearch) const;
    DictionaryTrie *m_DictRoot;
};

