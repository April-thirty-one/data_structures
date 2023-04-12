#include <cstdlib>
#include <iostream>
#include "./arrayHeap.h"

int main(int argc, char * argv[]) 
{
    try {
        srand(time(nullptr));

        int array[5]{1, 2, 3, 4, 5};
        arrayHeap<int> arrayHeap(array, 5);
        arrayHeap.buildHeap();
        arrayHeap.insert(11);
        for (int i = 0; i < 7; i++) {
            arrayHeap.insert(rand() % 30);
        }
        std::cout << arrayHeap << std::endl;

        arrayHeap.heapSort();
        std::cout << arrayHeap << std::endl;
    }
    catch (illegalError & message) {
        message.outputMessage();
    }
    return 0;
}