#ifndef DATA_STRUCTURES_11_CHAPTER_TREE_BINARYTREE_H__
#define DATA_STRUCTURES_11_CHAPTER_TREE_BINARYTREE_H__

#include <vector>

template <class T>
class binayTree {
public:
    virtual ~binayTree() {}

    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual std::vector<T> preOrder() const = 0;
    virtual std::vector<T> inOrder() const = 0;
    virtual std::vector<T> postOrder() const = 0;
    virtual std::vector<std::vector<T>> levelOrder() const = 0;
};

#endif
