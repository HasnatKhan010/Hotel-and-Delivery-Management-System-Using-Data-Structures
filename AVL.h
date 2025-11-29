#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <algorithm> 
#include "Display.h"

using namespace std;

template <typename T>
struct AVLNode {
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVL {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* N) {
        if (N == nullptr) return 0;
        return N->height;
    }

    int getBalance(AVLNode<T>* N) {
        if (N == nullptr) return 0;
        return height(N->left) - height(N->right);
    }

    AVLNode<T>* rightRotate(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode<T>* leftRotate(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode<T>* insertRec(AVLNode<T>* node, T val) {
        if (node == nullptr) return new AVLNode<T>(val);

        if (val < node->data)
            node->left = insertRec(node->left, val);
        else if (val > node->data)
            node->right = insertRec(node->right, val);
        else
            return node; 

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && val < node->left->data)
            return rightRotate(node);

        if (balance < -1 && val > node->right->data)
            return leftRotate(node);

        if (balance > 1 && val > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }


        if (balance < -1 && val < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    void inorderRec(AVLNode<T>* node) const {
        if (node != nullptr) {
            inorderRec(node->left);
            cout << node->data << " ";
            inorderRec(node->right);
        }
    }

    void clearRec(AVLNode<T>* node) {
        if (node) {
            clearRec(node->left);
            clearRec(node->right);
            delete node;
        }
    }

public:
    AVL() : root(nullptr) {}

    ~AVL() {
        clear();
    }

    void insert(T val) {
        root = insertRec(root, val);
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
