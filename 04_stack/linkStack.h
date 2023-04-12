#ifndef DATA_STRUCTURES_8_CHAPTER_STACK_LINKSTACK_H__
#define DATA_STRUCTURES_8_CHAPTER_STACK_LINKSTACK_H__

#include "stack.h"
#include "../util.h"
#include "../6_chapter/chainNode.h"


template <class T>
class linkStack : public stack<T> {
public:
    linkStack();
    ~linkStack();

    bool empty() const override;
    int size() const override;
    T & getTop() override;
    void pop() override;
    void push(const T & value) override;

    void pushNode(chainNode<T> * node);
    chainNode<T> * popNode();

private:
    chainNode<T> * dummyHead;
    int linkLength;
    void openingSpaceError(const char * position);
};

template <class T>
linkStack<T>::linkStack() 
{
    this->dummyHead = new chainNode<T>(-1, nullptr);
    if (this->dummyHead == nullptr) {
        openingSpaceError("in linkStack.h constructor");
    }
    this->linkLength = 0;
}

template <class T>
linkStack<T>::~linkStack()
{
    chainNode<T> * deleteNode;
    if (this->dummyHead != nullptr) {
        deleteNode = this->dummyHead;
        this->dummyHead = this->dummyHead->next;
        delete deleteNode;
    }
}

template <class T>
bool linkStack<T>::empty() const 
{
    return this->linkLength == 0;
}

template <class T>
int linkStack<T>::size() const 
{
    return this->linkLength;
}

template <class T>
T & linkStack<T>::getTop()
{
    return this->dummyHead->next->element;
}

template <class T>
void linkStack<T>::pop() 
{
    chainNode<T> * deleteNode = this->dummyHead->next;
    this->dummyHead->next = deleteNode->next;
    delete deleteNode;
    this->linkLength -= 1;
}

template <class T>
void linkStack<T>::push(const T & value) 
{
    chainNode<T> * newNode = new chainNode<T>(value, this->dummyHead->next);
    if (newNode == nullptr) {
        openingSpaceError("in linkStack.h push()");
    }
    this->dummyHead->next = newNode;
    this->linkLength += 1;
}

template <class T>
void linkStack<T>::openingSpaceError(const char * position)
{
    throw cc::illegalParameterValue(position, "opening space error");
}

template <class T>
void linkStack<T>::pushNode(chainNode<T> * node)
{
    node->next = this->dummyHead->next;
    this->dummyHead->next = node;
    this->linkLength += 1;
}

template <class T>
chainNode<T> * linkStack<T>::popNode()
{
    chainNode<T> * node = this->dummyHead->next;
    this->dummyHead->next = node->next;
    this->linkLength -= 1;
    return node;
}

#endif // !DATA_STRUCTURES_8_CHAPTER_STACK_LINKSTACK_H__
