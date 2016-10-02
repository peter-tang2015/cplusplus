#include "StdAfx.h"
#include "LiveStreamWordsDetector.h"

#include "DictionaryTrie.h"
#include "DictionaryTrie_internal.h"

LiveStreamWordsDetector::LiveStreamWordsDetector()
: mDictRoot(new DictionaryTrie())
{
}

LiveStreamWordsDetector::LiveStreamWordsDetector(std::vector<std::string> const &words)
: mDictRoot(new DictionaryTrie())
{
    AddWordsIntoDict(words);
}

LiveStreamWordsDetector::~LiveStreamWordsDetector()
{
    DestoryDictionaryTrie(mDictRoot);
    mDictRoot = nullptr;
}

void LiveStreamWordsDetector::AddWordIntoDict(std::string const &word)
{
    AddWord(mDictRoot, word.c_str());
}

void LiveStreamWordsDetector::AddWordsIntoDict(std::vector<std::string> const &words)
{
    auto iterEnd = words.end();
    for (auto iter = words.begin(); iter != iterEnd; ++iter) {
        AddWordIntoDict(*iter);
    }
}


void LiveStreamWordsDetector::AppendLiveStream(char const ch, std::vector<std::string> &words)
{
    words.clear();
    DictionaryTrie* temp = nullptr;
    for (auto iter = mPossibleWords.begin(); iter != mPossibleWords.end();) {
        temp = LocateChar(*iter, ch);
        if (temp){
            *iter = temp;
            if (temp->str) {
                words.push_back(temp->str);
            }
            ++iter;
        }
        else {
            iter = mPossibleWords.erase(iter);
        }
    }

    temp = LocateChar(mDictRoot, ch);
    if (temp) {
        mPossibleWords.push_front(temp);
        if (temp->str) {
            words.push_back(&ch);
        }
    }
}
