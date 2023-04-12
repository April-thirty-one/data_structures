#ifndef DATA_STRUCTRUES_7_CHAPTER_MATRIX_H__
#define DATA_STRUCTRUES_7_CHAPTER_MATRIX_H__

#include "../util.h"

template <class T>
class matrix;

template <class T>
std::ostream & operator << (std::ostream & out, const matrix<T> & obj);

template <class T>
class matrix {
public:
    matrix(int rows = 0, int cols = 0);
    matrix(const matrix<T> & other);
    ~matrix();

    int getRows() const;
    int getCols() const;

    T & operator () (int i, int j) const;
    void tranpose();

    matrix<T> & operator = (const matrix<T> & other);
    matrix<T> operator + () const;
    matrix<T> operator + (const matrix<T> & other) const;
    matrix<T> operator - () const;
    matrix<T> operator - (const matrix<T> & other) const;
    matrix<T> operator * (const matrix<T> & other) const;
    matrix<T> & operator += (const T & value);
    matrix<T> & operator -= (const T & value);
    matrix<T> & operator *= (const T & value);
    matrix<T> & operator /= (const T & value);

    friend std::ostream & operator << <>(std::ostream & out, const matrix<T> & obj);

private:
    int rows;
    int columns;
    T * element;
};

template <class T>
matrix<T>::matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0) {
        throw cc::illegalParameterValue("in matrix.h constructor", "row an cols must be > 0");
    }
    this->rows = rows;
    this->columns = cols;
    this->element = new T [this->rows * this->columns];

    std::cout << "-- constructor success." << std::endl;
}

template <class T>
matrix<T>::matrix(const matrix<T> & other)
{
    this->rows = other.rows;
    this->columns = other.columns;
    this->element = new T[this->rows * this->columns];
    std::copy(other.element, other.element + other.rows * other.columns, this->element);

    std::cout << "-- copy constructor success." << std::endl;
}

template <class T>
matrix<T>::~matrix()
{
    this->rows = 0;
    this->columns = 0;
    delete [] this->element;

    std::cout << "-- destructor success." << std::endl;
}

template <class T>
int matrix<T>::getRows() const
{
    return this->rows;
}

template <class T>
int matrix<T>::getCols() const
{
    return this->columns;
}

template <class T>
T & matrix<T>::operator () (int i, int j) const
{
    return *(this->element + (i * this->columns + j));
}

template <class T>
matrix<T> & matrix<T>::operator = (const matrix<T> & other)
{
    if (this == &other) {
        return *this;
    }

    if (this->element != nullptr) {
        delete [] this->element;
    }

    this->rows = other.rows;
    this->columns = other.columns;
    this->element = new T[this->rows * this->columns];
    std::copy(other.element, other.element + other.rows * other.columns, this->element);
}

template <class T>
matrix<T> matrix<T>::operator + (const matrix<T> & other) const
{
    if (this->rows != other.rows || this->columns != other.columns) {
        throw cc::illegalParameterValue("in matrix.h operator+", "the row and column of bath matrix be the same");
    }

    matrix<T> temp(this->rows, this->columns);
    for (size_t i = 0; i < this->rows * this->columns; i++) {
        temp.element[i] = this->element[i] + other.element[i];
    }
    return temp;
}

template <class T>
matrix<T> matrix<T>::operator - (const matrix<T> & other) const
{
    if (this->rows != other.rows || this->columns != other.columns) {
        throw cc::illegalParameterValue("in matrix.h operator+", "the row and column of bath matrix be the same");
    }

    matrix<T> temp(this->rows, this->columns);
    for (size_t i = 0; i < this->rows * this->columns; i++) {
        temp.element[i] = this->element[i] - other.element[i];
    }
    return temp;

}

template <class T>
matrix<T> matrix<T>::operator * (const matrix<T> & other) const
{
    if (this->columns != other.rows) {
        throw cc::illegalParameterValue("in matrix.h operator*", "");
    }

    matrix<T> w(this->rows, other.columns);
    // 定義矩陣 *this， m 和 w 的遊標初始化爲(0, 0)元素定位
    int ct = 0;
    int cm = 0;
    int cw = 0;
    // 對所有的 i 和 j 計算 w(i, j)
    for (size_t i = 0; i < this->rows; i++) {
        // 計算結果矩陣的第 i 行
        for (size_t j = 0; j < other.columns; j++) {
            // 計算 w(i, j) 的第一項
            T sum = this->element[ct] * other.element[cm];

            // 累加其餘所有項
            for (size_t k = 1; k < this->columns; k++) {
                ct ++;
                cm += other.columns;
                sum += this->element[ct] * other.element[cm];
            }
            w.element[cw++] = sum;

            // 從行的起點和下一列從新開始
            ct -= this->columns - 1;
            cm = j + 1;
        }

        // 從下一行和第一列重新開始
        ct += this->columns;
        cm = 0;
    }
    return w;
}

template <class T>
matrix<T> & matrix<T>::operator += (const T & value)
{
    for (size_t i = 0; i < this->rows * this->columns; i++) {
        this->element[i] = this->element[i] + value;
    }
    return *this;
}

template <class T>
matrix<T> & matrix<T>::operator -= (const T & value)
{
    for (size_t i = 0; i < this->rows * this->columns; i++) {
        this->element[i] = this->element[i] - value;
    }
    return *this;
}

template <class T>
matrix<T> & matrix<T>::operator *= (const T & value)
{
    for (size_t i = 0; i < this->rows * this->columns; i++) {
        this->element[i] = this->element[i] * value;
    }
    return *this;
}

template <class T>
matrix<T> & matrix<T>::operator /= (const T & value)
{
    for (size_t i = 0; i < this->rows * this->columns; i++) {
        this->element[i] = this->element[i] / value;
    }
    return *this;
}

template <class T>
std::ostream & operator << (std::ostream & out, const matrix<T> & obj)
{
    for (size_t i = 0; i < obj.rows; i++) {
        for (size_t j = 0; j < obj.columns; j++) {
            out << obj(i, j) << "  ";
        }
        out << std::endl;
    }
    return out;
}

template <class T>
void matrix<T>::tranpose()
{
    
}

#endif // !DATA_STRUCTRUES_7_CHAPTER_MATRIX_H__
