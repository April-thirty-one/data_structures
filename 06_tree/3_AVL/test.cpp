#include <cstdlib>
#include <ctime>
#include <iostream>
#include "./AVLTree.h"

int main(int argc, char * argv[])
{
    srand(time(nullptr));

    AVLTree<int> tree;
    tree.insert(21);
    tree.insert(12);
    tree.insert(33);
    tree.insert(23);
    tree.insert(42);
    tree.insert(44);
    tree.insert(46);
    tree.insert(49);
    tree.insert(62);
    tree.insert(47);
    tree.insert(1);
    tree.insert(5);
    tree.insert(20);
    tree.insert(7);
    tree.insert(9);
    tree.insert(28);
    tree.insert(29);
    tree.insert(27);

    tree.del(46);

    std::cout << tree << std::endl;
    return 0;
}