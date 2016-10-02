// MinNumOfSquare_Google.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MinNumOfSquareOp.h"

#include <cmath>

bool IsSquareNum(const size_t val)
{
    const size_t root = sqrt(val);
    return (val - root*root) == 0;
}

bool IsNumOfSquareEqualToX_DP(const size_t val, const size_t x)
{
    if (x == 0) {
        false;
    }

    if (x == 1) {
        return IsSquareNum(val);
    }

    if (x > 0) {
        const size_t ROOT_MAX = sqrt(val);
        for (size_t root = ROOT_MAX; root > 0; --root) {
            if (IsNumOfSquareEqualToX_DP(val - root*root, x - 1)){
                return true;
            }
        }
    }
    return false;
}

size_t MinNumOfSquare_lemma_breadth(const size_t val)
{
    if (val == 0) {
        return 0;
    }

    for (size_t num = 1; num < 4; ++num) {
        if (IsNumOfSquareEqualToX_DP(val, num)) {
            return num;
        }
    }
    
    return 4;
}

size_t MinNumOfSquare_lemma_depth(const size_t val)
{
    if (val == 0) {
        return 0;
    }
    if (IsSquareNum(val)) {
        return 1;
    }

    size_t numOfSquare = 4;
    const size_t ROOT_MAX = sqrt(val);
    for (size_t root = ROOT_MAX; root > 0; --root) {
        if (IsNumOfSquareEqualToX_DP(val - root*root, 1)) {
            return 2;
        }
        else if (IsNumOfSquareEqualToX_DP(val - root*root, 2)) {
            numOfSquare = 3;
        }
    }

    return numOfSquare;
}


#include <cassert>
void TestCases()
{
    assert(MinNumOfSquare_lemma_breadth(0) == 0);
    assert(MinNumOfSquare_lemma_breadth(1) == 1);
    assert(MinNumOfSquare_lemma_breadth(2) == 2);
    assert(MinNumOfSquare_lemma_breadth(3) == 3);
    assert(MinNumOfSquare_lemma_breadth(4) == 1);
    assert(MinNumOfSquare_lemma_breadth(5) == 2);
    assert(MinNumOfSquare_lemma_breadth(6) == 3);
    assert(MinNumOfSquare_lemma_breadth(7) == 4);
    assert(MinNumOfSquare_lemma_breadth(8) == 2);
    assert(MinNumOfSquare_lemma_breadth(9) == 1);
    assert(MinNumOfSquare_lemma_breadth(10) == 2);
    assert(MinNumOfSquare_lemma_breadth(11) == 3);
    assert(MinNumOfSquare_lemma_breadth(12) == 3);
    assert(MinNumOfSquare_lemma_breadth(13) == 2);
    assert(MinNumOfSquare_lemma_breadth(14) == 3);
    assert(MinNumOfSquare_lemma_breadth(15) == 4);
    assert(MinNumOfSquare_lemma_breadth(16) == 1);
    assert(MinNumOfSquare_lemma_breadth(17) == 2);
    assert(MinNumOfSquare_lemma_breadth(18) == 2);
    assert(MinNumOfSquare_lemma_breadth(19) == 3);
    assert(MinNumOfSquare_lemma_breadth(20) == 2);
    assert(MinNumOfSquare_lemma_breadth(21) == 3);
    assert(MinNumOfSquare_lemma_breadth(22) == 3);
    assert(MinNumOfSquare_lemma_breadth(23) == 4);
    assert(MinNumOfSquare_lemma_breadth(24) == 3);
    assert(MinNumOfSquare_lemma_breadth(25) == 1);

    assert(MinNumOfSquare_lemma_depth(0) == 0);
    assert(MinNumOfSquare_lemma_depth(1) == 1);
    assert(MinNumOfSquare_lemma_depth(2) == 2);
    assert(MinNumOfSquare_lemma_depth(3) == 3);
    assert(MinNumOfSquare_lemma_depth(4) == 1);
    assert(MinNumOfSquare_lemma_depth(5) == 2);
    assert(MinNumOfSquare_lemma_depth(6) == 3);
    assert(MinNumOfSquare_lemma_depth(7) == 4);
    assert(MinNumOfSquare_lemma_depth(8) == 2);
    assert(MinNumOfSquare_lemma_depth(9) == 1);
    assert(MinNumOfSquare_lemma_depth(10) == 2);
    assert(MinNumOfSquare_lemma_depth(11) == 3);
    assert(MinNumOfSquare_lemma_depth(12) == 3);
    assert(MinNumOfSquare_lemma_depth(13) == 2);
    assert(MinNumOfSquare_lemma_depth(14) == 3);
    assert(MinNumOfSquare_lemma_depth(15) == 4);
    assert(MinNumOfSquare_lemma_depth(16) == 1);
    assert(MinNumOfSquare_lemma_depth(17) == 2);
    assert(MinNumOfSquare_lemma_depth(18) == 2);
    assert(MinNumOfSquare_lemma_depth(19) == 3);
    assert(MinNumOfSquare_lemma_depth(20) == 2);
    assert(MinNumOfSquare_lemma_depth(21) == 3);
    assert(MinNumOfSquare_lemma_depth(22) == 3);
    assert(MinNumOfSquare_lemma_depth(23) == 4);
    assert(MinNumOfSquare_lemma_depth(24) == 3);
    assert(MinNumOfSquare_lemma_depth(25) == 1);

    {
        MinNumOfSquareOp mns;
        assert(mns(0) == 0);
        assert(mns(1) == 1);
        assert(mns(2) == 2);
        assert(mns(3) == 3);
        assert(mns(4) == 1);
        assert(mns(5) == 2);
        assert(mns(6) == 3);
        assert(mns(7) == 4);
        assert(mns(8) == 2);
        assert(mns(9) == 1);
        assert(mns(10) == 2);
        assert(mns(11) == 3);
        assert(mns(12) == 3);
        assert(mns(13) == 2);
        assert(mns(14) == 3);
        assert(mns(15) == 4);
        assert(mns(16) == 1);
        assert(mns(17) == 2);
        assert(mns(18) == 2);
        assert(mns(19) == 3);
        assert(mns(20) == 2);
        assert(mns(21) == 3);
        assert(mns(22) == 3);
        assert(mns(23) == 4);
        assert(mns(24) == 3);
        assert(mns(25) == 1);
        assert(mns(103) == 4);
    }
}

void MyFoo(int x)
{

}
void Foo(int* x) 
{
    return;
}

#include <vector>
void Foo(std::vector<int>* x)
{
    return;
}

void Bar(int** x)
{
}
/*
void Xyz(int)
{
}*/

void Xyz(std::initializer_list<int> x)
{
}

int _tmain(int argc, _TCHAR* argv[])
{
    //auto x = true ? nullptr : new int(1);
    //auto x = nullptr;
    //MyFoo(static_cast<int>(x));
    //Foo(static_cast<int*>(x));
    //Foo(static_cast<std::vector<int>*>(x));
    //int* y = nullptr;
    // Bar(&x);
    // Bar(static_cast<int**>(&x));
    //Bar(&y);

    //Xyz({ 1 });

    TestCases();
    return 0;
}

/*
overloading on std::initializer_list

*/

/*
1. Problem Decription

2. Analysis
Obviously this is a minization problem and its objective is to find the minimun K that a given numbe can be composed
of the sum of square numbers. Let's consider the bese case and the worse case of K.

Given a number of N, the best case of K will be 1 as N is a square number, which means that there is a interger that
meets the constraint, y= x2, given y = N.

Then what is the worst case of K. The easiest one pops up is that K is equal to N, where the square numbres are "1".
N = 1*1 + 1*! + ... + 1*1. This is of course the theoretical worst case. Can we think of anything better than this worst
case, as this this a miniminzation problem. The better we can narrow down the worst case, the fast the search can go.
Here is one of case can be regards as the worst case.
    - K = 0
    - x = root(N), N' = N - x*x and K increment to 1
    - If N' < 4, K = K + N'
        * If N' is equal to 3, 2, 1 or 0, then their K will be itself.
        * 3 = 1+1+1; 2 = 1+1; 1 = 1; 0 - N is a square number
        * return K (we call this K as K')
    - Else N = N' and repeat last 2 steps

Now let's think how bad this K' can be. Every time we divide N into two parts until N is less or equal to 3. Minically
this process reminds us of the compleixty of binary search, O(log2(N)). But actually we are doing better than O(log2(N)).
Because each time we are picking up the smaller half.
Assume that N is not a square number and exsti i*i < N < (i+1)*(i+1), each time we are picking up N - i*i, which is less
than (i+1)*(i+1) - i*i, as
    - N - i*i < (i+1)*(i+1) - i*i = 2*i + 1 ==> N - i*i < 2*i + 1
    - In the above we always pick N - i*i as the half we are going to repeat the steps
    - Let's compare the two halfs, one is i*i and another is N-(i*i) < 2*i + 1
    - Let's compare with the first half i*i even with the bigger value 2*i + 1.
    - So when i*i is less or equal to 2*i + 1 ==> i*i <= 2*i + 1
    - i*i - 2* + 1 <= 1 + 1 => (i-1)^2 <= 2
    - In the positive range only when i < 1 + root(2) < 3, we have i*i < 2*i+1
    - So as long as i >=3 or N > 9, then we always ahve i*i is more than 2*i + 1
    - Therefore as long as N > 9, i*i is always larger than N - i*i
    - Now we can conclude than K' is ~ log2(N)

Here we have successfully narrnow down the further the worst case can be, from N to K'. What is this telling us? Or how
will this piece of information help the computation complexity. We successfully narrow down the search from [1, N] to 
[1, K']. Any search of K that is higher than K', we can ignore it. Besides we can regard this as a recursive process.
As long as a better K is found (<K'), we could update K' and stop any search which is higer than the constantly updated
K' in the process.

Then what does this K' mean in the serach space? It means that the search depth (searh bredth and search depth I assume
everyone is faimiliar with). For instance given then worst case N,
    - K = 0
    - j = 1, N' = N - j*j = N - 1 and K increment to 1, search depth = 1
    - j = 1 again, N' = N - 1 - j*j = N - 2 and K increment to 2 and search depth = 2
    ......
    - j = 1 again, until N' = N - K' and K increment to K' and search depth = K'
    - Now can stop this seach beause not matter what happen K will be no better than K'

Of course here we considered the worst case. The other seach path is similar. K is increament as each step depth increment.
Stop search when it reach K' and update K' as the search depth is less than it at the point of leaf node. Of course the
search breadth can be optimized as well. When consider j with in [1, i], do we really need to consider j = 1? Not really.
The firt half of j within [i, i/2) is just repeating the search path of [i/2, i].

3. Complexity
Given a number N, it takes constant time if it is a square number. This is the best case that takes O(1) computation and whose
search depth is equal to 1. Let's consider a non-square number. There exits a number i that meets i*i < N < (i+1)*(i+1), where
i is equal to floor(sqrt(N)). 

Base on the above analysis
    - depth = 0; j within [i/2, i], the worst caseof N' = N - (i/2)*(i/2) < (i+1)*(i+i) - i*i/4 = 3/4*(i*i) + 2*i + 1
        = 3/4(i*i + 2*i + 1) + i/2 + 1/4 = 3/4(i+1)*(i+1) + i/2 + 1/4
        Therefor the worse case of N', meets 3/4*(i*i) < N' < 3/4*(i+1)*(i+1) + i/2 +3/4
        The worse case N' is scalar times N.
    - dpeth = 1, the worst case N' is scalar times N. The search breath is still ~ N^(1/2)
    - The search depth is limited to K', therefore the computation complexity is O(N^(1/2*(K'-1))
        Definitely better than O(N^(1/2*(log2(N))))
In the casae of Lemma, K' = 4, then the computation complexity is O(N^(1.5)) and the complexity if O(1).


4. C++ Implementation

*/