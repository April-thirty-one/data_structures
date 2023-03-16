#ifndef DATA_STRUCTURES_11_CHAPTER_TREE_LINKEDBINARYTREE_H__
#define DATA_STRUCTURES_11_CHAPTER_TREE_LINKEDBINARYTREE_H__

#include "./binaryTreeNode.h"
#include "./binaryTree.h"

#include <queue>
#include <stack>

template <class T>
class linkedBinayTree {
public:
    linkedBinayTree();
    linkedBinayTree(const linkedBinayTree<T> & other);
    ~linkedBinayTree();

    bool empty() const;
    int size() const;
    std::vector<T> preOrder() const;
    std::vector<T> inOrder() const;
    std::vector<T> postOrder() const;
    std::vector<std::vector<T>> levelOrder() const;
    
    // 使用 二叉搜索樹 的模式進行插入
    void insert(const binaryTreeNode<T> * node);

private:
    binaryTreeNode<T> * root;
    int treeSize;

    // 輔助函數：輔助拷貝構造函數
    binaryTreeNode<T> * copyNode(binaryTreeNode<T> * node);
    
    // 輔助函數：輔助拷貝構造函數
    void func(const binaryTreeNode<T> * current, const binaryTreeNode<T> * target);

    // 輔助函數：使用遞歸的方式完成前中後序便利
    void preTraversal(binaryTreeNode<T> * current, std::vector<T> & result);
    void inTraversal(binaryTreeNode<T> * current, std::vector<T> & result);
    void postTraversal(binaryTreeNode<T> * current, std::vector<T> & result);
};

template <class T>
linkedBinayTree<T>::linkedBinayTree() : root(nullptr), treeSize(0) {}

template <class T>
binaryTreeNode<T> * linkedBinayTree<T>::copyNode(binaryTreeNode<T> * node)
{
    if (node == nullptr) {
        return nullptr;
    }
    else {
        binaryTreeNode<T> * newNode = new binaryTreeNode<T>(node->val);
        newNode->left = copyNode(node->left);
        newNode->right = copyNode(node->right);
        return newNode;
    }
}

template <class T>
linkedBinayTree<T>::linkedBinayTree(const linkedBinayTree<T> & other)
{
    this->root = copyNode(other.root);
}

template <class T>
linkedBinayTree<T>::~linkedBinayTree() 
{
    // 使用前序便利 delete 每個節點
    std::stack<binaryTreeNode<T> *> stack;
    if (this->root == nullptr) {
        return;
    }
    else {
        stack.push(this->root);
    }

    binaryTreeNode<T> * currentNode;
    while (!stack.empty()) {
        currentNode = stack.top();
        stack.pop();
        if (currentNode->right != nullptr) {
            stack.push(currentNode->right);
        }
        if (currentNode->left != nullptr) {
            stack.push(currentNode->left);
        }
        delete currentNode;
    }
}

template <class T>
bool linkedBinayTree<T>::empty() const 
{
    return this->treeSize == 0;
}

template <class T>
int linkedBinayTree<T>::size() const 
{
    return this->treeSize;
}

// 前序遍里
template <class T>
void preTraversal(binaryTreeNode<T> * current, std::vector<T> & result)
{
    if (current == nullptr) {
        return;
    }

    result.push_back(current->val);
    preTraversal(current->left, result);
    preTraversal(current->right, result);
}

template <class T>
std::vector<T> linkedBinayTree<T>::preOrder() const 
{
    std::vector<T> result;
    preTraversal(this->root, result);
    return result;
}

// 中序便利
template <class T>
void linkedBinayTree<T>::inTraversal(binaryTreeNode<T> * current, std::vector<T> & result)
{
    if (current == nullptr) {
        return;
    }

    inTraversal(current->left, result);
    result.push_back(current->val);
    inTraversal(current->right, result);
}

template <class T>
std::vector<T> linkedBinayTree<T>::inOrder() const 
{
    std::vector<T> result;
    inTraversal(this->root, result);
    return result;
}

template <class T>
void linkedBinayTree<T>::postTraversal(binaryTreeNode<T> * current, std::vector<T> & result)
{
    if (current == nullptr) {
        return;
    }

    postTraversal(current->left, result);
    postTraversal(current->right, result);
    result.push_back(current->val);
}

template <class T>
std::vector<T> linkedBinayTree<T>::postOrder() const 
{
    std::vector<T> result;
    postTraversal(this->root, result);
    return result;
}

template <class T>
std::vector<std::vector<T>> linkedBinayTree<T>::levelOrder() const 
{
    std::queue<binaryTreeNode<T> *> queue;
    std::vector<std::vector<T>> result;
    unsigned int currentSize = 0;
    unsigned int nextSize = 0;

    if (this->root == nullptr) {
        return result;
    }
    else {
        queue.push(this->root);
        currentSize += 1;
    }

    binaryTreeNode<T> * currentNode;
    while (!queue.empty()) {
        std::vector<T> temp;
        for (int i = 0; i < currentSize; i++) {
            currentNode = queue.top();
            queue.pop();
            temp.push_back(currentNode->val);

            if (currentNode->left != nullptr) {
                queue.push(currentNode->left);
                nextSize += 1;
            }
            if (currentNode->right != nullptr) {
                queue.push(currentNode->right);
                nextSize += 1;
            }
        }
        result.push_back(temp);
        currentSize = nextSize;
        nextSize = 0;
    }
    return result;
}

template <class T>
void linkedBinayTree<T>::func(const binaryTreeNode<T> * current, const binaryTreeNode<T> * target)
{
    if (current == nullptr) {
        current = target;
        return;
    }

    if (target->element <= current->element) {
        func(current->left, target);
    }
    else {
        func(current->right, target);
    }
}

template <class T>
void linkedBinayTree<T>::insert(const binaryTreeNode<T> * node)
{
    func(this->root, node);
}

#endif

