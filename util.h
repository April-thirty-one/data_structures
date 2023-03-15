#include <algorithm>
#include <iostream>
#include <string>

namespace cc {

template <typename T>
void print(T item) {
    std::cout << item << "  ";
}

class illegalParameterValue {
private:
    std::string message;
    std::string position;

public:
    illegalParameterValue() : message("Illegal parameter value.") {}
    illegalParameterValue(const char * position, const char * theMessage)
    {
        this->message = theMessage;
        this->position = position;
    }

    void outputMessage() {
        std::cout << "-- position = " << position << ", " << message << std::endl;
    }
};

template <typename T>
// void changeLength1D(T * a, int oldLength, int newLength)    // error
void changeLength1D(T *& a, int oldLength, int newLength)
{
    if (newLength < 0) {
        illegalParameterValue("new length must be >= 0.", "changeLength1D");
    }
    T * temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a+number, temp);
    delete [] a;
    a = temp;
}

template <typename T>
void changeLength2D(T **& a, int oldXLength, int oldYLength, int newXLength, int newYLength) {
    if (newXLength < 0 || newYLength < 0) {
        illegalParameterValue("new length must be >= 0.", "changeLength2D");
    }

    T ** temp = new T*[newYLength];
    int numbery = std::min(oldYLength, newYLength);
    int numberx = std::min(oldXLength, newXLength);
    for (int i = 0; i < newYLength; i++) {
        temp[i] = new T[newXLength];
        if (i < oldYLength) {
            std::copy(a[i], a[i] + numberx, temp[i]);
        }
    }
    for (int i = 0; i < oldYLength; i++) {
        delete [] a[i];
    }
    a = temp;
}


// 將 字符串 映射爲 整數
long threeToLong(std::string str);

// 將 字符串 映射爲 整數
int stringToInt(std::string str);

} // end namespace cc
