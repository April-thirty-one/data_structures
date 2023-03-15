#ifndef DATA_STRUCTURES_9_CHAPTER_QUEUE_QUEUE_H__
#define DATA_STRUCTURES_9_CHAPTER_QUEUE_QUEUE_H__

template <class T>
class queue {
public:
    virtual ~queue() {};
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T & getFront() = 0;
    virtual T & getBlack() = 0;
    virtual void pop() = 0;
    virtual void push(const T & value) = 0;
};



#endif // !DATA_STRUCTURES_9_CHAPTER_QUEUE_QUEUE_H__
