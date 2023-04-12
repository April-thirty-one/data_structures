#ifndef DATA_STRCUTURES_SORTEDARRAYLIST_H__
#define DATA_STRCUTURES_SORTEDARRAYLIST_H__

#include "./dictionary.h"
#include "../util.h"
#include <algorithm>
#include <utility>

template <class K, class E>
class sortedArrayList : public dictionary<K, E> {
public:
    sortedArrayList(int initialCapacity = 10);
    ~sortedArrayList();

    bool empty() const override;
    int size() const override;
    std::pair<K, E> * find(const K & key) const override;
    void erase(const K & key) override;
    void insert(const std::pair<K, E> & element) override;

protected:
    std::pair<K, E> * element;
    int arrayCapacity;
    int arraySize;
};

template <class K, class E>
sortedArrayList<K, E>::sortedArrayList(int initialCapacity) 
{
    if (initialCapacity < 0) {
        throw cc::illegalParameterValue("sortedArrayList.h constructor()", "initialCapacity must be >= 0");
    }

    this->arraySize = 0;
    this->arrayCapacity = initialCapacity;
    this->element = new std::pair<K, E>[this->arrayCapacity];

    std::cout << "constructor success." << std::endl;
}

template <class K, class E>
sortedArrayList<K, E>::~sortedArrayList()
{
    if (this->element != nullptr) {
        delete [] this->element;
    }
    std::cout << "distructor success." << std::endl;
}

template <class K, class E>
bool sortedArrayList<K, E>::empty() const
{
    return this->arraySize == 0;
}

template <class K, class E>
int sortedArrayList<K, E>::size() const
{
    return this->arraySize;
}

template <class K, class E>
std::pair<K, E> * sortedArrayList<K, E>::find(const K & key) const
{
    int left = 0;
    int right = this->arraySize - 1;

    while (left < right) {
        int middle = left + (right - left) / 2;

        if (this->element[middle].first > key) {
            right = middle - 1;
        }
        else if (this->element[middle].first < key) {
            left = middle + 1;
        }
        else {
            return this->element + middle;
        }
    }
    return nullptr;
}

template <class K, class E>
void sortedArrayList<K, E>::erase(const K & key)
{
    int index = 0;
    while (index < this->arraySize && this->element[index].first < key) {
        index += 1;
    }
    if (this->element[index].first != key) {
        return;
    }
    else {
        while (index < this->arraySize - 1) {
            this->element[index] = this->element[index + 1];
            index += 1;
        }
        this->arraySize -= 1;
    }
}

template <class K, class E>
void sortedArrayList<K, E>::insert(const std::pair<K, E> & elem)
{
    if (this->arraySize == this->arrayCapacity) {
        std::pair<K, E> * temp = new std::pair<K, E>[this->arrayCapacity * 2];
        std::copy(this->element, this->element + this->arraySize, temp);
        delete [] this->element;
        this->element = temp;
        this->arrayCapacity *= 2;
    }
    
    int left = 0;
    int right = this->arraySize - 1;
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (this->element[middle].first < elem.first) {
            left = middle + 1;
        }
        else if (this->element[middle].first > elem.first) {
            right = middle - 1;
        }
        else {
            this->element[middle].second = elem.second;
            this->arraySize += 1;
            return;
        }
    }
    std::copy_backward(this->element + left + 1, this->element + this->arraySize, this->element + left);
    this->element[left].second = elem.second;
    this->arraySize += 1;
}

#endif // !DATA_STRCUTURES_SORTEDARRAYLIST_H__
