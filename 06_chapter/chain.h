#ifndef DATA_STRUCTURES_CHAIN_H__
#define DATA_STRUCTURES_CHAIN_H__

#include "../5_chapter/linearList.h"
#include "./chainNode.h"
#include "./iterator.h"
#include "../5_chapter/arrayList.h"

#include <ostream>
#include <utility>

template <class T>
class chain;

template <class T>
std::ostream & operator << (std::ostream & out, const chain<T> & obj);


template <class T>
class chain : public linearList<T> {
public:
    chain();
    chain(const chain<T> & other);
    ~chain();

    bool empty() const override;
    int size() const override;
    T & get(int index) const override;
    int indexOf(const T & value) const override;
    void erase(int index) override;
    void insert(int index, const T & value) override;
    void output(std::ostream & out) const override;

    iterator<T> begin() const;
    iterator<T> end() const;

    void setSize(int size);
    void set(int index, const T & value);
    void removeRange(int fromIndex, int toIndex);
    int lastIndexOf(const T & element) const;
    void swap(chain<T> & other);
    void clear();
    chain<T> & fromList(const arrayList<T> & arrayList);
    arrayList<T> & toList(arrayList<T> & arrayList);
    void leftShift(int moveDistance);
    void reverse();
    void meld(chain<T> & chainlist1, chain<T> & chainlist2);
    void merge(chain<T> & chainlist1, chain<T> & chainlist2);
    void split(chain<T> & chainlist1, chain<T> & chainlist2);

    T & operator [] (int index) const;
    bool operator == (const chain<T> & other) const;
    bool operator != (const chain<T> & other) const;
    bool operator < (const chain<T> & other) const;

    friend std::ostream & operator << <>(std::ostream & out, const chain<T> & obj);

private:
    void checkIndex(const char * position, int index) const;

    chainNode<T> * dummyHead;
    int listSize;
};

template <class T>
void chain<T>::checkIndex(const char * position, int index) const
{
    if (index < 0 || index >= this->listSize) {
        throw cc::illegalParameterValue(position, "index out of range.");
    }
}

template <class T>
chain<T>::chain()
{
    this->dummyHead = new chainNode<T>(-1, nullptr);
    if (this->dummyHead == nullptr) {
        throw cc::illegalParameterValue("in chain class constructor.", "constructor failed.");
    }
    this->listSize = 0;
    std::cout << "-- constructor success." << std::endl;
}

template <class T>
chain<T>::chain(const chain<T> & other)
{
    this->dummyHead = new chainNode<T>(-1, nullptr);
    if (this->dummyHead == nullptr) {
        throw cc::illegalParameterValue("in chain class constructor.", "constructor failed.");
    }
    this->listSize = 0;

    chainNode<T> * otherNode = other.dummyHead->next;
    chainNode<T> * current = this->dummyHead;
    while (otherNode != nullptr) {
        current->next = new chainNode<T>(otherNode->element, current->next);
        this->listSize += 1;
        current = current->next;
        otherNode = otherNode->next;
    }
    std::cout << "-- copy constructor success." << std::endl;
}

template <class T>
chain<T>::~chain()
{
    chainNode<T> * deleteNode = this->dummyHead;
    while (this->dummyHead != nullptr) {
        deleteNode = this->dummyHead;
        this->dummyHead = this->dummyHead->next;
        delete deleteNode;
    }
    this->listSize = 0;
    std::cout << "-- destructor success." << std::endl;
}

template <class T>
bool chain<T>::empty() const 
{
    return this->listSize == 0;
}

template <class T>
int chain<T>::size() const 
{
    return this->listSize;
}

template <class T>
T & chain<T>::get(int index) const
{
    checkIndex("in chain class get function.", index);

    chainNode<T> * current = this->dummyHead->next;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->element;
}

template <class T>
int chain<T>::indexOf(const T & value) const
{
    chainNode<T> * current = this->dummyHead->next;
    for (int i = 0; i < this->listSize; i++) {
        if (current->element == value) {
            return i;
        }
    }
    return -1;
}

template <class T>
void chain<T>::erase(int index)
{
    checkIndex("in chain.h erase function.", index);

    chainNode<T> * preNode = this->dummyHead;
    for (size_t i = 0; i < index; i++) {
        preNode = preNode->next;
    }
    chainNode<T> * deleteNode = preNode->next;
    preNode->next = deleteNode->next;
    delete deleteNode;
    this->listSize -= 1;
}

template <class T>
void chain<T>::insert(int index, const T & value)
{
    if (index < 0 || index > this->listSize) {
        throw cc::illegalParameterValue("in chain.h insert", "index out of range.");
    }

    chainNode<T> * preNode = this->dummyHead;
    for (size_t i = 0; i < index; i++) {
        preNode = preNode->next;
    }
    chainNode<T> * insertNode = new chainNode<T>(value, preNode->next);
    preNode->next = insertNode;
    this->listSize += 1;
}

template <class T>
void chain<T>::output(std::ostream & out) const {}

template <class T>
std::ostream & operator << (std::ostream & out, const chain<T> & obj) 
{
    chainNode<T> * head = obj.dummyHead->next;
    while (head != nullptr) {
        out << head->element << "  ";
        head = head->next;
    }
    return out;
}

template <class T>
iterator<T> chain<T>::begin() const
{
    return iterator<T>(this->dummyHead->next);
}

template <class T>
iterator<T> chain<T>::end() const
{
    // the iterator of link list cannot --, so it simply return nullptr.
    return iterator<T>(nullptr);
}

template <class T>
void chain<T>::setSize(int size)
{
    if (size < 0) {
        throw cc::illegalParameterValue("in chain.h setSize", "size must be >= 0");
    }

    if (this->listSize == size) {
        return;
    }
    else if (this->listSize > size) {
        chainNode<T> * preNode = this->dummyHead;
        for (size_t i = 0; i < size; i++) {
            preNode = preNode->next;
        }
        chainNode<T> * temp = preNode;
        preNode = preNode->next;
        temp->next = nullptr;

        chainNode<T> * deleteNode;
        while (preNode != nullptr) {
            deleteNode = preNode;
            preNode = preNode->next;
            delete deleteNode;
        }
        this->listSize = size;
    }
    else {
        const int number = size - this->listSize;
        chainNode<T> * current = this->dummyHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        for (size_t i = 0; i < number; i++) {
            current->next = new chainNode<T>(0, nullptr);
            current = current->next;
        }
        this->listSize = size;
    }
}

template <class T>
void chain<T>::set(int index, const T & value)
{
    checkIndex("in chain.h set()", index);

    this->get(index) = value;
}

template <class T>
void chain<T>::removeRange(int fromIndex, int toIndex)
{
    if (fromIndex < 0 || fromIndex > this->listSize || toIndex < 0 || toIndex > this->listSize) {
        throw cc::illegalParameterValue("in chain.h removeRange()", "index error");
    }

    chainNode<T> * preFromNode = this->dummyHead;
    chainNode<T> * ToNode = this->dummyHead;
    for (size_t i = 0; i < fromIndex; i++) {
        preFromNode = preFromNode->next;
        ToNode = ToNode->next;
    }
    chainNode<T> * deleteNode;
    ToNode = ToNode->next;
    for (size_t i = 0; i < toIndex - fromIndex; i++) {
        deleteNode = ToNode;
        ToNode = ToNode->next;
        delete deleteNode;
    }
    preFromNode->next = ToNode;
}

template <class T>
int chain<T>::lastIndexOf(const T & element) const
{
    int result = -1;
    chainNode<T> * current = this->dummyHead->next;
    for (int i = 0; i < this->listSize; i++) {
        if (current->element == element) {
            result = i;
        }
        current = current->next;
    }
    return result;
}

template <class T>
T & chain<T>::operator [] (int index) const
{
    checkIndex("in chain.h operator[]", index);

    return this->get(index);
}

template <class T>
bool chain<T>::operator == (const chain<T> & other) const
{
    if (this->listSize != other.listSize) {
        return false;
    }

    chainNode<T> * thisNode = this->dummyHead->next;
    chainNode<T> * otherNode = other.dummyHead->next;
    while (thisNode != nullptr) {
        if (thisNode->element != otherNode->element) {
            return false;
        }
        thisNode = thisNode->next;
        otherNode = otherNode->next;
    }
    return true;
}

template <class T>
bool chain<T>::operator != (const chain<T> & other) const
{
    return !(*this == other);
}


template <class T>
bool chain<T>::operator < (const chain<T> & other) const
{
    chainNode<T> * thisNode = this->dummyHead->next;
    chainNode<T> * otherNode = other.dummyHead->next;
    while (thisNode != nullptr && otherNode != nullptr) {
        if (thisNode->element > otherNode->element) {
            return false;
        }
        else if (thisNode->element < otherNode->element) {
            return true;
        }
        thisNode = thisNode->next;
        otherNode = otherNode->next;
    }
    return false;
}

template <class T>
void chain<T>::swap(chain<T> & other)
{
    chainNode<T> * temp = this->dummyHead->next;
    this->dummyHead->next = other.dummyHead->next;
    other.dummyHead->next = temp;
}

template <class T>
void chain<T>::clear()
{
    if (this->listSize == 0) {
        return;
    }
    chainNode<T> * current = this->dummyHead->next;
    chainNode<T> * deleteNode;
    while (current != nullptr) {
        deleteNode = current;
        current = current->next;
        delete deleteNode;
    }
    this->listSize = 0;
}

template <class T>
chain<T> & chain<T>::fromList(const arrayList<T> & arrayList)
{
    if (arrayList.size() == 0) {
        this->clear();
        return *this;
    }

    chainNode<T> * current = this->dummyHead;
    for (size_t i = 0; i < arrayList.size(); i++) {
        current->next = new chainNode<T>(arrayList[i], nullptr);
        current = current->next;
    }
    this->listSize = arrayList.size();
    return *this;
}

template <class T>
arrayList<T> & chain<T>::toList(arrayList<T> & arrayList)
{
    arrayList.clear();
    if (this->listSize == 0) {
        return arrayList;
    }
    
    chainNode<T> * current = this->dummyHead->next;
    for (size_t i = 0; i < arrayList.capacity(), current != nullptr; i++, current = current->next) {
        arrayList.insert(i, current->element);
    }
    return arrayList;
}

template <class T>
void chain<T>::leftShift(int moveDistance)
{
    chainNode<T> * head;
    chainNode<T> * current = this->dummyHead->next;;
    for (size_t i = 0; i < moveDistance; i++) {
        current = current->next;
    }
    head = current;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = this->dummyHead->next;
    this->dummyHead->next = head;

    while (current->next != head) {
        current = current->next;
    }
    current->next = nullptr;
}

template <class T>
void chain<T>::reverse()
{
    chainNode<T> * preNode = nullptr;
    chainNode<T> * head = this->dummyHead->next;
    chainNode<T> * temp;
    while (head != nullptr) {
        temp = preNode;
        preNode = head;
        head = head->next;
        preNode->next = temp;
    }
    this->dummyHead->next = preNode;
}

template <class T>
void chain<T>::meld(chain<T> & chainlist1, chain<T> & chainlist2)
{
    this->clear();
    chainNode<T> * curNode1 = chainlist1.dummyHead->next;
    chainNode<T> * curNode2 = chainlist2.dummyHead->next;
    chainNode<T> * thisNode = this->dummyHead;
    while (curNode1 != nullptr && curNode2 != nullptr) {
        thisNode->next = curNode1;
        thisNode = thisNode->next;
        curNode1 = curNode1->next;
        chainlist1.listSize -= 1;
        
        thisNode->next = curNode2;
        thisNode = thisNode->next;
        curNode2 = curNode2->next;
        chainlist2.listSize -= 1;

        this->listSize += 2;
    }
    if (curNode1 == nullptr && curNode2 == nullptr) {
        thisNode->next = nullptr;
    }
    else if (curNode1 == nullptr) {
        thisNode->next = curNode2;
        this->listSize += chainlist2.listSize;
    }
    else {
        thisNode->next = curNode1;
        this->listSize += chainlist1.listSize;
    }
    chainlist1.dummyHead->next = nullptr;
    chainlist1.listSize = 0;
    chainlist2.dummyHead->next = nullptr;
    chainlist2.listSize = 0;
}

template <class T>
void chain<T>::merge(chain<T> & chainlist1, chain<T> & chainlist2)
{
    this->clear();
    chainNode<T> * curNode1 = chainlist1.dummyHead->next;
    chainNode<T> * curNode2 = chainlist2.dummyHead->next;
    chainNode<T> * thisNode = this->dummyHead;
    while (curNode1 != nullptr && curNode2 != nullptr) {
        if (curNode1->element <= curNode2->element) {
            thisNode->next = curNode1;
            thisNode = thisNode->next;
            this->listSize += 1;
            curNode1 = curNode1->next;
        }
        else {
            thisNode->next = curNode2;
            thisNode = thisNode->next;
            this->listSize += 1;
            curNode2 = curNode2->next;
        }
    }
    if (curNode1 == nullptr && curNode2 == nullptr) {
        thisNode->next = nullptr;
    }
    else if (curNode1 == nullptr) {
        thisNode->next = curNode2;
        this->listSize += chainlist2.listSize;
    }
    else {
        thisNode->next = curNode1;
        this->listSize += chainlist1.listSize;
    }
    chainlist1.dummyHead->next = nullptr;
    chainlist1.listSize = 0;
    chainlist2.dummyHead->next = nullptr;
    chainlist2.listSize = 0;
}

template <class T>
void chain<T>::split(chain<T> & chainlist1, chain<T> & chainlist2)
{
    chainlist1.clear();
    chainNode<T> * tempNode1 = chainlist1.dummyHead;
    chainlist2.clear();
    chainNode<T> * tempNode2 = chainlist2.dummyHead;

    chainNode<T> * current = this->dummyHead->next;
    while (current != nullptr) {
        tempNode1->next = current;
        chainlist1.listSize += 1;
        current = current->next;
        tempNode1 = tempNode1->next;

        if (current != nullptr) {
            tempNode2->next = current;
            chainlist2.listSize += 1;
            current = current->next;
            tempNode2 = tempNode2->next;
        }
        else {
            break;
        }
    }
    tempNode1->next = nullptr;
    tempNode2->next = nullptr;
    this->dummyHead->next = nullptr;
}

#endif // !DATA_STRUCTURES_CHAIN_H__
