// CrackingCodingTest_Ch4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

struct TreeNode
{
    TreeNode(int v)
    : value(v), left(nullptr), right(nullptr)
    {}
    int value = 0;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

bool IsTreeBalanced_BFS(TreeNode* head)
{
    if (head == nullptr) {
        return true;
    }

    size_t minHeight = 0;
    size_t height = 0;
    bool foundMinHeight = false;
    std::queue<TreeNode*> bfsQueue;
    bfsQueue.push(head);
    bfsQueue.push(nullptr); // dummy node

    while (!bfsQueue.empty()) {
        const TreeNode* curNode = bfsQueue.front();
        if (curNode == nullptr) {
            // dummy node as separateor the level
            ++height;
            bfsQueue.push(nullptr);
            bfsQueue.pop();
            continue;
        }
        if (curNode->left == nullptr && curNode->right == nullptr) {
            // leaf node
            if (!foundMinHeight) {
                minHeight = height;
                foundMinHeight = true;
            }
        }
        if (curNode->left != nullptr) {
            bfsQueue.push(curNode->left);
        }
        if (curNode->right != nullptr) {
            bfsQueue.push(curNode->right);
        }
        bfsQueue.pop();
    }

    return (height - minHeight) < 2;
}

struct TreeNodeAndHeight {
    TreeNodeAndHeight(TreeNode* curNode, size_t h)
    : node(curNode), height(h)
    {}

    TreeNode* node;
    size_t height;
};

bool IsTreeBalanced_DFS(TreeNode* head)
{
    if (head == nullptr) {
        return true;
    }

    size_t minHeight = -1;
    size_t maxHeight = 0;
    std::stack<TreeNodeAndHeight> nodesToVisit;
    nodesToVisit.push(TreeNodeAndHeight(head, 1));

    while (!nodesToVisit.empty()) {
        const TreeNodeAndHeight& curTH = nodesToVisit.top();
        if (curTH.node->left == nullptr && curTH.node->right == nullptr) {
            if (curTH.height > maxHeight) {
                maxHeight = curTH.height;
            }
            if (curTH.height < minHeight) {
                minHeight = curTH.height;
            }
        }

        if (curTH.node->left != nullptr) {
            nodesToVisit.push(TreeNodeAndHeight(curTH.node->left, curTH.height + 1));
        }
        if (curTH.node->right != nullptr) {
            nodesToVisit.push(TreeNodeAndHeight(curTH.node->right, curTH.height + 1));
        }

        nodesToVisit.pop();
    }

    return (maxHeight - minHeight) < 2;
}

struct Position {
    size_t row;
    size_t column;
    Position(size_t r, size_t c)
        : row(r), column(c)
    {}

    Position()
        : row(0), column(0)
    {}

    bool operator==(const Position& rhs) const
    {
        return row == rhs.row && column == rhs.column;
    }

};

void PushNeighbours(const int** roadMap, size_t row, size_t column,
    const Position& curPos, std::queue<Position>& pathToDetect)
{
    if (curPos.column < column - 1) {
        if (roadMap[curPos.row][curPos.column + 1]) {
            pathToDetect.push(Position(curPos.row, curPos.column + 1));
        }
    }

    if (curPos.column > 0) {
        if (roadMap[curPos.row][curPos.column - 1]) {
            pathToDetect.push(Position(curPos.row, curPos.column - 1));
        }
    }

    if (curPos.row < row - 1) {
        if (roadMap[curPos.row + 1][curPos.column]) {
            pathToDetect.push(Position(curPos.row + 1, curPos.column));
        }
    }

    if (curPos.row > 0) {
        if (roadMap[curPos.row - 1][curPos.column]) {
            pathToDetect.push(Position(curPos.row - 1, curPos.column));
        }
    }
}

bool FindPath(const int** roadMap,
              size_t row,
              size_t column,
              const Position& start,
              const Position& end)
{
    if (row == 0 || column == 0) {
        return false;
    }

    if (start.column >= column || start.row >= row ||
        end.column >= column || end.row >= row) {
        return false;
    }

    std::vector<bool> visitedPositions(row*column, false);
    std::queue<Position> pathToDetect;
    pathToDetect.push(start);
    while (!pathToDetect.empty()) {
        const Position& curPos = pathToDetect.front();
        if (curPos == end) {
            return true;
        }
        PushNeighbours(roadMap, row, column, curPos, pathToDetect);
        pathToDetect.pop();
    }

    return false;
}

TreeNode* ConstructTreeOnSortedValue(const std::vector<int>& input,
                                     int start,
                                     int end)
{
    if (input.empty() || start > end || end >= input.size()) {
        return nullptr;
    }

    const size_t index = (start + end) >> 1;
    TreeNode* curNode = new TreeNode(input[index]);
    curNode->left = ConstructTreeOnSortedValue(input, start, index - 1);
    curNode->right = ConstructTreeOnSortedValue(input, index + 1, end);
    return curNode;
}

TreeNode* ConstructTreeOnSortedValue(const std::vector<int>& input)
{
    if (input.empty()) {
        return nullptr;
    }

    const int len = input.size();
    const int index = len >> 1;
    TreeNode* root = new TreeNode(input[index]);
    root->left = ConstructTreeOnSortedValue(input, 0, index - 1);
    root->right = ConstructTreeOnSortedValue(input, index + 1, len);

    return root;
}

struct TreeConstruction
{
    TreeConstruction()
    {}

    TreeConstruction(TreeNode* p, bool left, int s, int e)
        : parent(p), isLeftChild(left), start(s), end(e)
    {}

    TreeNode* parent = nullptr;
    bool      isLeftChild = false;
    int       start = 0;
    int       end = -1;
};

struct TreeConstruction2
{
    TreeConstruction2()
    {}

    TreeConstruction2(TreeNode** n, int s, int e)
        : node(n), start(s), end(e)
    {}

    TreeNode**  node = nullptr;
    int         start = 0;
    int         end = -1;
};


TreeNode* ConstructTreeOnSortedValueBFS(const std::vector<int>& input)
{
    if (input.empty()) {
        return;
    }

    const int len = input.size();
    int index = len >> 1;
    TreeNode* root = new TreeNode(input[index]);
    std::queue<TreeConstruction> nodesToBuild;
    nodesToBuild.push(TreeConstruction(root, true, 0, len - 1));
    nodesToBuild.push(TreeConstruction(root, false, index + 1, len));
    
    while (!nodesToBuild.empty()) {
        const TreeConstruction& curCon = nodesToBuild.front();
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
            TreeNode* tempNode = new TreeNode(input[index]);
            if (curCon.isLeftChild) {
                curCon.parent->left = tempNode;
            }
            else {
                curCon.parent->right = tempNode;
            }

            nodesToBuild.push(TreeConstruction(tempNode, true, curCon.start, index - 1));
            nodesToBuild.push(TreeConstruction(tempNode, false, index + 1, curCon.end));
        }
        nodesToBuild.pop();
    }

    return root;
}

TreeNode* ConstructTreeOnSortedValueDFS(const std::vector<int>& input)
{
    if (input.empty()) {
        return;
    }

    const int len = input.size();
    int index = len >> 1;
    TreeNode* root = new TreeNode(input[index]);
    std::stack<TreeConstruction2> nodesToBuild;
    nodesToBuild.push(TreeConstruction2(&root->left, 0, len - 1));
    nodesToBuild.push(TreeConstruction2(&root->right, index + 1, len));

    while (!nodesToBuild.empty()) {
        const TreeConstruction2& curCon = nodesToBuild.top();
        if (curCon.start > curCon.end) {
            *(curCon.node) = nullptr;
        }
        else {
            index = (curCon.start + curCon.end) >> 1;
            TreeNode* tempNode = new TreeNode(input[index]);
            *(curCon.node) = tempNode;

            nodesToBuild.push(TreeConstruction2(&tempNode->left,curCon.start, index - 1));
            nodesToBuild.push(TreeConstruction2(&tempNode->right, index + 1, curCon.end));
        }
        nodesToBuild.pop();
    }

    return root;
}


struct LLNode
{
    LLNode(int v)
        : value(v), next(nullptr)
    {}
    int value = 0;
    LLNode* next = nullptr;
};

void ConstructLLviaTree(TreeNode* root, std::vector<LLNode*> listOfLL)
{
    if (root == nullptr) {
        return;
    }

    std::queue<TreeNode*> nodes;
    nodes.push(nullptr); // dummy node
    nodes.push(root);
    nodes.push(nullptr); // dummy node
    size_t level = 0;
    LLNode** curHead;
    LLNode* curTail;
    while (!nodes.empty()) {
        const TreeNode* curNode = nodes.front();
        if (curNode == nullptr) {
            ++level;
            listOfLL.push_back(nullptr);
            curHead = &listOfLL[level - 1];
            curTail = nullptr;
        }
        else {
            if (*curHead == nullptr) {
                *curHead = new LLNode(curNode->value);
                curTail = *curHead;
            }
            else {
                curTail->next = new LLNode(curNode->value);
                curTail = curTail->next;
            }
            if (curNode->left != nullptr) {
                nodes.push(curNode->left);
            }
            if (curNode->right != nullptr) {
                nodes.push(curNode->right);
            }
        }

        nodes.pop();
    }
}

struct UpwardLinkedTreeNode{
    UpwardLinkedTreeNode()
    {}
    UpwardLinkedTreeNode(UpwardLinkedTreeNode* p, int v)
        : value(v), parent(p)
    {}

    int value = 0;
    UpwardLinkedTreeNode* parent = nullptr;
    UpwardLinkedTreeNode* left = nullptr;
    UpwardLinkedTreeNode* right = nullptr;
};

UpwardLinkedTreeNode* FindNextInOrder(UpwardLinkedTreeNode* given)
{
    if (given == nullptr) {
        return nullptr;
    }

    if (given->right) {
        // its successor is the leftest node of its right node
        UpwardLinkedTreeNode* curNode = given->right;
        while (curNode->left) {
            curNode = curNode->left;
        }
        return curNode;
    }

    if (given->parent != nullptr) {
        if (given->parent->left == given) {
            return given->parent;
        }
        else {
            UpwardLinkedTreeNode* curNode = given->parent;
            while (curNode->parent) {
                if (curNode->parent->left == curNode) {
                    return curNode->parent;
                }
                curNode = curNode->parent;
            }
        }
    }

    return nullptr;
}

bool ContainNode(TreeNode* root, TreeNode* x)
{
    if (root == nullptr) {
        return false;
    }

    if (root == x) {
        return true;
    }

    return ContainNode(root->left, x) || ContainNode(root->right, x);
}

TreeNode* CommonAncestor(TreeNode* root, TreeNode* a, TreeNode* b)
{
    if (ContainNode(root->left, a) && ContainNode(root->left, b)) {
        return CommonAncestor(root->left, a, b);
    }
    if (ContainNode(root->right, a) && ContainNode(root->right, b)) {
        return CommonAncestor(root->right, a, b);
    }

    return root;
}

void PrintPath(TreeNode* head, int given, std::vector<TreeNode*> pathSOfar)
{
    if (!pathSOfar.empty())
    {
        int sum = 0;
        auto rIter = pathSOfar.rbegin();
        auto rIterEnd = pathSOfar.rend();
        using TreeNodeIter = std::vector<TreeNode*>::reverse_iterator;
        std::vector<TreeNodeIter> result;
        for (; rIter != rIterEnd; ++rIter) {
            sum += (*rIter)->value;
            if (sum == given) {
                result.push_back(rIter);
            }
        }

        if (!result.empty()) {
            auto iterResult = result.begin();
            auto iterResultEnd = result.end();
            for (rIter = pathSOfar.rbegin(); 
                 rIter != rIterEnd && iterResult != iterResultEnd; ++rIter) {
                std::cout << *rIter << "|" << (*rIter)->value;
                if (*rIter == **iterResult) {
                    std::cout << "*";
                    ++iterResult;
                }
                if (iterResult != iterResultEnd) {
                    std::cout << "-";
                }
            }
            std::cout << std::endl;
        }
    }
    if (!head) {
        return;
    }
 
    if (head->left || head->right) {
        std::vector<TreeNode*> newPath(pathSOfar);
        newPath.reserve(pathSOfar.size() + 1);
        newPath.push_back(head);
        if (head->left) {
            PrintPath(head->left, given, newPath);
        }
        if (head->right) {
            PrintPath(head->right, given, newPath);
        }
    }
}

void PintPathsSumToGivenValue(TreeNode* root, int given)
{
    if (!root) {
        return;
    }

    PrintPath(root, given, std::vector<TreeNode*>(1, root));
}

bool MatchTree(TreeNode* src, TreeNode* ptn)
{
    if (!ptn) {
        return true;
    }

    if (!src) {
        return false;
    }

    if (src->value == ptn->value) {
        return MatchTree(src->left, ptn->left) &&
               MatchTree(src->right, ptn->right);
    }

    return false;
}

bool SubTree(TreeNode* src, TreeNode* ptn)
{
    if (!ptn) {
        return true;
    }

    if (!src) {
        return false;
    }

    if (src->value == ptn->value) {
        if (MatchTree(src, ptn)) {
            return true;
        }
    }

    return SubTree(src->left, ptn) || SubTree(src->right, ptn);
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

