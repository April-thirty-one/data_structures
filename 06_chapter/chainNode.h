#ifndef DATA_STRUCTURES_CHAINNODE_H__
#define DATA_STRUCTURES_CHAINNODE_H__

template <typename T>
struct chainNode 
{
    T element;
    chainNode<T> * next;

    chainNode();
    chainNode(const T & element);
    chainNode(const T & element, chainNode<T> * next);

    T & getValue() ;
};

template <typename T>
chainNode<T>::chainNode() : element(0), next(nullptr) {}

template <typename T>
chainNode<T>::chainNode(const T & element) : element(element), next(nullptr) {}

template <typename T>
chainNode<T>::chainNode(const T & element, chainNode<T> * next) : element(element), next(next) {}

template <class T>
T & chainNode<T>::getValue() 
{
    return this->element;
}

#endif // !DATA_STRUCTURES_CHAINNODE_H__
