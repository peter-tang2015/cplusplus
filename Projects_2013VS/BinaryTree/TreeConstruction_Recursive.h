#pragma once

#include "TreeNode.h"

#include <vector>

template<typename T>
void ConstructTreeRecursive(const std::vector<T>& input,
    int startIndex,
    int endIndex,
    TreeNode<T>** node)
{
    if (startIndex > endIndex) {
        *node = nullptr;
        return;
    }

    const int curIndex = (startIndex + endIndex) >> 1;
    *node = new TreeNode<T>(input[curIndex]);
    ConstructTreeRecursive(input,
        startIndex,
        curIndex - 1,
        &(*node)->left);
    ConstructTreeRecursive(input,
        curIndex + 1,
        endIndex,
        &(*node)->right);
}

template<typename T>
TreeNode<T>* ConstructTreeRecursive(const std::vector<T>& input)
{
    if (input.empty()) {
        return nullptr;
    }

    TreeNode<T>* root = nullptr;
    ConstructTreeRecursive(input, 0, input.size() - 1, &root);
    return root;
}
