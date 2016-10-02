#pragma once

#include <list>
#include <string>
#include <vector>

struct DictionaryTrie;

class LiveStreamWordsDetector
{
public:
    LiveStreamWordsDetector();
    LiveStreamWordsDetector(std::vector<std::string> const &words);
    ~LiveStreamWordsDetector();

    void AddWordIntoDict(std::string const& word);
    void AddWordsIntoDict(std::vector<std::string> const &words);

    void AppendLiveStream(char const ch,
                          std::vector<std::string> &liveWords);

private:
    DictionaryTrie* mDictRoot;
    std::list<DictionaryTrie*> mPossibleWords;
};

