// PhoneKeyMapDigToLetter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <vector>

std::vector<std::vector<std::string> > MapDigToLetter;

void ConstructMapDigToLetter(std::vector<std::vector<std::string> >& mdl) 
{
    {   // 2
        std::vector<std::string> noMap;
        noMap.push_back("A");
        noMap.push_back("B");
        noMap.push_back("C");
        mdl.push_back(noMap);
    }

    {   // 3
        std::vector<std::string> noMap;
        noMap.push_back("D");
        noMap.push_back("E");
        noMap.push_back("F");
        mdl.push_back(noMap);
    }

    {   // 4
        std::vector<std::string> noMap;
        noMap.push_back("G");
        noMap.push_back("H");
        noMap.push_back("I");
        mdl.push_back(noMap);
    }

    {   // 5
        std::vector<std::string> noMap;
        noMap.push_back("J");
        noMap.push_back("K");
        noMap.push_back("L");
        mdl.push_back(noMap);
    }

    {   // 6
        std::vector<std::string> noMap;
        noMap.push_back("M");
        noMap.push_back("N");
        noMap.push_back("O");
        mdl.push_back(noMap);
    }

    {   // 7
        std::vector<std::string> noMap;
        noMap.push_back("P");
        noMap.push_back("Q");
        noMap.push_back("R");
        noMap.push_back("S");
        mdl.push_back(noMap);
    }

    {   // 8
        std::vector<std::string> noMap;
        noMap.push_back("T");
        noMap.push_back("U");
        noMap.push_back("V");
        mdl.push_back(noMap);
    }

    {   //9
        std::vector<std::string> noMap;
        noMap.push_back("W");
        noMap.push_back("X");
        noMap.push_back("Y");
        noMap.push_back("Z");
        mdl.push_back(noMap);
    }
}

bool IsValidNumbers(const std::string& numberString, std::vector<unsigned char>& phoneNumber)
{
    phoneNumber.clear();
    phoneNumber.reserve(numberString.size());
    for (size_t i = 0; i < numberString.size(); ++i) {
        //numberString.        
    }

    return true;
}


void GetCombinationsOfLettersBasedOnNumbers(const std::vector<unsigned char>& phoneNumber,
                                            size_t index,
                                            std::string& words,
                                            std::string& letters)
{
    if (index == phoneNumber.size()) {
        words.append(letters);
        words.append(";");
        return;
    }

    unsigned char number = phoneNumber[index];
    std::vector<std::string>& curMap= MapDigToLetter[number - 2];
    for (unsigned size_t i = 0; i < curMap.size(); ++i) {
        std::string copyLetters(letters);
        copyLetters.append(curMap[i]);
        GetCombinationsOfLettersBasedOnNumbers(phoneNumber, index+1, words, copyLetters);
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
    ConstructMapDigToLetter(MapDigToLetter);

    std::vector<unsigned char> phoneNumber;
    phoneNumber.push_back(2);
    phoneNumber.push_back(2);
    phoneNumber.push_back(3);

    std::string words, letters;
    GetCombinationsOfLettersBasedOnNumbers(phoneNumber, 0, words, letters);
                                                                 
	return 0;
}

