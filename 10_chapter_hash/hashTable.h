#ifndef DATA_STRUCTURES_HASHTABLE_H__
#define DATA_STRUCTURES_HASHTABLE_H__

#include "../util.h"

#include <iostream>

class myHash
{
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

template <class K, class E>
class hashTable {
public:
    hashTable(int theDivisor);
    ~hashTable();

    int search(const K & key) const; 
        // 搜索散列表，查找關鍵字爲 key 的書對
        // 若存在，返回他的位置
        // 否則，若散列表不滿，返回一個 key 的書對可以插入的位置
    std::pair<const K, E> * find(const K & key) const; 
        // 返回匹配對數的指針
    void insert(const std::pair<const K, E> & pair);
        // 把書對 pair 出入到字典，若存在則覆蓋，若表滿，則拋出異常

private:
    std::pair<const K, E> ** table;     // 散列表
    myHash hash;                  // 把類型K映射到一個非整數
    int dSize;                          // 字典中書對個數
    int divisor;                        // 散列函數除數
};

template <class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
    this->divisor = theDivisor;
    this->dSize = 0;

    // 分配和初始化散列表數組
    this->table = new std::pair<const K, E> * [this->divisor];
    for (int i = 0; i < this->divisor; i++) {
        table[i] = nullptr;
    }
}

template <class K, class E>
hashTable<K, E>::~hashTable()
{
    if (this->table != nullptr) {
        delete [] this->table;
    }
}

template <class K, class E>
int hashTable<K, E>::search(const K & key) const
{
    int i = (int)hash(key) % this->divisor;
    int j = i;

    do {
        if (this->table[j] == nullptr || this->table[j]->first == key) {
            return j;
        }
        j = (j + 1) % this->divisor;
    } while (j != i);

    return j;
}

template <class K, class E>
std::pair<const K, E> * hashTable<K, E>::find(const K & key) const
{
    int targetIndex = this->search(key);
    if (this->table[targetIndex] == nullptr || this->table[targetIndex].first != key) {
        return nullptr;
    }
    return this->table[targetIndex];
}

template <class K, class E>
void hashTable<K, E>::insert(const std::pair<const K, E> & pair)
{
    int targetIndex = this->find(pair.first);
    if (this->table[targetIndex] == nullptr) {
        this->table[targetIndex] = new std::pair<const K, E>(pair);
        this->dSize += 1;
    }
    else if (this->table[targetIndex].first == pair.first) {
        this->table[targetIndex]->second = pair.second;
    }
    else {
        throw cc::illegalParameterValue("in hashTable.h insert", "table was full");
    }
}

#endif // !DATA_STRUCTURES_HASHTABLE_H__
