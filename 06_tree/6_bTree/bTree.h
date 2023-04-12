#include "../../utils/utils.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

/**
    level = 6 -- keys 最大可以存储 5 个key，若要加入第 6 个 key，先分裂，在加入
*/
const int degree = 3;

template <class T>
class bTree;

template <class T>
std::ostream & operator << (std::ostream & out, const bTree<T> & obj);

template <class T>
class bTree 
{
public:
    class bTreeNode 
    {
    public:
        bTreeNode(bool leaf);
        ~bTreeNode();

    public:
        bool leaf;                      // 叶子节点
        int nums;                       // 当前 keys 数组内有 nums 个 key

        T * keys;                       // key 数组
        bTreeNode ** childrens;         // child 数组
    };

public:
    bTree();
    ~bTree();

    void insertKey(const T & key);          // 插入一个 key
    bTreeNode * searchKey(const T & key) const;
    void deleteKey(const T & key);

    friend std::ostream & operator << <>(std::ostream & out, const bTree<T> & obj);

private:
    bTreeNode * tree;               // 当前树的 根节点

private:
    // helper function
    void deleteTree_(bTreeNode * targetNode);
    void splitNode_(bTreeNode * parent, int idx);
    void addNode_(bTreeNode * current, const T & key);
    void mergeNode_(bTreeNode * parent, const int idx);
    int binSearch_(const T * keys, const int nums, const T & key);
    bTreeNode * searchNode_(bTreeNode * current, const T & key) const;
    void leafBorrowKey_(bTreeNode * parent, int idx);
    void nonLeafBorrowKey_(bTreeNode * parent, int idx);
    void deleteCurrentKey_(bTreeNode * current, const T & key);
};

template <class T>
bTree<T>::bTreeNode::bTreeNode(bool leaf)
{
    this->nums = 0;
    this->leaf = leaf;
    this->keys = new T[(degree * 2) - 1];
    this->childrens = new bTreeNode*[degree * 2];
    for (size_t i = 0; i < degree * 2; i++) {
        this->childrens[i] = nullptr;
    }
}

template <class T>
bTree<T>::bTreeNode::~bTreeNode()
{
    delete [] this->keys;
    delete [] this->childrens;
} 

template <class T>
bTree<T>::bTree()
{
    this->tree = new bTreeNode(true);
    if (this->tree == nullptr) {
        throw illegalError("memory allocation failed");
    }
}

template <class T>
void bTree<T>::deleteTree_(bTreeNode * targetNode) 
{
    if (targetNode == nullptr) {
        return;
    }

    for (size_t i = 0; i < targetNode->nums + 1; i++) {
        deleteTree_(targetNode->childrens[i]);
    }
    delete targetNode;
}

template <class T>
bTree<T>::~bTree()
{
    deleteTree_(this->tree);
}

/**
    @param parent: 表示要分裂节点的父节点
    @param idx: 表示当前节点是父节点的第 idx 个孩子
*/
template <class T>
void bTree<T>::splitNode_(bTreeNode * parent, int idx)
{
    // 处理节点 一分为二
    bTreeNode * current = parent->childrens[idx];
    bTreeNode * brother = new bTreeNode(current->leaf);
    for (int i = 0; i < degree - 1; i++) {
        brother->keys[i] = current->keys[degree + i];
    }
    brother->nums = degree - 1;

    if (!current->leaf) {
        for (size_t i = 0; i < degree; i++) {
            brother->childrens[i] = current->childrens[degree + i];
        }
    }
    current->nums = degree - 1;
    // 节点分裂之后 curren 会有一个 key 上升到 parent -- current 是 parent 的第 idx 个孩子，则上升的 key 在 parent->keys 的索引就是 idx
    for (int i = parent->nums; i > idx; i--) {
        parent->keys[i] = parent->keys[i - 1];
    }
    parent->keys[idx] = current->keys[degree - 1];
    parent->nums += 1;
    // 现在处理 parent 的 childrens 指针
    for (int i = parent->nums + 1; i > idx + 1; i--) {
        parent->childrens[i] = parent->childrens[i - 1];
    }
    parent->childrens[idx + 1] = brother;
}

/**
    @param current: 表示要添加 key 的节点 (注意: 不一定要添加到当前节点，也有可能是当前节点的子节点)
    @param key: 要添加的 key
*/
template <class T>
void bTree<T>::addNode_(bTreeNode * current, const T & key)
{
    int idx = current->nums - 1;
    if (current->leaf) {    // 叶子节点
        while (idx >= 0 && key < current->keys[idx]) {
            current->keys[idx + 1] = current->keys[idx];
            idx -= 1;
        }
        current->keys[idx + 1] = key;
        current->nums += 1;
    }
    else {
        while (idx >= 0 && key < current->keys[idx]) {
            idx -= 1;
        }
        if (current->childrens[idx + 1]->nums == (degree * 2 - 1)) {
            this->splitNode_(current, idx + 1);
            // 当前节点多了一个 key，需要再次比较
            if (key > current->keys[idx + 1]) {
                idx += 1;
            }
        }
        this->addNode_(current->childrens[idx + 1], key);
    }
}

/**
    @param key: 要添加的 key
*/
template <class T>
void bTree<T>::insertKey(const T & key)
{
    bTreeNode * current = this->tree;

    // 检查根节点是否需要进行分裂
    if (current->nums == (degree * 2 - 1)) {
        bTreeNode * parent = new bTreeNode(false);
        this->tree = parent;
        parent->childrens[0] = current;
        this->splitNode_(parent, 0);
        int idx = 0;
        if (parent->keys[idx] < key) {
            idx += 1;
        }
        this->addNode_(parent->childrens[idx], key);
    }
    else {
        this->addNode_(this->tree, key);
    }
}

template <class T>
std::ostream & operator << (std::ostream & out, const bTree<T> & obj)
{
    using bTreeNode = typename bTree<T>::bTreeNode;

    std::queue<bTreeNode *> queue;    
    int sizeCurrent = 0;
    int sizeNext = 0;
    bTreeNode * current = obj.tree;
    if (current != nullptr) {
        queue.push(current);
        sizeCurrent += 1;
    }
    while (!queue.empty()) {
        for (int i = 0; i < sizeCurrent; i++) {
            current = queue.front();
            queue.pop();
            for (size_t j = 0; j < current->nums; j++) {
                out << current->keys[j] << "  ";
            }
            out << "\t\t";
            if (!current->leaf) {
                for (int j = 0; j <= current->nums; j++) {
                    queue.push(current->childrens[j]);
                    sizeNext += 1;
                }
            }
        }
        out << std::endl;
        sizeCurrent = sizeNext;
        sizeNext = 0;
    }

    return out;
}

/**
    @param parent: 当前节点的父节点
    @param idx: 当前跌点是父节点的第 idx 个(下标)孩子
*/
template <class T>
void bTree<T>::mergeNode_(bTreeNode * parent, const int idx)
{
    bTreeNode * left = parent->childrens[idx];
    bTreeNode * right = parent->childrens[idx + 1];
    
    // 将父节点的 key 拿下来，并开始合并
    left->keys[left->nums] = parent->keys[idx];
    left->nums += 1;
    for (size_t i = 0; i < right->nums; i++) {
        left->keys[left->nums] = right->keys[i];
        left->nums += 1;
    }
    if (!left->leaf) {
        for (size_t i = 0; i < degree; i++) {
            left->childrens[degree + i] = right->childrens[i];
        }
    }
    delete right;

    // 父节点的 keys数组 少了一个 key，要处理  keys数组，也要处理 childrens数组
    for (size_t i = idx; i < parent->nums - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
        // idx 的左右child已经合并
        parent->childrens[i + 1] = parent->childrens[i + 2];
    }
    parent->childrens[parent->nums] = nullptr;
    parent->nums -= 1;

    if (parent->nums == 0) {
        // 默认当前 B树 的 level > 3，否则不如使用 红黑树
        this->tree = left;
        delete parent;
    }
}

/**
    @param parent: 当前节点的父节点
    @param idx: 当前节点是父节点的第 idx 个孩子
    @brief 叶子节点借值，优先向左兄弟借值
*/
template <class T>
void  bTree<T>::leafBorrowKey_(bTreeNode * parent, int idx)
{
    bTreeNode * current = parent->childrens[idx];
    bTreeNode * borther;
    if (idx != 0 && parent->childrens[idx - 1]->nums >= degree) {                // 优先向左借值
        borther = parent->childrens[idx - 1];
        for (int i = current->nums; i > 0; i--) {
            current->keys[i] = current->keys[i - 1];
        }
        current->keys[0] = parent->keys[idx - 1];
        current->nums += 1;
        parent->keys[idx - 1] = borther->keys[borther->nums - 1];
        borther->nums -= 1;
    }
    else if (idx != parent->nums && parent->childrens[idx + 1] >= degree) {      // 实在不行就尝试向右借值
        borther = parent->childrens[idx + 1];
        current->keys[current->nums] = parent->keys[idx];
        parent->keys[idx] = borther->keys[0];
        std::copy(borther->keys + 1, borther->keys + borther->nums, borther->keys);
        borther->nums -= 1;
    }
    else {    // 左右都不满足就合并，优先向左合并
        if (idx != 0) {     // 向左合并
            this->mergeNode_(parent, idx - 1);
        }
        else if (idx != parent->nums) {
            this->mergeNode_(parent, idx);
        }
    }
}

/**
    @param current: 当前节点
    @param idx: 当前节点的第 idx 个 key 需要借值
    @brief 非叶子节点借值，优先向左孩子借
*/
template <class T>
void bTree<T>::nonLeafBorrowKey_(bTreeNode * current, int idx)
{
    bTreeNode * child;
    // 优先向左孩子借值，若是左孩子不满足条件，查看右孩子，若右孩子也不满足，强行向左孩子借值，在让左孩子借值
    if (current->childrens[idx] >= degree) {
        child = current->childrens[idx];
        
        current->keys[idx] = child->keys[child->nums - 1];
        if (!child->leaf) {
            this->nonLeafBorrowKey_(child, child->nums - 1);
        }
        else {
            // 是叶子节点
            child->nums -= 1;
            if (child->nums >= (degree - 1)) {
                return;
            }
            else {
                this->mergeNode_(current, idx);
            }
        }
    } 
    else if (current->childrens[idx + 1] >= degree) {
        child = current->childrens[idx + 1];

        current->keys[idx] = child->keys[0];
        if (!child->leaf) {
            this->nonLeafBorrowKey_(child, 0);
        }
        else {
            // child 是 叶子节点
            std::copy(child->keys + 1, child->keys + child->nums, child->keys);
            child->nums -= 1;
            if (child->nums >= (degree - 1)) {
                return;
            }
            else {
                this->leafBorrowKey_(current, idx + 1);
            }
        }
    }
    else {
        // 强行向左孩子借值 
        child = current->childrens[idx];

        current->keys[idx] = child->keys[child->nums - 1];
        if (child->leaf) {
            child->nums -= 1;
            this->mergeNode_(current, idx - 1);
        }
        else {
            // 若不是叶子节点，就继续向下借值
            this->nonLeafBorrowKey_(child, child->nums - 1);
        }
    }
}

// 使用二分查找 -- 查找当前 keys 中指定的 key，若没有找到，返回一个小于目标值的 key 下标
template <class T>
int bTree<T>::binSearch_(const T * keys, const int nums, const T & key) 
{
    int left = 0;
    int right = nums - 1;
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (keys[middle] < key) {
            left = middle + 1;
        }
        else if (keys[middle] > key) {
            right = middle - 1;
        }
        else {
            return middle;
        }
    }
    return left;
}

template <class T>
typename bTree<T>::bTreeNode * bTree<T>::searchNode_(bTreeNode * current, const T & key) const
{
    if (current == nullptr) {
        return nullptr;
    }

    int idx = binSearch_(current->keys, current->nums, key);
    if (current->keys[idx] == key) {
        return current;
    }
    else {
        if (current->leaf) {
            return nullptr;
        }
        else {
            return searchNode_(current->childrens[idx + 1], key);
        }
    }
}

template <class T>
typename bTree<T>::bTreeNode * bTree<T>::searchKey(const T & key) const
{
    bTreeNode * current = searchNode_(this->tree, key);
    return current;
}
    
/**
    删除 key 时，会导致一下三种情况的一种: 
        1. 合并
        2. 借值
        3. 直接删除
    合并 -- 合并只会发生在叶子节点上，当前节点的 nums < (degree - 1) 同时两个 brother->nums < degree，就会合并 当前节点 和 brother
    借值 -- 1. 若是非叶子节点，向孩子借值
            2. 若是叶子节点，当前节点的 nums < (degree - 1) 同时 brother->nums >= degree 就会产生借值
    直接删除 -- 1. 当前节点是叶子节点，同时当前节点的 nums >= degree 可以直接删除
                2. 若当前节点是叶子节点，且当前节点的 nums < degree，则删除后需要借值
                3. 当前节点是根节点也要直接删除
*/

template <class T>
void bTree<T>::deleteCurrentKey_(bTreeNode * current, const T & key) 
{
    int idx = 0;
    while (idx < current->nums && current->keys[idx] < key) {
        // 找到一个 大于等于 key 的 idx
        idx += 1;
    }
    if (idx < current->nums && key == current->keys[idx]) {     // 在当前节点找到了目标 key
        if (current->leaf) {        // 当前节点是叶子节点
            std::copy(current->keys + idx + 1, current->keys + current->nums, current->keys + idx);
            current->nums -= 1;
            if (current->nums == 0) {       // 当前节点是根节点，直接删除
                delete current;
                // current = nullptr;           !!!
                this->tree = nullptr;
            }
            return;
        }
        else {      // 当前节点不是叶子节点
            if (current->childrens[idx]->nums >= degree) {      // 当前节点删除一个 key 之后，从左孩子的 keys 中借值
                bTreeNode * left = current->childrens[idx];
                current->keys[idx] = left->keys[left->nums - 1];
                this->deleteCurrentKey_(left, left->keys[left->nums - 1]);
            }
            else if (current->childrens[idx + 1]->nums >= degree) {     // 当前节点删除一个 key 之后，从右孩子的 keys 中借值
                bTreeNode * right = current->childrens[idx + 1];
                current->keys[idx] = right->keys[0];
                this->deleteCurrentKey_(right, right->keys[0]);
            }
            else {      // 左右孩子都不能借值，那就合并
                T currentKey = current->keys[idx];
                this->mergeNode_(current, idx);
                this->deleteCurrentKey_(current->childrens[idx], currentKey);
            }
        }
    }
    else {          // 当前节点中没有 目标key
        bTreeNode * child = current->childrens[idx];
        if (child == nullptr) {
            throw illegalError("the target key was not found!");
        }

        if (child->nums == (degree - 1)) {      // 当前节点处于一个可能被合并的状态，若是child 的子节点中有目标值，且需要合并，我们需要找到 child 节点，但是我们没有 parent 指针，只能提前进行预防
            bTreeNode * left = nullptr;
            bTreeNode * right = nullptr;
            if (idx - 1 >= 0) {
                left = current->childrens[idx - 1];     // child 的左兄弟
            }
            if (idx + 1 <= current->nums) {
                right = current->childrens[idx + 1];   // child 的右兄弟
            }

            if ((left && left->nums >= degree) || (right && right->nums >= degree)) {   // 条件满足，表示可以向左右兄弟借值
                int borrowR = 0;
                if (right) {
                    borrowR = 1;
                }
                if (left && right) {
                    borrowR = (right->nums > left->nums) ? 1 : 0;
                }

                if (right && borrowR && right->nums >= degree) {        // 向右兄弟借值
                    child->keys[child->nums] = current->keys[idx];
                    child->childrens[child->nums + 1] = right->childrens[0];
                    child->nums += 1;

                    current->keys[idx] = right->keys[0];
                    for (size_t i = 0; i < right->nums - 1; i++) {
                        right->keys[i] = right->keys[i + 1];
                        right->childrens[i] = right->childrens[i + 1];
                    }
                    right->childrens[right->nums - 1] = right->childrens[right->nums];
                    right->childrens[right->nums] = nullptr;
                    right->nums -= 1;
                }
                else {      // 向左兄弟借值
                    for (int i = child->nums; i > 0; i--) {
                        child->keys[i] = child->keys[i - 1];
                        child->childrens[i - 1] = child->childrens[i];
                    }
                    child->childrens[1] = child->childrens[0];
                    child->childrens[0] = left->childrens[left->nums];
                    child->keys[0] = current->keys[idx - 1];
                    child->nums += 1;

                    current->keys[idx - 1] = left->keys[left->nums - 1];
                    left->childrens[left->nums] = nullptr;
                    left->nums -= 1;
                }
            }
            else {      // 左右兄弟条件都不满足，优先合并左孩子
                if (left && left->nums == (degree - 1)) {
                    this->mergeNode_(current, idx - 1);
                    child = left;
                }
                else if (right && right->nums == (degree - 1)) {
                    this->mergeNode_(current, idx);
                }
            }
        }
        this->deleteCurrentKey_(child, key);
    }
}

template <class T>
void bTree<T>::deleteKey(const T & key)
{
    if (this->tree == nullptr) {
        return;
    }

    bTreeNode * current = this->tree;
    this->deleteCurrentKey_(current, key);
}

