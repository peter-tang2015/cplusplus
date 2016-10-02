#include "stdafx.h"

#include <string>
#include <unordered_map>

bool ValidStringNumber(const std::string &plainText)
{
    if (plainText.empty()) {
        return false;
    }
    {
        auto itEnd = plainText.end();
        for (auto it = plainText.begin(); it != itEnd; ++it) {
            if (*it > '9' || *it < '0') {
                return false;
            }
        }
    }

    return true;
}

using StringDecoderMap = std::unordered_map<std::string, ptrdiff_t>;

ptrdiff_t StringDecoder_R(const std::string &number, 
                          const std::string::const_iterator curIt,
                          StringDecoderMap& cache)
{
    if (curIt == number.end()) {
        return 1;
    }
    if (*curIt == '0') {
        return -1;
    }
    auto itNext = curIt + 1;
    if (itNext == number.end()) {
        return 1;
    }

    const std::string key(curIt, number.end());
    auto itFound = cache.find(key);
    if (itFound != cache.end()) {
        return itFound->second;
    }

    ptrdiff_t decodes = -1;;
    ptrdiff_t tempCount = StringDecoder_R(number, itNext, cache);
    if (tempCount >= 0) {
        decodes = tempCount;
    }

    const std::string twoChars(curIt, curIt + 2);
    if (atoi(twoChars.c_str()) <= 26) {
        tempCount = StringDecoder_R(number, ++itNext, cache);
        if (tempCount >= 0) {
            if (decodes > 0) {
                decodes += tempCount;
            }
            else {
                decodes = tempCount;
            }
        }
    }

    cache.insert(std::make_pair(key, decodes));
    return decodes;
}

ptrdiff_t StringDecoder(const std::string &number)
{
    if (!ValidStringNumber(number)) {
        return -1;
    }

    StringDecoderMap cacheMap;
    return StringDecoder_R(number, number.begin(), cacheMap);
}

#include <cassert>
void TestDecoder()
{
    assert(StringDecoder("134a457") < 0);
    assert(StringDecoder("100") < 0);
    assert(StringDecoder("12") == 2);
    assert(StringDecoder("123") == 3);
    assert(StringDecoder("0123456789") < 0);
    assert(StringDecoder("10123") == 3);
    assert(StringDecoder("345") == 1);
    assert(StringDecoder("1123") == 5);
    assert(StringDecoder("5123") == 3);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestDecoder();
    return 0;
}

