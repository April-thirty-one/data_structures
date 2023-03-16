#include "./11_chapter_tree/linkedBinaryTree.h"
#include "./util.h"
#include "11_chapter_tree/binaryTreeNode.h"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main (int argc, char *argv[])
{
    try {
        linkedBinayTree<int> tree;
        binaryTreeNode<int> * node = new binaryTreeNode<int>(10);
        tree.insert(node);
    } 
    catch (cc::illegalParameterValue error) {
        error.outputMessage();
    }

    return 0;
}
