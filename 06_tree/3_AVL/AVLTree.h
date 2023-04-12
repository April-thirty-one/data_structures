// 网址：https://blog.csdn.net/RealCoder/article/details/107580597

#include <algorithm>
#include <ostream>
#include "../../utils/utils.h"

template <class T>
class AVLTree;

template <class T>
std::ostream & operator << (std::ostream & out, const AVLTree<T> & obj);

template <class T>
class AVLTree {
public:
    class Node {
    public:
        Node(T key, 
             Node * left = nullptr, 
             Node * right = nullptr, 
             Node * parent = nullptr) 
             : key(key), left(left), right(right), parent(parent) {} 
        ~Node() {};

    public:
        T key;
        Node * left;
        Node * right;
        Node * parent;
    };

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    void insert(const T & key);
    void del(const T & key);
    int getTreeHeight() const;

    friend std::ostream & operator << <>(std::ostream & out, const AVLTree<T> & obj);

private:
    void deleteTree_(Node * current);
    void leftRotate_(Node * current);
    void rightRotate_(Node * current);
    void leftAndRightRotate_(Node * current);
    void rightAndLeftRotate_(Node * current);
    void print_(std::ostream & out, const Node * current) const;
    int getHeight_(Node * current) const;
    int getFactor_(const Node * current) const;
    void adjust_(Node * current);
    void delNode_(Node * current, const T & key);

private:
    Node * root;
};

template <class T>
void AVLTree<T>::deleteTree_(Node * current) 
{
    if (current == nullptr) {
        return;
    }

    this->deleteTree_(current->left);
    this->deleteTree_(current->right);
    delete current;
}

template <class T>
AVLTree<T>::~AVLTree()
{
    this->deleteTree_(this->root);
}

/**
    @param current : 旋转之前的根节点
*/
template <class T>
void AVLTree<T>::leftRotate_(Node * current)
{
     Node * newHead = current->right;

     current->right = newHead->left;
     if (newHead->left != nullptr) {
        newHead->left->parent = current;
     }

     newHead->parent = current->parent;
     if (current->parent == nullptr) {
        this->root = newHead;
     }
     else if (current->parent->left == current) {
        current->parent->left = newHead;
     }
     else {
        current->parent->right = newHead;
     }

     current->parent= newHead;
     newHead->left = current;
}

template <class T>
void AVLTree<T>::rightRotate_(Node * current)
{
    Node * newHead = current->left;

    current->left = newHead->right;
    if (newHead->right != nullptr) {
        newHead->right->parent = current;
    }

    newHead->parent = current->parent;
    if (current->parent == nullptr) {
        this->root = newHead;
    }
    else if (current->parent->left == current) {
        current->parent->left = newHead;
    }
    else {
        current->parent->right = newHead;
    }
    current->parent = newHead;

    newHead->right = current;
}

template <class T>
void AVLTree<T>::leftAndRightRotate_(Node * current)
{
    this->leftRotate_(current->left);
    this->rightRotate_(current);
}

template <class T>
void AVLTree<T>::rightAndLeftRotate_(Node * current)
{
    this->rightRotate_(current->right);
    this->leftRotate_(current);
}
    
template <class T>
void AVLTree<T>::insert(const T & key)
{
    Node * preNode = nullptr;
    Node * current = this->root;
    while (current != nullptr) {
        preNode = current;
        if (key < current->key) {
            current = current->left;
        }
        else if (key > current->key) {
            current = current->right;
        }
        else {
            return;
        }
    }
    if (preNode == nullptr) {
        this->root = new Node(key);
    }
    else if (key < preNode->key) {
        preNode->left = new Node(key, nullptr, nullptr, preNode);
    }
    else {
        preNode->right = new Node(key, nullptr, nullptr, preNode);
    }

    // 调整至平衡树
    this->adjust_(preNode);
}

template <class T>
void AVLTree<T>::print_(std::ostream & out, const Node * current) const
{
    if (current == nullptr) {
        return;
    }
    this->print_(out, current->left);
    out << current->key 
        << "("
        << this->getFactor_(current)
        << ")"
        << "  ";
    this->print_(out, current->right);
}

template <class T>
std::ostream & operator << (std::ostream & out, const AVLTree<T> & obj)
{
    obj.print_(out, obj.root);
    // out << std::endl << obj.getFactor_(obj.root);
    return out;
}

template <class T>
int AVLTree<T>::getHeight_(Node * current) const
{
    if (current == nullptr) {
        return 0;
    }

    return 1 + std::max(this->getHeight_(current->left), this->getHeight_(current->right));
}

template <class T>
int AVLTree<T>::getTreeHeight() const
{
    return this->getHeight_(this->root);
}

template <class T>
int AVLTree<T>::getFactor_(const Node * current) const
{
    return this->getHeight_(current->left) - this->getHeight_(current->right);
}

template <class T>
void AVLTree<T>::adjust_(Node * current)
{
    while (current != nullptr) {
        int factor = this->getFactor_(current);
        if (factor >= -1 && factor <= 1) {
            current = current->parent;
        } else if (factor == 2) {  // 左高
            int leftFactor = this->getFactor_(current->left);
            if (leftFactor == 1) {
                this->rightRotate_(current);
            } else {
                this->leftAndRightRotate_(current);
            }
        } else {
            int rightFactor = this->getFactor_(current->right);
            if (rightFactor == -1) {
                this->leftRotate_(current);
            } else {
                this->rightAndLeftRotate_(current);
            }
        }
    }
}

template <class T>
void AVLTree<T>::delNode_(Node * current, const T & key)
{
    if (current == nullptr) {
        return;
    }

    if (key < current->key) {
        this->delNode_(current->left, key);
    }
    else if (key > current->key) {
        this->delNode_(current->right, key);
    }
    else {
        Node * parent = current->parent;
        if (current->left == nullptr && current->right == nullptr) {
            if (parent == nullptr) {
                this->root = nullptr;
            }
            else if (parent->left == current) {
                parent->left = nullptr;
            }
            else {
                parent->right = nullptr;
            }
            delete current;
            current = nullptr;
        }
        else if (current->left != nullptr && current->right == nullptr) {
            if (parent == nullptr) {
                this->root = current->left;
            }
            else if (parent->left == current) {
                parent->left = current->left;
            }
            else {
                parent->right = current->left;
            }
            delete current;
            current = nullptr;
        }
        else if (current->left == nullptr && current->right != nullptr) {
            if (parent == nullptr) {
                this->root = current->right;
            }
            else if (parent->left == current) {
                parent->left = current->right;
            }
            else {
                parent->right = current->right;
            }
            delete current;
            current = nullptr;
        }
        else {
            Node * deleteNode = current->right;
            while (deleteNode->left != nullptr) {
                deleteNode = deleteNode->left;
            }
            current->key = deleteNode->key;
            this->delNode_(current->right, deleteNode->key);
        }
        // 调整
        this->adjust_(parent);
    }
}

template <class T>
void AVLTree<T>::del(const T & key)
{
    this->delNode_(this->root, key);
}