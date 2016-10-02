#pragma once

#include "TreeNode.h"

#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

// delete node top-down
template<typename T>
void DeleteTree_TD(TreeNode<T>** root)
{
    TreeNode<T>* curNode = *root;
    if (curNode != nullptr) {
        TreeNode<T>* left = curNode->left;
        TreeNode<T>* right = curNode->right;
        delete curNode;
        curNode = nullptr;
        DeleteTree_TD(&left);
        DeleteTree_TD(&right);
    }
}


// delete nodes bottom-up
template<typename T>
void DeleteTree_BU(TreeNode<T> **root)
{
    TreeNode<T>* curNode = *root;
    if (!curNode->left && !curNode->right) {
        delete curNode;
        *root = nullptr;
        return;
    }

    if (curNode->left) {
        DeleteTree_BU(&curNode->left);
    }
    if (curNode->right) {
        DeleteTree_BU(&curNode->right);
    }
    delete curNode;
    *root = nullptr;
}


template <typename T>
size_t GetTreeSize_R(TreeNode<T>* root)
{
    if (root == nullptr) {
        return 0;
    }
    return 1 + GetTreeSize_R(root->left) + GetTreeSize_R(root->right);
}

template<typename T>
bool FindPath(TreeNode<T>* root, const T& val, std::stack<TreeNode<T>*>& path)
{
    TreeNode<T>* curNode = root;
    std::stack<TreeNode<T>*> result;
    bool found = false;
    while (curNode != nullptr) {
        result.push(curNode);

        const T& curVal = *curNode->data.get();
        if (curVal == val) {
            found = true;
            break;
        }
        if (curVal > val) {
            if (curNode->left == nullptr) {
                break;
            }
            curNode = curNode->left;
        }
        else {
            if (curNode->right == nullptr) {
                break;
            }
            curNode = curNode->right;
        }

    }
    if (found) {
        path.swap(result);
    }

    return found;
}

template <typename T>
TreeNode<T>* FindLeftestNode(TreeNode<T>* root)
{
    if (root == nullptr) {
        return nullptr;
    }
    TreeNode<T>* curNode = root;
    while (curNode->left != nullptr) {
        curNode = curNode->left;
    }

    return curNode;
}

template <typename T>
TreeNode<T>* FindRightestNode(TreeNode<T>* root)
{
    if (root == nullptr) {
        return nullptr;
    }

    TreeNode<T>* curNode = root;
    while (curNode->right != nullptr) {
        curNode = curNode->right;
    }

    return curNode;
}

template<typename T>
std::shared_ptr<T> NextInOrder(TreeNode<T>* root, const T& val)
{
    std::stack<TreeNode<T>*> path;
    if (!FindPath(root, val, path)) {
        return std::shared_ptr<T>();
    }

    TreeNode<T>* curNode = path.top();
    assert(*curNode->data.get() == val);
    if (curNode->right != nullptr) {
        auto leftest = FindLeftestNode(curNode->right);
        return leftest->data;
    }

    path.pop();
    TreeNode<T>* parentNode;
    while (!path.empty())
    {
        parentNode = path.top();
        if (parentNode->left == curNode) {
            return parentNode->data;
        }

        curNode = parentNode;
        path.pop();
    }

    return std::shared_ptr<T>();
}

template<typename T>
void GetSumOfEachLevelOfTree(TreeNode<T>* root, std::vector<T>& listOfLL)
{
    if (root == nullptr) {
        return;
    }

    std::queue<TreeNode<T>*> nodes;
    nodes.push(root);
    nodes.push(nullptr); // dummy node
    T sum(0);
    while (!nodes.empty()) {
        const TreeNode<T>* curNode = nodes.front();
        nodes.pop();
        if (curNode == nullptr) {
            listOfLL.push_back(sum);
            sum = 0;
            if (nodes.empty()) {
                break;
            }
            nodes.push(nullptr);
        }
        else {
            sum += *curNode->data;
            if (curNode->left != nullptr) {
                nodes.push(curNode->left);
            }
            if (curNode->right != nullptr) {
                nodes.push(curNode->right);
            }
        }
    }
}

template<typename T>
void GetFirstAndLastOfEachLevelOfTree(TreeNode<T>* root,
    std::vector<TreeNode<T>*>& listOfFL)
{
    if (root == nullptr) {
        return;
    }

    std::queue<TreeNode<T>*> nodes;
    nodes.push(root);
    nodes.push(nullptr); // dummy node
    TreeNode<T>* first;
    TreeNode<T>* prev = nullptr;
    while (!nodes.empty()) {
        TreeNode<T>* curNode = nodes.front();
        nodes.pop();
        if (curNode == nullptr) {
            listOfFL.push_back(first);
            if (prev != first) {
                listOfFL.push_back(prev);
            }
            if (nodes.empty()) {
                break;
            }
            nodes.push(nullptr);
        }
        else {
            if (prev == nullptr) {
                first = curNode;
            }

            if (curNode->left != nullptr) {
                nodes.push(curNode->left);
            }
            if (curNode->right != nullptr) {
                nodes.push(curNode->right);
            }
        }
        prev = curNode;
    }
}

template<typename T>
void GetUniqueElementsOfTree(const TreeNode<T>* tree,
    std::unordered_map<T, bool>& values)
{
    if (tree == nullptr) {
        return;
    }

    if (values.find(*tree->data) == values.end()) {
        values[*tree->data] = false;
    }

    GetUniqueElementsOfTree(tree->left, values);
    GetUniqueElementsOfTree(tree->right, values);
}

template<typename T>
bool CheckTreeAgainstValues(const TreeNode<T>* tree,
    std::unordered_map<T, bool>& values)
{
    if (tree == nullptr) {
        return true;
    }

    if (values.find(*tree->data) == values.end()) {
        return false;
    }
    else {
        values[*tree->data] = true;
    }

    bool result = CheckTreeAgainstValues(tree->left, values);
    if (result) {
        result = CheckTreeAgainstValues(tree->right, values);
    }

    return result;
}

template<typename T>
bool CheckTwoTreesWithSameValues(const TreeNode<T>* left, const TreeNode<T>* right)
{
    using HashMap = std::unordered_map<T, bool>;
    HashMap leftValues;
    GetUniqueElementsOfTree(left, leftValues);

    if (CheckTreeAgainstValues(right, leftValues)) {
        auto iterEnd = leftValues.end();
        for (auto iter = leftValues.begin(); iter != iterEnd; ++iter)
        {
            if (!iter->second) {
                return false;
            }
        }

        return true;
    }

    return false;
}

template<typename T>
bool CompareTwoTrees_R(TreeNode<T>* lhs, TreeNode<T>* rhs)
{
    if (lhs == nullptr && rhs == nullptr) {
        return true;
    }
    if ((lhs == nullptr || rhs == nullptr) ||
        *lhs->data != *rhs->data) {
        return false;
    }

    return CompareTwoTrees_R(lhs->left, rhs->left) ||
           CompareTwoTrees_R(lhs->right, rhs->right);
}

template <typename T>
bool ContainSubTree_R(TreeNode<T> *base,
                      TreeNode<T>* sub,
                      TreeNode<T>* &entry1,
                      TreeNode<T>* &entry2)
{
    if (base == nullptr || sub == nullptr) {
        return false;
    }
    if (CompareTwoTrees_R(base, sub)) {
        entry1 = base;
        entry2 = sub;
        return true;
    }
    return ContainSubTree_R(base->left, sub, entry1, entry2) ||
           ContainSubTree_R(base->right, sub, entry1, entry2);
}

template <typename T>
bool MoreThanNNodes_R(TreeNode<T>* root, const size_t N, size_t &curSize)
{
    if (curSize > N) {
        return true;
    }
    if (!root) {
        return false;
    }

    ++curSize;
    return MoreThanNNodes_R(root->left, N, curSize) ||
           MoreThanNNodes_R(root->right, N, curSize);
}

template <typename T>
bool MoreThanNNodes_R(TreeNode<T>* root, const size_t N)
{
    size_t curSize = 0;
    return MoreThanNNodes_R(root, N, curSize);
}

template <typename T>
bool FindCommonTree_R(TreeNode<T>* base1,
                      TreeNode<T>* base2,
                      TreeNode<T>* &entry1,
                      TreeNode<T>* &entry2)
{
    if (!MoreThanNNodes_R(base1, 2) || !MoreThanNNodes_R(base2, 2)) {
        return false;
    }
    return ContainSubTree_R(base1, base2, entry1, entry2) ||
           FindCommonTree_R(base1, base2->left, entry1, entry2) ||
           FindCommonTree_R(base1, base2->right, entry1, entry2);
}

template <typename T>
bool HaveDuplicateSubTree_R(TreeNode<T> *root, TreeNode<T>* &entry1, TreeNode<T>* &entry2)
{
    if (root == nullptr) {
        return false;
    }

    return FindCommonTree_R(root->left, root->right, entry1, entry2) ||
           HaveDuplicateSubTree_R(root->left, entry1, entry2) ||
           HaveDuplicateSubTree_R(root->right, entry1, entry2);
}

template <typename T>
size_t CalculateHashMapOfTree_R(TreeNode<T>* root,
    std::unordered_map<size_t, std::unordered_set<TreeNode<T>*>> &hm)
{
    const size_t PrimeOfCurNode = 1009;
    const size_t PrimeOfLeftNode = 2909;
    const size_t PrimeOfRightNode = 4021;
    if (!root) {
        return 0;
    }

    size_t hashKey = *root->data * PrimeOfCurNode;
    if (root->left) {
        hashKey += PrimeOfLeftNode * CalculateHashMapOfTree_R(root->left, hm);
    }
    if (root->right) {
        hashKey += PrimeOfRightNode * CalculateHashMapOfTree_R(root->right, hm);
    }

    size_t hashValue = std::hash<size_t>{}(hashKey);
    auto foundIt = hm.find(hashValue);
    if (foundIt == hm.end()) {
        std::unordered_set<TreeNode<T>*> entry;
        entry.insert(root);
        hm.insert(std::make_pair(hashValue, entry));
    }
    else {
        std::unordered_set<TreeNode<T>*>& refEntry = foundIt->second;
        if (refEntry.find(root) == refEntry.end()) {
            refEntry.insert(root);
        }
    }
    return hashValue;
}

template <typename T>
bool FindDuplicateTreeInEntries(const std::unordered_set<TreeNode<T>*> entries,
                                TreeNode<T>* &entry1,
                                TreeNode<T>* &entry2)
{
    auto itEnd = entries.end();
    for (auto it = entries.begin(); it != itEnd; ++it) {
        auto itInner = it;
        ++itInner;
        for (; itInner != itEnd; ++itInner) {
            if (MoreThanNNodes_R(*it, 2) && 
                MoreThanNNodes_R(*itInner, 2) && 
                CompareTwoTrees_R(*it, *itInner)) {
                entry1 = *it;
                entry2 = *itInner;
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool HaveDuplicateSubTree2_R(TreeNode<T> *root, TreeNode<T>* &entry1, TreeNode<T>* &entry2)
{
    std::unordered_map<size_t, std::unordered_set<TreeNode<T>*>> nodeHM;
    CalculateHashMapOfTree_R(root, nodeHM);
    auto itEnd = nodeHM.end();
    for (auto it = nodeHM.begin(); it != itEnd; ++it) {
        std::unordered_set<TreeNode<T>*>& entryRef = it->second;
        if (FindDuplicateTreeInEntries(entryRef, entry1, entry2)) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool FindDuplicateTreeInEntries(const std::unordered_set<TreeNode<T>*> entries,
                                TreeNode<T>* refEntry,
                                TreeNode<T>* &entry1,
                                TreeNode<T>* &entry2)
{
    if (!MoreThanNNodes_R(refEntry, 2)) {
        return false;
    }
    auto itEnd = entries.end();
    for (auto it = entries.begin(); it != itEnd; ++it) {
        if (MoreThanNNodes_R(*it, 2) && CompareTwoTrees_R(*it, refEntry)) {
            entry1 = *it;
            entry2 = refEntry;
            return true;
        }
    }

    return false;
}

template <typename T>
size_t CalculateHashMapAndFindSubTree_R(TreeNode<T>* root,
    std::unordered_map<size_t, std::unordered_set<TreeNode<T>*>> &hm,
    TreeNode<T>* &entry1,
    TreeNode<T>* &entry2,
    bool &found)
{
    const size_t PrimeOfCurNode = 1009;
    const size_t PrimeOfLeftNode = 2909;
    const size_t PrimeOfRightNode = 4021;
    if (!root || found) {
        return 0;
    }

    size_t hashKey = *root->data * PrimeOfCurNode;
    if (root->left) {
        hashKey += PrimeOfLeftNode * CalculateHashMapAndFindSubTree_R(root->left,
                                                                      hm,
                                                                      entry1,
                                                                      entry2,
                                                                      found);
    }
    if (!found && root->right) {
        hashKey += PrimeOfRightNode * CalculateHashMapAndFindSubTree_R(root->right,
                                                                       hm,
                                                                       entry1,
                                                                       entry2,
                                                                       found);
    }
    if (!found) {
        size_t hashValue = std::hash<size_t>{}(hashKey);
        auto foundIt = hm.find(hashValue);
        if (foundIt == hm.end()) {
            std::unordered_set<TreeNode<T>*> entry;
            entry.insert(root);
            hm.insert(std::make_pair(hashValue, entry));
        }
        else {
            std::unordered_set<TreeNode<T>*>& refEntry = foundIt->second;
            if (refEntry.find(root) == refEntry.end()) {
                found = FindDuplicateTreeInEntries(refEntry, root, entry1, entry2);
                if (!found) {
                    refEntry.insert(root);
                }
            }
        }
        return hashValue;
    }
    return 0;
}

template <typename T>
bool HaveDuplicateSubTree3_R(TreeNode<T> *root, TreeNode<T>* &entry1, TreeNode<T>* &entry2)
{
    std::unordered_map<size_t, std::unordered_set<TreeNode<T>*>> nodeHM;
    bool found = false;
    CalculateHashMapAndFindSubTree_R(root, nodeHM, entry1, entry2, found);
    return found;
}

template <typename T>
TreeNode<T>* FindClosetNode_R_Internal(TreeNode<T> *root, 
                                       const T& val,
                                       TreeNode<T>* lowerBound,
                                       TreeNode<T>* upperBound)
{
    if (!root) {
        if (lowerBound && upperBound) {
            // TODO: To cope other T type, implement a its own "closest" function
            T toLowerBound = abs(val - *lowerBound->data);
            T toUpperBound = abs(*upperBound->data - val);
            return toLowerBound <= toUpperBound ? lowerBound : upperBound;
        }
        else if (lowerBound) {
            return lowerBound;
        }
        else if (upperBound) {
            return upperBound;
        }
        return NULL;
    }

    if (*root->data == val) {
        return root;
    }
    else if (*root->data > val) {
        return FindClosetNode_R_Internal(root->left, val, lowerBound, root);
    }
    else {
        return FindClosetNode_R_Internal(root->right, val, root, upperBound);
    }
}

template <typename T>
TreeNode<T>* FindClosetNode_R(TreeNode<T> *root, const T& val)
{
    return FindClosetNode_R_Internal<T>(root, val, NULL, NULL);
}

// https://www.careercup.com/question?id=5121304794497024
template <typename T>
TreeNode<T>* FindClosetNode(TreeNode<T> *root, const T& val)
{
    TreeNode<T> *lowerBound = NULL;
    TreeNode<T> *upperBound = NULL;

    TreeNode<T> *curNode = root;
    while (curNode) {
        if (*curNode->data == val) {
            return curNode;
        }
        else if (*curNode->data > val) {
            upperBound = curNode;
            curNode = curNode->left;
        }
        else {
            lowerBound = curNode;
            curNode = curNode->right;
        }
    }

    if (lowerBound && upperBound) {
        // TODO: To cope other T type, implement a its own "closest" function
        T toLowerBound = abs(val - *lowerBound->data);
        T toUpperBound = abs(*upperBound->data - val);
        return toLowerBound <= toUpperBound ? lowerBound : upperBound;
    }
    else if (lowerBound) {
        return lowerBound;
    }
    else if (upperBound) {
        return upperBound;
    }

    return NULL;
}
