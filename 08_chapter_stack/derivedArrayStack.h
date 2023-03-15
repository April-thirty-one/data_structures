#ifndef DATA_STRUCTURES_8_CHAPTER_STACK_DERIVEDARRAYSTACK_H__
#define DATA_STRUCTURES_8_CHAPTER_STACK_DERIVEDARRAYSTACK_H__

#include "../5_chapter/arrayList.h"
#include "stack.h"

template <class T>
class derivedArrayStack : public stack<T>, private arrayList<T> {
public:
    derivedArrayStack(int capacity = 10);

    bool empty() const override;
    int size() const override;
    T & getTop() override;
    void pop() override;
    void push(const T & value) override;
};

template <class T>
derivedArrayStack<T>::derivedArrayStack(int capacity) : arrayList<T>(capacity) {}

template <class T>
bool derivedArrayStack<T>::empty() const
{
    return arrayList<T>::empty();
}

template <class T>
int derivedArrayStack<T>::size() const 
{
    return arrayList<T>::size();
}

template <class T>
T & derivedArrayStack<T>::getTop() 
{
    if (this->empty()) {
        cc::illegalParameterValue("in derivedArrayStack.h top()", "");
    }

    return arrayList<T>::element[arrayList<T>::listSize - 1];
}

template <class T>
void derivedArrayStack<T>::pop() 
{
    if (this->empty()) {
        cc::illegalParameterValue("in derivedArrayStack.h pop()", "");
    }

    arrayList<T>::erase(arrayList<T>::listSize - 1);
}

template <class T>
void derivedArrayStack<T>::push(const T & value) 
{
    arrayList<T>::insert(arrayList<T>::listSize, value);
}





#endif // !DATA_STRUCTURES_8_CHAPTER_STACK_DERIVEDARRAYSTACK_H__
