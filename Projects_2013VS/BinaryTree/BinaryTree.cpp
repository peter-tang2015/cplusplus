// BinaryTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cassert>

#include <array>
#include <vector>

#include "TreeConstruction_BFS.h"
#include "TreeConstruction_DFS.h"
#include "TreeConstruction_Recursive.h"
#include "TreeNodeUtil.h"
#include "TreePreInPostOrder.h"
#include "Pyramid.h"

void TestCasesOfNextInOrder()
{
    // http://www.careercup.com/question?id=5656021852749824

    const std::vector<int> testInput{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    TreeNode<int>* rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);

    auto nextInOrder = NextInOrder(rootBFS, 0);
    assert(nextInOrder.get() == nullptr);
    nextInOrder = NextInOrder(rootBFS, 1);
    assert(*nextInOrder == 2);
    nextInOrder = NextInOrder(rootBFS, 2);
    assert(*nextInOrder == 3);
    nextInOrder = NextInOrder(rootBFS, 3);
    assert(*nextInOrder == 4);
    nextInOrder = NextInOrder(rootBFS, 4);
    assert(*nextInOrder == 5);
    nextInOrder = NextInOrder(rootBFS, 5);
    assert(*nextInOrder == 6);
    nextInOrder = NextInOrder(rootBFS, 6);
    assert(*nextInOrder == 7);
    nextInOrder = NextInOrder(rootBFS, 7);
    assert(*nextInOrder == 8);
    nextInOrder = NextInOrder(rootBFS, 8);
    assert(*nextInOrder == 9);
    nextInOrder = NextInOrder(rootBFS, 9);
    assert(*nextInOrder == 10);
    nextInOrder = NextInOrder(rootBFS, 10);
    assert(nextInOrder.get() == nullptr);
    nextInOrder = NextInOrder(rootBFS, 11);
    assert(nextInOrder == nullptr);


    TreeNode<int>* rootDFS = ConstructTreeOnSortedValueDFS(testInput);
    assert(rootDFS != nullptr);
    nextInOrder = NextInOrder(rootDFS, 0);
    assert(nextInOrder.get() == nullptr);
    nextInOrder = NextInOrder(rootDFS, 1);
    assert(*nextInOrder == 2);
    nextInOrder = NextInOrder(rootDFS, 2);
    assert(*nextInOrder == 3);
    nextInOrder = NextInOrder(rootDFS, 3);
    assert(*nextInOrder == 4);
    nextInOrder = NextInOrder(rootDFS, 4);
    assert(*nextInOrder == 5);
    nextInOrder = NextInOrder(rootDFS, 5);
    assert(*nextInOrder == 6);
    nextInOrder = NextInOrder(rootDFS, 6);
    assert(*nextInOrder == 7);
    nextInOrder = NextInOrder(rootDFS, 7);
    assert(*nextInOrder == 8);
    nextInOrder = NextInOrder(rootDFS, 8);
    assert(*nextInOrder == 9);
    nextInOrder = NextInOrder(rootDFS, 9);
    assert(*nextInOrder == 10);
    nextInOrder = NextInOrder(rootDFS, 10);
    assert(nextInOrder.get() == nullptr);
    nextInOrder = NextInOrder(rootDFS, 11);
    assert(nextInOrder == nullptr);

    DeleteTree_TD(&rootBFS);
    DeleteTree_TD(&rootDFS);
}

void TestCasesOfSumOfEachLevelOfTree()
{
    std::vector<int> testInput{ 1 };
    TreeNode<int>* rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);

    std::vector<int> result;
    GetSumOfEachLevelOfTree(rootBFS, result);
    assert(result.size() == 1);
    assert(result[0] == 1);
    DeleteTree_TD(&rootBFS);

    testInput = {1, 2};
    rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);
    result.clear();
    GetSumOfEachLevelOfTree(rootBFS, result);
    assert(result.size() == 2);
    assert(result[0] == 2);
    assert(result[1] == 1);
    DeleteTree_TD(&rootBFS);

    testInput = { 1, 2, 3 };
    rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);
    result.clear();
    GetSumOfEachLevelOfTree(rootBFS, result);
    assert(result.size() == 2);
    assert(result[0] == 2);
    assert(result[1] == 4);
    DeleteTree_TD(&rootBFS);

    testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);
    result.clear();
    GetSumOfEachLevelOfTree(rootBFS, result);
    assert(result.size() == 4);
    assert(result[0] == 6); // 6
    assert(result[1] == 11);// 3, 8
    assert(result[2] == 21); // 1, 4, 7, 9 
    assert(result[3] == 17);// 2, 5, 10
    DeleteTree_TD(&rootBFS);
}

void TestCasesOfFirstAndLastOfEachLevelOfTree()
{
    std::vector<int> testInput{ 1 };
    TreeNode<int>* rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);

    std::vector<TreeNode<int>*> result;
    GetFirstAndLastOfEachLevelOfTree(rootBFS, result);
    assert(result.size() == 1);
    assert(*result[0]->data == 1);
    DeleteTree_TD(&rootBFS);

    testInput = { 1, 2 };
    rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);
    result.clear();
    GetFirstAndLastOfEachLevelOfTree(rootBFS, result);
    assert(result.size() == 2);
    assert(*result[0]->data == 2);
    assert(*result[1]->data == 1);
    DeleteTree_TD(&rootBFS);

    testInput = { 1, 2, 3 };
    rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);
    result.clear();
    GetFirstAndLastOfEachLevelOfTree(rootBFS, result);
    assert(result.size() == 3);
    assert(*result[0]->data == 2);
    assert(*result[1]->data == 1);
    assert(*result[2]->data == 3);
    DeleteTree_TD(&rootBFS);

    testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    rootBFS = ConstructTreeOnSortedValueBFS(testInput);
    assert(rootBFS != nullptr);
    result.clear();
    GetFirstAndLastOfEachLevelOfTree(rootBFS, result);
    assert(result.size() == 7);
    // Tree:
    // 6
    // 3, 8
    // 1, 4, 7, 9 
    // 2, 5, 10
    assert(*result[0]->data == 6);
    assert(*result[1]->data == 3);
    assert(*result[2]->data == 8); 
    assert(*result[3]->data == 1);
    assert(*result[4]->data == 9);
    assert(*result[5]->data == 2); 
    assert(*result[6]->data == 10);
    DeleteTree_TD(&rootBFS);
}

void TestCasesOfCheckTwoTreesWithSameElements()
{
    const std::vector<int> testInput1 = { 1, 3, 5, 7, 2, 4, 6, 8 };
    auto tree1 = ConstructTreeRecursive(testInput1);
    assert(tree1 != nullptr);

    {
        TreeNode<int>* invalid1 = nullptr;
        TreeNode<int>* invalid2 = nullptr;

        assert(CheckTwoTreesWithSameValues(invalid1, invalid2) == true);
        assert(CheckTwoTreesWithSameValues(tree1, invalid2) == false);
        assert(CheckTwoTreesWithSameValues(invalid1, tree1) == false);
    }

    {
        const std::vector<int> testInput2 = { 1, 3, 5, 7, 2, 4, 6, 1, 5, 2, 4 };
        auto tree2 = ConstructTreeRecursive(testInput2);
        assert(tree2 != nullptr);
        assert(CheckTwoTreesWithSameValues(tree1, tree2) == false);
        DeleteTree_TD(&tree2);
    }

    {
        const std::vector<int> testInput2 = { 1, 3, 5, 7, 2, 4, 6, 8, 1, 3, 5, 7, 2, 4, 6, 8 };
        auto tree2 = ConstructTreeRecursive(testInput2);
        assert(tree2 != nullptr);
        assert(CheckTwoTreesWithSameValues(tree1, tree2) == true);
        DeleteTree_TD(&tree2);
    }

    {
        const std::vector<int> testInput2 = { 1, 3, 5, 7, 2, 4, 6, 8, 1, 3, 5, 7, 2, 4, 6, 8, 9 };
        auto tree2 = ConstructTreeRecursive(testInput2);
        assert(tree2 != nullptr);
        assert(CheckTwoTreesWithSameValues(tree1, tree2) == false);
        DeleteTree_TD(&tree2);
    }

    DeleteTree_TD(&tree1);
}

struct IntPair{
    int nodeValue;
    int nodeLevel;
};

void TestTreeTraverse()
{
    {
        TreeNode<int>* root = nullptr;
        assert(PreOrder_R(root).empty() == true);
        assert(InOrder_R(root).empty() == true);
        assert(PostOrder_R(root).empty() == true);
        assert(PreOrder(root).empty() == true);
        assert(InOrder(root).empty() == true);
        assert(PostOrder(root).empty() == true);

        assert(PreOrderWithLevel_R(root).empty() == true);
        assert(InOrderWithLevel_R(root).empty() == true);
        assert(PostOrderWithLevel_R(root).empty() == true);
        assert(PreOrderWithLevel(root).empty() == true);
        assert(InOrderWithLevel(root).empty() == true);
        assert(PostOrderWithLevel(root).empty() == true);
    }
    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        TreeNode<int>* root = ConstructTreeOnSortedValueBFS(testInput);
        assert(root != nullptr);
        // Tree:
        //                    6
        //        3,                  8
        // 1,         4,         7,       9 
        //     2,          5,                 10
        // PreOrder: {6, 3, 1, 2, 4, 5, 8, 7, 9, 10}
        // PreOrder: {6, 0}, {3, 1}, {1, 2}, {2, 3}, {4, 2}, {5, 3}, {8, 1}, {7, 2}, {9, 2}, {10, 3}
        // InOrder:  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
        // InOrder:  {1, 2}, {2, 3}, {3, 1}, {4, 2}, {5, 3}, {6, 0}, {7, 2}, {8, 1}, {9, 2}, {10, 3}
        // PostOrder:{ 2, 1, 5, 4, 3, 7, 10, 9, 8, 6};
        // PostOrder:{2, 3}, {1, 2}, {5, 3}, {4, 2}, {3, 1}, {7, 2}, {10, 3}, {9, 2}, {8, 1}, {6, 0}
        {
            const std::array<int, 10> testResult = { 6, 3, 1, 2, 4, 5, 8, 7, 9, 10 };
            auto result = PreOrder_R(root);
            assert(result.size() == testResult.size());
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx] == testResult[idx]);
            }
            result = PreOrder(root);
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx] == testResult[idx]);
            }
        }

        {
            const std::array<int, 10> testResult = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            auto result = InOrder_R(root);
            assert(result.size() == testResult.size());
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx] == testResult[idx]);
            }
            result = InOrder(root);
            assert(result.size() == testResult.size());
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx] == testResult[idx]);
            }
        }

        {
            const std::array<int, 10> testResult = { 2, 1, 5, 4, 3, 7, 10, 9, 8, 6 };
            auto result = PostOrder_R(root);
            assert(result.size() == testResult.size());
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx] == testResult[idx]);
            }
            result = PostOrder(root);
            assert(result.size() == testResult.size());
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx] == testResult[idx]);
            }
        }

        {
            const std::vector<IntPair> testResult = { { 6, 0 }, { 3, 1 }, { 1, 2 }, { 2, 3 }, { 4, 2 }, { 5, 3 }, { 8, 1 }, { 7, 2 }, { 9, 2 }, { 10, 3 } };
            auto result = PreOrderWithLevel_R(root);
            assert(result.size() == testResult.size());
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx].data == testResult[idx].nodeValue);
                assert(result[idx].level == testResult[idx].nodeLevel);
            }
            result = PreOrderWithLevel(root);
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx].data == testResult[idx].nodeValue);
                assert(result[idx].level == testResult[idx].nodeLevel);
            }
        }

        {
            const std::vector<IntPair> testResult = { { 1, 2 }, { 2, 3 }, { 3, 1 }, { 4, 2 }, { 5, 3 }, { 6, 0 }, { 7, 2 }, { 8, 1 }, { 9, 2 }, { 10, 3 } };
            auto result = InOrderWithLevel_R(root);
            assert(result.size() == testResult.size());
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx].data == testResult[idx].nodeValue);
                assert(result[idx].level == testResult[idx].nodeLevel);
            }
            result = InOrderWithLevel(root);
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx].data == testResult[idx].nodeValue);
                assert(result[idx].level == testResult[idx].nodeLevel);
            }
        }

        {
            const std::vector<IntPair> testResult = { { 2, 3 }, { 1, 2 }, { 5, 3 }, { 4, 2 }, { 3, 1 }, { 7, 2 }, { 10, 3 }, { 9, 2 }, { 8, 1 }, { 6, 0 } };
            auto result = PostOrderWithLevel_R(root);
            assert(result.size() == testResult.size());
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx].data == testResult[idx].nodeValue);
                assert(result[idx].level == testResult[idx].nodeLevel);
            }
            result = PostOrderWithLevel(root);
            for (size_t idx = 0; idx != result.size(); ++idx) {
                assert(*result[idx].data == testResult[idx].nodeValue);
                assert(result[idx].level == testResult[idx].nodeLevel);
            }
        }

        DeleteTree_TD(&root);
    }
}

void TestFindDuplicateSubTree()
{
    {
        TreeNode<int>* root = nullptr;
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);
    }

    {
        const std::vector<int> testInput = { 1, 2 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root);
        auto rightestNode = FindRightestNode(root);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root);
        auto rightestNode = FindRightestNode(root);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->left);
        auto rightestNode = FindRightestNode(root->left);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 4);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }
}

void TestFindDuplicateSubTree2()
{
    {
        TreeNode<int>* root = nullptr;
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);
    }

    {
        const std::vector<int> testInput = { 1, 2 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root);
        auto rightestNode = FindRightestNode(root);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root);
        auto rightestNode = FindRightestNode(root);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->left);
        auto rightestNode = FindRightestNode(root->left);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 4);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1 = nullptr;
        TreeNode<int>* entry2 = nullptr;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput1 = { 100, 101, 102 };
        const std::vector<int> subTreeInput2 = { 102, 101, 100 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput1);
        auto subTree2 = ConstructTreeRecursive(subTreeInput2);
        assert(GetTreeSize_R(subTree1) == subTreeInput1.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput2.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);
        assert(entry1 == nullptr);
        assert(entry2 == nullptr);
        
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1 = nullptr;
        TreeNode<int>* entry2 = nullptr;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        TreeNode<int>* subTree1 = new TreeNode<int>(1000);
        subTree1->left = new TreeNode<int>(1001);
        subTree1->left->left = new TreeNode<int>(1002);
        TreeNode<int>* subTree2 = new TreeNode<int>(1000);
        subTree2->right = new TreeNode<int>(1001);
        subTree2->right->right = new TreeNode<int>(1002);
        assert(GetTreeSize_R(subTree1) == 3);
        assert(GetTreeSize_R(subTree2) == 3);
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);
        assert(entry1 == nullptr);
        assert(entry2 == nullptr);

        DeleteTree_TD(&root);
    }
    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1 = nullptr;
        TreeNode<int>* entry2 = nullptr;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        TreeNode<int>* subTree1 = new TreeNode<int>(1000);
        subTree1->left = new TreeNode<int>(1001);
        subTree1->right = new TreeNode<int>(1002);
        TreeNode<int>* subTree2 = new TreeNode<int>(1000);
        subTree2->right = new TreeNode<int>(1001);
        subTree2->right->right = new TreeNode<int>(1002);
        assert(GetTreeSize_R(subTree1) == 3);
        assert(GetTreeSize_R(subTree2) == 3);
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);
        assert(entry1 == nullptr);
        assert(entry2 == nullptr);

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1 = nullptr;
        TreeNode<int>* entry2 = nullptr;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);

        TreeNode<int>* subTree1 = new TreeNode<int>(1000);
        subTree1->right = new TreeNode<int>(1002);
        subTree1->right->right = new TreeNode<int>(1001);
        TreeNode<int>* subTree2 = new TreeNode<int>(1000);
        subTree2->right = new TreeNode<int>(1001);
        subTree2->right->right = new TreeNode<int>(1002);
        assert(GetTreeSize_R(subTree1) == 3);
        assert(GetTreeSize_R(subTree2) == 3);
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree2_R(root, entry1, entry2) == false);
        assert(entry1 == nullptr);
        assert(entry2 == nullptr);

        DeleteTree_TD(&root);
    }
}

void TestFindDuplicateSubTree3()
{
    {
        TreeNode<int>* root = nullptr;
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);
    }

    {
        const std::vector<int> testInput = { 1, 2 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);
        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root);
        auto rightestNode = FindRightestNode(root);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root);
        auto rightestNode = FindRightestNode(root);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->left);
        auto rightestNode = FindRightestNode(root->left);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 1);
        assert(*rightestNode->data == 4);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1;
        TreeNode<int>* entry2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput = { 100, 101, 102 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput);
        auto subTree2 = ConstructTreeRecursive(subTreeInput);
        assert(GetTreeSize_R(subTree1) == subTreeInput.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == true);
        assert(entry1 != nullptr);
        assert(entry2 != nullptr);
        assert(CheckTwoTreesWithSameValues(entry1, subTree1));
        assert(CheckTwoTreesWithSameValues(entry2, subTree2));
        assert(CheckTwoTreesWithSameValues(entry1, entry2));

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1 = nullptr;
        TreeNode<int>* entry2 = nullptr;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        const std::vector<int> subTreeInput1 = { 100, 101, 102 };
        const std::vector<int> subTreeInput2 = { 102, 101, 100 };
        auto subTree1 = ConstructTreeRecursive(subTreeInput1);
        auto subTree2 = ConstructTreeRecursive(subTreeInput2);
        assert(GetTreeSize_R(subTree1) == subTreeInput1.size());
        assert(GetTreeSize_R(subTree2) == subTreeInput2.size());
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);
        assert(entry1 == nullptr);
        assert(entry2 == nullptr);

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1 = nullptr;
        TreeNode<int>* entry2 = nullptr;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        TreeNode<int>* subTree1 = new TreeNode<int>(1000);
        subTree1->left = new TreeNode<int>(1001);
        subTree1->left->left = new TreeNode<int>(1002);
        TreeNode<int>* subTree2 = new TreeNode<int>(1000);
        subTree2->right = new TreeNode<int>(1001);
        subTree2->right->right = new TreeNode<int>(1002);
        assert(GetTreeSize_R(subTree1) == 3);
        assert(GetTreeSize_R(subTree2) == 3);
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);
        assert(entry1 == nullptr);
        assert(entry2 == nullptr);

        DeleteTree_TD(&root);
    }
    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1 = nullptr;
        TreeNode<int>* entry2 = nullptr;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        TreeNode<int>* subTree1 = new TreeNode<int>(1000);
        subTree1->left = new TreeNode<int>(1001);
        subTree1->right = new TreeNode<int>(1002);
        TreeNode<int>* subTree2 = new TreeNode<int>(1000);
        subTree2->right = new TreeNode<int>(1001);
        subTree2->right->right = new TreeNode<int>(1002);
        assert(GetTreeSize_R(subTree1) == 3);
        assert(GetTreeSize_R(subTree2) == 3);
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);
        assert(entry1 == nullptr);
        assert(entry2 == nullptr);

        DeleteTree_TD(&root);
    }

    {
        const std::vector<int> testInput = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        auto root = ConstructTreeRecursive(testInput);
        assert(root != nullptr);
        assert(GetTreeSize_R(root) == testInput.size());
        TreeNode<int>* entry1 = nullptr;
        TreeNode<int>* entry2 = nullptr;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);

        TreeNode<int>* subTree1 = new TreeNode<int>(1000);
        subTree1->right = new TreeNode<int>(1002);
        subTree1->right->right = new TreeNode<int>(1001);
        TreeNode<int>* subTree2 = new TreeNode<int>(1000);
        subTree2->right = new TreeNode<int>(1001);
        subTree2->right->right = new TreeNode<int>(1002);
        assert(GetTreeSize_R(subTree1) == 3);
        assert(GetTreeSize_R(subTree2) == 3);
        assert(CheckTwoTreesWithSameValues(subTree1, subTree2) == true);

        auto leftestNode = FindLeftestNode(root->right);
        auto rightestNode = FindRightestNode(root->right);
        assert(leftestNode != nullptr);
        assert(leftestNode->left == nullptr);
        assert(rightestNode != nullptr);
        assert(rightestNode->right == nullptr);
        assert(*leftestNode->data == 6);
        assert(*rightestNode->data == 10);

        leftestNode->left = subTree1;
        rightestNode->right = subTree2;
        assert(HaveDuplicateSubTree3_R(root, entry1, entry2) == false);
        assert(entry1 == nullptr);
        assert(entry2 == nullptr);

        DeleteTree_TD(&root);
    }
}

using namespace Pyramid;
void TestPyramidTree()
{
    {
        const std::vector<int> input;
        assert(Pyramid::ValidInput(input) == 0);
        const std::vector<int> input1 = { 1 };
        assert(Pyramid::ValidInput(input1) == 1);
        const std::vector<int> input2 = { 1, 2, 3 };
        assert(Pyramid::ValidInput(input2) == 2);
        const std::vector<int> input3 = { 1, 2, 3, 4, 5, 6 };
        assert(Pyramid::ValidInput(input3) == 3);
        const std::vector<int> input4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        assert(Pyramid::ValidInput(input4) == 4);
        const std::vector<int> input5 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        assert(Pyramid::ValidInput(input5) == 5);
    }
    {
        const std::vector<int> input1 = { 1, 0 };
        assert(Pyramid::ValidInput(input1) == 0);
        const std::vector<int> input2 = { 1, 2, 3, 0 };
        assert(Pyramid::ValidInput(input2) == 0);
        const std::vector<int> input3 = { 1, 2, 3, 4, 5, 6, 0 };
        assert(Pyramid::ValidInput(input3) == 0);
        const std::vector<int> input4 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0 };
        assert(Pyramid::ValidInput(input4) == 0);
        const std::vector<int> input5 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0 };
        assert(Pyramid::ValidInput(input5) == 0);
    }

    {
        PyramidTree<int> pyramid;
        try {
            pyramid.GetDepth();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }
        try {
            pyramid.FindMaxSum();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }

        try {
            pyramid.FindMaxSumAndPath();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }

        try {
            pyramid.ConstructPyramid({1, 2, 3, 4});
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Construction failure - invalid input");
        }

        try {
            pyramid.FindMaxSum();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }

        try {
            pyramid.FindMaxSumAndPath();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }

        pyramid.ConstructPyramid({ 1, 2, 3 });
        assert(pyramid.GetDepth() == 2);
        assert(pyramid.FindMaxSum() == 4);
        auto path = pyramid.FindMaxSumAndPath();
        assert(path.sum == 4);
        assert(path.path == std::vector<int>({1, 3}));

        pyramid.ConstructPyramid({ 1, 2, 3, 4, 5, 6 });
        assert(pyramid.GetDepth() == 3);
        assert(pyramid.FindMaxSum() == 10);
        path = pyramid.FindMaxSumAndPath();
        assert(path.sum == 10);
        assert(path.path == std::vector<int>({ 1, 3, 6 }));

        pyramid.ConstructPyramid({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
        assert(pyramid.GetDepth() == 4);
        assert(pyramid.FindMaxSum() == 20);
        path = pyramid.FindMaxSumAndPath();
        assert(path.sum == 20);
        assert(path.path == std::vector<int>({ 1, 3, 6, 10 }));

        pyramid.ConstructPyramid({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
        assert(pyramid.GetDepth() == 5);
        assert(pyramid.FindMaxSum() == 35);
        path = pyramid.FindMaxSumAndPath();
        assert(path.sum == 35);
        assert(path.path == std::vector<int>({ 1, 3, 6, 10, 15 }));
    }
}

void TestPyramidArray()
{
    {
        PyramidArray<int> pyramid;
        try {
            pyramid.GetDepth();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }
        try {
            pyramid.FindMaxSum();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }

        try {
            pyramid.FindMaxSumAndPath();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }

        try {
            pyramid.ConstructPyramid({ 1, 2, 3, 4 });
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Construction failure - invalid input");
        }

        try {
            pyramid.FindMaxSum();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }

        try {
            pyramid.FindMaxSumAndPath();
            assert(false);
        }
        catch (const PyramixException &e) {
            assert(std::string(e.what()) == "Pyramid not constructed yet");
        }

        pyramid.ConstructPyramid({ 1, 2, 3 });
        assert(pyramid.GetDepth() == 2);
        assert(pyramid.FindMaxSum() == 4);
        auto path = pyramid.FindMaxSumAndPath();
        assert(path.sum == 4);
        assert(path.path == std::vector<int>({ 1, 3 }));

        pyramid.ConstructPyramid({ 1, 2, 3, 4, 5, 6 });
        assert(pyramid.GetDepth() == 3);
        assert(pyramid.FindMaxSum() == 10);
        path = pyramid.FindMaxSumAndPath();
        assert(path.sum == 10);
        assert(path.path == std::vector<int>({ 1, 3, 6 }));

        pyramid.ConstructPyramid({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
        assert(pyramid.GetDepth() == 4);
        assert(pyramid.FindMaxSum() == 20);
        path = pyramid.FindMaxSumAndPath();
        assert(path.sum == 20);
        assert(path.path == std::vector<int>({ 1, 3, 6, 10 }));

        pyramid.ConstructPyramid({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 });
        assert(pyramid.GetDepth() == 5);
        assert(pyramid.FindMaxSum() == 35);
        path = pyramid.FindMaxSumAndPath();
        assert(path.sum == 35);
        assert(path.path == std::vector<int>({ 1, 3, 6, 10, 15 }));
    }
}

void TestFindCloesetNode_R()
{
    TreeNode<double> *root = NULL;
    assert(FindClosetNode_R(root, 0.0) == NULL);

    std::vector<double> input = { 1.0 };
    root = ConstructTreeRecursive(input);
    assert(root);
    TreeNode<double> *foundNode = FindClosetNode_R(root, 1.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode_R(root, 100.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode_R(root, -100.0);
    assert(*foundNode->data == 1.0);
    DeleteTree_BU(&root);

    input = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    root = ConstructTreeOnSortedValueBFS(input);
    assert(root);
    foundNode = FindClosetNode_R(root, -100.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode_R(root, -1.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode_R(root, -1.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode_R(root, 1.2);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode_R(root, 1.6);
    assert(*foundNode->data == 2.0);
    foundNode = FindClosetNode_R(root, 2.0);
    assert(*foundNode->data == 2.0);
    foundNode = FindClosetNode_R(root, 2.1);
    assert(*foundNode->data == 2.0);
    foundNode = FindClosetNode_R(root, 2.6);
    assert(*foundNode->data == 3.0);
    foundNode = FindClosetNode_R(root, 3.0);
    assert(*foundNode->data == 3.0);
    foundNode = FindClosetNode_R(root, 3.4);
    assert(*foundNode->data == 3.0);
    foundNode = FindClosetNode_R(root, 3.6);
    assert(*foundNode->data == 4.0);
    foundNode = FindClosetNode_R(root, 4.0);
    assert(*foundNode->data == 4.0);
    foundNode = FindClosetNode_R(root, 4.4);
    assert(*foundNode->data == 4.0);
    foundNode = FindClosetNode_R(root, 4.6);
    assert(*foundNode->data == 5.0);
    foundNode = FindClosetNode_R(root, 5.0);
    assert(*foundNode->data == 5.0);
    foundNode = FindClosetNode_R(root, 5.3);
    assert(*foundNode->data == 5.0);
    foundNode = FindClosetNode_R(root, 5.6);
    assert(*foundNode->data == 6.0);
    foundNode = FindClosetNode_R(root, 6.0);
    assert(*foundNode->data == 6.0);
    foundNode = FindClosetNode_R(root, 6.3);
    assert(*foundNode->data == 6.0);
    foundNode = FindClosetNode_R(root, 6.6);
    assert(*foundNode->data == 7.0);
    foundNode = FindClosetNode_R(root, 7.0);
    assert(*foundNode->data == 7.0);
    foundNode = FindClosetNode_R(root, 7.3);
    assert(*foundNode->data == 7.0);
    foundNode = FindClosetNode_R(root, 7.6);
    assert(*foundNode->data == 8.0);
    foundNode = FindClosetNode_R(root, 8.0);
    assert(*foundNode->data == 8.0);
    foundNode = FindClosetNode_R(root, 8.3);
    assert(*foundNode->data == 8.0);
    foundNode = FindClosetNode_R(root, 8.6);
    assert(*foundNode->data == 9.0);
    foundNode = FindClosetNode_R(root, 9.0);
    assert(*foundNode->data == 9.0);
    foundNode = FindClosetNode_R(root, 9.3);
    assert(*foundNode->data == 9.0);
    foundNode = FindClosetNode_R(root, 9.6);
    assert(*foundNode->data == 10.0);
    foundNode = FindClosetNode_R(root, 10.0);
    assert(*foundNode->data == 10.0);
    foundNode = FindClosetNode_R(root, 10.3);
    assert(*foundNode->data == 10.0);
    foundNode = FindClosetNode_R(root, 10.6);
    assert(*foundNode->data == 11.0);
    foundNode = FindClosetNode_R(root, 11.0);
    assert(*foundNode->data == 11.0);
    foundNode = FindClosetNode_R(root, 11.3);
    assert(*foundNode->data == 11.0);
    foundNode = FindClosetNode_R(root, 11.6);
    assert(*foundNode->data == 12.0);
    foundNode = FindClosetNode_R(root, 12.0);
    assert(*foundNode->data == 12.0);
    foundNode = FindClosetNode_R(root, 12.3);
    assert(*foundNode->data == 12.0);
    foundNode = FindClosetNode_R(root, 12.6);
    assert(*foundNode->data == 13.0);
    foundNode = FindClosetNode_R(root, 13.0);
    assert(*foundNode->data == 13.0);
    foundNode = FindClosetNode_R(root, 13.3);
    assert(*foundNode->data == 13.0);
    foundNode = FindClosetNode_R(root, 13.6);
    assert(*foundNode->data == 14.0);
    foundNode = FindClosetNode_R(root, 14.0);
    assert(*foundNode->data == 14.0);
    foundNode = FindClosetNode_R(root, 14.3);
    assert(*foundNode->data == 14.0);
    foundNode = FindClosetNode_R(root, 14.6);
    assert(*foundNode->data == 15.0);
    foundNode = FindClosetNode_R(root, 15.0);
    assert(*foundNode->data == 15.0);
    foundNode = FindClosetNode_R(root, 15.3);
    assert(*foundNode->data == 15.0);
    foundNode = FindClosetNode_R(root, 15.6);
    assert(*foundNode->data == 16.0);
    foundNode = FindClosetNode_R(root, 16.0);
    assert(*foundNode->data == 16.0);
    foundNode = FindClosetNode_R(root, 16.3);
    assert(*foundNode->data == 16.0);
    foundNode = FindClosetNode_R(root, 100.0);
    assert(*foundNode->data == 16.0);
    DeleteTree_TD(&root);
}

void TestFindCloesetNode()
{
    TreeNode<double> *root = NULL;
    assert(FindClosetNode(root, 0.0) == NULL);

    std::vector<double> input = { 1.0 };
    root = ConstructTreeRecursive(input);
    assert(root);
    TreeNode<double> *foundNode = FindClosetNode(root, 1.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode(root, 100.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode(root, -100.0);
    assert(*foundNode->data == 1.0);
    DeleteTree_BU(&root);

    input = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    root = ConstructTreeOnSortedValueBFS(input);
    assert(root);
    foundNode = FindClosetNode(root, -100.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode(root, -1.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode(root, -1.0);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode(root, 1.2);
    assert(*foundNode->data == 1.0);
    foundNode = FindClosetNode(root, 1.6);
    assert(*foundNode->data == 2.0);
    foundNode = FindClosetNode(root, 2.0);
    assert(*foundNode->data == 2.0);
    foundNode = FindClosetNode(root, 2.1);
    assert(*foundNode->data == 2.0);
    foundNode = FindClosetNode(root, 2.6);
    assert(*foundNode->data == 3.0);
    foundNode = FindClosetNode(root, 3.0);
    assert(*foundNode->data == 3.0);
    foundNode = FindClosetNode(root, 3.4);
    assert(*foundNode->data == 3.0);
    foundNode = FindClosetNode(root, 3.6);
    assert(*foundNode->data == 4.0);
    foundNode = FindClosetNode(root, 4.0);
    assert(*foundNode->data == 4.0);
    foundNode = FindClosetNode(root, 4.4);
    assert(*foundNode->data == 4.0);
    foundNode = FindClosetNode(root, 4.6);
    assert(*foundNode->data == 5.0);
    foundNode = FindClosetNode(root, 5.0);
    assert(*foundNode->data == 5.0);
    foundNode = FindClosetNode(root, 5.3);
    assert(*foundNode->data == 5.0);
    foundNode = FindClosetNode(root, 5.6);
    assert(*foundNode->data == 6.0);
    foundNode = FindClosetNode(root, 6.0);
    assert(*foundNode->data == 6.0);
    foundNode = FindClosetNode(root, 6.3);
    assert(*foundNode->data == 6.0);
    foundNode = FindClosetNode(root, 6.6);
    assert(*foundNode->data == 7.0);
    foundNode = FindClosetNode(root, 7.0);
    assert(*foundNode->data == 7.0);
    foundNode = FindClosetNode(root, 7.3);
    assert(*foundNode->data == 7.0);
    foundNode = FindClosetNode(root, 7.6);
    assert(*foundNode->data == 8.0);
    foundNode = FindClosetNode(root, 8.0);
    assert(*foundNode->data == 8.0);
    foundNode = FindClosetNode(root, 8.3);
    assert(*foundNode->data == 8.0);
    foundNode = FindClosetNode(root, 8.6);
    assert(*foundNode->data == 9.0);
    foundNode = FindClosetNode(root, 9.0);
    assert(*foundNode->data == 9.0);
    foundNode = FindClosetNode(root, 9.3);
    assert(*foundNode->data == 9.0);
    foundNode = FindClosetNode(root, 9.6);
    assert(*foundNode->data == 10.0);
    foundNode = FindClosetNode(root, 10.0);
    assert(*foundNode->data == 10.0);
    foundNode = FindClosetNode(root, 10.3);
    assert(*foundNode->data == 10.0);
    foundNode = FindClosetNode(root, 10.6);
    assert(*foundNode->data == 11.0);
    foundNode = FindClosetNode(root, 11.0);
    assert(*foundNode->data == 11.0);
    foundNode = FindClosetNode(root, 11.3);
    assert(*foundNode->data == 11.0);
    foundNode = FindClosetNode(root, 11.6);
    assert(*foundNode->data == 12.0);
    foundNode = FindClosetNode(root, 12.0);
    assert(*foundNode->data == 12.0);
    foundNode = FindClosetNode(root, 12.3);
    assert(*foundNode->data == 12.0);
    foundNode = FindClosetNode(root, 12.6);
    assert(*foundNode->data == 13.0);
    foundNode = FindClosetNode(root, 13.0);
    assert(*foundNode->data == 13.0);
    foundNode = FindClosetNode(root, 13.3);
    assert(*foundNode->data == 13.0);
    foundNode = FindClosetNode(root, 13.6);
    assert(*foundNode->data == 14.0);
    foundNode = FindClosetNode(root, 14.0);
    assert(*foundNode->data == 14.0);
    foundNode = FindClosetNode_R(root, 14.3);
    assert(*foundNode->data == 14.0);
    foundNode = FindClosetNode(root, 14.6);
    assert(*foundNode->data == 15.0);
    foundNode = FindClosetNode(root, 15.0);
    assert(*foundNode->data == 15.0);
    foundNode = FindClosetNode(root, 15.3);
    assert(*foundNode->data == 15.0);
    foundNode = FindClosetNode(root, 15.6);
    assert(*foundNode->data == 16.0);
    foundNode = FindClosetNode(root, 16.0);
    assert(*foundNode->data == 16.0);
    foundNode = FindClosetNode(root, 16.3);
    assert(*foundNode->data == 16.0);
    foundNode = FindClosetNode(root, 100.0);
    assert(*foundNode->data == 16.0);
    DeleteTree_TD(&root);
}

int _tmain(int argc, _TCHAR* argv[])
{
    TestCasesOfCheckTwoTreesWithSameElements();
    TestCasesOfFirstAndLastOfEachLevelOfTree();
    TestCasesOfSumOfEachLevelOfTree();
    TestCasesOfNextInOrder();
    TestTreeTraverse();
    TestFindDuplicateSubTree();
    TestFindDuplicateSubTree2();
    TestFindDuplicateSubTree3();
    TestPyramidTree();
    TestPyramidArray();
    TestFindCloesetNode_R();
    TestFindCloesetNode();

    return 0;
}

// http://www.careercup.com/question?id=5714594192424960 done
// http://www.careercup.com/question?id=5088794078347264 done
// http://www.careercup.com/question?id=5630275595796480 done
// http://www.careercup.com/question?id=5164197555994624
// http://www.careercup.com/question?id=5131437827162112 done
// http://www.careercup.com/question?id=5133958972964864
// http://www.careercup.com/question?id=5678853664014336
// http://www.careercup.com/question?id=5737921569095680
// http://www.careercup.com/question?id=5673390490779648
// ABCABC -> ABBACC -> AABBCC