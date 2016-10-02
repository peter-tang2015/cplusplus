// ScheduleNmettingsKrooms_Amazon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <set>

void ScheduleNmeetingsKrooms(const std::vector<double>& start,
                             const std::vector<double>& end,
                             const size_t kRooms)
{
    if (start.empty() || end.empty() || kRooms == 0) {
        return;
    }

    if (start.size() != end.size()) {
        return;
    }

    std::set<double> LB(start.begin(), start.end());
    //std::set<double> UB(end.begin(), end.end());

    std::vector<size_t> overlaps;
    overlaps.reserve(start.size());
    size_t maxOverlap = 0;
    size_t maxOverlapIdx = 0;

    for (size_t idx = 0; idx < start.size(); ++idx) {
        auto startIt = LB.find(start[idx]);
        ptrdiff_t locStart = std::distance(LB.begin(), startIt);
        auto endIt = LB.lower_bound(end[idx]);
        ptrdiff_t locEnd = std::distance(LB.begin(), endIt);
        size_t overlap = locEnd - locStart;
        overlaps.push_back(overlap);
        if (overlap > maxOverlap) {
            maxOverlap = overlap;
            maxOverlapIdx = idx;
        }
    }

    if (maxOverlap < kRooms) {
        return;
    }
    else {
        
    }
}


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

