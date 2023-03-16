#ifndef DATA_STRUCTURES_11_CHAPTER_TREE_BINARYTREENODE_H__
#define DATA_STRUCTURES_11_CHAPTER_TREE_BINARYTREENODE_H__

template <typename T>
struct binaryTreeNode {
    T element;
    binaryTreeNode<T> * left;
    binaryTreeNode<T> * right;

    binaryTreeNode();
    binaryTreeNode(const T & element, binaryTreeNode<T> * left = nullptr, binaryTreeNode<T> * right = nullptr);
};

template <typename T>
binaryTreeNode<T>::binaryTreeNode() : left(nullptr), right(nullptr)
{
}

template <typename T>
binaryTreeNode<T>::binaryTreeNode(const T & element, binaryTreeNode<T> * left, binaryTreeNode<T> * right) : element(element), left(left), right(right)
{
}

#endif // !DATA_STRUCTURES_11_CHAPTER_TREE_BINARYTREENODE_H__
