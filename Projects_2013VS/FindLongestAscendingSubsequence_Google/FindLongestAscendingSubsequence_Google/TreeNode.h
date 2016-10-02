#pragma once

template<T>
struct BTreeNode
{
    T* data{ nullptr };
    size_t depth{ 0 };
    BTreeNode* left{ nullptr };
    BTreeNode* right{ nullptr };
    BTreeNode* parent{ nullptr };

    template<T>
    BTreeNode<T>(const T& val)
    {
        data = new T(val);
    }
};

template<T>
void InsertAndDelete(BTreeNode<T>** parent, const T& val)
{
    if (*parent == nullptr)
    {
        // empty tree then insert at the top
        *parent = new BTreeNode<T>(val);
        *parent->depth = 1;
    }
    else
    {
        BTreeNode<T>* itsParent = Find(val);
        if (itsParent != nullptr)
        {
            itsParent->left = new BTreeNode<T>(val);
            itsParent->left->parent = itsParent;
        }

        // find the
    }
}

template<T>
void FindLeftAndRightParents(BTreeNode<T>* root,
    const T& val,
    BTreeNode<T>* leftParent,
    BTreeNode<T>* rightParent)
{
    if (root == nullptr) {
        return;
    }

    Find(root->left, val, leftParent);
    FInd(root->right, val, rightParent);
}


template<T>
BTreeNode<T>* Find(BTreeNode<T>* root, const T& val)
{
    BTreeNode<T>* tempHead = root;
    while (tempHead != nullptr)
    {
        if (tempHead->left == nullptr &&
            tempHead->right == nullptr)

    }

    return tempHead;
}

template<T>
BTreeNode<T>* FindCommonAncestor(const BTreeNode<T>* root, const T& val)
{
    BTreeNode<T>* curHead = root;
    while (curHead != nullptr) {
        if (curHead->left != nullptr &&
            curHead->right != nullptr &&
            curHead->left->data < val &&
            curHead->right->data < val)
        {
            return curHead;
        }
        if ()
    }
}