// PathFinder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <queue>
#include <vector>

#include <assert.h>

struct Position {
    unsigned int row;
    unsigned int col;
    
    Position(unsigned int posR = 0,
        unsigned int posC = 0)
        : row(posR), col(posC)
    {}

    bool operator==(const Position& rhs) const
    {
        return row == rhs.row && col == rhs.col;
    }
};

bool PathFinder(const Position& start,
                const Position& end,
                std::vector<std::vector<unsigned char>>& roadMap,
                const unsigned int MATRIX_ROW,
                const unsigned int MATRIX_COL)
{
    if (start.row >= MATRIX_ROW || start.col >= MATRIX_COL ||
        end.row >= MATRIX_ROW || end.col >= MATRIX_COL) {
        return false;
    }

    if (roadMap[start.row][start.col] == 1 ||
        roadMap[end.row][end.col] == 1) {
        return false;
    }

    std::queue<Position> posToVisit;
    posToVisit.push(start);

    while (!posToVisit.empty()) {
        const Position curPos = posToVisit.front();

        if (curPos == end) {
            return true;
        }

        // Position in the corodinate of row and col
        // (row = 0, col = 0) in the northwest corner
        // (row = MATRIX_ROW, rol = MATRIX_COL) in the southeast corner
        if (curPos.row > 0) {
            Position northPos{ curPos.row - 1, curPos.col };
            if (roadMap[northPos.row][northPos.col] == 0) {
                posToVisit.push(northPos);
            }
        }
        if (curPos.row < (MATRIX_ROW - 1)) {
            Position southPos{ curPos.row + 1, curPos.col };
            if (roadMap[southPos.row][southPos.col] == 0) {
                posToVisit.push(southPos);
            }
        }
        if (curPos.col > 0) {
            Position westPos{ curPos.row, curPos.col - 1 };
            if (roadMap[westPos.row][westPos.col] == 0) {
                posToVisit.push(westPos);
            }
        }
        if (curPos.col < (MATRIX_COL - 1)) {
            Position eastPos{ curPos.row, curPos.col + 1 };
            if (roadMap[eastPos.row][eastPos.col] == 0) {
                posToVisit.push(eastPos);
            }
        }
        roadMap[curPos.row][curPos.col] = 2;

        posToVisit.pop();
    }

    return false;
}

void TestPass_1()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
                            Position{ 9, 9 },
                            roadMap,
                            MATRIX_ROW,
                            MATRIX_COL
                           );

    assert(found == true);
}

void TestPass_2()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == true);
}

void TestPass_3()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == true);
}

void TestPass_4()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 1, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 1, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 0, 0 },
        { 0, 1, 0, 1, 0, 1, 0, 1, 1, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == true);
}

void TestPass_5()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == true);
}

void TestPass_6()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 1, 1, 1, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == true);
}

void TestFail_1()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == false);
}

void TestFail_2()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == false);
}

void TestFail_3()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == false);
}

void TestFail_4()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == false);
}

void TestFail_5()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == false);
}

void TestFail_6()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == false);
}

void TestFail_7()
{
    const unsigned int MATRIX_ROW = 10;
    const unsigned int MATRIX_COL = 10;
    std::vector<std::vector<unsigned char>> roadMap =
    {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    bool found = PathFinder(Position{ 0, 0 },
        Position{ 9, 9 },
        roadMap,
        MATRIX_ROW,
        MATRIX_COL
        );

    assert(found == false);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestPass_1();
    TestPass_2();
    TestPass_3();
    TestPass_4();
    TestPass_5();
    TestPass_6();

    TestFail_1();
    TestFail_2();
    TestFail_3();
    TestFail_4();
    TestFail_5();
    TestFail_6();
    TestFail_7();

	return 0;
}

