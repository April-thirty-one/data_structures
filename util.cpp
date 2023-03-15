#include "./util.h"

// 將 字符串 映射爲 整數
long threeToLong(std::string str)
{
    // 最左側的字符
    long answer = str.at(0);
    
    // 做移8位，加入下一個字符
    answer = (answer << 8) + str.at(1);

    return (answer << 8) + str.at(1);
}

// 將 字符串 映射爲 整數
int stringToInt(std::string str)
{
    // 把 str 轉換一個非負整數
    int length = (int)str.length();
    int result = 0;
    if (length % 2 == 1) {
        result = str.at(length - 1);
        length -= 1;
    }

    // 長度爲偶數
    for (int i = 0; i < length; i += 2) {
        result += str.at(i);
        result += ((int)str.at(i + 1)) << 8;
    }

    return (result < 0) ? -result : result;
}

