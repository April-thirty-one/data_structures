#include "./bTree.h"
#include <pthread.h>

#include <algorithm>
#include <iostream>

int main (int argc, char *argv[])
{
    try {
        bTree<char> tree;
        tree.insertKey('a');
        tree.insertKey('b');
        tree.insertKey('c');
        tree.insertKey('d');
        tree.insertKey('e');
        tree.insertKey('f');
        tree.insertKey('g');
        tree.insertKey('h');
        tree.insertKey('i');
        tree.insertKey('j');
        tree.insertKey('k');
        tree.insertKey('l');
        tree.insertKey('m');
        tree.insertKey('n');
        tree.insertKey('o');
        tree.insertKey('p');
        tree.insertKey('q');
        tree.insertKey('r');
        tree.insertKey('s');
        tree.insertKey('t');
        tree.insertKey('u');


        tree.deleteKey('f');
        tree.deleteKey('i');
        std::cout << tree << std::endl;
    }
    catch (illegalError & illegalMessage) {
        illegalMessage.outputMessage();
    }
    return 0;
    
}
