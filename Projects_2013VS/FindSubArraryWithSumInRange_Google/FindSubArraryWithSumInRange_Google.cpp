// FindSubArraryWithSumInRange_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <set>
#include <tuple>
#include <vector>

struct SumAndEndIndex{
    SumAndEndIndex()
        : sum(0.0)
        , index(0)
    {}
    SumAndEndIndex(const double s, const size_t i)
        : sum(s)
        , index(i)
    {}
    double sum;
    size_t index;
};

struct SumAndEndIndexCmpLess
{
    bool operator()(const SumAndEndIndex *lhs,
                    const SumAndEndIndex *rhs) const
    {
        return lhs->sum < rhs->sum ||
            (lhs->sum == rhs->sum && lhs->index < rhs->index);
    }
};

using SumAndEndIndexVec = std::vector<SumAndEndIndex>;
using SumAndEndIndexSet = std::set<const SumAndEndIndex*, SumAndEndIndexCmpLess>;

void CreateSumAndEndIndexVec(const std::vector<double> &input,
                             SumAndEndIndexVec &seiv)
{
    if (input.empty()) {
        SumAndEndIndexVec().swap(seiv);
        return;
    }
    SumAndEndIndexVec tempVec;
    tempVec.reserve(input.size());
    auto itEnd = input.cend();
    double sum = 0;
    size_t index = 0;
    for (auto it = input.cbegin(); it != itEnd; ++it, ++index) {
        sum = sum + *it;
        tempVec.push_back(SumAndEndIndex(sum, index));
    }
    tempVec.swap(seiv);
}

using PairResultVect = std::vector<std::tuple<size_t, size_t>>;
PairResultVect FindSubArrayWithSumInRange(const std::vector<double> &input,
                                          const double lowerBound,
                                          const double upperBound,
                                          const SumAndEndIndexVec &sumAndIndexVec,
                                          SumAndEndIndexSet &sortedSumAndIndices)
{
    PairResultVect result;
    auto itEnd = input.cend();
    SumAndEndIndex seiLB(lowerBound, 0);
    SumAndEndIndex seiUB(upperBound, input.size());
    size_t startIndex = 0;
    auto itVec = sumAndIndexVec.cbegin();
    for (auto it = input.cbegin(); it != itEnd; ++it, ++startIndex, ++itVec) {
        auto lbIt = sortedSumAndIndices.lower_bound(&seiLB);
        auto ubIt = sortedSumAndIndices.upper_bound(&seiUB);
        for (auto foundIt = lbIt; foundIt != ubIt; ++foundIt) {
            result.push_back(std::make_tuple(startIndex, (*foundIt)->index));
        }
        seiLB.sum += *it;
        seiUB.sum += *it;
        sortedSumAndIndices.erase(&(*itVec));
    }

    return result;
}

PairResultVect FindSubArrayWithSumInRange(const std::vector<double> &input,
                                          const double lowerBound,
                                          const double upperBound)
{
    if (input.empty() || lowerBound > upperBound) {
        return PairResultVect();
    }
    SumAndEndIndexVec sumAndIndexVec;
    CreateSumAndEndIndexVec(input, sumAndIndexVec);
    SumAndEndIndexSet sortedSumAndIndices;
    auto itEnd = sumAndIndexVec.cend();
    for (auto it = sumAndIndexVec.cbegin(); it != itEnd; ++it) {
        sortedSumAndIndices.insert(&(*it));
    }

    return FindSubArrayWithSumInRange(input,
                                      lowerBound,
                                      upperBound,
                                      sumAndIndexVec,
                                      sortedSumAndIndices);
}


#include <cassert>
void Test_FindSubArrayWithSumInRange()
{
    PairResultVect result;
    {
        const std::vector<double> input;
        result = FindSubArrayWithSumInRange(input, 0, 1);
        assert(result.empty() == true);
    }
    {
        const std::vector<double> input = { 1.0, 2.0, 3.0, 4.0,
                                            5.0, 6.0, 7.0, 8.0,
                                            9.0, 10.0 };
        result = FindSubArrayWithSumInRange(input, 20, 15);
        assert(result.empty() == true);
        result = FindSubArrayWithSumInRange(input, -10, 0);
        assert(result.empty() == true);
        result = FindSubArrayWithSumInRange(input, 15.0, 20.0);
        assert(result.size() == 8);
    }
    {
        const std::vector<double> input = {-1, 1, -1, 1, -1, 1};
        result = FindSubArrayWithSumInRange(input, -1, 1);
        assert(result.size() == 21);
    }
}

#include <iostream>
struct Base{

    ~Base() {
        std::cout << "~Base" << std::endl;
    }
};

struct Derived : public Base {
    ~Derived() {
        std::cout << "~Derived" << std::endl;
    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    Test_FindSubArrayWithSumInRange();

    {
        Base *bPtr = new Derived();
        delete bPtr;
    }
    return 0;
}
