#ifndef DATA_STRUCTURES_6_CHAPTER_EXTENDEDCHAIN_H__
#define DATA_STRUCTURES_6_CHAPTER_EXTENDEDCHAIN_H__

#include "./extendedLinearList.h"
#include "chainNode.h"
#include <ostream>

template <class T>
class extendedChain;

template <class T>
std::ostream & operator << (std::ostream & out, const extendedChain<T> & obj);

template <class T>
class extendedChain : public extendedLinearList<T> {
public:
    extendedChain();
    extendedChain(const extendedChain<T> & other);
    ~extendedChain();

    bool empty() const override;
    int size() const override;
    T & get(int index) const override;
    int indexOf(const T & value) const override;
    void erase(int index) override;
    void insert(int index, const T & value) override;
    void output(std::ostream & out) const override;
    void clear() override;
    void push_back(const T & element) override;

    friend std::ostream & operator << <>(std::ostream & out, const extendedChain<T> & obj);

private:
    void checkIndex(const char * position, int index) const;

    chainNode<T> * dummyHead;
    chainNode<T> * tailNode;
    int listSize;
};

template <class T>
void extendedChain<T>::checkIndex(const char * position, int index) const
{
    if (index < 0 || index >= this->listSize) {
        throw cc::illegalParameterValue(position, "index out of range.");
    }
}

template <class T>
extendedChain<T>::extendedChain() 
{
    this->dummyHead = new chainNode<T>(-1, nullptr);
    this->tailNode = nullptr;
    this->listSize = 0;
    std::cout << "-- constructor success." << std::endl;
}

template <class T>
extendedChain<T>::extendedChain(const extendedChain<T> & other) 
{
    if (other.dummyHead->next == nullptr) {
        return;
    }

    chainNode<T> * otherNode = other.dummyHead->next;
    chainNode<T> * current = this->dummyHead;
    this->listSize = 0;
    while (otherNode != nullptr) {
        current->next = new chainNode<T>(otherNode->element, current->next);
        this->listSize += 1;
        current = current->next;
        this->tailNode = current;
        otherNode = otherNode->next;
    }
    std::cout << "-- copy constructor success." << std::endl;
}

template <class T>
extendedChain<T>::~extendedChain() 
{
    chainNode<T> * deleteNode = this->dummyHead;
    while (this->dummyHead != nullptr) {
        deleteNode = this->dummyHead;
        this->dummyHead = this->dummyHead->next;
        delete deleteNode;
    }
    this->listSize = 0;
    this->dummyHead = nullptr;
    this->tailNode = nullptr;
    std::cout << "-- destructor success." << std::endl;
}

template <class T>
bool extendedChain<T>::empty() const 
{
    return this->listSize == 0;
}

template <class T>
int extendedChain<T>::size() const 
{
    return this->listSize;
}

template <class T>
T & extendedChain<T>::get(int index) const 
{
    checkIndex("in extendedChain.h", index);

    chainNode<T> * current = this->dummyHead->next;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->element;
}

template <class T>
int extendedChain<T>::indexOf(const T & value) const 
{
    chainNode<T> * current = this->dummyHead->next;
    for (size_t i = 0; i < this->listSize; i++) {
        if (current->element == value) {
            return i;
        }
    }
    return -1;
}

template <class T>
void extendedChain<T>::erase(int index)
{
    checkIndex("in extendedChain.h", index);

    chainNode<T> * preNode = this->dummyHead;
    for (size_t i = 0; i < index; i++) {
        preNode = preNode->next;
    }
    chainNode<T> * deleteNode = preNode->next;
    preNode->next = deleteNode->next;
    delete deleteNode;
    this->listSize -= 1;
    if (preNode->next == nullptr) {
        this->tailNode = preNode;
    }
}

template <class T>
void extendedChain<T>::insert(int index, const T & value)
{
    if (index < 0 || index > this->listSize) {
        throw cc::illegalParameterValue("in extendedChain.h", "index out of range");
    }

    if (index == this->listSize) {
        this->push_back(value);
    }
    else {
        chainNode<T> * preNode = this->dummyHead;
        for (size_t i = 0; i < index; i++) {
            preNode = preNode->next;
        }
        chainNode<T> * insertNode = new chainNode<T>(value, preNode->next);
        preNode->next = insertNode;
        this->listSize += 1;
    }
}

template <class T>
void extendedChain<T>::output(std::ostream &out) const {}

template <class T>
std::ostream & operator << (std::ostream & out, const extendedChain<T> & obj) 
{
    chainNode<T> * head = obj.dummyHead->next;
    while (head != nullptr) {
        out << head->element << "  ";
        head = head->next;
    }
    return out;
}

template <class T>
void extendedChain<T>::clear() 
{
    chainNode<T> * head = this->dummyHead->next;
    chainNode<T> * deleteNode;
    while (head != nullptr) {
        deleteNode = head;
        head = head->next;
        delete deleteNode;
    }
    this->listSize = 0;
    this->tailNode = nullptr;
}

template <class T>
void extendedChain<T>::push_back(const T & element)
{
    chainNode<T> * insertNode = new chainNode<T>(element, nullptr);
    if (this->listSize == 0) {
        this->dummyHead->next = insertNode;
        this->tailNode = insertNode;
    }
    else {
        this->tailNode->next = insertNode;
        this->tailNode = insertNode;
    }
    this->listSize += 1;
}

#endif // !DATA_STRUCTURES_6_CHAPTER_EXTENDEDCHAIN_H__
