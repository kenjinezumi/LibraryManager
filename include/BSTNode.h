#ifndef BSTNODE_H
#define BSTNODE_H

template <typename T>
class BSTNode {
public:
    T key;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const T& data) : data(data), left(nullptr), right(nullptr) {}
};

#endif // BSTNODE_H
