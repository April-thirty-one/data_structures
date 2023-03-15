#ifndef DATA_STRUCTURES_SORTEDCHAIN_H__
#define DATA_STRUCTURES_SORTEDCHAIN_H__

/**
 * 實現了排序的鏈表，每個節點都是 pair
 * 有個錯誤：若是想要配合 sortedArrayList 使用的話，不能使用 hummyHead 虛擬節點
 */

#include "dictionary.h"

#include <iostream>
#include <utility>

template <typename K, typename E>
struct pairNode {
    std::pair<K, E> element;
    pairNode<K, E> * next;

    pairNode(const std::pair<K, E> & elem) : element(elem), next(nullptr) {}
    pairNode(const std::pair<K, E> & elem, pairNode<K, E> * next) : element(elem), next(next) {}
};

template <class K, class E>
class sortedChain : public dictionary<K, E> {
public:
    sortedChain();
    ~sortedChain();

    bool empty() const override;
    int size() const override;
    std::pair<K, E> * find(const K & key) const override;
    void erase(const K & key) override;
    void insert(const std::pair<K, E> & other) override;

private:
    pairNode<K, E> * dummyHead;
    pairNode<K, E> * tailNode;
    int listSize;
};

template <class K, class E>
sortedChain<K, E>::sortedChain()
{
    this->listSize = 0;
    this->dummyHead = new pairNode<K, E>(std::pair<K, E>(), nullptr);
    this->tailNode = dummyHead;
}

template <class K, class E>
sortedChain<K, E>::~sortedChain()
{
    pairNode<K, E> * deleteNode;
    while (this->dummyHead != nullptr) {
        deleteNode = this->dummyHead;
        this->dummyHead = this->dummyHead->next;
        delete deleteNode;
    }
    this->listSize = 0;
    this->tailNode = nullptr;
}

template <class K, class E>
bool sortedChain<K, E>::empty() const
{
    return this->listSize == 0;
}

template <class K, class E>
int sortedChain<K, E>::size() const 
{
    return this->listSize;
}

template <class K, class E>
std::pair<K, E> * sortedChain<K, E>::find(const K & key) const
{
    pairNode<K, E> * currentNode = this->dummyHead->next;
    while (currentNode != nullptr && currentNode->element.first != key) {
        currentNode = currentNode->next;
    }
    if (currentNode == nullptr) {
        return nullptr;
    }
    else {
        return &currentNode->element;
    }
}

template <class K, class E>
void sortedChain<K, E>::erase(const K & key)
{
    pairNode<K, E> * preNode = this->dummyHead;
    while (preNode->next != nullptr && preNode->next->element.first != key) {
        preNode = preNode->next;
    }

    if (preNode->next == nullptr) {
        return;
    }
    else {
        pairNode<K, E> * deleteNode = preNode->next;
        if (this->tailNode == deleteNode) {
            this->tailNode = preNode;
        }
        preNode->next = deleteNode->next;
        delete deleteNode;
        this->listSize -= 1;
    }
}

template <class K, class E>
void sortedChain<K, E>::insert(const std::pair<K, E> & element)
{
    pairNode<K, E> * preNode = this->dummyHead;
    while (preNode->next != nullptr && preNode->next->element.first < element.first) {
        preNode = preNode->next;
    }
    
    if (preNode->next->element.first == element.first) {
        preNode->next->element.second = element.second;
    }
    else {
        pairNode<K, E> * insertNode = new pairNode<K, E>(element, preNode->next);
        preNode->next = insertNode;
        this->listSize += 1;
    }
}

#endif // !DATA_STRUCTURES_SORTEDCHAIN_H__
