// SieveOfEratosthenes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>

using namespace std;

vector<size_t> SieveOfEratosthenes(size_t n) 
{
    if (n < 2) {
        return vector<size_t>();
    }

    vector<size_t> result;
    result.reserve(n>>1);
    result.push_back(2);
    vector<size_t> flags((n>>1)- 1, true); // 3, 5, 7    
    size_t p;
    for (size_t i = 0; i < flags.size(); ++i) {
        if (flags[i]){
            p = (i << 1) + 3;
            for (size_t j = p*p; j < n; j+=(2*p)) {
                flags[(j-3) >> 1] = false;
            }
            result.push_back(p);
        }
    }

    return result;
}


void SieveOfEratosthenes(size_t n, vector<size_t>& result) 
{
    result.clear();
    if (n < 2) {
        return;
    }

    vector<size_t> flags((n>>1)- 1, true); // 3, 5, 7    
    size_t p;
    for (size_t i = 0; i < flags.size(); ++i) {
        if (flags[i]){
            p = (i << 1) + 3;
            for (size_t j = p*p; j < n; j+=(2*p)) {
                flags[(j-3) >> 1] = false;
            }
        }
    }

    result.reserve((n>>1) - 1);
    result.push_back(2);
    for (size_t i = 0; i < flags.size(); ++i) {
        if (flags[i]) {
            result.push_back((i<<1) + 3);
        }
    }

}

void SieveOfEratosthenes(size_t start, size_t end, vector<size_t>& result)
{
    
}



int _tmain(int argc, _TCHAR* argv[])
{
    vector<size_t> result = SieveOfEratosthenes(100);
	return 0;
}

