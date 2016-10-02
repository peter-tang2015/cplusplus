#pragma once

#include "TreeNode.h"

#include <stack>
#include <vector>

template<typename T>
struct TreeConstructionDFS
{
    TreeConstructionDFS()
    {}

    TreeConstructionDFS(TreeNode<T>** n, int s, int e)
        : node(n), start(s), end(e)
    {}

    TreeNode<T>**   node = nullptr;
    int             start = 0;
    int             end = -1;
};

template<typename T>
TreeNode<T>* ConstructTreeOnSortedValueDFS(const std::vector<T>& input)
{
    if (input.empty()) {
        return nullptr;
    }

    const int len = input.size();
    int index = len >> 1;
    TreeNode<T>* root = new TreeNode<T>(input[index]);
    std::stack<TreeConstructionDFS<T>> nodesToBuild;
    nodesToBuild.push(TreeConstructionDFS<T>(&root->left, 0, index - 1));
    nodesToBuild.push(TreeConstructionDFS<T>(&root->right, index + 1, len - 1));

    while (!nodesToBuild.empty()) {
        const TreeConstructionDFS<T>& curCon = nodesToBuild.top();
        if (curCon.start > curCon.end) {
            *(curCon.node) = nullptr;
            nodesToBuild.pop();
        }
        else {
            index = (curCon.start + curCon.end) >> 1;
            TreeNode<T>* tempNode = new TreeNode<T>(input[index]);
            *(curCon.node) = tempNode;

            TreeConstructionDFS<T> left(&tempNode->left,
                curCon.start,
                index - 1);
            TreeConstructionDFS<T> right(&tempNode->right,
                index + 1,
                curCon.end);
            nodesToBuild.pop();
            nodesToBuild.push(left);
            nodesToBuild.push(right);
        }
    }

    return root;
}
