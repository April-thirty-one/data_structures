#ifndef DATA_STRUCTURES_VECTORLIST_H__
#define DATA_STRUCTURES_VECTORLIST_H__

#include "linearList.h"
#include <iterator>
#include <vector>
template <class T>
class vectorList : public linearList<T> {
private:
    std::vector<T> * element;

    void checkIndex(const char * position, int index) const;

public:
    vectorList(int capacity = 10);
    vectorList(const vectorList<T> & other);
    ~vectorList();

    bool empty() const override;
    int size() const override;
    T & get(int index) const override;
    int indexOf(const T & value) const override;
    void erase(int index) override;
    void insert(int index, const T & value) override;
    void output(std::ostream & out = std::cout) const override;

    int capacity() const;
    void push_back(const T & value);

    typename std::vector<T>::iterator begin() const;
    typename std::vector<T>::iterator end() const;
};

template <class T>
void vectorList<T>::checkIndex(const char * position, int index) const 
{
    if (index > this->element->size() || index < 0) {
        throw cc::illegalParameterValue(" index out of range.", position);
    }
}

template <class T>
vectorList<T>::vectorList(int capacity) 
{
    if (capacity < 0) {
        throw cc::illegalParameterValue("vectorList class -- constructor.", "capacity must be >= 0.");
    }
    this->element = new std::vector<T>(capacity);
    std::cout << "vectorList constructor success." << std::endl;
}

template <class T>
vectorList<T>::vectorList(const vectorList<T> & other) 
{
    if (other.element == nullptr) {
        return;
    }
    this->element = new std::vector<T>(other.capacity());
    for (size_t i = 0; i < other.size(); i++) {
        this->element[i] = other.element[i];
    }
}

template <class T>
vectorList<T>::~vectorList() 
{
    if (this->element != nullptr) {
        delete this->element;
    }
    std::cout << "-- destructor success." << std::endl;
}

template <class T>
bool vectorList<T>::empty() const 
{
    return this->element->empty();
}

template <class T>
int vectorList<T>::size() const 
{
    return this->element->size();
}

template <class T>
T & vectorList<T>::get(int index) const 
{
    checkIndex("vectorList class get function.", index);

    return this->element->at(index);
}

template <class T>
int vectorList<T>::indexOf(const T & value) const 
{
    for (size_t i = 0; i < this->element->size(); i++) {
        if (this->element->at(i) == value) {
            return i;
        }
    }
    return -1;
}

template <class T>
void vectorList<T>::erase(int index) 
{
    this->element->erase(this->element->begin() + index);
}

template <class T>
void vectorList<T>::insert(int index, const T & value) 
{
    this->element->insert(this->element->begin() + index, value);
}

template <class T>
void vectorList<T>::output(std::ostream & out) const 
{
    std::copy(this->element->begin(), this->element->end(), std::ostream_iterator<T>(out, "  "));
}

template <class T>
std::ostream & operator << (std::ostream & out, const vectorList<T> & obj) 
{
    obj.output(out);
    return out;
}


template <class T>
int vectorList<T>::capacity() const
{
    return this->element->capacity();
}


template <class T>
typename std::vector<T>::iterator vectorList<T>::begin() const
{
    return this->element->begin();
}

template <class T>
typename std::vector<T>::iterator vectorList<T>::end() const 
{
    return this->element->end();
}

template <class T>
void vectorList<T>::push_back(const T & value)
{
    this->element->push_back(value);
}


#endif // !DATA_STRUCTURES_VECTORLIST_H__
