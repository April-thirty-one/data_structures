#include <iostream>
#include "./bPlusTree.h"

int main(int argc, char * argv[])
{
    BPlusTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    tree.insert(11);
    tree.insert(12);
    tree.insert(13);
    tree.insert(14);
    tree.insert(15);
    tree.insert(16);
    tree.insert(17);
    tree.insert(18);
    tree.insert(19);
    // tree.insert(20);
    // tree.insert(21);

    std::cout << tree << std::endl;
    return 0;
}
