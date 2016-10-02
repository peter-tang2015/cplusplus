// FindPathGivenSumInTree_Amazion.cpp : Defines the entry point for the console application.
//

// http://www.hawstein.com/posts/ctci-solutions-contents.html
// http://www.careercup.com/question?id=5709839151923200
// http://www.careercup.com/question?id=5192167330938880
// http://www.careercup.com/question?id=5647266494808064
// http://www.careercup.com/question?id=5639359996887040
// http://www.careercup.com/question?id=5752929803829248

/*
Comparing with normal tree traversal via BFS and DFS. The only thing need to do for this problem is to take push the sum (from root to its parent node) into the stack or queue. As traversing through the tree, compare this sum plus its own value against the given SUM. If equal, then found a path. Otherwise no.

Here is the implementation: cpluspluslearning-petert.blogspot.co.uk/2015/07/data-structure-and-algorithm-find-tree.html
*/

// http://www.careercup.com/question?id=4918286745600000
#include "stdafx.h"

#include <queue>
#include <stack>

struct TreeNode
{
    int value;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
};

struct NodeSumPair
{
    TreeNode* node;
    size_t    sum;
    NodeSumPair(TreeNode* curNode, size_t curSum)
        : node(curNode)
        , sum(curSum)
    {}
};

std::vector<TreeNode*> FindNumOfPathsDFS(TreeNode* root, size_t sum)
{
    std::stack<NodeSumPair> curStack;
    size_t curSum = 0;
    curStack.push(NodeSumPair(root, curSum));
    std::vector<TreeNode*> result;
    while (!curStack.empty()) {
        const NodeSumPair& curPair = curStack.top();
        if (curPair.node) {
            curSum = curPair.sum + curPair.node->value;
            if (curSum == sum) {
                result.push_back(curPair.node);
            }

            curStack.push(NodeSumPair(curPair.node->right, curSum));
            curStack.push(NodeSumPair(curPair.node->left, curSum));
        }
        curStack.pop();
    }

    return result;
}

std::vector<TreeNode*> FindNumOfPathsBFS(TreeNode* root, size_t sum)
{
    std::queue<NodeSumPair> curQueue;
    size_t curSum = 0;
    curQueue.push(NodeSumPair(root, curSum));
    std::vector<TreeNode*> result;
    while (!curQueue.empty()) {
        NodeSumPair curPair = curQueue.front();
        if (curPair.node) {
            curSum = curPair.sum + curPair.node->value;
            if (curSum == sum) {
                result.push_back(curPair.node);
            }

            curQueue.push(NodeSumPair(curPair.node->left, curSum));
            curQueue.push(NodeSumPair(curPair.node->right, curSum));
        }
        curQueue.pop();
    }
    
    return result;
}

int count_one(unsigned int x){
    // x = 11110000
    // 11110000 + 08888000&55555555 = 11110000
    x = (x & (0x55555555)) + ((x >> 1) & (0x55555555));
    // 11110000 + 04444000&55555555 = 11110000
    x = (x & (0x33333333)) + ((x >> 2) & (0x33333333));
    x = (x & (0x0f0f0f0f)) + ((x >> 4) & (0x0f0f0f0f));//02020000
    x = (x & (0x00ff00ff)) + ((x >> 8) & (0x00ff00ff));//00040000
    x = (x & (0x0000ffff)) + ((x >> 16) & (0x0000ffff));//00000004
    return x;
}

#include <cassert>
int _tmain(int argc, _TCHAR* argv[])
{
    TreeNode* root = nullptr;
    assert(FindNumOfPathsBFS(root, 1).empty() == true);
    assert(FindNumOfPathsDFS(root, 1).empty() == true);

    //count_one(0x11110000);
    //count_one(0x55555555);
    count_one(0xffffffff);

	return 0;
}

