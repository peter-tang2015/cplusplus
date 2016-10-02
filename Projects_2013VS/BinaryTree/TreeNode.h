#pragma once

#include <memory>

template<typename T>
struct TreeNode
{
    TreeNode(const T& d)
    : data(new T(d)), left(nullptr), right(nullptr)
    {}

    TreeNode(const std::shared_ptr<T> &sPtr)
        : data(sPtr), left(nullptr), right(nullptr)
    {}

    ~TreeNode()
    {}

    std::shared_ptr<T> data;
    TreeNode* left;
    TreeNode* right;
};