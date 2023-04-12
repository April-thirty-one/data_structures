#ifndef BINARYTREE_COMMONBINARYTRE
#define BINARYTREE_COMMONBINARYTRE

/**
    README
    这是一个 普通二叉树
    内部集成了 中序遍历迭代器、前序遍历迭代器、后续遍历迭代器、层次遍历迭代器 （使用非递归的方式完成）
    插入节点是按照 二叉搜索树 的标准编写的
    得到树高
    子树的高度差
    子树的最大高度差
    前序遍历，后序遍历、中序遍历（使用 递归的方法完成） 和 层次遍历
*/

#include "../../utils/utils.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

template <class T>
class CommonBinaryTree
{
// 节点类
public:
    class Node 
    {  
    public:
        Node(const T & element, Node * left = nullptr, Node * right = nullptr) : element(element), left(left), right(right) {}
        ~Node() {}

    public:
        Node * left;
        Node * right;
        T element;
    };

// 中序遍历迭代器
public:
    class InOrderIterator
    {
    public:
        InOrderIterator(Node * root);

        T operator * () { return nodeStack.top()->element; }
        Node * operator -> () { return nodeStack.top(); }
        InOrderIterator & operator ++ ();
        bool operator != (const InOrderIterator & other) { return nodeStack != other.nodeStack; }


    private:
        // helper function
        void pushLeftNodes_(Node * taregt);

    private:
        std::stack<Node *> nodeStack;
    };

    InOrderIterator inBegin() { return InOrderIterator(this->root); }
    InOrderIterator inEnd() { return InOrderIterator(nullptr); }

// 前序遍历迭代器
public:
    class PreOrderIterator
    {
    public:
        PreOrderIterator(Node * root) { current = root; }

        T operator * () { return current->element; }
        Node * operator -> () { return current; }
        bool operator != (const PreOrderIterator & other) { return current != other.current; }
        PreOrderIterator & operator ++ ();

    private:
        std::stack<Node *> nodeStack;
        Node * current;
    };

    PreOrderIterator preBegin() { return PreOrderIterator(this->root); }
    PreOrderIterator preEnd() { return PreOrderIterator(nullptr); }

// 后续遍历迭代器
public:
    class PostOrderIterator
    {
    public:
        PostOrderIterator(Node * root);

        T operator * () { return current->element; }
        Node * operator -> () { return current; } 
        bool operator != (const PostOrderIterator & other) { return current != other.current; }
        PostOrderIterator & operator ++ ();

    private:
        std::stack<Node *> nodeStack;
        Node * current;
        Node * lastPtr;
    };

    PostOrderIterator postBegin() { return PostOrderIterator(this->root); }
    PostOrderIterator postEnd() { return PostOrderIterator(nullptr); }

// 层次遍历 迭代器
public:
    class LevelOrderIterator
    {
    public:
        LevelOrderIterator(Node * root) { 
            current = root; 
            if (current != nullptr) {
                if (current->left != nullptr) {
                    nodeQueue.push(current->left);
                }
                if (current->right != nullptr) {
                    nodeQueue.push(current->right);
                }
            }
        }

        T operator * () { return current->element; }
        Node * operator -> () { return current; }
        bool operator != (const LevelOrderIterator & other) { return current != other.current; }
        LevelOrderIterator & operator ++ ();

    private:
        std::queue<Node *> nodeQueue;
        Node * current;
    };

    LevelOrderIterator levelBegin() { return LevelOrderIterator(this->root); }
    LevelOrderIterator levelEnd() { return LevelOrderIterator(nullptr); } 

public:
    // 构造函数、复制构造函数、析构函数
    CommonBinaryTree();
    CommonBinaryTree(const CommonBinaryTree<T> & otherTree);
    ~CommonBinaryTree();

    void insert(const T & element);             // 搜索树的插入，并不是随意的插入
    void print() const;                         // 按照层次遍历进行打印
    int getHeight() const;                      // 树的高度
    bool isSame(const CommonBinaryTree<T> & otherTree) const;           // 判断两颗树是否相同
    std::vector<T> preOrder() const;            // 前序遍历
    std::vector<T> inOrder() const;             // 中序遍历
    std::vector<T> postOrder() const;           // 后续遍历
    std::vector<T> levelOrder() const;          // 层次遍历
    void swapTrees();                           // 交换一颗树的左右节点
    int heightDifference(const Node * target) const;  // taregt 左右子树的高度差 
    int maxHeightDifference() const;            // 这棵树的最大子树高度差

private:
    // helper function
    void deleteTree_(Node * target);
    int getHeight_(Node * target) const;
    Node * copyTree_(Node * current, const Node * target);
    bool isSame_(const Node * srcNode, const Node * desNode) const;
    void preOrder_(const Node * target, std::vector<T> & result) const;
    void inOrder_(const Node * target, std::vector<T> & result) const;
    void postOrder_(const Node * target, std::vector<T> & result) const;
    void swapTrees_(Node * target);
    int maxHeightDifference_(const Node * target) const; 

private:
    Node * root;
};

template <class T>
typename CommonBinaryTree<T>::Node * CommonBinaryTree<T>::copyTree_(Node * current, const Node * target)
{
    if (target == nullptr) {
        return current;
    }
    current = new Node(target->element);        // current 的值发生了变化，因为他指向了一个新的地址空间
    current->left = this->copyTree_(current->left, target->left);
    current->right = this->copyTree_(current->right, target->right);
    return current;
}

template <class T>
CommonBinaryTree<T>::CommonBinaryTree(const CommonBinaryTree<T> & otherTree)
{
    Node * current = this->root;
    this->root = this->copyTree_(current, otherTree.root);
}

template <class T>
CommonBinaryTree<T>::CommonBinaryTree() 
{
    this->root = nullptr;
}

template <class T>
void CommonBinaryTree<T>::deleteTree_(Node * target)
{
    if (target == nullptr) {
        return;
    }

    this->deleteTree_(target->left);
    this->deleteTree_(target->right);    
    delete target;
}

template <class T>
CommonBinaryTree<T>::~CommonBinaryTree()
{
    Node * current = this->root;
    this->deleteTree_(current);
}

template <class T>
void CommonBinaryTree<T>::insert(const T & element) 
{
    Node * parent = nullptr;
    Node * current = this->root;
    while (current != nullptr) {
        parent = current;
        if (element < current->element) {
            current = current->left;
        }
        else if (element > current->element) {
            current = current->right;
        }
        else {
            throw illegalError("target element already exist");
        }
    }
    Node * insertNode = new Node(element);
    if (parent == nullptr) {
        this->root = insertNode;
    }
    else {
        if (element < parent->element) {
            parent->left = insertNode;
        }
        else {
            parent->right = insertNode;
        }
    }
}

template <class T>
void CommonBinaryTree<T>::print() const
{
    Node * current;
    std::queue<Node *> queue;
    if (this->root != nullptr) {
        queue.push(this->root);
    }
    while (!queue.empty()) {
        current = queue.front();
        queue.pop();
        std::cout << current->element << "  ";
        if (current->left != nullptr) {
            queue.push(current->left);
        }
        if (current->right != nullptr) {
            queue.push(current->right);
        }
    }
    std::cout << std::endl;
}

template <class T>
int CommonBinaryTree<T>::getHeight_(Node * target) const
{
    int height = 0;
    if (target == nullptr) {
        return height;
    }
    height += 1;

    height += std::max(this->getHeight_(target->left), this->getHeight_(target->right));
    return height;
}

template <class T>
int CommonBinaryTree<T>::getHeight() const
{
    return this->getHeight_(this->root);
}

template <class T>
bool CommonBinaryTree<T>::isSame_(const Node * srcNode, const Node * desNode) const
{
    if (srcNode == nullptr && desNode == nullptr) {
        return true;
    }
    else if (srcNode == nullptr || desNode == nullptr) {
        return false;
    }
    else if (srcNode->element != desNode->element) {
        return false;
    }

    bool left = this->isSame_(srcNode->left, desNode->left);
    bool right = this->isSame_(srcNode->right, desNode->right);
    return (left && right);
}

template <class T>
bool CommonBinaryTree<T>::isSame(const CommonBinaryTree<T> & otherTree) const
{
    return this->isSame_(this->root, otherTree.root);    
}

template <class T>
void CommonBinaryTree<T>::preOrder_(const Node * target, std::vector<T> & result) const
{
    if (target == nullptr) {
        return;
    }

    result.push_back(target->element);
    this->preOrder_(target->left, result);
    this->preOrder_(target->right, result);
}

template <class T>
std::vector<T> CommonBinaryTree<T>::preOrder() const
{
    std::vector<T> result;
    this->preOrder_(this->root, result);
    return result;
}

template <class T>
void CommonBinaryTree<T>::inOrder_(const Node * target, std::vector<T> & result) const
{
    if (target == nullptr) {
        return;
    }

    this->inOrder_(target->left, result);
    result.push_back(target->element);
    this->inOrder_(target->right, result);
}

template <class T>
std::vector<T> CommonBinaryTree<T>::inOrder() const
{
     std::vector<int> result;
     this->inOrder_(this->root, result);
     return result;
}

template <class T>
void CommonBinaryTree<T>::postOrder_(const Node * target, std::vector<T> & result) const
{
    if (target == nullptr) {
        return;
    }

    this->postOrder_(target->left, result);
    this->postOrder_(target->right, result);
    result.push_back(target->element);
}

template <class T>
std::vector<T> CommonBinaryTree<T>::postOrder() const
{
    std::vector<T> result;
    this->postOrder_(this->root, result);
    return result;
}

template <class T>
std::vector<T> CommonBinaryTree<T>::levelOrder() const 
{
    std::queue<Node *> queue;
    std::vector<T> result;
    if (this->root != nullptr) {
        queue.push(this->root);
    }
    Node * current;
    while (!queue.empty()) {
        current = queue.front();
        queue.pop();
        result.push_back(current->element);
        if (current->left != nullptr) {
            queue.push(current->left);
        }
        if (current->right != nullptr) {
            queue.push(current->right);
        }
    }
    return result;
}

template <class T>
void CommonBinaryTree<T>::swapTrees_(Node * target)
{
    if (target == nullptr) {
        return;
    }
     
    Node * temp = target->left;
    target->left = target->right;
    target->right = temp;
}

template <class T>
void CommonBinaryTree<T>::swapTrees()
{
    this->swapTrees_(this->root);
}

template <class T>
int CommonBinaryTree<T>::heightDifference(const Node * target) const
{
    return std::abs(this->getHeight_(target->left) - this->getHeight_(target->right));
}

template <class T>
int CommonBinaryTree<T>::maxHeightDifference_(const Node * target) const
{
    if (target == nullptr) {
        return 0;
    }

    return std::max(this->heightDifference(target), 
                    std::max(this->maxHeightDifference_(target->left), 
                             this->maxHeightDifference_(target->right)
                    )
            ); 
}

template <class T>
int CommonBinaryTree<T>::maxHeightDifference() const
{
    return this->maxHeightDifference_(this->root);
}

template <class T>
void CommonBinaryTree<T>::InOrderIterator::pushLeftNodes_(Node * taregt)
{
    while (taregt != nullptr) {
        this->nodeStack.push(taregt);
        taregt = taregt->left;
    }
}

template <class T>
CommonBinaryTree<T>::InOrderIterator::InOrderIterator(Node * root)
{
    this->pushLeftNodes_(root);
}

template <class T>
typename CommonBinaryTree<T>::InOrderIterator & CommonBinaryTree<T>::InOrderIterator::operator ++ ()
{
    Node * current = this->nodeStack.top();
    this->nodeStack.pop();
    if (current->right != nullptr) {
        this->pushLeftNodes_(current->right);
    }
    return *this;
}

template <class T>
typename CommonBinaryTree<T>::PreOrderIterator & CommonBinaryTree<T>::PreOrderIterator::operator ++ ()
{
    if (this->current == nullptr) {
        return *this;
    }

    if (this->current != nullptr) {
        if (this->current->right != nullptr) {
            this->nodeStack.push(current->right);
        }
        if (this->current->left != nullptr) {
            this->nodeStack.push(current->left);
        }
    }
    
    if (!this->nodeStack.empty()) {
        this->current = this->nodeStack.top();
        this->nodeStack.pop();
    }
    else {
        this->current = nullptr;
    }

    return *this;
}

template <class T>
CommonBinaryTree<T>::PostOrderIterator::PostOrderIterator(Node * root)
{
    this->current = root;
    this->lastPtr = nullptr;

    while (current != nullptr) {
        while (current != nullptr) {
            this->nodeStack.push(this->current);
            this->current = this->current->left;
        }
        this->current = this->nodeStack.top()->right;
    }
    if (!this->nodeStack.empty()) {
        this->current = this->nodeStack.top();
        this->nodeStack.pop();
        this->lastPtr = this->current;
    }
}

template <class T>
typename CommonBinaryTree<T>::PostOrderIterator & CommonBinaryTree<T>::PostOrderIterator::operator ++ ()
{
    if (!this->nodeStack.empty()) {
        this->current = this->nodeStack.top();
        // 存在右子树且没有被访问过
        if (this->current->right != nullptr && this->current->right != this->lastPtr) {
            this->current = this->current->right;
            // 找到下一个最左边的叶子节点
            while (this->current != nullptr) {
                while (this->current != nullptr) {
                    this->nodeStack.push(this->current);
                    this->current = this->current->left;
                }
                this->current = this->nodeStack.top()->right;
            }
            this->current = this->nodeStack.top();
            // this->lastPtr = this->current;
        }
        this->lastPtr = this->current;
        this->nodeStack.pop();
    }
    else {
        // 遍历结束
        this->current = nullptr;
    }
    return *this;
}

template <class T>
typename CommonBinaryTree<T>::LevelOrderIterator & CommonBinaryTree<T>::LevelOrderIterator::operator ++ ()
{
    if (!this->nodeQueue.empty()) {
        this->current = this->nodeQueue.front();
        this->nodeQueue.pop();
        if (this->current->left != nullptr) {
            this->nodeQueue.push(this->current->left);
        }
        if (this->current->right != nullptr) {
            this->nodeQueue.push(this->current->right);
        }
    }
    else {
        this->current = nullptr;
    }
    return *this;
}

#endif