#pragma once

#include "TreeNode.h"

#include <memory>
#include <stack>
#include <vector>

template <typename T>
void PreOrder_R(TreeNode<T>* root, std::vector<std::shared_ptr<T>>& result)
{
    if (root == nullptr) {
        return;
    }

    result.push_back(root->data);
    PreOrder_R(root->left, result);
    PreOrder_R(root->right, result);
}

template <typename T>
std::vector<std::shared_ptr<T>> PreOrder_R(TreeNode<T>* root)
{
    std::vector<std::shared_ptr<T>> result;
    PreOrder_R(root, result);

    return result;
}

template <typename T>
void PreOrder(TreeNode<T>* root, std::vector<std::shared_ptr<T>> &result)
{
    std::stack<TreeNode<T>*> parentStack;
    TreeNode<T>* curNode = root;
    while (!parentStack.empty() || curNode != nullptr) {
        if (curNode != nullptr) {
            result.push_back(curNode->data);
            if (curNode->right != nullptr) {
                parentStack.push(curNode->right);
            }
            curNode = curNode->left;
        }
        else {
            curNode = parentStack.top();
            parentStack.pop();
        }
    }
}

template <typename T>
std::vector<std::shared_ptr<T>> PreOrder(TreeNode<T>* root)
{
    std::vector<std::shared_ptr<T>> result;
    PreOrder(root, result);

    return result;
}

template <typename T>
void InOrder_R(TreeNode<T>* root, std::vector<std::shared_ptr<T>>& result)
{
    if (root == nullptr) {
        return;
    }

    InOrder_R(root->left, result);
    result.push_back(root->data);
    InOrder_R(root->right, result);
}

template <typename T>
std::vector<std::shared_ptr<T>> InOrder_R(TreeNode<T>* root)
{
    std::vector<std::shared_ptr<T>> result;
    InOrder_R(root, result);

    return result;
}

template <typename T>
void InOrder(TreeNode<T>* root, std::vector<std::shared_ptr<T>>& result)
{
    std::stack<TreeNode<T>*> parentStack;
    TreeNode<T>* curNode = root;
    while (!parentStack.empty() || curNode != nullptr) {
        if (curNode != nullptr) {
            parentStack.push(curNode);
            curNode = curNode->left;
        }
        else {
            curNode = parentStack.top();
            parentStack.pop();
            result.push_back(curNode->data);
            curNode = curNode->right;
        }
    }
}

template <typename T>
std::vector<std::shared_ptr<T>> InOrder(TreeNode<T>* root)
{
    std::vector<std::shared_ptr<T>> result;
    InOrder(root, result);

    return result;
}

template <typename T>
void PostOrder_R(TreeNode<T>* root, std::vector<std::shared_ptr<T>>& result)
{
    if (root == nullptr) {
        return;
    }

    PostOrder_R(root->left, result);
    PostOrder_R(root->right, result);
    result.push_back(root->data);
}


template <typename T>
std::vector<std::shared_ptr<T>> PostOrder_R(TreeNode<T>* root)
{
    std::vector<std::shared_ptr<T>> result;
    PostOrder_R(root, result);

    return result;
}

template <typename T>
void PostOrder(TreeNode<T>* root, std::vector<std::shared_ptr<T>>& result)
{
    std::stack<TreeNode<T>*> parentStack;
    TreeNode<T>* lastVisited = nullptr;
    TreeNode<T>* curNode = root;
    TreeNode<T>* tempNode;
    while (!parentStack.empty() || curNode != nullptr) {
        if (curNode != nullptr) {
            parentStack.push(curNode);
            curNode = curNode->left;
        }
        else {
            tempNode = parentStack.top();
            if (tempNode->right != nullptr && lastVisited != tempNode->right) {
                curNode = tempNode->right;
            }
            else {
                result.push_back(tempNode->data);
                lastVisited = tempNode;
                parentStack.pop();
            }
        }
    }
}

template <typename T>
std::vector<std::shared_ptr<T>> PostOrder(TreeNode<T>* root)
{
    std::vector<std::shared_ptr<T>> result;
    PostOrder(root, result);

    return result;
}

template <typename T>
struct DataAndLevel {
    DataAndLevel()
        : data(nullptr)
        , level(0)
    {}
    DataAndLevel(std::shared_ptr<T>& d, size_t l)
        : data(d)
        , level(l)
    {}

    std::shared_ptr<T> data;
    size_t level;
};

template <typename T>
struct TreeNodeAndLevel {
    TreeNodeAndLevel()
        : node(nullptr)
        , level(0)
    {}
    TreeNodeAndLevel(TreeNode<T>* nd, size_t l)
        : node(nd)
        , level(l)
    {}

    TreeNode<T>* node;
    size_t level;
};

template <typename T>
void PreOrderWithLevel_R(TreeNode<T>* root, size_t level, std::vector<DataAndLevel<T>>& result)
{
    if (root == nullptr) {
        return;
    }

    result.push_back(DataAndLevel<T>(root->data, level));
    PreOrderWithLevel_R(root->left, level + 1, result);
    PreOrderWithLevel_R(root->right, level + 1, result);
}

template <typename T>
std::vector<DataAndLevel<T>> PreOrderWithLevel_R(TreeNode<T>* root)
{
    std::vector<DataAndLevel<T>> result;
    PreOrderWithLevel_R(root, 0, result);

    return result;
}

template <typename T>
void PreOrderWithLevel(TreeNode<T>* root, std::vector<DataAndLevel<T>> &result)
{
    std::stack<TreeNodeAndLevel<T>> parentStack;
    TreeNodeAndLevel<T> tnl(root, 0);
    while (!parentStack.empty() || tnl.node != nullptr) {
        if (tnl.node != nullptr) {
            result.push_back(DataAndLevel<T>(tnl.node->data, tnl.level));
            if (tnl.node->right != nullptr) {
                parentStack.push(TreeNodeAndLevel<T>(tnl.node->right, tnl.level + 1));
            }
            tnl.node = tnl.node->left;
            ++tnl.level;
        }
        else {
            tnl = parentStack.top();
            parentStack.pop();
        }
    }
}

template <typename T>
std::vector<DataAndLevel<T>> PreOrderWithLevel(TreeNode<T>* root)
{
    std::vector<DataAndLevel<T>> result;
    PreOrderWithLevel(root, result);

    return result;
}

template <typename T>
void InOrderWithLevel_R(TreeNode<T>* root, size_t level, std::vector<DataAndLevel<T>>& result)
{
    if (root == nullptr) {
        return;
    }

    InOrderWithLevel_R(root->left, level + 1, result);
    result.push_back(DataAndLevel<T>(root->data, level));
    InOrderWithLevel_R(root->right, level + 1, result);
}

template <typename T>
std::vector<DataAndLevel<T>> InOrderWithLevel_R(TreeNode<T>* root)
{
    std::vector<DataAndLevel<T>> result;
    InOrderWithLevel_R(root, 0, result);

    return result;
}

template <typename T>
void InOrderWithLevel(TreeNode<T>* root, std::vector<DataAndLevel<T>>& result)
{
    std::stack<TreeNodeAndLevel<T>> parentStack;
    TreeNodeAndLevel<T> tnl(root, 0);
    while (!parentStack.empty() || tnl.node != nullptr) {
        if (tnl.node != nullptr) {
            parentStack.push(TreeNodeAndLevel<T>(tnl.node, tnl.level));
            tnl.node = tnl.node->left;
            ++tnl.level;
        }
        else {
            tnl = parentStack.top();
            parentStack.pop();
            result.push_back(DataAndLevel<T>(tnl.node->data, tnl.level));
            tnl.node = tnl.node->right;
            ++tnl.level;
        }
    }
}

template <typename T>
std::vector<DataAndLevel<T>> InOrderWithLevel(TreeNode<T>* root)
{
    std::vector<DataAndLevel<T>> result;
    InOrderWithLevel(root, result);

    return result;
}

template <typename T>
void PostOrderWithLevel_R(TreeNode<T>* root, size_t level, std::vector<DataAndLevel<T>>& result)
{
    if (root == nullptr) {
        return;
    }

    PostOrderWithLevel_R(root->left, level + 1, result);
    PostOrderWithLevel_R(root->right, level + 1, result);
    result.push_back(DataAndLevel<T>(root->data, level));
}

template <typename T>
std::vector<DataAndLevel<T>> PostOrderWithLevel_R(TreeNode<T>* root)
{
    std::vector<DataAndLevel<T>> result;
    PostOrderWithLevel_R(root, 0, result);

    return result;
}

template <typename T>
void PostOrderWithLevel(TreeNode<T>* root, std::vector<DataAndLevel<T>>& result)
{
    std::stack<TreeNodeAndLevel<T>> parentStack;
    TreeNode<T>* lastVisited = nullptr;
    TreeNodeAndLevel<T> tnl(root, 0);

    while (!parentStack.empty() || tnl.node != nullptr) {
        if (tnl.node != nullptr) {
            parentStack.push(tnl);
            tnl.node = tnl.node->left;
            ++tnl.level;
        }
        else {
            TreeNodeAndLevel<T>& tempTnl = parentStack.top();
            if (tempTnl.node->right != nullptr && lastVisited != tempTnl.node->right) {
                tnl.node = tempTnl.node->right;
                tnl.level = tempTnl.level + 1;
            }
            else {
                result.push_back(DataAndLevel<T>(tempTnl.node->data, tempTnl.level));
                lastVisited = tempTnl.node;
                parentStack.pop();
            }
        }
    }
}

template <typename T>
std::vector<DataAndLevel<T>> PostOrderWithLevel(TreeNode<T>* root)
{
    std::vector<DataAndLevel<T>> result;
    PostOrderWithLevel(root, result);

    return result;
}
