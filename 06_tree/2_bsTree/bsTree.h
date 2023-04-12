#ifndef TREE_BSTREE_BSTREE_H__
#define TREE_BSTREE_BSTREE_H__

#include <iostream>
#include <memory>
#include <utility>
#include "../../utils/utils.h"
#include "mcheck.h"

template <class K, class E>
class BinarySearchTree;

template <class K, class E>
std::ostream & operator << (std::ostream & out, const BinarySearchTree<K, E> & obj);

template <class K, class E>
class BinarySearchTree 
{
public:
    class Node 
    {
    public:
        Node(const std::pair<K, E> & thePair, Node * left = nullptr, Node * right = nullptr) : element(thePair), left(left), right(right) {}
        ~Node() {}
    public:
        std::pair<K, E> element;
        Node * left;
        Node * right;
    };
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree();

    void insert(const std::pair<K, E> & thePair);
    void erase(const K & key);
    std::pair<K, E> & find(const K & key) const;
    friend std::ostream & operator << <>(std::ostream & out, const BinarySearchTree<K, E> & obj);

private:
    // helper function
    void deleteTree_(Node * current);
    Node * insertNode_(Node * current, const std::pair<K, E> & thePair);
    void print_(std::ostream & out, Node * current) const;
    Node * erase_(Node * current, const K & key);

private:
    Node * root;
};

template <class K, class E>
void BinarySearchTree<K, E>::deleteTree_(Node * current) 
{
    if (current == nullptr) {
        return;
    }

    this->deleteTree_(current->left);
    this->deleteTree_(current->right);
    delete current;
}

template <class K, class E>
BinarySearchTree<K, E>::~BinarySearchTree() 
{
    this->deleteTree_(this->root);
}

template <class K, class E>
typename BinarySearchTree<K, E>::Node * BinarySearchTree<K, E>::insertNode_(Node * root, const std::pair<K, E> & thePair)
{
    if (root == nullptr) {
        return new Node(thePair);
    }

    if (thePair.first < root->element.first) {
        root->left = this->insertNode_(root->left, thePair);
    }
    else if (thePair.first > root->element.first) {
        root->right = this->insertNode_(root->right, thePair);
    }
    return root;
}

template <class K, class E>
void BinarySearchTree<K, E>::insert(const std::pair<K, E> & thePair)
{
    this->root = this->insertNode_(this->root, thePair);
}

template <class K, class E>
void BinarySearchTree<K, E>::print_(std::ostream & out, Node * current) const
{
    if (current == nullptr) {
        return;
    }

    this->print_(out, current->left);
    out << "(" << current->element.first << ", " << current->element.second << ")" << "   ";
    this->print_(out, current->right);
}

template <class K, class E>
std::ostream & operator << (std::ostream & out, const BinarySearchTree<K, E> & obj)
{
    obj.print_(out, obj.root);
    return out;
}

template <class K, class E>
typename BinarySearchTree<K, E>::Node * BinarySearchTree<K, E>::erase_(Node * current, const K & key)
{
    if (current == nullptr) {
        return nullptr;
    }

    if (key < current->element.first) {
        current->left = this->erase_(current->left, key);
        return current;
    }
    else if (key > current->element.first) {
        current->right = this->erase_(current->right, key);
        return current;
    }
    else {
        // 找到了
        Node * deleteNode = current;
        if (current->left == nullptr) {
            current = current->right;
            delete deleteNode;
        }
        else if (current->right == nullptr) {
            current = current->left;
            delete deleteNode;
        }
        else {
            deleteNode = current->right;
            while (deleteNode->left != nullptr) {
                deleteNode = deleteNode->left;
            }
            current->element = deleteNode->element;
            current->right = this->erase_(current->right, deleteNode->element.first);
        }
        return current;
    }
}

template <class K, class E>
void BinarySearchTree<K, E>::erase(const K & key)
{
    this->root = this->erase_(this->root, key);
}


template <class K, class E>
std::pair<K, E> & BinarySearchTree<K, E>::find(const K & key) const
{
    Node * current = this->root;
    while (current != nullptr) {
        if (key < current->element.first) {
            current = current->left;
        }
        else if (key > current->element.first) {
            current = current->right;
        }
        else {
            return current->element;
        }
    }

    throw illegalError("there is no target key in current search tree.");
}

#endif
