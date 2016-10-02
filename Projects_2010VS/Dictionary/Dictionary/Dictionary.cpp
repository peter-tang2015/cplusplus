// Dictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DictionaryImpl.h"

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
			


int _tmain(int argc, _TCHAR* argv[])
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
			} else {
				dict.Query(word, result);
				if (result.empty()) {
					std::cout << word << " NOT FOUND" << std::endl;
				} else {
					DisplayWords(std::cout, "MATCH FOUND: ", word, result);
				}
			}
		}
		else if (*input.rbegin() == '\-') {
			std::string word(input.begin(), input.end() - 1);
			if (word.empty()) {
				break;
			} else {
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

	return 0;
}

