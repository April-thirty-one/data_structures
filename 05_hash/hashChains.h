#ifndef DATA_STRUCTURES_10_CHAPTER_HASH_HASHCHAINS_H__
#define DATA_STRUCTURES_10_CHAPTER_HASH_HASHCHAINS_H__

#include "./hash.h"
#include "./dictionary.h"
#include "./sortedChain.h"

#include <iostream>
#include <sys/types.h>

template <class K, class E>
class hashChains : public dictionary<K, E> {
public:
    hashChains(int divisor = 11);
    ~hashChains();

    bool empty() const;
    int size() const;
    std::pair<K, E> * find(const K & key) const;
    void insert(const std::pair<K, E> & pair);
    void erase(const K & key);
    
    friend std::ostream & operator << (std::ostream & out, const hashChains<K, E> & obj);

protected:
    sortedChain<K, E> * table;
    hash<K> hash;
    int dSize;
    int divisor;
};

template <class K, class E>
hashChains<K, E>::hashChains(int divisor)
{

}




#endif //
