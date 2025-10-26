#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include "linkedList.h"
using namespace std;

template <typename T>
struct TreeNode {
    T data;
    bool occupied;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(T val) : data(val), occupied(false), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root;
    // Maintain an auxiliary linked list of pointers to tree nodes in in-order
    LinkedList<TreeNode<T>*> nodeList;
    // AVL helpers
    int height(TreeNode<T>* node) {
        return node ? node->height : 0;
    }

    int getBalance(TreeNode<T>* node) {
        if (!node) return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(TreeNode<T>* node) {
        if (node) node->height = 1 + std::max(height(node->left), height(node->right));
    }

    TreeNode<T>* rotateRight(TreeNode<T>* y) {
        TreeNode<T>* x = y->left;
        TreeNode<T>* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    TreeNode<T>* rotateLeft(TreeNode<T>* x) {
        TreeNode<T>* y = x->right;
        TreeNode<T>* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    TreeNode<T>* insert(TreeNode<T>* node, T value) {
        // Standard BST insert
        if (node == nullptr) {
            TreeNode<T>* newTreeNode = new TreeNode<T>(value);

            // Insert pointer into auxiliary in-order linked list
            Node<TreeNode<T>*>* head = nodeList.getHead();
            if (head == nullptr || value < head->data->data) {
                nodeList.insertAtFront(newTreeNode);
            } else {
                // find insert position (before first node with data > value)
                Node<TreeNode<T>*>* cur = head;
                while (cur->next != nullptr && cur->next->data->data < value)
                    cur = cur->next;

                Node<TreeNode<T>*>* newListNode = new Node<TreeNode<T>*>(newTreeNode);
                newListNode->next = cur->next;
                cur->next = newListNode;
            }

            return newTreeNode;
        }

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (node->data < value)
            node->right = insert(node->right, value);
        else
            return node; // equal keys not inserted

        // Update height of this ancestor node
        updateHeight(node);

        // Get balance factor
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && node->right && node->right->data < value)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && node->left && node->left->data < value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && node->right && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

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
        // Prefer left subtree first to find lowest-value free bed
        TreeNode<T>* left = findFree(node->left);
        if (left != nullptr && !left->occupied) return left;
        if (!node->occupied) return node;
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

    // Find node by value (non-destructive). Returns nullptr if not found.
    TreeNode<T>* find(T value) {
        TreeNode<T>* node = root;
        while (node != nullptr) {
            if (node->data == value)
                return node;
            else if (value < node->data)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    TreeNode<T>* findFreeBed() {
        return findFree(root);
    }
};

#endif
