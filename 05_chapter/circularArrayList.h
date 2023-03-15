#ifndef DATA_STRUCTURES_CIRCULARARRAYLIST_H__
#define DATA_STRUCTURES_CIRCULARARRAYLIST_H__

#include "./linearList.h"
#include <algorithm>
#include <iterator>
#include <utility>

template <class T>
class circularArrayList;

template <class T>
circularArrayList<T> meld(const circularArrayList<T> & rth, const circularArrayList<T> & lth);

template <class T>
class circularArrayList : public linearList<T> {
private:
    T * element;                        // one-dimensional array
    int arrayLength;                    // length of array
    int listSize;                       // number of element
    int first;                          // position of first element
    
    void checkIndex(int index, const char * position) const;   // throw an exception if the index is invalid 

public:
    circularArrayList(int initialCapacity = 10);
    circularArrayList(const circularArrayList<T> &);
    ~circularArrayList();

    bool empty() const override;
    int size() const override;
    int capacity() const;
    T & get(int index) const override;
    int indexOf(const T & value) const override;
    void erase(int index) override;
    void push_back(const T & value);
    void insert(int index, const T & element) override;
    void swap(circularArrayList<T> & other);
    void reserve(int capacity);
    T set(int index, const T & value);
    void clear();
    void removeRange(int begin, int end);       // [begin, end)
    int lastIndexOf(const T & value) const;
    void reverse();
    void leftShift(int moveNumber);
    void circularShift(int moveNumber);
    void half();
    void buildHeap();
    void insertHeap(const T & value);
    T popHeap();
    void sortHeap();
    void merge(circularArrayList<T> & a, circularArrayList<T> & b);
    void spilt(circularArrayList<T> & a, circularArrayList<T> & b);
    void output(std::ostream & out = std::cout) const override;

    T & operator [] (int index) const;
    bool operator == (const circularArrayList<T> & other) const;
    bool operator != (const circularArrayList<T> & other) const;
    bool operator < (const circularArrayList<T> & other) const;
    void operator = (const circularArrayList<T> & other);

    friend circularArrayList<T> meld<>(const circularArrayList<T> & rth, const circularArrayList<T> & lth);
};

template <class T>
circularArrayList<T>::circularArrayList(int initialCapacity) {
    if (initialCapacity < 0) {
        throw cc::illegalParameterValue("-- capacity must > 0.", "constructor");
    }
    this->element = new T[initialCapacity];
    this->arrayLength = initialCapacity;
    this->listSize = 0;
    this->first = -1;
    std::cout << "-- circularArrayList constructor success." << std::endl;
}

template <class T>
circularArrayList<T>::circularArrayList(const circularArrayList<T> & other) 
{
    if (this == &other) {
        return;
    }

    this->element = new T[other.arrayLength];
    std::copy(other.element, other.element + other.listSize, this->element);
    this->listSize = other.listSize;
    this->arrayLength = other.arrayLength;
    this->first = 0;
    std::cout << "-- circularArrayList copy constructor success." << std::endl;
}

template <class T>
circularArrayList<T>::~circularArrayList() 
{
    if (this->element != nullptr) {
        delete [] this->element;
    }
    std::cout << "-- destructor success." << std::endl;;
}

template <class T>
void circularArrayList<T>::checkIndex(int index, const char * position) const 
{
    if (index > this->listSize || index < 0) {
        throw cc::illegalParameterValue(" index out of range.", position);
    }
}

template <class T>
bool circularArrayList<T>::empty() const 
{
    return this->listSize == 0;
}

template <class T>
int circularArrayList<T>::size() const 
{
    return this->listSize - this->first;
}

template <class T>
int circularArrayList<T>::capacity() const 
{
    return this->arrayLength;
}

template <class T>
T & circularArrayList<T>::get(int index) const 
{
    checkIndex(index, "get ");

    return this->element[index];
}

template <class T>
int circularArrayList<T>::indexOf(const T & value) const 
{
    int index = (int)(std::find(this->element, this->element + this->listSize, value) - this->element);
    if (index == this->listSize) {
        return -1;
    }
    return index;
}

template <class T>
void circularArrayList<T>::erase(int index)
{
    checkIndex(index, "erase");
    std::cout << this->first << std::endl;

    if (this->listSize - index - 1 > index) {
        // shift to the left 
        std::copy_backward(this->element + this->first, this->element + index, this->element + index + 1);
        this->first += 1;
        this->listSize -= 1;
    }
    else {
        // shift to the right
        std::copy(this->element + index + 1, this->element + this->listSize, this->element + index);
        this->listSize -= 1;
    }

    // estimate whether to reduce the array size
    if (this->listSize * 4 < this->arrayLength) {
        cc::changeLength1D(this->element, this->arrayLength, this->arrayLength / 4);
        this->arrayLength /= 4;
    }
}

template <class T>
void circularArrayList<T>::push_back(const T & value)
{
    if (this->listSize == this->arrayLength) {
        cc::changeLength1D(this->element, this->arrayLength, this->arrayLength * 2);
        this->arrayLength *= 2;
    }
    
    if (this->first == 0 || this->first == -1) {
        this->element[this->listSize] = value;
        this->listSize += 1;
    }
    else {
        this->element[--first] = value;
        this->listSize += 1;
    }

    if (this->first == -1) {
        this->first = 0;
    }
}

template <class T>
void circularArrayList<T>::insert(int index, const T & value)
{
    checkIndex(index, "insert");

    if (this->listSize == this->arrayLength) {
        cc::changeLength1D(this->element, this->arrayLength, this->arrayLength * 2);
        this->arrayLength *= 2;
    }
    if (this->listSize - index > index && this->first != 0) {
        // shift to the left
        std::copy(this->element + this->first, this->element + index, this->element + this->first - 1);
        this->first -= 1;
        this->element[index] = value;
        this->listSize += 1;
    }
    else {
        // shift to the right
        std::copy_backward(this->element + index, this->element + this->listSize, this->element + this->listSize + 1);
        this->element[index] = value;
        this->listSize++;
    }
    if (this->first == -1) {
        this->first += 1;
    }
}

template <class T>
void circularArrayList<T>::output(std::ostream & out) const 
{
    std::copy(this->element + this->first, this->element + this->listSize + this->first, std::ostream_iterator<T>(out, "  "));
}

template <class T>
std::ostream & operator << (std::ostream & out, const circularArrayList<T> & obj)
{
    obj.output(out);
    return out;
}

template <class T>
T & circularArrayList<T>::operator [] (int index) const
{
    checkIndex(index, "operator []");
    
    return this->element[index];
}

template <class T>
bool circularArrayList<T>::operator == (const circularArrayList<T> & other) const 
{
    if (this->listSize != other.listSize || this->arrayLength != other.arrayLength || this->first != other.first) {
        return false;
    }

    for (int i = this->first; i < this->listSize; i++) {
        if (this->element[i] != other.element[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool circularArrayList<T>::operator != (const circularArrayList<T> & other) const 
{
    return !(*this == other);
}

template <class T>
bool circularArrayList<T>::operator < (const circularArrayList<T> & other) const
{
    for (int i = 0; i < this->listSize && i < other.listSize; i++) {
        if (this->element[i + this->first] == other.element[i + other.first]) {
            continue;
        }
        else if (this->element[i + this->first] > other.element[i + other.first]) {
            return false;
        }
        else {
            return true;
        }
    }

    if (this->listSize < other.listSize) {
        return true;
    }
    else {
        return false;
    }
}

template <class T>
void circularArrayList<T>::swap(circularArrayList<T> & other) 
{
    T * temp_element = this->element;
    int temp_listSize = this->listSize;
    int temp_arrayLength = this->arrayLength;
    int temp_first = this->first;

    this->element = other.element;
    this->listSize = other.listSize;
    this->arrayLength = other.arrayLength;
    this->first = other.first;

    other.element = temp_element;
    other.listSize = temp_listSize;
    other.arrayLength = temp_arrayLength;
    other.first = temp_first;
}

template <class T>
void circularArrayList<T>::reserve(int capacity)
{
    if (capacity < 0) {
        cc::illegalParameterValue("new capacity must be >= 0.", "reserve");
    }

    if (this->arrayLength >= capacity) {
        return;
    }
    else {
        T * temp = new T[capacity];
        std::copy(this->element, this->element + this->listSize, temp);
        delete this->element;
        this->element = temp;
        this->arrayLength = capacity;
    }
}
template <class T>
T circularArrayList<T>::set(int index, const T & value) 
{
    checkIndex(index, "set");

    T result = this->element[index];
    this->element[index] = value;
    return result;
}

template <class T>
void circularArrayList<T>::clear()
{
    this->listSize = 0;
    this->first = -1;
}

template <class T>
void circularArrayList<T>::removeRange(int begin, int end) 
{
    checkIndex(begin, "removeRange");
    checkIndex(end, "removeRange");

    std::copy(this->element + end, this->element + this->listSize, this->element + begin);
    this->listSize -= (end - begin);
}

template <class T>
int circularArrayList<T>::lastIndexOf(const T & value) const 
{
    for (int i = this->listSize - 1; i >= 0; i--) {
        if (this->element[i] == value) {
            return i;
        }
    }
    return -1;
}

template <class T>
void circularArrayList<T>::reverse()
{
    // stl algorithm
    // std::reverse(this->element, this->element + this->listSize);

    for (int i = 0, j = this->listSize - 1; i < j; i++, j--) {
        T temp = this->element[i];
        this->element[i] = this->element[j];
        this->element[j] = temp;
    }
}

template <class T>
void circularArrayList<T>::leftShift(int moveNumber)
{
    if (moveNumber > this->listSize) {
        throw cc::illegalParameterValue("moveNumber must be <= listsize.", "leftShift");
    }
    std::copy(this->element + moveNumber, this->element + this->listSize, this->element);
    this->listSize -=  moveNumber;
}

template <class T>
void circularArrayList<T>::circularShift(int moveNumber)
{
    for (int i = 0; i < moveNumber; i++) {
        T temp = this->element[0];
        std::copy(this->element + 1, this->element + this->listSize, this->element);
        this->element[this->listSize - 1] = temp;
    }
}

template <class T>
void circularArrayList<T>::half()
{
    if (this->listSize == 0 || this->listSize == 1) {
        return;
    }
    for (int i = 1; i < this->listSize; i++) {
        std::copy(this->element + i + 1, this->element + this->listSize, this->element + i);
        this->listSize--;
    }
}

template <class T>
circularArrayList<T> meld(const circularArrayList<T> & rth, const circularArrayList<T> & lth)
{
    circularArrayList<T> temp(rth.listSize + lth.listSize);
    for (int i = 0, j = 0; i < rth.listSize && i < lth.listSize; i++) {
        temp.element[j++] = lth.element[i];
        temp.element[j++] = rth.element[i];
        temp.listSize += 2;
    }
    if (lth.listSize > rth.listSize) {
        std::copy(lth.element + temp.listSize / 2, lth.element + lth.listSize, temp.element + temp.listSize);
    }
    else if (lth.listSize < rth.listSize) {
        std::copy(rth.element + temp.listSize / 2, rth.element + rth.listSize, temp.element + temp.listSize);
    }
    return temp;
}

template <class T>
void circularArrayList<T>::buildHeap()
{
    for (int i = (listSize / 2) - 1; i >= 0; i--) {
        int cur = element[i];
        int parent;
        int child;

        for (parent = i; (parent * 2 + 1) < listSize; parent = child) {
            child = parent * 2 + 1;
            if (((child + 1) < listSize) && (element[child] < element[child + 1])) {
                child  += 1;
            }

            if (cur > element[child]) {
                break;
            }
            else {
                element[parent] = element[child];
                element[child] = cur;
            }
        }
    }
}

template <class T>
void circularArrayList<T>::insertHeap(const T & value)
{
    if (this->listSize >= this->arrayLength) {
        cc::changeLength1D(this->element, this->arrayLength, this->arrayLength * 2);
        this->arrayLength *= 2;
    }
    
    this->element[listSize++] = value;
    int index = listSize - 1;
    while (index > 0) {
        int child = this->element[index];
        int parent = (index - 1) / 2;
        
        if (parent >= 0) {
            if (child > this->element[parent]) {
                this->element[index] = this->element[parent];
                this->element[parent] = child;
                index = parent;
            }
            else {
                return;
            }
        }
        else {
            break;
        }
    }
}

template <class T>
T circularArrayList<T>::popHeap() 
{
    if (this->listSize < 1) {
        throw cc::illegalParameterValue("element number of array must be >= 1.", "circularArrayList class popHeap");
    }

    T value = this->element[0];
    this->element[0] = this->element[this->listSize - 1];
    this->listSize -= 1;

    int cur = this->element[0];
    int parent;
    int child;
    for (parent = 0; (parent * 2 + 1) < this->listSize; parent = child) {
        child = parent * 2 + 1;
        if (((child + 1) < this->listSize) && (this->element[child] < this->element[child + 1])) {
            child += 1;
        }
        if (cur > this->element[child]) {
            break;
        }
        else {
            this->element[parent] = this->element[child];
            this->element[child] = cur;
        }
    }
    return value;
}

template <class T>
void circularArrayList<T>::sortHeap()
{
    if (this->listSize < 1) {
        return;
    }

    int size = this->listSize;
    while (this->listSize > 0) {
        int temp = this->element[0];
        this->element[0] = this->element[this->listSize - 1];
        this->element[this->listSize - 1] = temp;
        this->listSize -= 1;

        int cur = this->element[0];
        int parent;
        int child;
        for (parent = 0; (parent * 2 + 1) < this->listSize; parent = child) {
            child = parent * 2 + 1;;
            if (((child + 1) < this->listSize && (this->element[child] < this->element[child + 1]))) {
                child += 1;
            }
            if (cur > this->element[child]) {
                break;
            }
            else {
                this->element[parent] = this->element[child];
                this->element[child] = cur;
            }
        }
    }
    this->listSize = size;
}

template <class T>
void circularArrayList<T>::operator = (const circularArrayList<T> & other)
{
    if (this == &other) {
        return;
    }

    if (this->element != nullptr) {
        delete [] this->element;
    }
    this->element = new T[other.arrayLength];
    std::copy(other.element, other.element + other.listSize, this->element);
    this->listSize = other.listSize;
    this->arrayLength = other.arrayLength;
}

template <class T>
void circularArrayList<T>::merge(circularArrayList<T> & a, circularArrayList<T> & b)
{
    *this = a;
    this->buildHeap();
    for (size_t i = 0; i < b.listSize; i++) {
        this->insertHeap(b.element[i]);
    }
    this->sortHeap();
}

template <class T>
void circularArrayList<T>::spilt(circularArrayList<T> & a, circularArrayList<T> & b)
{
    if (a.arrayLength < this->listSize / 2 || b.arrayLength < this->listSize) {
        throw cc::illegalParameterValue("the array length connot be satisfied.", "circularArrayList class split.");
    }
    if (a.element != nullptr) {
        a.listSize = 0;
    }
    if (b.element != nullptr) {
        b.listSize = 0;
    }
    
    for (size_t i = 0, j = 0, k = 0; k < this->listSize; k++) {
        if (k % 2 == 0) {
            a.element[i++] = this->element[k];
            a.listSize += 1;
        }
        else {
            b.element[j++] = this->element[k];
            b.listSize += 1;
        }
    }
}

#endif // !DATA_STRUCTURES_CIRCULARARRAYLIST_H__
