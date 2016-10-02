#pragma once

#include "TreeNode.h"

template <typename T>
class DuplicateSubTreeDetector {
public:
    bool operator()(TreeNode<T>* root);

};