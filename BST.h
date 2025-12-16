#ifndef BST_H
#define BST_H

#include <iostream>
#include "Display.h"

using namespace std;

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
protected:
    TreeNode<T>* root;

    TreeNode<T>* insertRec(TreeNode<T>* node, T val) {
        if (node == nullptr) {
            return new TreeNode<T>(val);
        }

        if (val < node->data) {
            node->left = insertRec(node->left, val);
        } else if (val > node->data) {
            node->right = insertRec(node->right, val);
        }
        return node;
    }

    void inorderRec(TreeNode<T>* node) const {
        if (node != nullptr) {
            inorderRec(node->left);
            cout << node->data << " ";
            inorderRec(node->right);
        }
    }

    TreeNode<T>* searchRec(TreeNode<T>* node, T val) const {
        if (node == nullptr || node->data == val) {
            return node;
        }
        if (val < node->data) {
            return searchRec(node->left, val);
        }
        return searchRec(node->right, val);
    }

    TreeNode<T>* minValueNode(TreeNode<T>* node) {
        TreeNode<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    TreeNode<T>* deleteRec(TreeNode<T>* node, T val) {
        if (node == nullptr) return node;

        if (val < node->data) {
            node->left = deleteRec(node->left, val);
        } else if (val > node->data) {
            node->right = deleteRec(node->right, val);
        } else {
            if (node->left == nullptr) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode<T>* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = deleteRec(node->right, temp->data);
        }
        return node;
    }

    void clearRec(TreeNode<T>* node) {
        if (node) {
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}

    virtual ~BST() {
        clear();
    }

    void insert(T val) {
        root = insertRec(root, val);
    }

    void remove(T val) {
        root = deleteRec(root, val);
    }

    bool search(T val) const {
        return searchRec(root, val) != nullptr;
    }

    void display() const {
        inorderRec(root);
        cout << "\n";
    }

    void clear() {
        clearRec(root);
        root = nullptr;
    }
};

#endif
