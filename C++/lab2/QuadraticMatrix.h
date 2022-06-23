#ifndef QUADRATICMATRIX
#define QUADRATICMATRIX

#include <iostream>

#include "Sequence.h"

template <class T>
class QuadraticMatrix;

template <class T>
std::ostream &operator<<(std::ostream &ostream, const QuadraticMatrix<T> &quadraticMatrix);
template <class T>
std::istream &operator>>(std::istream &istream, QuadraticMatrix<T> &quadraticMatrix);
template <class T>
const QuadraticMatrix<T> operator+(QuadraticMatrix<T> &x1, QuadraticMatrix<T> &x2);
template <class T>
const QuadraticMatrix<T> operator*(QuadraticMatrix<T> &x, T coefficient);

template <class T>
class QuadraticMatrix
{
    friend std::ostream &operator<< <T>(std::ostream &ostream, const QuadraticMatrix<T> &quadraticMatrix);
    friend std::istream &operator>><T>(std::istream &istream, QuadraticMatrix<T> &quadraticMatrix);
    friend const QuadraticMatrix<T> operator+<T>(QuadraticMatrix<T> &x1, QuadraticMatrix<T> &x2);
    friend const QuadraticMatrix<T> operator*<T>(QuadraticMatrix<T> &x, T coefficient);

public:
    QuadraticMatrix()
    {
        rows = NULL;
        m = 0;
    }

    QuadraticMatrix(Sequence<T> *new_rows) : QuadraticMatrix() //не копирует; если не пустой сиквенс, то rows = NULL
    {
        if (!new_rows->GetLength())
        {
            rows = new_rows;
        }
    }

    QuadraticMatrix(const QuadraticMatrix<T> &quadraticMatrix)
    {
        rows = quadraticMatrix.rows->Copy();
        m = quadraticMatrix.m;
    }

    int GetHeight()
    {
        return m;
    }

    int GetWidth()
    {
        return m;
    }

    void RowPermutate(int firstIndex, int secondIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->Permutate(firstIndex * m + i, secondIndex * m + i);
        }
    }

    void ColumnPermutate(int firstIndex, int secondIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->Permutate(firstIndex + i * m, secondIndex + i * m);
        }
    }

    void RowMultiple(int index, T coefficient)
    {
        for (int i = 0; i < m; i++)
        {
            rows->Set(index * m + i, rows->Get(index * m + i) * coefficient);
        }
    }

    void ColumnMultiple(int index, T coefficient)
    {
        for (int i = 0; i < m; i++)
        {
            rows->Set(index + i * m, rows->Get(index + i * m) * coefficient);
        }
    }

    void RowLinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->LinearTransformation(fromIndex * m + i, coefficient, toIndex * m + i);
        }
    }

    void ColumnLinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->LinearTransformation(fromIndex + i * m, coefficient, toIndex + i * m);
        }
    }

    QuadraticMatrix<T> &operator=(const QuadraticMatrix<T> &quadraticMatrix)
    {
        if (rows)
        {
            delete rows;
        }
        rows = quadraticMatrix.rows->Copy();
        m = quadraticMatrix.m;
        return *this;
    }

    ~QuadraticMatrix()
    {
        if (rows)
        {
            delete rows;
        }
    }

private:
    int m;
    Sequence<T> *rows;
};

template <class T>
const QuadraticMatrix<T> operator+(QuadraticMatrix<T> &x1, QuadraticMatrix<T> &x2) //тот же тип, что и x1
{
    QuadraticMatrix<T> sumMatrix = QuadraticMatrix<T>(x1);
    *sumMatrix.rows += *x2.rows;
    return sumMatrix;
}

template <class T>
const QuadraticMatrix<T> operator*(QuadraticMatrix<T> &x, T coefficient)
{
    QuadraticMatrix<T> sumMatrix = QuadraticMatrix<T>(x);
    *sumMatrix.rows *= coefficient;
    return sumMatrix;
}

template <class T>
std::ostream &operator<<(std::ostream &ostream, const QuadraticMatrix<T> &quadraticMatrix)
{
    for (int i = 0; i < quadraticMatrix.m; i++)
    {
        for (int j = 0; j < quadraticMatrix.m; j++)
        {
            ostream << quadraticMatrix.rows->Get(i * quadraticMatrix.m + j) << "  ";
        }
        ostream << std::endl;
    }
    return ostream;
}

template <class T>
std::istream &operator>>(std::istream &istream, QuadraticMatrix<T> &quadraticMatrix)
{
    int m = 0;
    std::cout << "Введите количество строк квадратной матрицы:" << std::endl;
    istream >> m;
    quadraticMatrix.m = m;
    T value;
    for (int i = 0; i < m; i++)
    {
        std::cout << "Введите элементы строки номер " << i + 1 << " в количестве " << m << ":" << std::endl;
        for (int j = 0; j < m; j++)
        {
            istream >> value;
            quadraticMatrix.rows->Append(value);
        }
    }
    return istream;
}

#endif