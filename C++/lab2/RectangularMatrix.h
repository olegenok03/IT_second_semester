#ifndef RECTANGULARMATRIX
#define RECTANGULARMATRIX

#include <iostream>

#include "Sequence.h"

template <class T>
class RectangularMatrix;

template <class T>
std::ostream &operator<<(std::ostream &ostream, const RectangularMatrix<T> &rectangularMatrix);
template <class T>
std::istream &operator>>(std::istream &istream, RectangularMatrix<T> &rectangularMatrix);
template <class T>
const RectangularMatrix<T> operator+(RectangularMatrix<T> &x1, RectangularMatrix<T> &x2);
template <class T>
const RectangularMatrix<T> operator*(RectangularMatrix<T> &x, T coefficient);

template <class T>
class RectangularMatrix
{
    friend std::ostream &operator<< <T>(std::ostream &ostream, const RectangularMatrix<T> &rectangularMatrix);
    friend std::istream &operator>><T>(std::istream &istream, RectangularMatrix<T> &rectangularMatrix);
    friend const RectangularMatrix<T> operator+<T>(RectangularMatrix<T> &x1, RectangularMatrix<T> &x2);
    friend const RectangularMatrix<T> operator*<T>(RectangularMatrix<T> &x, T coefficient);

public:
    RectangularMatrix()
    {
        rows = NULL;
        m = 0;
        n = 0;
    }

    RectangularMatrix(Sequence<T> *new_rows) : RectangularMatrix() //не копирует; если не пустой сиквенс, то rows = NULL
    {
        if (!new_rows->GetLength())
        {
            rows = new_rows;
        }
    }

    RectangularMatrix(const RectangularMatrix<T> &rectangularMatrix)
    {
        rows = rectangularMatrix.rows->Copy();
        m = rectangularMatrix.m;
        n = rectangularMatrix.n;
    }

    int GetHeight()
    {
        return m;
    }

    int GetWidth()
    {
        return n;
    }

    void RowPermutate(int firstIndex, int secondIndex)
    {
        for (int i = 0; i < n; i++)
        {
            rows->Permutate(firstIndex * n + i, secondIndex * n + i);
        }
    }

    void ColumnPermutate(int firstIndex, int secondIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->Permutate(firstIndex + i * n, secondIndex + i * n);
        }
    }

    void RowMultiple(int index, T coefficient)
    {
        for (int i = 0; i < n; i++)
        {
            rows->Set(index * n + i, rows->Get(index * n + i) * coefficient);
        }
    }

    void ColumnMultiple(int index, T coefficient)
    {
        for (int i = 0; i < m; i++)
        {
            rows->Set(index + i * n, rows->Get(index + i * n) * coefficient);
        }
    }

    void RowLinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        for (int i = 0; i < n; i++)
        {
            rows->LinearTransformation(fromIndex * n + i, coefficient, toIndex * n + i);
        }
    }

    void ColumnLinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->LinearTransformation(fromIndex + i * n, coefficient, toIndex + i * n);
        }
    }

    RectangularMatrix<T> &operator=(const RectangularMatrix<T> &rectangularMatrix)
    {
        if (rows)
        {
            delete rows;
        }
        rows = rectangularMatrix.rows->Copy();
        m = rectangularMatrix.m;
        n = rectangularMatrix.n;
        return *this;
    }

    ~RectangularMatrix()
    {
        if (rows)
        {
            delete rows;
        }
    }

private:
    int m, n;
    Sequence<T> *rows;
};

template <class T>
const RectangularMatrix<T> operator+(RectangularMatrix<T> &x1, RectangularMatrix<T> &x2) //тот же тип, что и x1
{
    RectangularMatrix<T> sumMatrix = RectangularMatrix<T>(x1);
    *sumMatrix.rows += *x2.rows;
    return sumMatrix;
}

template <class T>
const RectangularMatrix<T> operator*(RectangularMatrix<T> &x, T coefficient)
{
    RectangularMatrix<T> sumMatrix = RectangularMatrix<T>(x);
    *sumMatrix.rows *= coefficient;
    return sumMatrix;
}

template <class T>
std::ostream &operator<<(std::ostream &ostream, const RectangularMatrix<T> &rectangularMatrix)
{
    for (int i = 0; i < rectangularMatrix.m; i++)
    {
        for (int j = 0; j < rectangularMatrix.n; j++)
        {
            ostream << rectangularMatrix.rows->Get(i * rectangularMatrix.n + j) << "  ";
        }
        ostream << std::endl;
    }
    return ostream;
}

template <class T>
std::istream &operator>>(std::istream &istream, RectangularMatrix<T> &rectangularMatrix)
{
    int m = 0, n = 0;
    std::cout << "Введите количество строк матрицы:" << std::endl;
    istream >> m;
    std::cout << "Введите количество столбцов матрицы:" << std::endl;
    istream >> n;
    rectangularMatrix.m = m;
    rectangularMatrix.n = n;
    T value;
    for (int i = 0; i < m; i++)
    {
        std::cout << "Введите элементы строки номер " << i + 1 << " в количестве " << n << ":" << std::endl;
        for (int j = 0; j < n; j++)
        {
            istream >> value;
            rectangularMatrix.rows->Append(value);
        }
    }
    return istream;
}

#endif