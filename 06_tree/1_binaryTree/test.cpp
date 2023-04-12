#include "./commonBinaryTree.h"

#include <algorithm>
#include <iostream>
#include <iterator>

int main(int argc, char * argv[])
{
    CommonBinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(2);
    tree.insert(9);
    tree.insert(7);
    tree.insert(8);

    std::vector<int> ivin(tree.inOrder());
    std::for_each(ivin.begin(), ivin.end(), [] (int item) {
        std::cout << item << "  ";
    });
    std::cout << std::endl;

    std::cout << "inIterator -- ";
    CommonBinaryTree<int>::InOrderIterator inIter = tree.inBegin();
    for (; inIter != tree.inEnd(); ++inIter) {
        std::cout << *inIter << "   ";
    }
    std::cout << std::endl << std::endl;

    std::vector<int> ivpre(tree.preOrder());
    std::for_each(ivpre.begin(), ivpre.end(), [] (int item) {
        std::cout << item << "  ";
    });
    std::cout << std::endl;

    std::cout << "preIterator -- ";
    CommonBinaryTree<int>::PreOrderIterator preIter = tree.preBegin();
    for (; preIter != tree.preEnd(); ++preIter) {
        std::cout << *preIter << "   ";
    }
    std::cout << std::endl << std::endl;

    std::vector<int> ivPost(tree.postOrder());
    std::for_each(ivPost.begin(), ivPost.end(), [] (int item) {
        std::cout << item << "  ";
    });
    std::cout << std::endl;

    std::cout << "postIterator -- ";
    CommonBinaryTree<int>::PostOrderIterator postIter = tree.postBegin();
    for (; postIter != tree.postEnd(); ++postIter) {
        std::cout << *postIter << "  ";
    }
    std::cout << std::endl << std::endl;

    std::vector<int> ivLeve(tree.levelOrder());
    std::for_each(ivLeve.begin(), ivLeve.end(), [] (int item) {
        std::cout << item << "  ";
    });
    std::cout << std::endl;

    std::cout << "postIterator -- ";
    CommonBinaryTree<int>::LevelOrderIterator levelIter = tree.levelBegin();
    for (; levelIter != tree.levelEnd(); ++levelIter) {
        std::cout << *levelIter << "  ";
    }
    std::cout << std::endl << std::endl;
    return 0;
}