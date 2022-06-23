#ifndef TRIANGULARMATRIX
#define TRIANGULARMATRIX

#include <iostream>

#include "Sequence.h"

template <class T>
class TriangularMatrix;

template <class T>
std::ostream &operator<<(std::ostream &ostream, const TriangularMatrix<T> &triangularMatrix);
template <class T>
std::istream &operator>>(std::istream &istream, TriangularMatrix<T> &triangularMatrix);
template <class T>
const TriangularMatrix<T> operator+(TriangularMatrix<T> &x1, TriangularMatrix<T> &x2);
template <class T>
const TriangularMatrix<T> operator*(TriangularMatrix<T> &x, T coefficient);

template <class T>
class TriangularMatrix
{
    friend std::ostream &operator<< <T>(std::ostream &ostream, const TriangularMatrix<T> &triangularMatrix);
    friend std::istream &operator>><T>(std::istream &istream, TriangularMatrix<T> &triangularMatrix);
    friend const TriangularMatrix<T> operator+<T>(TriangularMatrix<T> &x1, TriangularMatrix<T> &x2);
    friend const TriangularMatrix<T> operator*<T>(TriangularMatrix<T> &x, T coefficient);

public:
    TriangularMatrix()
    {
        rows = NULL;
        m = 0;
    }

    TriangularMatrix(Sequence<T> *new_rows) : TriangularMatrix() //не копирует; если не пустой сиквенс, то rows = NULL
    {
        if (!new_rows->GetLength())
        {
            rows = new_rows;
        }
    }

    TriangularMatrix(const TriangularMatrix<T> &triangularMatrix)
    {
        rows = triangularMatrix.rows->Copy();
        m = triangularMatrix.m;
    }

    int GetHeight()
    {
        return m;
    }

    int GetWidth()
    {
        return m;
    }

    void RowMultiple(int index, T coefficient)
    {
        int firstIndex = CalculateIndex(index, index);
        for (int i = 0; i < m - index; i++)
        {
            rows->Set(firstIndex + i, rows->Get(firstIndex + i) * coefficient);
        }
    }

    void ColumnMultiple(int index, T coefficient)
    {
        for (int i = 0; i <= index; i++)
        {
            rows->Set(CalculateIndex(i, index), rows->Get(CalculateIndex(i, index)) * coefficient);
        }
    }

    void RowLinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        if (fromIndex >= toIndex)
        {
            int fromStartIndex = CalculateIndex(fromIndex, fromIndex);
            int toStartIndex = CalculateIndex(toIndex, fromIndex);
            for (int i = 0; i < m - fromIndex; i++)
            {
                rows->LinearTransformation(fromStartIndex + i, coefficient, toStartIndex + i);
            }
        }
    }

    void ColumnLinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        if (fromIndex <= toIndex)
        {
            for (int i = 0; i <= fromIndex; i++)
            {
                rows->LinearTransformation(CalculateIndex(i, fromIndex), coefficient, CalculateIndex(i, toIndex));
            }
        }
    }

    TriangularMatrix<T> &operator=(const TriangularMatrix<T> &triangularMatrix)
    {
        if (rows)
        {
            delete rows;
        }
        rows = triangularMatrix.rows->Copy();
        m = triangularMatrix.m;
        return *this;
    }

    ~TriangularMatrix()
    {
        if (rows)
        {
            delete rows;
        }
    }

private:
    int m;
    Sequence<T> *rows;
    int CalculateIndex(int i, int j) const
    {
        return m * i + j - i * (i + 1) / 2;
    }
};

template <class T>
const TriangularMatrix<T> operator+(TriangularMatrix<T> &x1, TriangularMatrix<T> &x2) //тот же тип, что и x1
{
    TriangularMatrix<T> sumMatrix = TriangularMatrix<T>(x1);
    *sumMatrix.rows += *x2.rows;
    return sumMatrix;
}

template <class T>
const TriangularMatrix<T> operator*(TriangularMatrix<T> &x, T coefficient)
{
    TriangularMatrix<T> sumMatrix = TriangularMatrix<T>(x);
    *sumMatrix.rows *= coefficient;
    return sumMatrix;
}

template <class T>
std::ostream &operator<<(std::ostream &ostream, const TriangularMatrix<T> &triangularMatrix)
{
    for (int i = 0; i < triangularMatrix.m; i++)
    {
        for (int j = 0; j < triangularMatrix.m; j++)
        {
            if (i <= j)
            {
                ostream << triangularMatrix.rows->Get(triangularMatrix.CalculateIndex(i, j)) << "  ";
            }
            else
            {
                ostream << "0  ";
            }
        }
        ostream << std::endl;
    }
    return ostream;
}

template <class T>
std::istream &operator>>(std::istream &istream, TriangularMatrix<T> &triangularMatrix)
{
    int m = 0;
    std::cout << "Введите количество строк треугольной матрицы:" << std::endl;
    istream >> m;
    triangularMatrix.m = m;
    T value;
    for (int i = 0; i < m; i++)
    {
        std::cout << "Введите элементы строки номер " << i + 1 << " в количестве " << m - i << ":" << std::endl;
        for (int j = i; j < m; j++)
        {
            istream >> value;
            triangularMatrix.rows->Append(value);
        }
    }
    return istream;
}

#endif