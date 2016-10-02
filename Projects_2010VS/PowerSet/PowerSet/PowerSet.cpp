// PowerSet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iterator>
#include <vector>

typedef std::vector<int> SET;
typedef std::vector<SET> POWERSET;

void RelationshipOfProblemAndSubproblem(POWERSET& result, int Mn)
{
    size_t len = result.size();
    
    for (size_t i = 0; i < len; ++i) {
        result.push_back(result[i]);
    }
    
    for (size_t i = len; i < result.size(); ++i) {
        SET& curSet = result[i];
        curSet.push_back(Mn);
    }
    result.push_back(SET(1, Mn));
}

void PowerSetR(const SET& s, size_t pos, POWERSET& result)
{
    if (pos == s.size()) {
        return;
    }

    PowerSetR(s, pos + 1, result);
    RelationshipOfProblemAndSubproblem(result, s[pos]);
}

POWERSET PowerSetNR(const SET& s)
{
    POWERSET result;
    
    for (size_t i = 0; i < s.size(); ++i) {
        RelationshipOfProblemAndSubproblem(result, s[i]);
    }

    return result;
}

int _tmain(int argc, _TCHAR* argv[])
{
    SET s;
    s.push_back(1);
    s.push_back(4);
    s.push_back(6);

    POWERSET resultR;
    PowerSetR(s, 0, resultR);

    POWERSET resultNR = PowerSetNR(s);

	return 0;
}

