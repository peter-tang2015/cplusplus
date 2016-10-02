// GuardWallAndOpenLand_Facekbook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <list>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
enum class MuseumItem
{
    WALL = 0,
    OPEN,
    GUARD
};

struct LocHashFunc
{
    size_t operator()(const std::tuple<size_t, size_t> &loc) const {
        size_t row, col;
        std::tie<size_t, size_t>(row, col) = loc;
        return std::hash<size_t>()(row) ^ std::hash<size_t>()(col);
    }

    bool operator()(const std::tuple<size_t, size_t> &lhs,
                    const std::tuple<size_t, size_t> &rhs) const {
        return lhs == rhs;
    }
};

using LocationMap = std::unordered_set<std::tuple<size_t, size_t>, LocHashFunc, LocHashFunc>;
using LocAndDistMap = std::unordered_map<std::tuple<size_t, size_t>, int, LocHashFunc, LocHashFunc>;

bool ParserMuseumMap(const std::vector<std::vector<MuseumItem>> &museum,
                     LocationMap &guards,
                     LocationMap &walls)
{
    // for this implementation, the mesum must be square
    const size_t ROWS = museum.size();
    if (ROWS == 0) {
        return false;
    }

    const size_t COLS = museum[0].size();
    auto itEnd = museum.end();
    size_t row = 0, col = 0;
    for (auto it = museum.begin(); it != itEnd; ++it, ++row) {
        if (it->size() != COLS) {
            return false; // enforce square map
        }

        auto itRowEnd = it->end();
        col = 0;
        for (auto itRow = it->begin(); itRow != itRowEnd; ++itRow, ++col) {
            switch (*itRow) {
            case MuseumItem::WALL:
                walls.insert(std::make_tuple(row, col));
                break;
            case MuseumItem::OPEN:
                break;
            case MuseumItem::GUARD:
                guards.insert(std::make_tuple(row, col));
                break;
            default:
                return false;
            }
        }
    }
    return true;
}

void ExpandSeach(const std::tuple<size_t, size_t> &loc,
                 const LocationMap &guards,
                 const LocationMap &walls,
                 const size_t distance,
                 LocAndDistMap & distances,
                 std::list < std::tuple<size_t, size_t> > &toVisits)
{
    if (walls.find(loc) != walls.end()) {
        return;
    }

    if (guards.find(loc) != guards.end()) {
        return;
    }

    if (distances.find(loc) == distances.end()) {
        distances.insert(std::make_pair(loc, distance));
        toVisits.push_back(loc);
    }
}

const LocAndDistMap GetDistances(const size_t ROWS,
                                 const size_t COLS,
                                 const LocationMap &guards,
                                 const LocationMap &walls)
{
    LocAndDistMap distances;
    std::list<std::tuple<size_t, size_t>> toVisits(guards.begin(), guards.end());
    toVisits.push_back(std::tuple<size_t, size_t>{-1, -1});
    LocationMap visited;
    size_t dist = 1;
    size_t row, col;
    size_t distance = 1;
    while (!toVisits.empty()) {
        std::tie<size_t, size_t>(row, col) = toVisits.front();
        if (row == -1 && col == -1) {
            ++distance;
            toVisits.pop_front();
            if (toVisits.empty()) {
                break;
            }
            toVisits.push_back(std::make_tuple(-1, -1));
        }
        else {
            if (row > 0) {
                auto loc = std::make_tuple( row - 1, col );
                ExpandSeach(loc, guards, walls, distance, distances, toVisits);
            }
            if (row != (ROWS - 1)) {
                auto loc = std::make_tuple(row + 1, col);
                ExpandSeach(loc, guards, walls, distance, distances, toVisits);
            }
            if (col > 0) {
                auto loc = std::make_tuple(row, col - 1);
                ExpandSeach(loc, guards, walls, distance, distances, toVisits);
            }
            if (col != (COLS - 1)) {
                auto loc = std::make_tuple(row, col + 1);
                ExpandSeach(loc, guards, walls, distance, distances, toVisits);
            }
            toVisits.pop_front();
        }
    }

    return distances;
}

const LocAndDistMap GetDistances(const std::vector<std::vector<MuseumItem>> &museum)
{
    LocationMap guards;
    LocationMap walls;
    if (!ParserMuseumMap(museum, guards, walls)) {
        return LocAndDistMap();
    }

    const size_t ROWS = museum.size();
    const size_t COLS = museum[0].size();
    return GetDistances(ROWS, COLS, guards, walls);
}

#include <cassert>
void TestGetDistances()
{
    {
        const std::vector<std::vector<MuseumItem>> museum =
        {{MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN},
         {MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN},
         {MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::GUARD, MuseumItem::OPEN, MuseumItem::OPEN},
         {MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN},
         {MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN} };

        LocAndDistMap distances = GetDistances(museum);
        assert(distances.find(std::make_tuple(0, 0))->second == 4);
        assert(distances.find(std::make_tuple(1, 0))->second == 3);
        assert(distances.find(std::make_tuple(2, 0))->second == 2);
        assert(distances.find(std::make_tuple(3, 0))->second == 3);
        assert(distances.find(std::make_tuple(4, 0))->second == 4);
        assert(distances.find(std::make_tuple(0, 1))->second == 3);
        assert(distances.find(std::make_tuple(1, 1))->second == 2);
        assert(distances.find(std::make_tuple(2, 1))->second == 1);
        assert(distances.find(std::make_tuple(3, 1))->second == 2);
        assert(distances.find(std::make_tuple(4, 1))->second == 3);
        assert(distances.find(std::make_tuple(0, 2))->second == 2);
        assert(distances.find(std::make_tuple(1, 2))->second == 1);
        assert(distances.find(std::make_tuple(2, 2)) == distances.end());
        assert(distances.find(std::make_tuple(3, 2))->second == 1);
        assert(distances.find(std::make_tuple(4, 2))->second == 2);
        assert(distances.find(std::make_tuple(0, 3))->second == 3);
        assert(distances.find(std::make_tuple(1, 3))->second == 2);
        assert(distances.find(std::make_tuple(2, 3))->second == 1);
        assert(distances.find(std::make_tuple(3, 3))->second == 2);
        assert(distances.find(std::make_tuple(4, 3))->second == 3);
        assert(distances.find(std::make_tuple(0, 4))->second == 4);
        assert(distances.find(std::make_tuple(1, 4))->second == 3);
        assert(distances.find(std::make_tuple(2, 4))->second == 2);
        assert(distances.find(std::make_tuple(3, 4))->second == 3);
        assert(distances.find(std::make_tuple(4, 4))->second == 4);
    }

    {
        const std::vector<std::vector<MuseumItem>> museum =
        { { MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN },
        { MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN },
        { MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::GUARD, MuseumItem::OPEN, MuseumItem::OPEN },
        { MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN },
        { MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN } };

        LocAndDistMap distances = GetDistances(museum);
        assert(distances.find(std::make_tuple(0, 0)) == distances.end());
        assert(distances.find(std::make_tuple(1, 0)) == distances.end());
        assert(distances.find(std::make_tuple(2, 0)) == distances.end());
        assert(distances.find(std::make_tuple(3, 0)) == distances.end());
        assert(distances.find(std::make_tuple(4, 0)) == distances.end());
        assert(distances.find(std::make_tuple(0, 1)) == distances.end());
        assert(distances.find(std::make_tuple(1, 1)) == distances.end());
        assert(distances.find(std::make_tuple(2, 1)) == distances.end());
        assert(distances.find(std::make_tuple(3, 1)) == distances.end());
        assert(distances.find(std::make_tuple(4, 1)) == distances.end());
        assert(distances.find(std::make_tuple(0, 2))->second == 2);
        assert(distances.find(std::make_tuple(1, 2))->second == 1);
        assert(distances.find(std::make_tuple(2, 2)) == distances.end());
        assert(distances.find(std::make_tuple(3, 2))->second == 1);
        assert(distances.find(std::make_tuple(4, 2))->second == 2);
        assert(distances.find(std::make_tuple(0, 3))->second == 3);
        assert(distances.find(std::make_tuple(1, 3))->second == 2);
        assert(distances.find(std::make_tuple(2, 3))->second == 1);
        assert(distances.find(std::make_tuple(3, 3))->second == 2);
        assert(distances.find(std::make_tuple(4, 3))->second == 3);
        assert(distances.find(std::make_tuple(0, 4))->second == 4);
        assert(distances.find(std::make_tuple(1, 4))->second == 3);
        assert(distances.find(std::make_tuple(2, 4))->second == 2);
        assert(distances.find(std::make_tuple(3, 4))->second == 3);
        assert(distances.find(std::make_tuple(4, 4))->second == 4);
    }

    {
        const std::vector<std::vector<MuseumItem>> museum =
        { { MuseumItem::GUARD, MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::OPEN, MuseumItem::OPEN },
        { MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::OPEN, MuseumItem::OPEN },
        { MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::GUARD, MuseumItem::OPEN },
        { MuseumItem::GUARD, MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::OPEN, MuseumItem::OPEN },
        { MuseumItem::OPEN, MuseumItem::OPEN, MuseumItem::WALL, MuseumItem::OPEN, MuseumItem::OPEN } };

        LocAndDistMap distances = GetDistances(museum);
        assert(distances.find(std::make_tuple(0, 0)) == distances.end());
        assert(distances.find(std::make_tuple(1, 0))->second == 1);
        assert(distances.find(std::make_tuple(2, 0))->second == 1);
        assert(distances.find(std::make_tuple(3, 0)) == distances.end());
        assert(distances.find(std::make_tuple(4, 0))->second == 1);
        assert(distances.find(std::make_tuple(0, 1))->second == 1);
        assert(distances.find(std::make_tuple(1, 1))->second == 2);
        assert(distances.find(std::make_tuple(2, 1))->second == 2);
        assert(distances.find(std::make_tuple(3, 1))->second == 1);
        assert(distances.find(std::make_tuple(4, 1))->second == 2);
        assert(distances.find(std::make_tuple(0, 2)) == distances.end());
        assert(distances.find(std::make_tuple(1, 2)) == distances.end());
        assert(distances.find(std::make_tuple(2, 2))->second == 1);
        assert(distances.find(std::make_tuple(3, 2)) == distances.end());
        assert(distances.find(std::make_tuple(4, 2)) == distances.end());
        assert(distances.find(std::make_tuple(0, 3))->second == 2);
        assert(distances.find(std::make_tuple(1, 3))->second == 1);
        assert(distances.find(std::make_tuple(2, 3)) == distances.end());
        assert(distances.find(std::make_tuple(3, 3))->second == 1);
        assert(distances.find(std::make_tuple(4, 3))->second == 2);
        assert(distances.find(std::make_tuple(0, 4))->second == 3);
        assert(distances.find(std::make_tuple(1, 4))->second == 2);
        assert(distances.find(std::make_tuple(2, 4))->second == 1);
        assert(distances.find(std::make_tuple(3, 4))->second == 2);
        assert(distances.find(std::make_tuple(4, 4))->second == 3);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestGetDistances();
	return 0;
}

