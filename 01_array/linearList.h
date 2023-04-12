#ifndef DATA_STRUCTURES_LINEARLIST_H__
#define DATA_STRUCTURES_LINEARLIST_H__

#include "../util.h"

#include <ostream>

template <class T>
class linearList {
public:
    virtual ~linearList() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T & get(int index) const = 0;
    virtual int indexOf(const T & value) const = 0;
    virtual void erase(int index) = 0;
    virtual void insert(int index, const T & value) = 0;
    virtual void output(std::ostream & out) const = 0;
};

#endif // !DATA_STRUCTURES_LINEARLIST_H__
