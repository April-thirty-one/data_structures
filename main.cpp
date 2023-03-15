#include "./10_chapter_hash/hashTable.h"


#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main (int argc, char *argv[])
{
    try {
        hashTable<int, int> hash(10);
    } 
    catch (cc::illegalParameterValue error) {
        error.outputMessage();
    }

    return 0;
}
