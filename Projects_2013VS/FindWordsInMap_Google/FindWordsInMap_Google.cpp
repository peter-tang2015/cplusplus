// FindWordsInMap_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

/*
Please use this Google doc to code during your interview.To free your hands for coding, 
we recommend that you use a headset or a phone with speaker option.

QWER
SADF
POUY
BNPM
// 

READ
READY
READER
POP
*/

#include <string>
#include <set>
#include <vector>
#include <queue>

struct Position
{
    Position(size_t r,
             size_t c,
             const std::string& curWord,
             std::vector<std::vector<bool>> paths)
             : row(r), col(c), word(curWord), visitedCells(paths)
    {}
    size_t row;
    size_t col;
    std::string word;
    std::vector<std::vector<bool>> visitedCells;
};

bool SanityCheckingOnInput(const std::vector<std::vector<char>>&  input)
{
    if (input.empty()) {
        return false;
    }
    auto iter = input.begin();
    auto iterEnd = input.end();
    size_t colMax = iter->size();
    for (; iter != iterEnd; ++iter) {
        if (iter->size() != colMax) {
            return false;
        }
    }

    return true;
}

bool IsWord(const std::string& word, const std::set<std::string>& dict)
{
    return dict.find(word) != dict.end();
}

void FindAllWordsStartWith(const std::set<std::string>& dict,
    const std::vector<std::vector<char>>& input,
    size_t row, size_t col,
    std::set<std::string>& output)
{
    if (!SanityCheckingOnInput(input)) {
        return;
    }

    size_t rowMax = input.size();
    size_t colMax = input.begin()->size();
    std::queue<Position> bfsQueue;
    bfsQueue.push(Position(row, col, &input[row][col], 
                           std::vector<std::vector<bool>>(rowMax,std::vector<bool>(colMax, false))));
    while (!bfsQueue.empty())
    {
        Position& curPos = bfsQueue.front();
        if (IsWord(curPos.word, dict)) {
            output.insert(curPos.word);
        }
        if (!curPos.visitedCells[curPos.row][curPos.col]) {
            curPos.visitedCells[curPos.row][curPos.col] = true;
        }
        if (curPos.row > 0) {
            if (!curPos.visitedCells[curPos.row - 1][curPos.col]) {
                bfsQueue.push(Position(curPos.row - 1, curPos.col,
                    curPos.word + input[curPos.row - 1][curPos.col], curPos.visitedCells));
            }
        }
        if (curPos.row < rowMax - 1) {
            if (!curPos.visitedCells[curPos.row + 1][curPos.col]) {
                bfsQueue.push(Position(curPos.row + 1, curPos.col,
                    curPos.word + input[curPos.row + 1][curPos.col], curPos.visitedCells));
            }
        }
        if (curPos.col > 0) {
            if (!curPos.visitedCells[curPos.row][curPos.col + 1]) {
                bfsQueue.push(Position(curPos.row, curPos.col + 1,
                    curPos.word + input[curPos.row][curPos.col + 1], curPos.visitedCells));
            }
        }
        if (curPos.col < colMax - 1) {
            if (!curPos.visitedCells[curPos.row][curPos.col - 1]) {
                bfsQueue.push(Position(curPos.row, curPos.col - 1,
                    curPos.word + input[curPos.row][curPos.col - 1], curPos.visitedCells));
            }
        }
        if (curPos.row > 0 && curPos.col > 0)
        {
            if (!curPos.visitedCells[curPos.row - 1][curPos.col - 1]) {
                bfsQueue.push(Position(curPos.row - 1, curPos.col - 1,
                    curPos.word + input[curPos.row - 1][curPos.col - 1], curPos.visitedCells));
            }
        }
        if (curPos.row < rowMax - 1 && curPos.col > 0)
        {
            if (!curPos.visitedCells[curPos.row + 1][curPos.col - 1]) {
                bfsQueue.push(Position(curPos.row + 1, curPos.col - 1,
                    curPos.word + input[curPos.row + 1][curPos.col - 1], curPos.visitedCells));
            }
        }

        if (curPos.row >0 && curPos.col < colMax - 1)
        {
            if (!curPos.visitedCells[curPos.row + 1][curPos.col - 1]) {
                bfsQueue.push(Position(curPos.row - 1, curPos.col + 1,
                    curPos.word + input[curPos.row - 1][curPos.col + 1], curPos.visitedCells));
            }
        }

        if (curPos.row < rowMax - 1 && curPos.col < colMax - 1)
        {
            if (!curPos.visitedCells[curPos.row + 1][curPos.col + 1]) {
                bfsQueue.push(Position(curPos.row + 1, curPos.col + 1,
                    curPos.word + input[curPos.row + 1][curPos.col + 1], curPos.visitedCells));
            }
        }

        bfsQueue.pop();
    }
}

void FindAllWords(const std::set<std::string>& dict,
    const std::vector<std::vector<char>>& input,
    std::set<std::string>& output)
{
    if (!SanityCheckingOnInput(input)) {
        return;
    }

    size_t colMax = input.begin()->size();
    size_t rowMax = input.size();
    for (size_t row = 0; row < rowMax; ++row) {
        for (size_t col = 0; col < colMax; ++col) {
            FindAllWordsStartWith(dict, input, row, col, output);
        }
    }
}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

