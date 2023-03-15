#include <cstddef>
#include <iostream>

template <class T>
class iterator {
private:
    T * position;
public:
    // use C++ typedef statements to implement bidirectional iterator
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T                               value_type;
    typedef ptrdiff_t                       difference_type;
    typedef T *                             pointer;
    typedef T &                             reference;

    // constructor 
    iterator(T * position = 0);

    // 解引用操作符
    T & operator * () const;
    T * operator -> () const;

    // ++
    iterator & operator ++ ();
    iterator operator ++ (int);
    // --
    iterator & operator -- ();
    iterator operator -- (int);

    // test for equality
    bool operator != (const iterator & other) const;
    bool operator == (const iterator & other) const;
};

template <class T>
iterator<T>::iterator(T * position) 
{
    this->position = position;
}

template <class T>
T & iterator<T>::operator * () const 
{
    return *this->position;
}

template <class T>
T * iterator<T>::operator -> () const 
{
    return this->position;
}

template <class T>
iterator<T> & iterator<T>::operator ++ () 
{
    this->position++;
    return *this;
}

template <class T>
iterator<T> iterator<T>::operator ++ (int) 
{
    iterator old = *this;
    this->position++;
    return old;
}

template <class T>
iterator<T> & iterator<T>::operator -- ()
{
    this->position--;
    return *this;
}

template <class T>
iterator<T> iterator<T>::operator -- (int)
{
    iterator old = *this;
    this->position--;
    return old;
}

template <class T>
bool iterator<T>::operator != (const iterator & other) const 
{
    return this->position != other.position;
}

template <class T>
bool iterator<T>::operator == (const iterator & other) const 
{
    return this->position == other.position;
}

