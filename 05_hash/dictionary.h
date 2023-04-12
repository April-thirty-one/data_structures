#ifndef DATA_STRUCTURES_DICTIONARY_H__
#define DATA_STRUCTURES_DICTIONARY_H__

#include <iostream>

template <class K, class E>
class dictionary {
public:
    virtual ~dictionary() = default;

    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual std::pair<K, E> * find(const K &) const = 0;
    virtual void erase(const K &) = 0;
    virtual void insert(const std::pair<K, E> & element) = 0;
};

#endif // !DATA_STRUCTURES_DICTIONARY_H__


