// WordGame_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


Please use this Google doc to code during your interview.To free your hands for coding, we recommend that you use a headset or a phone with speaker option.



QWER
SADF
POUY
BNPM
// 

READ
READY
READER
POP

#include <string>
#include <vector>
#include <queue>

struct Position
{
    Position(size_t r, size_t c, const std::string& curWord)
    : row(r), col(c), word(curWord)
    {}
    size_t row;
    size_t col;
    std::string word;
}

bool SanityCheckingOnInput(const std::vector<std::vecotr<char>>&  input)
{
    auto iter = input.begin();
    auto iterEnd = input.end();
    size_t len = iter->size();
    for (; iter != iterEnd; ++iter) {
        if (iter->size() != len) {
            return false;
        }
    }

    return true;
}

bool IsWord(const std::string& word, const std::set<std::string>& dict)
{
    return dict.find(word) != dict.end();
}

void FindAllWordsStartWith(const std::vector<std::vector<char>>& input,
    size_t row, size_t col,
    std::set<std::string>& output)
{
    if (!SanityCheckingOnInput(input)
    {
        return;
    }

    size_t rowMax = input.size();
    size_t colMax = input.beging()->size();
    std::vector<std::vector<bool>> visitedCells(rowMax,
        std::vector<boo>(colMax, false));
    visitedCells[row][col] = true;
    // start from this row and col and check 8 directions to find if
    // it is word
    std::queue<Position> bfsQueue;
    bfsQueue.push(Position(row, col, input[row][col]);
    while (!bfsQueue.empty())
    {
        Position& curPos = bfsQueue.front();
        if (IsWord(curPos.word)) {
            output.insert(word);
        }
        if (!visitedCelles[curPos.row][curPos.col]) {
            visitedCelles[curPos.row][curPos.col] = true;
        }

        if (curPos.row > 0) {
            if (!vistedCelles[curPos.row - 1][curPos.col]) {
                bfsQueue.push(Position(curPos.row - 1, curPos.col,
                    curPos.word + input[curPos.row - 1][curPos.col]
            }
        }
        if (curPos.row < rowMax - 1) {
            if (!vistedCelles[curPos.row + 1][curPos.col]) {
                bfsQueue.push(Position(curPos.row + 1, curPos.col,
                    curPos.word + input[curPos.row + 1][curPos.col]
            }
        }
        if (curPos.col > 0) {
            if (!vistedCelles[curPos.row][curPos.col + 1]) {
                bfsQueue.push(Position(curPos.row, curPos.col + 1,
                    curPos.word + input[curPos.row][curPos.col + 1]
            }
        }
        if (curPos.col < colMax - 1) {
            if (!vistedCelles[curPos.row][curPos.col - 1]) {
                bfsQueue.push(Position(curPos.row, curPos.col - 1,
                    curPos.word + input[curPos.row][curPos.col - 1]
            }
        }
        if (curPos.row > 0 && cruPos.Col > 0)
        {
            if (!vistedCelles[curPos.row - 1][curPos.col - 1]) {
                bfsQueue.push(Position(curPos.row - 1, curPos.col - 1,
                    curPos.word + input[curPos.row - 1][curPos.col - 1]
            }
        }
        if (curPos.row < rowMax - 1 && cruPos.Col > 0)
        {
            if (!vistedCelles[curPos.row + 1][curPos.col - 1]) {
                bfsQueue.push(Position(curPos.row + 1, curPos.col - 1,
                    curPos.word + input[curPos.row + 1][curPos.col - 1]
            }
        }

        if (curPos.row >0 && cruPos.Col < colMax - 1)
        {
            if (!vistedCelles[curPos.row + 1][curPos.col - 1]) {
                bfsQueue.push(Position(curPos.row - 1, curPos.col + 1,
                    curPos.word + input[curPos.row - 1][curPos.col + 1]
            }
        }

        if (curPos.row < rowMax - 1 && cruPos.Col < rowCol - 1)
        {
            if (!vistedCelles[curPos.row + 1][curPos.col + 1]) {
                bfsQueue.push(Position(curPos.row + 1, curPos.col + 1,
                    curPos.word + input[curPos.row + 1][curPos.col + 1]
            }
        }

        bfsQueue.pop();
    }
}

void FindAllWords(const std::vector<std::vector<char>>& input,
    std::set<std::string>& output)
{
    if (!SanityCheckingOnInput(input)
    {
        return;
    }

    auto iter = input.begin();
    size_t len = iter->size();

    size_t rowMax = input.size();
    for (size_t row = 0; row < rowMax; ++row) {
        for (size_t col = 0; col < len; ++col) {
            FindAllWordsStartWith(input, row, col, output);
        }
    }
}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

