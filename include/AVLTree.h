#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class AVLNode {
public:
    T key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const T& k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode<T>* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode<T>* node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    AVLNode<T>* balance(AVLNode<T>* node) {
        updateHeight(node);
        if (balanceFactor(node) == 2) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balanceFactor(node) == -2) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode<T>* insert(AVLNode<T>* node, const T& key) {
        if (!node) return new AVLNode<T>(key);
        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;
        return balance(node);
    }

    AVLNode<T>* findMin(AVLNode<T>* node) {
        return node->left ? findMin(node->left) : node;
    }

    AVLNode<T>* removeMin(AVLNode<T>* node) {
        if (!node->left) return node->right;
        node->left = removeMin(node->left);
        return balance(node);
    }

    AVLNode<T>* remove(AVLNode<T>* node, const T& key) {
        if (!node) return nullptr;
        if (key < node->key)
            node->left = remove(node->left, key);
        else if (key > node->key)
            node->right = remove(node->right, key);
        else {
            AVLNode<T>* left = node->left;
            AVLNode<T>* right = node->right;
            delete node;
            if (!right) return left;
            AVLNode<T>* min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            return balance(min);
        }
        return balance(node);
    }

    void inorder(AVLNode<T>* node, std::vector<T>& result) const {
        if (node) {
            inorder(node->left, result);
            result.push_back(node->key);
            inorder(node->right, result);
        }
    }

    AVLNode<T>* searchNode(AVLNode<T>* node, const T& key) const {
        if (!node || node->key == key)
            return node;
        if (key < node->key)
            return searchNode(node->left, key);
        else
            return searchNode(node->right, key);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const T& key) {
        root = insert(root, key);
    }

    void remove(const T& key) {
        root = remove(root, key);
    }

    std::vector<T> inorder() const {
        std::vector<T> result;
        inorder(root, result);
        return result;
    }

    T* search(const T& key) const {
        AVLNode<T>* node = searchNode(root, key);
        return node ? &node->key : nullptr;
    }
};

#endif // AVLTREE_H
