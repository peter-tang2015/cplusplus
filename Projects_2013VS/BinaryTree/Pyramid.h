#pragma once

#include "TreeNode.h"

#include <exception>
#include <queue>
#include <string>
#include <vector>

namespace Pyramid
{
template <typename T>
size_t ValidInput(const std::vector<T> &input) {
    if (input.empty()) {
        return 0;
    }

    // 1, 2, 3, 4, 5
    // 1 + 2 + 3 + 4 + 5 = (1+5)*5/2= 15
    // level = sqrt(30) = 5
    // 5 * 6 = 30
    const size_t inputLen = input.size();
    const size_t level = static_cast<size_t>(sqrt(inputLen * 2));
    return level*(level + 1) == 2 * inputLen ? level : 0;
}

template<typename T>
struct PyramidPath
{
    PyramidPath()
    : sum(0.)
    {}

    PyramidPath(const T& val)
        : sum(val)
    {
        path.push_back(val);
    }

    PyramidPath(const PyramidPath &rhs, T val)
        : sum(val + rhs.sum)
    {
        path.reserve(1 + rhs.path.size());
        path.push_back(val);
        path.insert(path.end(), rhs.path.begin(), rhs.path.end());
    }
    std::vector<T> path;
    double sum;
};

class PyramixException : std::exception
{
public:
    PyramixException(const std::string& msg)
        : m_ErrMsg(msg)
    {}

    const char* what() const{
        return m_ErrMsg.c_str();
    }

private:
    std::string m_ErrMsg;
};

template<typename T>
class PyramidTree
{
public:
    PyramidTree()
        : m_root(NULL), m_Depth(0)
    {}

    PyramidTree(const std::vector<T> &input)
        : m_root(NULL), m_Depth(0)
    {
        ConstructPyramid(input);
    }

    ~PyramidTree() {
        Destory();
    }

    void ConstructPyramid(const std::vector<T> &input)
    {
        const size_t level = ValidInput(input);
        if (level == 0) {
            throw PyramixException("Construction failure - invalid input");
        }

        Destory();

        m_Depth = level;
        std::queue<TreeNode<T>*> leafNodes;
        auto iter = input.begin();
        while (iter != input.end()) {
            if (leafNodes.empty()) {
                m_root = new TreeNode<T>(*iter);
                leafNodes.push(m_root);
                ++iter;
            }
            else {
                size_t leafNodeSize = leafNodes.size();
                TreeNode<T>* newNode = new TreeNode<T>(*iter);
                leafNodes.push(newNode);
                while (leafNodeSize) {
                    TreeNode<T>* curNode = leafNodes.front();
                    curNode->left = newNode;
                    ++iter;
                    newNode = new TreeNode<T>(*iter);
                    curNode->right = newNode;
                    leafNodes.pop();
                    leafNodes.push(newNode);
                    --leafNodeSize;
                }
                ++iter;
            }
        }
    }

    double FindMaxSum() const {
        if (!m_root) {
            throw PyramixException("Pyramid not constructed yet");
        }

        return FindMaxSumInternal(m_root);
    }

    PyramidPath<T> FindMaxSumAndPath() const {
        if (!m_root) {
            throw PyramixException("Pyramid not constructed yet");
        }

        return FindMaxSumAndPathInternal(m_root);
    }

    size_t GetDepth() const {
        if (!m_root) {
            throw PyramixException("Pyramid not constructed yet");
        }
        return m_Depth;
    }

    void Destory() {
        if (m_root) {
            std::queue<TreeNode<T>*> nodesAtSameLevel;
            nodesAtSameLevel.push(m_root);
            TreeNode<T>* curNode = NULL;
            while (!nodesAtSameLevel.empty()) {
                size_t numOfNodesAtSameLevel = nodesAtSameLevel.size();
                curNode = nodesAtSameLevel.front();
                if (curNode->left) {
                    nodesAtSameLevel.push(curNode->left);
                }
                while (numOfNodesAtSameLevel) {
                    curNode = nodesAtSameLevel.front();
                    if (curNode->right) {
                        nodesAtSameLevel.push(curNode->right);
                    }
                    delete curNode;
                    nodesAtSameLevel.pop();
                    --numOfNodesAtSameLevel;
                }

            }
            m_root = NULL;
        }

        m_Depth = 0;
    }

private:
    double FindMaxSumInternal(TreeNode<T> *curNode) const {
        if (!curNode) {
            return 0.;
        }
        const double leftBranchSum = FindMaxSumInternal(curNode->left) + *curNode->data;
        const double rightBranchSum = FindMaxSumInternal(curNode->right) + *curNode->data;
        return leftBranchSum > rightBranchSum ? leftBranchSum : rightBranchSum;
    }

    PyramidPath<T> FindMaxSumAndPathInternal(TreeNode<T> *curNode) const {
        if (!curNode) {
            return PyramidPath<T>();
        }
        const PyramidPath<T> leftBranchPath = FindMaxSumAndPathInternal(curNode->left);
        const PyramidPath<T> rightBranchPath = FindMaxSumAndPathInternal(curNode->right);;
        if (leftBranchPath.sum >= rightBranchPath.sum) {
            return PyramidPath<T>(leftBranchPath, *curNode->data);
        }
        return PyramidPath<T>(rightBranchPath, *curNode->data);
    }

    TreeNode<T> * m_root;
    size_t m_Depth;
};

template <typename T>
class PyramidArray
{
private:
    struct PyramidArrNode {
        PyramidArrNode(size_t l, size_t n)
            : level(l), node(n)
        {}
        
        size_t GetIndex() const {
            return (level*(level + 1) >> 1) + node;
        }

        // root : level 0
        // level 1 - two nodes (0, 1)
        // level 2 - three nodes(0, 1, 2)
        // ......
        size_t level;
        size_t node;
    };

public:
    PyramidArray()
        : m_Depth(0)
    {}

    PyramidArray(const std::vector<T> &input)
        : PyramidArray()
    {
        ConstructPyramid(input);
    }

    void ConstructPyramid(const std::vector<T> &input) {
        const size_t level = ValidInput(input);
        if (level == 0) {
            throw PyramixException("Construction failure - invalid input");
        }
        m_data = input;
        m_Depth = level;
    }

    double FindMaxSum() const {
        if (m_data.empty()) {
            throw PyramixException("Pyramid not constructed yet");
        }

        return FindMaxSumInternal(PyramidArrNode(0, 0));
    }

    PyramidPath<T> FindMaxSumAndPath() const {
        if (m_data.empty()) {
            throw PyramixException("Pyramid not constructed yet");
        }

        return FindMaxSumAndPathInternal(PyramidArrNode(0, 0));
    }

    size_t GetDepth() const {
        if (m_data.empty()) {
            throw PyramixException("Pyramid not constructed yet");
        }
        return m_Depth;
    }

private:
    double FindMaxSumInternal(const PyramidArrNode &node) const {
        // Node(0, 0) -> 0
        // Node(1, 0) -> 1
        // Node(1, 1) -> 2
        // Node(2, 0) -> ((1+2)/2)*2+0 = 3;
        // Node(2, 1) -> 
        if (!HaveChildren(node)) {
            return m_data[node.GetIndex()];
        }

        const double leftBranchSum = FindMaxSumInternal(PyramidArrNode(node.level + 1, node.node));
        const double rightBranchSum = FindMaxSumInternal(PyramidArrNode(node.level + 1, node.node + 1));
        return leftBranchSum > rightBranchSum ? leftBranchSum + m_data[node.GetIndex()] :
                                                rightBranchSum + m_data[node.GetIndex()];
    }

    PyramidPath<T> FindMaxSumAndPathInternal(const PyramidArrNode &node) const {
        if (!HaveChildren(node)) {
            return PyramidPath<T>(m_data[node.GetIndex()]);
        }
        const PyramidPath<T> leftBranchPath = FindMaxSumAndPathInternal(PyramidArrNode(node.level + 1, node.node));
        const PyramidPath<T> rightBranchPath = FindMaxSumAndPathInternal(PyramidArrNode(node.level + 1, node.node + 1));
        if (leftBranchPath.sum >= rightBranchPath.sum) {
            return PyramidPath<T>(leftBranchPath, m_data[node.GetIndex()]);
        }
        return PyramidPath<T>(rightBranchPath, m_data[node.GetIndex()]);
    }

    bool HaveChildren(const PyramidArrNode &node) const {
        const size_t size = (node.level + 1) * (node.level + 2) >> 1;
        return m_data.size() > size;
    }

    std::vector<T> m_data;
    size_t m_Depth;
};

}// namespace Pyramid