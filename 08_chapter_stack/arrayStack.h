#ifndef DATA_STRUCTURES_8_CHAPTER_STACK_ARRAYTSACK_H__
#define DATA_STRUCTURES_8_CHAPTER_STACK_ARRAYTSACK_H__

#include "stack.h"
#include "../util.h"
#include <algorithm>

template <class T>
class arrayStack : public stack<T> {
public:
    arrayStack(int capacity = 10);
    ~arrayStack();

    bool empty() const override;
    bool full() const;
    int size() const override;
    int capacity() const;
    T & getTop() override;
    void pop() override;
    void push(const T & value) override;

private:
    int top;
    int arrayLength;
    T * element;
};

template <class T>
arrayStack<T>::arrayStack(int capacity)
{
    if (capacity < 0) {
        throw cc::illegalParameterValue("in arrayStack.h constructor", "capacity must be >= 0");
    }

    this->arrayLength = capacity;
    this->element = new T[this->arrayLength];
    this->top = -1;

    std::cout << "-- constructor success." << std::endl;
}

template <class T>
arrayStack<T>::~arrayStack()
{
    if (this->element != nullptr) {
        delete [] this->element;
    }
    std::cout << "-- destructor success." << std::endl;
}

template <class T>
bool arrayStack<T>::empty() const 
{
    return this->top == -1;
}

template <class T>
bool arrayStack<T>::full() const 
{
    return this->top >= this->arrayLength - 1;
}

template <class T>
int arrayStack<T>::size() const 
{
    return this->top + 1;
}

template <class T>
int arrayStack<T>::capacity() const 
{
    return this->arrayLength;
}

template <class T>
T & arrayStack<T>::getTop() 
{
    if (this->empty()) {
        cc::illegalParameterValue("in arrayStack.h getTop", "");
    }
    return this->element[this->top];
}

template <class T>
void arrayStack<T>::pop() 
{
    if (this->empty()) {
        cc::illegalParameterValue("in arrayStack.h getTop", "");
    }
    this->top -= 1;
}

template <class T>
void arrayStack<T>::push(const T & value) 
{
    if (this->top == this->arrayLength - 1) {
        T * temp = new T[this->arrayLength * 2];
        std::copy(this->element, this->element + this->arrayLength, temp);
        delete [] this->element;
        this->element = temp;
        this->arrayLength *= 2;
    }

    this->element[++this->top] = value;
}

#endif // !DATA_STRUCTURES_8_CHAPTER_STACK_ARRAYTSACK_H__
