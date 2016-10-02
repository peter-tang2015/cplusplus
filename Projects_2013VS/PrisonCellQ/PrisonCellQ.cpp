// PrisonCellQ.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <unordered_map>
#include <vector>

struct PrisonCellKey
{
    PrisonCellKey(const std::vector<size_t> &c,
                  const std::vector<size_t> &r)
        : cells(c)
        , releases(r)
    {}
    std::vector<size_t> cells;
    std::vector<size_t> releases;

    bool operator==(const PrisonCellKey& rhs) const {
        return cells == rhs.cells && releases == rhs.releases;
    }
};

size_t SizetVectorHash(const std::vector<size_t> &input)
{
    size_t hash = 0;
    for (auto it = input.begin(); it != input.end(); ++it) {
        hash = hash^std::hash<size_t>()(*it);
    }

    return hash;
}

struct PrisionCellHashFunc
{
    const static size_t PrimeOfCells = 2909;
    const static size_t PrimeOfReleases = 4021;

    size_t operator()(const PrisonCellKey &key) const {
        size_t cellsHash = SizetVectorHash(key.cells);
        size_t releasesHash = SizetVectorHash(key.releases);

        return std::hash<size_t>()(
            cellsHash*PrimeOfCells + releasesHash*PrimeOfReleases);
    }

    bool operator()(const PrisonCellKey &lhs, const PrisonCellKey &rhs) const {
        return lhs.operator==(rhs);
    }

};

using PrisonCellHashMap = std::unordered_map<PrisonCellKey, size_t, PrisionCellHashFunc, PrisionCellHashFunc>;

size_t MinCostOfReleasingCells_R(const std::vector<size_t> &cells,
                               const std::vector<size_t> &toRelease,
                               PrisonCellHashMap &cache)
{
    const size_t NRelease = toRelease.size();
    if (NRelease == 0) {
        return 0;
    }
    else if (NRelease == 1) {
        return cells.size() - 1;
    }

    const PrisonCellKey key(cells, toRelease);
    auto it = cache.find(key);
    if (it != cache.end()) {
        return it->second;
    }
    const size_t NCells = cells.size();
    auto itEnd = toRelease.end();
    size_t minCost = -1;
    size_t tempCost;
    for (auto it = toRelease.begin(); it != itEnd; ++it) {
        tempCost = NCells - 1;
        {
            auto tmpIt = cells.begin();
            std::advance(tmpIt, *it);
            std::vector<size_t> LeftCells(cells.begin(), tmpIt);
            std::vector<size_t> LeftToRelease(toRelease.begin(), it);
            tempCost += MinCostOfReleasingCells_R(LeftCells, LeftToRelease, cache);
        }
        {
            std::vector<size_t> RightCells;
            for (int i = *it + 1; i < NCells; ++i) {
                RightCells.push_back(i - *it - 1);
            }
            std::vector<size_t> RightToRelease;
            for (auto tmpIt = it + 1; tmpIt != toRelease.end(); ++tmpIt) {
                RightToRelease.push_back(*tmpIt - *it - 1);
            }
            tempCost += MinCostOfReleasingCells_R(RightCells, RightToRelease, cache);
        }
        if (tempCost < minCost) {
            minCost = tempCost;
        }
    }

    cache.insert(std::make_pair(key, minCost));

    return minCost;
}

size_t MinCostOfReleasingCells(const std::vector<size_t> &cells,
                               const std::vector<size_t> &toRelease)
{
    PrisonCellHashMap cache;
    return MinCostOfReleasingCells_R(cells, toRelease, cache);
}

#include <cassert>
void TestPrisionCellQ()
{
    const std::vector<size_t> cells = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    {
        const std::vector<size_t> releases = { 1 };
        assert(MinCostOfReleasingCells(cells, releases) == 8);
    }
    {
        const std::vector<size_t> releases = { 8 };
        assert(MinCostOfReleasingCells(cells, releases) == 8);
    }
    {
        const std::vector<size_t> releases = { 1, 6 };
        assert(MinCostOfReleasingCells(cells, releases) == 13);
    }
    {
        const std::vector<size_t> releases = { 1, 3 };
        assert(MinCostOfReleasingCells(cells, releases) == 10);
    }
    {
        const std::vector<size_t> releases = { 1, 3, 8 };
        assert(MinCostOfReleasingCells(cells, releases) == 14);
    }
    {
        const std::vector<size_t> releases = { 1, 3, 5 };
        assert(MinCostOfReleasingCells(cells, releases) == 14);
    }
    {
        const std::vector<size_t> releases = { 3, 4, 5 };
        assert(MinCostOfReleasingCells(cells, releases) == 12);
    }
    {
        const std::vector<size_t> releases = { 3, 4, 5, 8 };
        assert(MinCostOfReleasingCells(cells, releases) == 14);
    }
    {
        const std::vector<size_t> releases = { 0, 3, 4, 5, 8 };
        assert(MinCostOfReleasingCells(cells, releases) == 16);
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestPrisionCellQ();
	return 0;
}
