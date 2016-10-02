// FindWordLadder_Amazon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <queue>
#include <map>
#include <stack>
#include <set>
#include <string>
#include <vector>

using GraphMap = std::map<std::string, std::vector<std::string>>;

GraphMap BuildGraphMap(const std::vector<std::string>& words)
{

}

std::stack<std::string> FidWordLadder(const GraphMap& gm,
                                      const std::string& start,
                                      const std::string& end)
{
    std::stack<std::string> path;
    if (gm.empty()) {
        return path;
    }

    std::set<std::string> visited;
    std::queue<std::string> toVisit;

    toVisit.push(start);
    while (!toVisit.empty()) {
        auto& top = toVisit.front();
        auto iter = gm.find(top);
        if (iter != gm.end()) {
            if (iter->first == end) {
                // found here
            }
            else {
                const std::vector<std::string>& children = iter->second;
                for (auto& x : children) {
                    if (x == end) {
                        // found here
                    }
                    else {
                        visited.
                    }
                }
            }
        }

    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    const std::vector<std::string> words =
        {"FOOL", "BOOL", "POOL",
         "POOR", "POLL", "POLE", "PULL", "POLA", "POLA",
         "PALE", "PALL", "GALE", "SALE", "HALE", "SAGE",
         "GAGE", "SAGA", }
    return 0;
}


/*
3
5
7
---
9
5, 15
7, 21
---
9

*/