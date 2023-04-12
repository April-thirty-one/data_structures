#ifndef TREE_7_B_PLUE_TREE_B_PLUS_TREE_H__
#define TREE_7_B_PLUE_TREE_B_PLUS_TREE_H__

/**
    和BTree一样，没有父节点，所以表面上是6阶，实质上在检查时若是5个key就要分裂
    使用共用体，因为非叶子节点没有 next 指针，叶子节点没有 children 指针
*/
#include <concepts>
#include <iostream>
#include <ostream>
#include <queue>
#include "../../utils/utils.h"

const int degree = 3;

template <class T>
class BPlusTree;

template <class T>
std::ostream & operator << (std::ostream & out, const BPlusTree<T> & obj);

template <class T>
class BPlusTree 
{
public:
    class Node 
    {
    public:
        bool isLeaf;
        T * keys;
        int nums;
        union m_ptr {
            Node ** childrens;
            Node * next;
        } ptr;

    public:
        Node(bool isLeaf);
        ~Node();
    };

public:
    BPlusTree(); 
    ~BPlusTree();

    void insert(const T & key);

    friend std::ostream & operator << <>(std::ostream & out, const BPlusTree<T> & obj);

private:    // helper function
    void deleteTree_(Node * current);
    void insertKey_(Node * current, const T & key);
    void splitNode_(Node * parent, int idx);

private:
    Node * root;
};

template <class T>
BPlusTree<T>::Node::Node(bool isLeaf) : isLeaf(isLeaf), nums(0)
{
    this->keys = new T[degree * 2 - 1];
    if (this->keys == nullptr) {
        throw illegalError("Node constructor failed.");
    }
    if (!this->isLeaf) {
        this->ptr.childrens = new Node*[degree * 2];
        for (size_t i = 0; i < degree; i++) {
            this->ptr.childrens[i] = nullptr;
        }
    }
}

template <class T>
BPlusTree<T>::Node::~Node()
{
    if (this->keys != nullptr) {
        delete [] this->keys;
    }
}

template <class T>
BPlusTree<T>::BPlusTree()
{
    this->root = new Node(true);
    if (this->root == nullptr) {
        throw illegalError("BPlusTree constructor failed.");
    }
}

template <class T>
void BPlusTree<T>::deleteTree_(Node * current)
{
    if (current == nullptr) {
        return;
    }

    // 这里要多加一个条件，不然可能会操作空指针
    for (size_t i = 0; i <= current->nums && !current->isLeaf; i++) {
        this->deleteTree_(current->ptr.childrens[i]);
    }

    if (!current->isLeaf) {
        delete [] current->ptr.childrens;
    }
    delete current;
}

template <class T>
BPlusTree<T>::~BPlusTree()
{
    this->deleteTree_(this->root);
    this->root = nullptr;
}

/**
    @param current: 要添加key的节点(不一定是在当前节点添加)
    @param key: 要添加的 key
*/
template <class T>
void BPlusTree<T>::insertKey_(Node * current, const T & key)
{
    int idx = current->nums - 1;
    if (current->isLeaf) {      // 叶子节点
        while (idx >= 0 && key < current->keys[idx]) {
            current->keys[idx + 1] = current->keys[idx];
            idx -= 1;
        }
        current->keys[idx + 1] = key;
        current->nums += 1;
    }
    else {          // 非叶子节点
        idx = binarySearch(current->keys, current->nums, key);
        // 判断 key 在左右哪个子树中
        if (idx == -1) {
            idx += 1;
        }

        // if (key <= current->keys[idx]) {
        if (true) {
            if (current->ptr.childrens[idx]->nums == (degree * 2 - 1)) {
                this->splitNode_(current, idx);
            }
        }


        else { 


            if (current->ptr.childrens[idx + 1]->nums == (degree * 2 - 1)) {
                this->splitNode_(current, idx + 1);
                idx += 1;
            }
            idx += 1;
        }
        this->insertKey_(current->ptr.childrens[idx], key);
    }
}

/**
    先分裂，再插入 key
    非叶子节点的分裂 和 B树的非叶子节点 差不多
    叶子节点分裂会（有可能）将当前节点最大值保留在父节点中
    leftChild 中存放的是 <= currentKey
*/
template <class T>
void BPlusTree<T>::splitNode_(Node * parent, int idx)
{
    Node * current = parent->ptr.childrens[idx];
    Node * brother = new Node(current->isLeaf);
    // 处理叶子节点指针
    brother->ptr.next = current->ptr.next;
    current->ptr.next = brother;

    // 处理key -- 将 key 转移到 brother 中
    for (size_t i = 0; i < degree - 1; i++) {
        brother->keys[i] = current->keys[degree + i];
    }
    brother->nums = degree - 1;
    // 若是非叶子节点，处理孩子节点
    if (!current->isLeaf) {
        for (size_t i = 0; i < degree; i++) {
            brother->ptr.childrens[i] = current->ptr.childrens[degree + i];
        }
    }
    current->nums = degree;

    // 节点分裂后
    // 若是非叶子节点 -- 当前节点不保留key，key上升到 parent 节点中
    // 若是叶子节点 -- 当前节点保留 key，key 上升到 parent 节点中
    // 所以key无论如何都会上升到 parent 中
    for (int i = parent->nums; i > idx; i--) {
        parent->keys[i] = parent->keys[i - 1];
    }
    parent->keys[idx] = current->keys[current->nums - 1];
    if (!current->isLeaf) {
        current->nums -= 1;
    }
    // 现在处理 parent 的 children 指针
    for (int i = parent->nums + 1; i > idx + 1; i--) {
        parent->ptr.childrens[i] = parent->ptr.childrens[i - 1];
    }
    parent->ptr.childrens[idx + 1] = brother;
    parent->nums += 1;
}

template <class T>
void BPlusTree<T>::insert(const T & key)
{
    Node * current = this->root;
   
    // 检查根节点，因为根节点要一分为三，是特例
    if (current->nums == (degree * 2 - 1)) {
        Node * parent = new Node(false);
        this->root = parent;
        parent->ptr.childrens[0] = current;
        this->splitNode_(parent, 0);

        int idx = 0;
        // 左子树中存放 <= currentKey
        if (parent->keys[idx] < key) {
            idx += 1;
        }
        this->insertKey_(parent->ptr.childrens[idx], key);
    }
    else {
        this->insertKey_(current, key);
    }
}

template <class T>
std::ostream & operator << (std::ostream & out, const BPlusTree<T> & obj)
{
    using Node = typename BPlusTree<T>::Node;

    std::queue<Node *> queue;
    int sizeCurrent = 0;
    int sizeNext = 0;
    Node * current = obj.root;
    if (current != nullptr) {
        queue.push(current);
        sizeCurrent += 1;
    }
    while (!queue.empty()) {
        for (int i = 0; i < sizeCurrent; i++) {
            current = queue.front();
            queue.pop();
            for (size_t j = 0; j < current->nums; j++) {
                out << current->keys[j] << "  ";
            }
            out << "\t\t";
            if (!current->isLeaf) {
                for (int j = 0; j <= current->nums; j++) {
                  queue.push(current->ptr.childrens[j]);
                  sizeNext += 1;
                }
            }
        }
        out << std::endl;
        sizeCurrent = sizeNext;
        sizeNext = 0;
    }

    return out;
}

#endif
