#ifndef DATA_STRUCTURES_6_CHAPTER_EXTENDEDLINEARLIST_H__
#define DATA_STRUCTURES_6_CHAPTER_EXTENDEDLINEARLIST_H__

#include "../5_chapter/linearList.h"

template <class T>
class extendedLinearList : public linearList<T> {
public:
    virtual ~extendedLinearList() {}
    virtual void clear() = 0;
    virtual void push_back(const T & element) = 0;
};


#endif // !DATA_STRUCTURES_6_CHAPTER_EXTENDEDLINEARLIST_H__
