#ifndef TREE_PRIORITYQUEUE_HEAP_ARRAYHEAP_H__
#define TREE_PRIORITYQUEUE_HEAP_ARRAYHEAP_H__

#include "../../../utils/utils.h"

#include <array>
#include <iostream>
#include <ostream>

template <class T>
class arrayHeap;

template <class T>
std::ostream & operator << (std::ostream & out, const arrayHeap<T> & obj);

template <class T>
class arrayHeap
{
public:
    arrayHeap(int initLength = 10);
    arrayHeap(const T * array, const int size);
    ~arrayHeap();

    void buildHeap();                   // 将无序数组转换为 最大堆
    void insert(const T & element);     // 插入元素
    void popMax(T & element);           // 堆顶元素出堆
    void heapSort();                    // 堆排序

    friend std::ostream & operator << <>(std::ostream & out, const arrayHeap<T> & obj);

private:
    // helper function 
    void adjustUp_(int idx);            // 当前节点向上调整
    void adjustDown_(int idx);          // 当前节点向下调整

private:
    int arrayLength;
    int heapSize;
    T * heap;
};

template <class T>
arrayHeap<T>::arrayHeap(int initLength)
{
    if (initLength <= 0) {
        throw illegalError("the initial length must be greater than 0");
    }

    this->heap = new T[initLength];
    this->arrayLength = initLength;
    this->heapSize = 0;
}

template <class T>
arrayHeap<T>::arrayHeap(const T * array, const int size)
{
    if (size <= 0) {
        throw illegalError("The size of the pilot array must be greater than 0. ");
    }
    
    this->heapSize = size;
    this->arrayLength = size;
    this->heap = new T[this->heapSize];

    std::copy(array, array + size, this->heap);
}

template <class T>
arrayHeap<T>::~arrayHeap()
{
    if (this->heap != nullptr) {
        delete [] this->heap;
    }
}

template <class T>
void arrayHeap<T>::adjustUp_(int idx)
{
    if (idx < 0) {
        throw illegalError("the index is illegal.");
    }

    while (idx > 0) {
        int child = idx;
        int parent = (idx - 1) / 2;

        if (parent >= 0) {
            if (this->heap[child] > this->heap[parent]) {
                std::swap(this->heap[child], this->heap[parent]);
                idx = parent;
            }
            else {
                return;
            }
        }
    }
}

template <class T>
void arrayHeap<T>::adjustDown_(int idx)
{
    int parent, child;
    
    /*
     * 判断否存在大于当前节点子节点，
     * 如果不存在﹐则堆本身是平衡的，不需要调整;
     * 如果存在，则将最大的子节点与之交换.
     * 交换后，如果这个子节点还有子节点，则要继续按照同样的步骤对这个子节点进行调整
     */
    for (parent = idx; (parent * 2 + 1) < this->heapSize; parent = child) {
        child = parent * 2 + 1;

        // 取两个子结点中最大的节点
        if (((child + 1) < this->heapSize) && (this->heap[child] < this->heap[child + 1])) {
            child += 1;
        }

        // 判断最大的节点是否大于当前的父节点
        if (this->heap[parent] > this->heap[child]) {
            break;
        }
        else {
            std::swap(this->heap[parent], this->heap[child]);
        }
    }
}

template <class T>
void arrayHeap<T>::buildHeap()
{
    for (int i = (this->heapSize / 2) - 1; i >= 0; i--) {
        this->adjustDown_(i);
    }
}

template <class T>
void arrayHeap<T>::insert(const T & element)
{
    // 若 数组 满了，进行扩容，每次扩容两倍
    if (this->heapSize == this->arrayLength) {
        this->heap = arrayExpansion(this->heap, this->arrayLength);
        this->arrayLength *= 2;
    }
    this->heap[this->heapSize] = element;
    this->adjustUp_(this->heapSize);
    this->heapSize += 1;
}

template <class T>
void arrayHeap<T>::popMax(T & element)
{
    if (this->heapSize <= 0) {
        throw illegalError("The size of this heap is less than 0 and cannot be pop.");
    }

    element = this->heap[0];
    this->heap[0] = this->heap[this->heapSize - 1];
    this->heapSize -= 1;
    this->adjustDown_(0);
}

template <class T>
void arrayHeap<T>::heapSort()
{
    int temp = this->heapSize;
    while (this->heapSize > 0) {
        std::swap(this->heap[0], this->heap[this->heapSize - 1]);
        this->heapSize -= 1;
        this->adjustDown_(0);
    }
    this->heapSize = temp;
}

template <class T>
std::ostream & operator << (std::ostream & out, const arrayHeap<T> & obj)
{
    for (size_t i = 0; i < obj.heapSize; i++) {
        out << obj.heap[i] << "  ";
    }
    return out;
}

#endif  // ! TREE_PRIORITYQUEUE_HEAP_ARRAYHEAP_H__