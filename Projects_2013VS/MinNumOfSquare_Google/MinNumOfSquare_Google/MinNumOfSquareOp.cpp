#include "stdafx.h"
#include "MinNumOfSquareOp.h"

#include <cmath>

MinNumOfSquareOp::MinNumOfSquareOp()
{
}


MinNumOfSquareOp::~MinNumOfSquareOp()
{
}

size_t MinNumOfSquareOp::FindTheSearchDepth_DP(size_t x) const
{
    if (x <= 3) {
        return x;
    }

    const size_t root = sqrt(x);
    return 1 + FindTheSearchDepth_DP(x - root*root);
}

void MinNumOfSquareOp::FindSolutionNotWorseThanK_DP(const size_t x,
                                                    size_t depth,
                                                    size_t& k) const
{
    if (depth >= k) {
        return;
    }

    if (x <= 3) {
        if ((depth + x) < k) {
            k = depth + x;
        }
        return;
    }

    const size_t root = sqrt(x);
    const size_t halfOfRoot = root >> 1;
    for (size_t val = root; val >= halfOfRoot; --val) {
        FindSolutionNotWorseThanK_DP(x - val*val, depth + 1, k);
        if (k == 2) {
            return;
        }
    }
}

size_t MinNumOfSquareOp::operator()(size_t x) const
{
    //size_t k = FindTheSearchDepth_DP(x);
    size_t k = 4;
    if (k <= 2) {
        return k;
    }

    FindSolutionNotWorseThanK_DP(x, 0, k);
    return k;
}