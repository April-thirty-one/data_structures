#ifndef DATA_STRUCTURES_6_CHAPTER_ITERATOR_H__
#define DATA_STRUCTURES_6_CHAPTER_ITERATOR_H__

#include "chainNode.h"
#include <cstddef>
#include <iterator>

template <class T>
class iterator {
public:
    // using C++ typedef statements to implement forward iterator
    typedef std::forward_iterator_tag   iterator_category;
    typedef T                           value_type;
    typedef ptrdiff_t                   difference_type;
    typedef T *                         pointer;
    typedef T &                         reference;

    iterator(chainNode<T> * node = nullptr);

    T & operator * () const;
    T * operator -> () const;

    iterator operator ++ ();
    iterator operator ++ (int);

    bool operator != (const iterator right) const;
    bool operator == (const iterator right) const;

    iterator begin() const;
    iterator end() const;

private:
    chainNode<T> * node;
};

template <class T>
iterator<T>::iterator(chainNode<T> * node) : node(node) {}

template <class T>
T & iterator<T>::operator * () const 
{
    return this->node->element;
}

template <class T>
T * iterator<T>::operator -> () const 
{
    return &this->node->element;
}

template <class T>
iterator<T> iterator<T>::operator ++ ()
{
    this->node = this->node->next;
    return *this;
}

template <class T>
iterator<T> iterator<T>::operator ++ (int)
{
    auto temp = *this;
    this->node = this->node->next;
    return temp;
}

template <class T>
bool iterator<T>::operator != (const iterator right) const
{
    return this->node != right.node;
}

template <class T>
bool iterator<T>::operator == (const iterator right) const
{
    return this->node == right.node;
}


#endif // !DATA_STRUCTURES_6_CHAPTER_ITERATOR_H__
