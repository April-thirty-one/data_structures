#ifndef DATA_STRUCTURES_ARRAYLIST_H__
#define DATA_STRUCTURES_ARRAYLIST_H__

#include "./linearList.h"
#include <algorithm>
#include <iterator>
#include <utility>

template <class T>
class arrayList;

template <class T>
arrayList<T> meld(const arrayList<T> & rth, const arrayList<T> & lth);

template <class T>
class arrayList : public linearList<T> {
protected:
    T * element;                        // one-dimensional array
    int arrayLength;                    // length of array
    int listSize;                       // number of element
    
    void checkIndex(int index, const char * position) const;   // throw an exception if the index is invalid 

public:
    arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T> &);
    ~arrayList();

    bool empty() const override;
    int size() const override;
    int capacity() const;
    T & get(int index) const override;
    int indexOf(const T & value) const override;
    void erase(int index) override;
    void push_back(const T & value);
    void insert(int index, const T & element) override;
    void swap(arrayList<T> & other);
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
    void merge(arrayList<T> & a, arrayList<T> & b);
    void spilt(arrayList<T> & a, arrayList<T> & b);
    void output(std::ostream & out = std::cout) const override;

    T & operator [] (int index) const;
    bool operator == (const arrayList<T> & other) const;
    bool operator != (const arrayList<T> & other) const;
    bool operator < (const arrayList<T> & other) const;
    void operator = (const arrayList<T> & other);

    friend arrayList<T> meld<>(const arrayList<T> & rth, const arrayList<T> & lth);
};

template <class T>
arrayList<T>::arrayList(int initialCapacity) {
    if (initialCapacity < 0) {
        throw cc::illegalParameterValue("-- capacity must > 0.", "constructor");
    }
    this->element = new T[initialCapacity];
    this->arrayLength = initialCapacity;
    this->listSize = 0;
    std::cout << "-- arrayList constructor success." << std::endl;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> & other) 
{
    if (this == &other) {
        return;
    }

    this->element = new T[other.arrayLength];
    std::copy(other.element, other.element + other.listSize, this->element);
    this->listSize = other.listSize;
    this->arrayLength = other.arrayLength;
    std::cout << "-- arrayList copy constructor success." << std::endl;
}

template <class T>
arrayList<T>::~arrayList() 
{
    if (this->element != nullptr) {
        delete [] this->element;
    }
    std::cout << "-- destructor success." << std::endl;;
}

template <class T>
void arrayList<T>::checkIndex(int index, const char * position) const 
{
    if (index > this->listSize || index < 0) {
        throw cc::illegalParameterValue(" index out of range.", position);
    }
}

template <class T>
bool arrayList<T>::empty() const 
{
    return this->listSize == 0;
}

template <class T>
int arrayList<T>::size() const 
{
    return this->listSize;
}

template <class T>
int arrayList<T>::capacity() const 
{
    return this->arrayLength;
}

template <class T>
T & arrayList<T>::get(int index) const 
{
    checkIndex(index, "get ");

    return this->element[index];
}

template <class T>
int arrayList<T>::indexOf(const T & value) const 
{
    int index = (int)(std::find(this->element, this->element + this->listSize, value) - this->element);
    if (index == this->listSize) {
        return -1;
    }
    return index;
}

template <class T>
void arrayList<T>::erase(int index)
{
    checkIndex(index, "erase");

    std::copy(this->element+index + 1, this->element + this->listSize, this->element + index);
    this->listSize--;

    // estimate whether to reduce the array size
    if (this->listSize * 4 < this->arrayLength) {
        cc::changeLength1D(this->element, this->arrayLength, this->arrayLength / 4);
        this->arrayLength /= 4;
    }
}

template <class T>
void arrayList<T>::push_back(const T & value)
{
    if (this->listSize == this->arrayLength) {
        cc::changeLength1D(this->element, this->arrayLength, this->arrayLength * 2);
        this->arrayLength *= 2;
    }
    this->element[this->listSize] = value;
    this->listSize++;
}

template <class T>
void arrayList<T>::insert(int index, const T & value)
{
    checkIndex(index, "insert");

    if (this->listSize == this->arrayLength) {
        cc::changeLength1D(this->element, this->arrayLength, this->arrayLength * 2);
        this->arrayLength *= 2;
    }
    std::copy_backward(this->element + index, this->element + this->listSize, this->element + this->listSize + 1);
    this->element[index] = value;
    this->listSize++;
}

template <class T>
void arrayList<T>::output(std::ostream & out) const 
{
    std::copy(this->element, this->element + this->listSize, std::ostream_iterator<T>(out, "  "));
}

template <class T>
std::ostream & operator << (std::ostream & out, const arrayList<T> & obj)
{
    obj.output(out);
    return out;
}

template <class T>
T & arrayList<T>::operator [] (int index) const
{
    checkIndex(index, "operator []");
    
    return this->element[index];
}

template <class T>
bool arrayList<T>::operator == (const arrayList<T> & other) const 
{
    if (this->listSize != other.listSize || this->arrayLength != other.arrayLength) {
        return false;
    }

    for (int i = 0; i < this->listSize; i++) {
        if (this->element[i] != other.element[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool arrayList<T>::operator != (const arrayList<T> & other) const 
{
    return !(*this == other);
}

template <class T>
bool arrayList<T>::operator < (const arrayList<T> & other) const
{
    for (int i = 0; i < this->listSize && i < other.listSize; i++) {
        if (this->element[i] == other.element[i]) {
            continue;
        }
        else if (this->element[i] > other.element[i]) {
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
void arrayList<T>::swap(arrayList<T> & other) 
{
    T * temp_element = this->element;
    int temp_listSize = this->listSize;
    int temp_arrayLength = this->arrayLength;

    this->element = other.element;
    this->listSize = other.listSize;
    this->arrayLength = other.arrayLength;

    other.element = temp_element;
    other.listSize = temp_listSize;
    other.arrayLength = temp_arrayLength;
}

template <class T>
void arrayList<T>::reserve(int capacity)
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
T arrayList<T>::set(int index, const T & value) 
{
    checkIndex(index, "set");

    T result = this->element[index];
    this->element[index] = value;
    return result;
}

template <class T>
void arrayList<T>::clear()
{
    this->listSize = 0;
}

template <class T>
void arrayList<T>::removeRange(int begin, int end) 
{
    checkIndex(begin, "removeRange");
    checkIndex(end, "removeRange");

    std::copy(this->element + end, this->element + this->listSize, this->element + begin);
    this->listSize -= (end - begin);
}

template <class T>
int arrayList<T>::lastIndexOf(const T & value) const 
{
    for (int i = this->listSize - 1; i >= 0; i--) {
        if (this->element[i] == value) {
            return i;
        }
    }
    return -1;
}

template <class T>
void arrayList<T>::reverse()
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
void arrayList<T>::leftShift(int moveNumber)
{
    if (moveNumber > this->listSize) {
        throw cc::illegalParameterValue("moveNumber must be <= listsize.", "leftShift");
    }
    std::copy(this->element + moveNumber, this->element + this->listSize, this->element);
    this->listSize -=  moveNumber;
}

template <class T>
void arrayList<T>::circularShift(int moveNumber)
{
    for (int i = 0; i < moveNumber; i++) {
        T temp = this->element[0];
        std::copy(this->element + 1, this->element + this->listSize, this->element);
        this->element[this->listSize - 1] = temp;
    }
}

template <class T>
void arrayList<T>::half()
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
arrayList<T> meld(const arrayList<T> & rth, const arrayList<T> & lth)
{
    arrayList<T> temp(rth.listSize + lth.listSize);
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
void arrayList<T>::buildHeap()
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
void arrayList<T>::insertHeap(const T & value)
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
T arrayList<T>::popHeap() 
{
    if (this->listSize < 1) {
        throw cc::illegalParameterValue("element number of array must be >= 1.", "arrayList class popHeap");
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
void arrayList<T>::sortHeap()
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
void arrayList<T>::operator = (const arrayList<T> & other)
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
void arrayList<T>::merge(arrayList<T> & a, arrayList<T> & b)
{
    *this = a;
    this->buildHeap();
    for (size_t i = 0; i < b.listSize; i++) {
        this->insertHeap(b.element[i]);
    }
    this->sortHeap();
}

template <class T>
void arrayList<T>::spilt(arrayList<T> & a, arrayList<T> & b)
{
    if (a.arrayLength < this->listSize / 2 || b.arrayLength < this->listSize) {
        throw cc::illegalParameterValue("the array length connot be satisfied.", "arrayList class split.");
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

#endif // !DATA_STRUCTURES_ARRAYLIST_H__
