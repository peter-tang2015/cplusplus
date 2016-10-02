// FindDifferenecOfAsceondingAndDescendingSequence_Amazon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <exception>
#include <unordered_map>
#include <vector>

class InvalidParamException : public std::exception
{
public:
    InvalidParamException(const std::string & msg)
        : m_msg(msg)
    {}

    const char* what() const {
        return m_msg.c_str();
    }
private:
    const std::string m_msg;
};

struct HashKey
{
    size_t idx;
    size_t remainingSeqLen;

    bool operator==(const HashKey& rhs) const {
        return idx == rhs.idx && remainingSeqLen == rhs.remainingSeqLen;
    }
};

struct HashKeyHashFunc
{
    size_t operator()(const HashKey &key) const {
        return std::hash<size_t>()(key.idx) ^
            std::hash<size_t>()(key.remainingSeqLen);
    }

    bool operator()(const HashKey &lhs, const HashKey &rhs) const {
        return lhs == rhs;
    }
};

using HashMap = std::unordered_map<HashKey, int, HashKeyHashFunc, HashKeyHashFunc>;

template <typename T>
int DetectAscendingOrDescendingSequence(const std::vector<T> &input,
                                        const size_t input_size,
                                        const size_t idx,
                                        const bool isAscending,
                                        size_t m,
                                        HashMap &cacheAscending,
                                        HashMap &cacheDescending)
{
    if (!m) {
        // F(0, r, s, t) return 1
        return 1;
    }

    // Return the cached value if it's a repeated computation
    if (isAscending) {
        auto foundIter = cacheAscending.find(HashKey{ idx, m });
        if (foundIter != cacheAscending.end()) {
            return foundIter->second;
        }
    }
    else {
        auto foundIter = cacheDescending.find(HashKey{ idx, m });
        if (foundIter != cacheDescending.end()) {
            return foundIter->second;
        }
    }

    int numSeq = 0;
    for (size_t i = idx; i <= (input_size - m); ++i) {
        // Continue the sub-problem if sequence's order is maintained
        // Check next available digits if the order is broken
        if ( (isAscending && input[idx - 1] < input[i]) ||
             (!isAscending && input[idx - 1] > input[i])) {
            numSeq += DetectAscendingOrDescendingSequence(input,
                input_size,
                i + 1,
                isAscending,
                m - 1,
                cacheAscending,
                cacheDescending);
        }
    }

    // cache the result
    if (isAscending) {
        cacheAscending.insert(std::make_pair(HashKey{ idx, m }, numSeq));
    }
    else {
        cacheDescending.insert(std::make_pair(HashKey{ idx, m }, numSeq));
    }

    return numSeq;
}

template <typename T>
int GetDiffOfAscendingAndDescedningSequence(const std::vector<T> &input, size_t m)
{
    if (m < 2) {
        throw InvalidParamException("The length of sequence MUST be >= 2.");
    }

    if (input.empty()) {
        throw InvalidParamException("The input array is empty.");
    }

    const size_t INPUT_LEN = input.size();
    if (INPUT_LEN < m) {
        throw InvalidParamException("The length of sequence must be <= the length of input array.");
    }

    int numOfAscending = 0;
    int numOfDescening = 0;
    bool isAscending;
    int temp;
    HashMap CacheAscendingSeq;
    HashMap CacheDescedningSeq;
    for (size_t idx1 = 0; idx1 <= INPUT_LEN - m; ++idx1) {
        for (size_t idx2 = idx1 + 1; idx2 <= (INPUT_LEN - m + 1); ++idx2) {
            // First two digits in the sequence to decide ascending/descending
            isAscending = input[idx1] < input[idx2];
            temp = DetectAscendingOrDescendingSequence(input,
                                                       INPUT_LEN,
                                                       idx2 + 1,
                                                       isAscending,
                                                       m - 2,
                                                       CacheAscendingSeq,
                                                       CacheDescedningSeq);
            if (isAscending) {
                numOfAscending += temp;
            }
            else {
                numOfDescening += temp;
            }
        }
    }

    return numOfAscending - numOfDescening;
}


#include <cassert>
void TestFindDiffOfAscAndDescSeq()
{
    {
        bool exceptionCaught = false;
        try {
            const std::vector<int> input;
            GetDiffOfAscendingAndDescedningSequence(input, 2);
        }
        catch (const InvalidParamException &e) {
            exceptionCaught = true;
        }
        catch (...)
        {
        }
        assert(exceptionCaught == true);

        exceptionCaught = false;
        try {
            const std::vector<int> input = { 1, 2, 3 };
            GetDiffOfAscendingAndDescedningSequence(input, 1);
        }
        catch (const InvalidParamException &e) {
            exceptionCaught = true;
        }
        catch (...)
        {
        }
        assert(exceptionCaught == true);

        exceptionCaught = false;
        try {
            const std::vector<int> input = { 1, 2, 3 };
            GetDiffOfAscendingAndDescedningSequence(input, 4);
        }
        catch (const InvalidParamException &e) {
            exceptionCaught = true;
        }
        catch (...)
        {
        }
        assert(exceptionCaught == true);

        exceptionCaught = false;
        try {
            const std::vector<int> input = { 1, 2, 3 };
            GetDiffOfAscendingAndDescedningSequence(input, 1);
        }
        catch (const InvalidParamException &e) {
            exceptionCaught = true;
        }
        catch (...)
        {
        }
        assert(exceptionCaught == true);
    }
    {
        const std::vector<int> input = { 1, 2, 3, 4, 5, 6, 7, 8 };
        assert(GetDiffOfAscendingAndDescedningSequence(input, 2) == 28);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 3) == 56);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 4) == 70);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 5) == 56);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 6) == 28);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 7) == 8);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 8) == 1);
    }
    {
        const std::vector<int> input = { 8, 7, 6, 5, 4, 3, 2, 1 };
        assert(GetDiffOfAscendingAndDescedningSequence(input, 2) == -28);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 3) == -56);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 4) == -70);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 5) == -56);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 6) == -28);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 7) == -8);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 8) == -1);
    }
    {
        const std::vector<int> input = { 8, 7, 6, 5, 4, 3, 2, 1, 11, 12, 13, 14, 15, 16, 17, 18 };
        assert(GetDiffOfAscendingAndDescedningSequence(input, 2) == 8*8); 
        assert(GetDiffOfAscendingAndDescedningSequence(input, 3) == 8*28); 
        assert(GetDiffOfAscendingAndDescedningSequence(input, 4) == 8*56);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 5) == 8*70);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 6) == 8*56);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 7) == 8*28);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 8) == 8*8);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 9) == 8);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 10) == 0);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 11) == 0);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 12) == 0);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 13) == 0);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 14) == 0);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 15) == 0);
        assert(GetDiffOfAscendingAndDescedningSequence(input, 16) == 0);
    }

}

int _tmain(int argc, _TCHAR* argv[])
{
    TestFindDiffOfAscAndDescSeq();
    return 0;
}

