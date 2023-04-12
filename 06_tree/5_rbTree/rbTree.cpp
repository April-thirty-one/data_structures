#include <iostream>
#include <queue>

class rbTree {
public:
    struct rbTreeNode {
        int key;
        rbTreeNode * left;
        rbTreeNode * right;
        rbTreeNode * parent;

        unsigned char color;

        rbTreeNode(int key = 0, 
                   rbTreeNode * left = nullptr, 
                   rbTreeNode * right = nullptr, 
                   rbTreeNode * parent = nullptr, 
                   unsigned char color = nodeColor::RED) 
        : key(key), left(left), right(right), parent(parent), color(color) {}
    };

public:
    rbTree();
    ~rbTree();
    void rbTreeInsert(int key);
    rbTreeNode * reTreeSearch(int key);
    void rbTreeTraversal();
    void deleteNode(int theKey);
    void deleteNoOrOneChildNode(rbTreeNode * preNode, rbTreeNode * curNode);
    void deleteFixUp(rbTreeNode * node);

private:
    rbTreeNode * root;
    rbTreeNode * nil;

    enum nodeColor {
        RED,
        BLACK
    };

private:
    void preOrder(rbTreeNode * node);
    void inOrder(rbTreeNode * node);
    void rbTreeLeftRotate(rbTreeNode * targetNode);
    void rbTreeRightRotate(rbTreeNode * targetNode);
    void deleteTree(rbTreeNode * node);
    void rbTreeInsertFixup(rbTreeNode * targetNode);
};

rbTree::rbTree()
{
    this->nil = new rbTreeNode;
    this->root = this->nil;
}

void rbTree::deleteTree(rbTree::rbTreeNode * node) 
{
    if (node == this->nil) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

rbTree::~rbTree()
{
    deleteTree(this->root);
    delete this->nil;
}

void rbTree::rbTreeLeftRotate(rbTreeNode * targetNode)
{
    rbTreeNode * head = targetNode->right;

    targetNode->right = head->left;
    if (head->left != this->nil) {
        head->left->parent = targetNode;
    }

    head->parent = targetNode->parent;
    if (targetNode->parent == this->nil) {
        this->root = head;
    }
    else if (targetNode->parent->left == targetNode) {
        targetNode->parent->left = head;
    }
    else {
        targetNode->parent->right = head;
    }

    targetNode->parent = head;
    head->left = targetNode;
}

void rbTree::rbTreeRightRotate(rbTreeNode * targetNode)
{
    rbTreeNode * head = targetNode->left;
    
    targetNode->left = head->right;
    if (head->right != this->nil) {
        head->right->parent = targetNode;
    }

    head->parent = targetNode->parent;
    if (targetNode->parent == this->nil) {
        this->root = head;
    }
    else if (targetNode->parent->left == targetNode) {
        targetNode->parent->left = head;
    }
    else {
        targetNode->parent->right = head;
    }

    targetNode->parent = head;
    head->right = targetNode;
}

void rbTree::rbTreeInsert(int key)
{
    rbTreeNode * preNode = this->nil;
    rbTreeNode * currentNode = this->root;
    while (currentNode != this->nil) {
        preNode = currentNode;
        if (key > currentNode->key) {
            currentNode = currentNode->right;
        }
        else if (key < currentNode->key) {
            currentNode = currentNode->left;
        }
        else {
            return;
        }
    }

    rbTreeNode * targetNode = new rbTreeNode(key);
    if (preNode == this->nil) {
        // 表示这是一个空树
        this->root = targetNode;
    }
    else {
        if (targetNode->key > preNode->key) {
            preNode->right = targetNode; 
        }
        else {
            preNode->left = targetNode;
        }
    }
    targetNode->parent = preNode;
    targetNode->left = this->nil;
    targetNode->right = this->nil;
    targetNode->color = nodeColor::RED;

    // 进行调整
    rbTreeInsertFixup(targetNode);
}

void rbTree::rbTreeInsertFixup(rbTreeNode * targetNode)
{
    rbTreeNode * parent = targetNode->parent;
    rbTreeNode * ancleNode;

    while (parent != this->nil && parent->color == nodeColor::RED) {
        if (parent->parent != this->nil) {
            if (parent == parent->parent->left) {
                ancleNode = parent->parent->right;
                if (ancleNode != nullptr && ancleNode->color == RED) {
                    parent->color = BLACK;
                    ancleNode->color = BLACK;
                    parent->parent->color = RED;

                    targetNode = parent->parent;
                    parent = targetNode->parent;
                }
                else {
                    if (targetNode == parent->right) {
                        rbTreeLeftRotate(parent);
                        targetNode = targetNode->left;
                        parent = targetNode->parent;
                    }
                    parent->color = BLACK;
                    parent->parent->color = RED;
                    rbTreeRightRotate(parent->parent);
                    break;
                }
            }
            else {
                ancleNode = parent->parent->left;
                if (ancleNode != this->nil && ancleNode->color == RED) {
                    parent->color = BLACK;
                    ancleNode->color = BLACK;
                    parent->parent->color = RED;

                    targetNode = parent->parent;
                    parent = targetNode->parent;
                }
                else {
                    if (targetNode == parent->left) {
                        rbTreeRightRotate(parent);
                        targetNode = parent->right;
                        parent = targetNode->parent;
                    }
                    parent->color = BLACK;
                    parent->parent->color = RED;
                    rbTreeLeftRotate(parent->parent);
                    break;
                }
            }
        }
        else {
            break;
        }
    }
    this->root->color = BLACK;





    /**
     * 情况一：父节点是祖父节点的左孩子
     *      1. 叔父节点是红色的
     *      2. 叔父节点是黑色的
     *          1. 当前节点是左孩子
     *          2. 当前节点是右孩子
     * 情况二：父节点是祖父节点的右孩子
     *      1. 叔父节点是红色的
     *      2. 叔父节点是黑色的
     */
    // while ((targetNode != this->root) && targetNode->parent->color == nodeColor::RED) {
    //     if (targetNode->parent == targetNode->parent->parent->left) {
    //         // std::cout << " +++ " << std::endl;
    //         rbTreeNode * uncleNode = targetNode->parent->parent->right;
    //         if (uncleNode->color == nodeColor::RED) {
    //             // 父节点 和 叔父节点 都是红色
    //             targetNode->parent->color = nodeColor::BLACK;
    //             uncleNode->color = nodeColor::BLACK;
    //             targetNode->parent->parent->color = nodeColor::RED;
    //             targetNode = targetNode->parent->parent;
    //         }
    //         else {
    //             // 父节点 是红色，叔父节点是 黑色
    //             if (targetNode->parent == targetNode->parent->parent->right) {
    //                 targetNode = targetNode->parent;
    //                 rbTreeLeftRotate(targetNode);
    //             }
    //             targetNode->parent->color = nodeColor::BLACK;
    //             targetNode->parent->parent->color = nodeColor::RED;
    //             rbTreeRightRotate(targetNode->parent->parent);
    //         }
    //     }
    //     else {      // 当前节点是父节点的右节点
    //         rbTreeNode * uncleNode = targetNode->parent->parent->left;
    //         if (uncleNode->color == nodeColor::RED) {
    //             // 父节点 和 叔父节点 都是红色
    //             targetNode->parent->color = nodeColor::BLACK;
    //             uncleNode->color = nodeColor::BLACK;
    //             targetNode->parent->parent->color = nodeColor::RED;

    //             targetNode = targetNode->parent->parent;
    //         }
    //         else {
    //             // 父节点(右)是红色，叔父节点(左)是黑色
    //             if (targetNode == targetNode->parent->left) {
    //                 targetNode = targetNode->parent;
    //                 rbTreeRightRotate(targetNode);
    //             }

    //             targetNode->parent->color = nodeColor::BLACK;
    //             targetNode->parent->parent->color = nodeColor::RED;
    //             rbTreeLeftRotate(targetNode->parent->parent);
    //         }
    //     }
    // }
    // this->root->color = nodeColor::BLACK;
}

rbTree::rbTreeNode * rbTree::reTreeSearch(int key)
{
    rbTreeNode * curNode = this->root;
    while (curNode != this->nil) {
        if (key == curNode->key) {
            return curNode;
        }
        else if (key > curNode->key) {
            curNode = curNode->right;
        }
        else {
            curNode = curNode->left;
        }
    }
    return nullptr;
}

void rbTree::preOrder(rbTreeNode * node) 
{
    if (node == this->nil) {
        return;
    }

    std::cout << node->key;
    if (node->color == nodeColor::RED) {
        std::cout << "红" << "   ";
    }
    else {
        std::cout << "黑" << "   ";
    }
    
    preOrder(node->left);
    preOrder(node->right);
}

void rbTree::inOrder(rbTreeNode * node) 
{
    if (node == this->nil) {
        return;
    }

    inOrder(node->left);
    std::cout << node->key;
    if (node->color == nodeColor::RED) {
        std::cout << "红" << "   ";
    }
    else {
        std::cout << "黑" << "   ";
    }
    inOrder(node->right);
}

void rbTree::deleteNode(int theKey)
{
    rbTreeNode * preNode = this->nil;
    rbTreeNode * curNode = this->root;
    while (curNode != this->nil) {
        if (theKey > curNode->key) {
            curNode = curNode->right;
        }
        else if (theKey < curNode->key) {
            curNode = curNode->left;
        }
        else {
            break;
        }
    }
    if (curNode == this->nil) {
        // 没有找到
        return;
    }
    rbTreeNode * child;
    unsigned char color;
    if (curNode->left == this->nil || curNode->right == this->nil) {
        if (curNode->right != this->nil) {
            // 右孩子 存在
            child = curNode->right;
        }
        else {
            child = curNode->left;
        }
        color = curNode->color;
        deleteNoOrOneChildNode(preNode, curNode);
        if (child != this->nil && color == BLACK) {
            deleteFixUp(child);
        }
    }
    else {
        // 左右子树都不是空
        // 找到右子树的最左节点 -- 这个节点比右边所有节点都小，但是比左边节点都大
        rbTreeNode * rPreNode = curNode;
        rbTreeNode * rCurNode = curNode->right;
        while (rCurNode->left != this->nil) {
            rPreNode = rCurNode;
            rCurNode = rCurNode->left;
        }
        curNode->key = rCurNode->key;
        child = rCurNode->right;    // 肯定没有 左孩子
        color = rCurNode->color;
        deleteNoOrOneChildNode(rPreNode, rCurNode);
        if (child != this->nil && color == BLACK) {
            deleteFixUp(child);
        }
    }
}

// 当 左孩子 和 右孩子 有一个或两个都是空的情况下
void rbTree::deleteNoOrOneChildNode(rbTreeNode * preNode, rbTreeNode * curNode)
{
    if (curNode->left == this->nil && curNode->right == this->nil) {
        // 左右子树 都是空
        if (preNode == this->nil) {
            this->root = this->nil;
        }
        else if (curNode == preNode->left) {
            preNode->left = this->nil;
        }
        else {
            preNode->right = this->nil;
        }
        delete curNode;
    }
    else if (curNode->right != this->nil) {
        // 右子树 不是空
        if (preNode == this->nil) {
            this->root = curNode->right;
            this->root->parent = this->nil;
        }
        else if (curNode == preNode->left) {
            preNode->left = curNode->right;
            curNode->right->parent = preNode;
        }
        else {
            preNode->right = curNode->right;
            curNode->right->parent = preNode;
        }
        delete curNode;
    }
    else {
        // 左子树 不是空
        if (preNode == this->nil) {
            this->root = curNode->left;
            this->root->parent = this->nil;
        }
        else if (curNode == preNode->left) {
            preNode->left = curNode->left;
            curNode->left->parent = preNode;
        }
        else {
            preNode->right = curNode->left;
            curNode->left->parent = preNode;
        }
        delete curNode;
    }
}
void rbTree::deleteFixUp(rbTreeNode * node)
{
    if (node->color == RED) {
        rbTreeInsertFixup(node);
    }
}

void rbTree::rbTreeTraversal()
{
    preOrder(this->root);
    std::cout << std::endl;

    inOrder(this->root);
    std::cout << std::endl;
}

int main (int argc, char *argv[])
{
    rbTree tree;
    tree.rbTreeInsert(12);
    tree.rbTreeInsert(9);
    tree.rbTreeInsert(5);
    tree.rbTreeInsert(15);
    tree.rbTreeInsert(22);
    tree.rbTreeInsert(23);
    tree.rbTreeInsert(20);
    tree.rbTreeInsert(1);
    tree.rbTreeInsert(25);
    tree.rbTreeInsert(35);
    tree.rbTreeInsert(45);
    tree.rbTreeInsert(55);
    tree.rbTreeInsert(65);
    tree.rbTreeInsert(75);
    tree.rbTreeInsert(85);
    tree.rbTreeInsert(95);
    tree.rbTreeInsert(215);
    tree.rbTreeTraversal();

    std::cout << std::endl;
    tree.deleteNode(65);
    tree.rbTreeTraversal();
    return 0;
}
