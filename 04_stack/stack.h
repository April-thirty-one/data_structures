#ifndef DATA_STRUCTURES_8_CHAPTER_STACK_STACK_H__
#define DATA_STRUCTURES_8_CHAPTER_STACK_STACK_H__

template <class T>
class stack {
public:
    virtual ~stack() {}
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T & getTop() = 0;
    virtual void pop() = 0;
    virtual void push(const T & value) = 0;
};


#endif // !DATA_STRUCTURES_8_CHAPTER_STACK_STACK_H__
