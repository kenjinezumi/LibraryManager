#ifndef BST_H
#define BST_H

#include <iostream>
#include <mutex>
#include <vector>

template <typename T>
class BSTNode {
public:
    T data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
private:
    BSTNode<T>* root;
    mutable std::mutex mtx;

    void inorderHelper(BSTNode<T>* node, std::vector<T>& result) const {
        if (node) {
            inorderHelper(node->left, result);
            result.push_back(node->data);
            inorderHelper(node->right, result);
        }
    }

    BSTNode<T>* searchNode(BSTNode<T>* node, const T& value) const {
        if (!node || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return searchNode(node->left, value);
        }
        return searchNode(node->right, value);
    }

public:
    BST() : root(nullptr) {}

    BSTNode<T>* search(const T& value) const {
        std::lock_guard<std::mutex> lock(mtx);
        return searchNode(root, value);
    }

    void insert(const T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        BSTNode<T>* newNode = new BSTNode<T>(value);
        if (!root) {
            root = newNode;
            return;
        }
        BSTNode<T>* current = root;
        BSTNode<T>* parent = nullptr;
        while (current) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (value < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    std::vector<T> inorder() const {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<T> result;
        inorderHelper(root, result);
        return result;
    }
};

#endif
