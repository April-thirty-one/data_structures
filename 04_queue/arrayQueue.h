#ifndef DATA_STRUCTURES_9_CHAPTER_QUEUE_ARRAYQUEUE_H__
#define DATA_STRUCTURES_9_CHAPTER_QUEUE_ARRAYQUEUE_H__

#include "queue.h"
#include "../util.h"

#include <algorithm>


template <class T>
class arrayQueue : public queue<T> {
public:
    arrayQueue(int initialCapacity = 10);
    ~arrayQueue();

    bool empty() const override;
    int size() const override;
    int capacity() const;
    T & getFront() override;
    T & getBlack() override;
    void pop() override;
    void push(const T & value) override;

private:
    int front;
    int back;
    int queueLength;
    T * array;
};

template <class T>
arrayQueue<T>::arrayQueue(int initialCapacity) 
{
    if (initialCapacity < 0) {
        throw cc::illegalParameterValue("in arrayQueue.h constructor", "initial queueLength must be >= 0");
    }
    this->front = 0;
    this->back = 0;
    this->queueLength = initialCapacity;
    this->array = new T[initialCapacity];
}

template <class T>
arrayQueue<T>::~arrayQueue()
{
    if (this->array != nullptr){
        delete [] this->array;
    }
}

template <class T>
bool arrayQueue<T>::empty() const 
{
    return this->front == this->back;
}

template <class T>
int arrayQueue<T>::size() const 
{
    if (this->front <= this->back) {
        return this->back - this->front;
    }
    else {
        return (this->queueLength - this->front) + this->back;
    }
}

template <class T>
int arrayQueue<T>::capacity() const
{
    return this->queueLength;
}


template <class T>
T & arrayQueue<T>::getFront() 
{
    if (this->empty()) {
        throw cc::illegalParameterValue("in arrayQueue.h getFront()", "array is empty");
    }
    return this->array[this->front];
}

template <class T>
T & arrayQueue<T>::getBlack() 
{
    if (this->empty()) {
        throw cc::illegalParameterValue("in arrayQueue.h getBlack()", "array is empty");
    }
    return this->array[this->back - 1];
}

template <class T>
void arrayQueue<T>::pop() 
{
    if (this->empty()) {
        throw cc::illegalParameterValue("in arrayQueue.h getBlack()", "array is empty");
    }
    this->front += 1;

    if (this->size() <= this->capacity() / 4 && this->queueLength >= 5) {
        T * temp = new T[this->capacity() / 2];
        for (int i = this->front, j = 0; i != this->back; i = (i + 1) % this->queueLength, j++) {
            temp[j] = this->array[i];
        }
        std::cout << " --- " << std::endl;
        delete [] this->array;
        this->back = this->size();
        this->front = 0;
        this->queueLength /= 2;
        this->array = temp;
    }
}

template <class T>
void arrayQueue<T>::push(const T & value) 
{
    if ((this->back + 1) % this->queueLength == this->front) {
        // equeue full
        T * temp = new T[this->queueLength * 2];
        for (int i = this->front, j = 0; i != this->back; i = (i + 1) % this->queueLength, j++) {
            temp[j] = this->array[i];
        }
        delete [] this->array;
        this->array = temp;
        this->front = 0;
        this->back = this->queueLength - 1;
        this->queueLength *= 2;
    }
    this->array[this->back] = value;
    this->back = (this->back + 1) % this->queueLength;
}

#endif // !DATA_STRUCTURES_9_CHAPTER_QUEUE_ARRAYQUEUE_H__
