// Dictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DictionaryImpl.h"
#include "ExoticStringComparator.h"
#include "LiveStreamWordsDetector.h"
#include "PermutationDetector.h"

#include <boost\shared_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>

void InitDictWords(DictionaryImpl& dict)
{
	dict.Add("hello");
	dict.Add("world");
}

void DisplayWords(std::ostream& outStream,
				  const std::string& prefix, 
				  const std::string& word,
				  const std::vector<std::string>& result)
{
	outStream << prefix << word << std::endl;
	std::copy(result.begin(),
			  result.end(),
			  std::ostream_iterator<std::string>(outStream, "\n"));
}
			

void TestWordQuery()
{
    DictionaryImpl dict;

    InitDictWords(dict);

    std::cout << "Welcome to Dictionary Program" << std::endl;
    std::string input;
    while (true) {
        std::cin >> input;
        if (*input.rbegin() == '\?') {
            std::string word(input.begin(), input.end() - 1);
            std::vector<std::string> result;
            if (word.empty()) {
                dict.RetrieveAll(result);
                DisplayWords(std::cout, "PRINT ALL WORDS: ", "", result);
            }
            else {
                dict.Query(word, result);
                if (result.empty()) {
                    std::cout << word << " NOT FOUND" << std::endl;
                }
                else {
                    DisplayWords(std::cout, "MATCH FOUND: ", word, result);
                }
            }
        }
        else if (*input.rbegin() == '\-') {
            std::string word(input.begin(), input.end() - 1);
            if (word.empty()) {
                break;
            }
            else {
                std::vector<std::string> result;
                dict.RetrieveAll(result);
                DisplayWords(std::cout, "BEFORE REMOVE: ", word, result);
                dict.Remove(word);
                dict.RetrieveAll(result);
                DisplayWords(std::cout, "AFTER REMOVE: ", word, result);
            }
        }
        else {
            std::vector<std::string> result;
            dict.RetrieveAll(result);
            DisplayWords(std::cout, "BEFORE ADD: ", input, result);
            dict.Add(input);
            dict.RetrieveAll(result);
            DisplayWords(std::cout, "AFTER ADD: ", input, result);
        }
    }
}

void TestLiveStream()
{
    const std::vector<std::string> words =
        {"ok", "test", "one", "try", "trying"};
    LiveStreamWordsDetector lsd(words);

    const std::string input("abcokdeftrying");
    std::vector<std::string> output;

    lsd.AppendLiveStream('a', output);
    assert(output.empty());
    lsd.AppendLiveStream('b', output);
    assert(output.empty());
    lsd.AppendLiveStream('c', output);
    assert(output.empty());
    lsd.AppendLiveStream('o', output);
    assert(output.empty());
    lsd.AppendLiveStream('k', output);
    assert(output.size() == 1);
    assert(output[0] == "ok");

    lsd.AppendLiveStream('d', output);
    assert(output.empty());
    lsd.AppendLiveStream('e', output);
    assert(output.empty());
    lsd.AppendLiveStream('f', output);
    assert(output.empty());
    lsd.AppendLiveStream('t', output);
    assert(output.empty());
    lsd.AppendLiveStream('r', output);
    assert(output.empty());
    lsd.AppendLiveStream('y', output);
    assert(output.size() == 1);
    assert(output[0] == "try");
    lsd.AppendLiveStream('i', output);
    assert(output.empty());
    lsd.AppendLiveStream('n', output);
    assert(output.empty());
    lsd.AppendLiveStream('g', output);
    assert(output.size() == 1);
    assert(output[0] == "trying");
}

void TestExoticStringComparator()
{
    {
        // non-exotic testing
        const std::vector<ExoticChar> charTable = { 
            { "a", 'a' },
            { "b", 'b' },
            { "c", 'c' },
            { "d", 'd' },
            { "e", 'e' },
            { "f", 'f' },
            { "g", 'g' },
            { "h", 'h' },
            { "i", 'i' },
            { "j", 'j' },
            { "k", 'k' },
            { "l", 'l' },
            { "m", 'm' },
            { "n", 'n' },
            { "o", 'o' },
            { "p", 'p' },
            { "q", 'q' },
            { "r", 'r' },
            { "s", 's' },
            { "t", 't' },
            { "u", 'u' },
            { "v", 'v' },
            { "w", 'w' },
            { "x", 'x' },
            { "y", 'y' },
            { "z", 'z' } };
            
        ExoticStringComparator esc(charTable);
        assert(esc.CompareExoticString("lkasdfajsd", "lkasdfajsd") == 0);
        assert(esc.CompareExoticString("lkasdfajsd", "lkasdfahsd") > 0);
        assert(esc.CompareExoticString("lkasdfajsd", "lkasdfaxsd") < 0);
        assert(esc.CompareExoticString("lkasdfajsdz", "lkasdfajsd") > 0);
        assert(esc.CompareExoticString("lkasdfajsd", "lkasdfajsdz") < 0);
    
    }

    {
        // exotic testing
        const std::vector<ExoticChar> charTable = {
            { "a", 'a' },
            { "b", 'b' },
            { "c", 'c' },
            { "d", 'd' },
            { "e", 'e' },
            { "f", 'f' },
            { "g", 'g' },
            { "h", 'h' },
            { "i", 'i' },
            { "j", 'j' },
            { "k", 'k' },
            { "l", 'l' },
            { "m", 'm' },
            { "n", 'n' },
            { "o", 'o' },
            { "p", 'p' },
            { "q", 'q' },
            { "r", 'r' },
            { "s", 's' },
            { "t", 't' },
            { "u", 'u' },
            { "v", 'v' },
            { "w", 'w' },
            { "x", 'x' },
            { "y", 'y' },
            { "z", 'z' },
            { "ae", 'z' + 1 },
            { "oe", 'z' + 2 },
            { "ue", 'a' - 1 },
            { "sch", 'a' - 2 }, };

        ExoticStringComparator esc(charTable);
        assert(esc.CompareExoticString("ae", "oe") < 0);
        assert(esc.CompareExoticString("ae", "ue") > 0);
        assert(esc.CompareExoticString("oe", "sch") > 0);
        assert(esc.CompareExoticString("oe", "ue") > 0);
        assert(esc.CompareExoticString("lkasdfaesd", "lkasdfajsdz") > 0);
        assert(esc.CompareExoticString("lkasdfschaesd", "lkasdfaajsdz") < 0);
        assert(esc.CompareExoticString("lkasdfschaesd", "lkasdfschoesd") < 0);

    }
}

void Test_PermutationDetector()
{
    PermutationDetector detector({"actor", "bad", "act", "good"});
    assert(detector.IsPermutation("badactorgoodacting") == false);
    assert(detector.IsPermutation_R("badactorgoodacting") == false);

    detector.ConstructDict({"actor", "bad", "acting", "good"}, false);
    assert(detector.IsPermutation("badactorgoodacting") == true);
    assert(detector.IsPermutation_R("badactorgoodacting") == true);
}


int _tmain(int argc, _TCHAR* argv[])
{
    TestLiveStream();

    TestExoticStringComparator();

    Test_PermutationDetector();

	return 0;
}

