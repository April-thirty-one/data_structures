#ifndef DATA_STRUCTURES_10_CHAPTER_HASH_HASH_H__
#define DATA_STRUCTURES_10_CHAPTER_HASH_HASH_H__

#include <iostream>

template <class T>
class hash;

template <>
class hash<std::string> {
public:
    size_t operator() (const std::string key) const 
    {
        unsigned long hashValue = 0;
        int length = (int)key.length();
        for (int i = 0; i < length; i++) {
            hashValue = 5 * hashValue + key.at(i);
        }
        return size_t(hashValue);
    }
};

#endif // !DATA_STRUCTURES_
