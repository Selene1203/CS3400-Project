#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
using namespace std;

template <typename T>
struct TreeNode {
    T data;
    bool occupied;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val) : data(val), occupied(false), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root;

    TreeNode<T>* insert(TreeNode<T>* node, T value) {
        if (node == nullptr)
            return new TreeNode<T>(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);
        return node;
    }

    void inorder(TreeNode<T>* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << " (Occupied: " << (node->occupied ? "Yes" : "No") << ")\n";
        inorder(node->right);
    }

    TreeNode<T>* findFree(TreeNode<T>* node) {
        if (node == nullptr) return nullptr;
        if (!node->occupied) return node;
        TreeNode<T>* left = findFree(node->left);
        if (left != nullptr) return left;
        return findFree(node->right);
    }

public:
    BinaryTree() : root(nullptr) {}

    void add(T value) {
        root = insert(root, value);
    }

    void assignBed(T value) {
        TreeNode<T>* node = root;
        while (node != nullptr) {
            if (node->data == value) {
                node->occupied = true;
                cout << "Bed " << value << " assigned.\n";
                return;
            } else if (value < node->data)
                node = node->left;
            else
                node = node->right;
        }
        cout << "Bed not found.\n";
    }

    void display() {
        inorder(root);
    }

    TreeNode<T>* findFreeBed() {
        return findFree(root);
    }
};

#endif
