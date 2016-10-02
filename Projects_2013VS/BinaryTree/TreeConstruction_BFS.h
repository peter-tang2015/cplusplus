#pragma once

#include "TreeNode.h"

#include <queue>
#include <vector>

template<typename T>
struct TreeConstructionBFS
{
    TreeConstructionBFS()
    {}

    TreeConstructionBFS(TreeNode<T>* p, bool left, int s, int e)
        : parent(p), isLeftChild(left), start(s), end(e)
    {}

    TreeNode<T>*    parent = nullptr;
    bool            isLeftChild = false;
    int             start = 0;
    int             end = -1;
};

template<typename T>
TreeNode<T>* ConstructTreeOnSortedValueBFS(const std::vector<T>& input)
{
    if (input.empty()) {
        return nullptr;
    }

    const int len = input.size();
    int index = len >> 1;
    TreeNode<T>* root = new TreeNode<T>(input[index]);
    std::queue<TreeConstructionBFS<T>> nodesToBuild;
    nodesToBuild.push(TreeConstructionBFS<T>(root, true, 0, index - 1));
    nodesToBuild.push(TreeConstructionBFS<T>(root, false, index + 1, len - 1));

    while (!nodesToBuild.empty()) {
        const TreeConstructionBFS<T>& curCon = nodesToBuild.front();
        if (curCon.start > curCon.end) {
            if (curCon.isLeftChild) {
                curCon.parent->left = nullptr;
            }
            else {
                curCon.parent->right = nullptr;
            }
        }
        else {
            index = (curCon.start + curCon.end) >> 1;
            TreeNode<T>* tempNode = new TreeNode<T>(input[index]);
            if (curCon.isLeftChild) {
                curCon.parent->left = tempNode;
            }
            else {
                curCon.parent->right = tempNode;
            }

            nodesToBuild.push(TreeConstructionBFS<T>(tempNode,
                true,
                curCon.start,
                index - 1));
            nodesToBuild.push(TreeConstructionBFS<T>(tempNode,
                false,
                index + 1,
                curCon.end));
        }
        nodesToBuild.pop();
    }

    return root;
}
