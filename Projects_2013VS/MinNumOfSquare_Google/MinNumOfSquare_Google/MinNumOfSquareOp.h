#pragma once

class MinNumOfSquareOp
{
public:
    MinNumOfSquareOp();
    ~MinNumOfSquareOp();

    size_t operator()(const size_t x) const;

private:
    size_t FindTheSearchDepth_DP(const size_t x) const;
    void FindSolutionNotWorseThanK_DP(const size_t x, size_t depth, size_t& k) const;
};
