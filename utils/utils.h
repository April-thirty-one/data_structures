#include <algorithm>
#include <iostream>
#include <ctime>

class illegalError {
public:
    illegalError() : message("") {}
    illegalError(const char * theMessage) : message(theMessage) {}
    void outputMessage() { std::cout << "--error " << this->message << std::endl; }

private:
    std::string message;
};

// 对数据的 length 进行扩容
template <class T>
T * arrayExpansion(T * array, int currentSize)
{
    if (currentSize <= 0) {
        throw illegalError("The size of the pilot array must be greater than 0.");
    }

    T * temp = new T[currentSize * 2];
    std::copy(array, array + currentSize, temp);
    delete [] array;
    return temp;
}

/**
    二分查找法
    若是找到target，返回对应的索引
    若是没有找到，返回比target小且最节点的元素索引
*/
template <class T>
int binarySearch(T * arr, int size, const T & target) 
{
    int left = 0;
    int right = size - 1;
    int middle;
    while (left <= right) {
        middle = left + (right - left) / 2;
        if (arr[middle] < target) {
            left = middle + 1;
        }
        else if (arr[middle] > target) {
            right = middle - 1;
        }
        else {
            return middle;
        }
    }
    return right;
}