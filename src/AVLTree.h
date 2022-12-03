#ifndef AVLTREE_H
#define AVLTREE_H

using namespace std;
#include <string>
#include <iostream>
#include "SearchTree.h"

class AVLTree : public SearchTree
{
private:
    Node *root;
    void destroyRecursive(Node *node)
    {
        if (node != nullptr)
        {
            if (node->left != nullptr)
            {
                destroyRecursive(node->left);
            }
            if (node->right != nullptr)
            {
                destroyRecursive(node->right);
            }
            delete node;
        }
    }

    int getHeight(Node *node)
    {
        if (node != nullptr)
            return node->height;
        return -1;
    }

    int getBF(Node *node)
    {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node *leftRotate(Node *node)
    {
        Node *y = node->right;
        node->right = y->left;
        y->left = node;
        node->height = (getBF(node) > 0 ? getHeight(node->left) : getHeight(node->right)) + 1;
        if (getHeight(node->right) > node->height)
        {
            y->height = getHeight(node->right) + 1;
        }
        else
        {
            y->height = node->height + 1;
        }
        return y;
    }

    Node *RLRotate(Node *t)
    {
        t->right = rightRotate(t->right);
        return leftRotate(t);
    }

    Node *LRRotate(Node *t)
    {
        t->left = leftRotate(t->left);
        return rightRotate(t);
    }

    Node *rightRotate(Node *node)
    {
        Node *x = node->left;
        node->left = x->right;
        x->right = node;
        node->height = (getBF(node) > 0 ? getHeight(node->left) : getHeight(node->right)) + 1;
        if (getHeight(x->left) > node->height)
        {
            x->height = getHeight(x->left) + 1;
        }
        else
        {
            x->height = node->height + 1;
        }
        return x;
    }

    Node *insert(int key, Node *node)
    {
        if (node == nullptr)
        {
            node = new Node(key);
        }
        else if (key < node->key)
        {
            node->left = insert(key, node->left);
            if (getBF(node) == 2)
            {
                if (key < node->left->key)
                    node = rightRotate(node);
                else
                    node = LRRotate(node);
            }
        }
        else if (key > node->key)
        {
            node->right = insert(key, node->right);
            if (-getBF(node) == 2)
            {
                if (key > node->right->key)
                    node = leftRotate(node);
                else
                    node = RLRotate(node);
            }
        }
        node->height = (getBF(node) > 0 ? getHeight(node->left) : getHeight(node->right)) + 1;
        return node;
    }

    Node *findSucc(Node *node)
    {
        if (node == nullptr)
            return nullptr;
        else if (node->left == nullptr)
            return node;
        else
            return findSucc(node->left);
    }

    Node *remove(int key, Node *node)
    {
        Node *temp;
        if (node == nullptr)
            return nullptr;
        else if (key < node->key)
            node->left = remove(key, node->left);
        else if (key > node->key)
            node->right = remove(key, node->right);
        else if (node->left && node->right)
        {
            temp = findSucc(node->right);
            node->key = temp->key;
            node->right = remove(node->key, node->right);
        }
        else
        {
            temp = node;
            if (node->left == nullptr)
                node = node->right;
            else if (node->right == nullptr)
                node = node->left;
            delete temp;
        }
        if (node == nullptr)
            return node;

        node->height = (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right)) + 1;
        if (getHeight(node->left) - getHeight(node->right) == 2)
        {
            if (getHeight(node->left->left) - getHeight(node->left->right) == 1)
            {

                return rightRotate(node);
            }
            else
            {

                return LRRotate(node);
            }
        }
        else if (getHeight(node->right) - getHeight(node->left) == 2)
        {
            if (getHeight(node->right->right) - getHeight(node->right->left) == 1)
            {

                return leftRotate(node);
            }
            else
            {

                return RLRotate(node);
            }
        }
        return node;
    }

    Node *find(int key, Node *node)
    {
        if (node == nullptr)
            return nullptr;
        if (node->key == key)
            return node;

        auto lsearch = find(key, node->left);
        auto rsearch = find(key, node->right);
        if (lsearch != nullptr)
            return lsearch;
        if (rsearch != nullptr)
            return rsearch;
        return nullptr;
    }

public:
    AVLTree()
    {
        root = nullptr;
    }
    ~AVLTree()
    {
        destroyRecursive(root);
    }

    void insert(int data)
    {
        root = insert(data, root);
    }

    Node *find(int key)
    {
        Node *currNode = root;
        while (currNode != nullptr)
        {
            if (key < currNode->key)
            {
                currNode = currNode->left;
            }
            else if (key > currNode->key)
            {
                currNode = currNode->right;
            }
            else
            {
                return currNode;
            }
        }
        return currNode;
    }

    void remove(int key)
    {
        root = remove(key, root);
    }

    /* This function is borrowed from the internet just for debug printing of the tree */
    void printBT(const std::string &prefix, Node *node, bool isLeft)
    {
        if (node != nullptr)
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──");

            std::cout << node->key << "::" << node->height << std::endl;

            printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
            printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }

    void printBT()
    {
        printBT("", root, false);
    }
};

#endif