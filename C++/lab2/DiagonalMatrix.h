#ifndef DIAGONALMATRIX
#define DIAGONALMATRIX

#include <iostream>
//#include <stdbool.h>

#include "Sequence.h"

template <class T>
class DiagonalMatrix;

template <class T>
std::ostream &operator<<(std::ostream &ostream, const DiagonalMatrix<T> &diagonalMatrix);
template <class T>
std::istream &operator>>(std::istream &istream, DiagonalMatrix<T> &diagonalMatrix);
template <class T>
const DiagonalMatrix<T> operator+(DiagonalMatrix<T> &x1, DiagonalMatrix<T> &x2);
template <class T>
const DiagonalMatrix<T> operator*(DiagonalMatrix<T> &x, T coefficient);

template <class T>
class DiagonalMatrix
{
    friend std::ostream &operator<< <T>(std::ostream &ostream, const DiagonalMatrix<T> &diagonalMatrix);
    friend std::istream &operator>><T>(std::istream &istream, DiagonalMatrix<T> &diagonalMatrix);
    friend const DiagonalMatrix<T> operator+<T>(DiagonalMatrix<T> &x1, DiagonalMatrix<T> &x2);
    friend const DiagonalMatrix<T> operator*<T>(DiagonalMatrix<T> &x, T coefficient);

public:
    DiagonalMatrix()
    {
        diagonals = NULL;
        m = 0;
        k = 0;
    }

    DiagonalMatrix(Sequence<T> *new_diagonals) : DiagonalMatrix() //не копирует; если не пустой сиквенс, то diagonals = NULL
    {
        if (!new_diagonals->GetLength())
        {
            diagonals = new_diagonals;
        }
    }

    DiagonalMatrix(const DiagonalMatrix<T> &diagonalMatrix)
    {
        diagonals = diagonalMatrix.diagonals->Copy();
        m = diagonalMatrix.m;
        k = diagonalMatrix.k;
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
        int minIndex = 0, maxIndex = m;
        if (index - (k - 1) / 2 > minIndex)
        {
            minIndex = index - (k - 1) / 2;
        }
        if (index + (k - 1) / 2 < maxIndex)
        {
            maxIndex = index + (k - 1) / 2;
        }
        for (int j = minIndex; j <= maxIndex; j++)
        {
            diagonals->Set(CalculateIndex(index, j), diagonals->Get(CalculateIndex(index, j)) * coefficient);
        }
    }

    void ColumnMultiple(int index, T coefficient)
    {
        int minIndex = 0, maxIndex = m;
        if (index - (k - 1) / 2 > minIndex)
        {
            minIndex = index - (k - 1) / 2;
        }
        if (index + (k - 1) / 2 < maxIndex)
        {
            maxIndex = index + (k - 1) / 2;
        }
        for (int i = minIndex; i <= maxIndex; i++)
        {
            diagonals->Set(CalculateIndex(i, index), diagonals->Get(CalculateIndex(i, index)) * coefficient);
        }
    }

    DiagonalMatrix<T> &operator=(const DiagonalMatrix<T> &diagonalMatrix)
    {
        if (diagonals)
        {
            delete diagonals;
        }
        diagonals = diagonalMatrix.diagonals->Copy();
        m = diagonalMatrix.m;
        k = diagonalMatrix.k;
        return *this;
    }

    ~DiagonalMatrix()
    {
        if (diagonals)
        {
            delete diagonals;
        }
    }

private:
    int m, k;
    Sequence<T> *diagonals;
    int CalculateIndex(int i, int j) const
    {
        int length = 0;
        if (i <= j)
        {
            length = (k + 2 * i - 2 * j - 1) * (4 * m + 2 * i - 2 * j - k - 1) / 8;
            return length + i;
        }
        length = ((k + 1) * (4 * m - k + 1) + 4 * (2 * m - i + j) * (i - j - 1)) / 8;
        return length + j;
    }

    /*bool Optimize() {
        bool optimized = 0;
        for(int i = 0; i < m - (k - 1) / 2) {

        }
    }*/
};

template <class T>
const DiagonalMatrix<T> operator+(DiagonalMatrix<T> &x1, DiagonalMatrix<T> &x2) //тот же тип, что и x1
{
    if (x1.k <= x2.k)
    {
        DiagonalMatrix<T> sumMatrix = DiagonalMatrix<T>(x1);
        while (sumMatrix.diagonals->GetLength() != x2.diagonals->GetLength())
        {
            sumMatrix.diagonals->Append(0);
            sumMatrix.diagonals->Prepend(0);
        }
        *sumMatrix.diagonals += *x2.diagonals;
        sumMatrix.k = x2.k;
        return sumMatrix;
    }
    else
    {
        DiagonalMatrix<T> sumMatrix = DiagonalMatrix<T>(x2);
        while (sumMatrix.diagonals->GetLength() != x1.diagonals->GetLength())
        {
            sumMatrix.diagonals->Append(0);
            sumMatrix.diagonals->Prepend(0);
        }
        *sumMatrix.diagonals += *x1.diagonals;
        sumMatrix.k = x1.k;
        return sumMatrix;
    }
}

template <class T>
const DiagonalMatrix<T> operator*(DiagonalMatrix<T> &x, T coefficient)
{
    DiagonalMatrix<T> sumMatrix = DiagonalMatrix<T>(x);
    *sumMatrix.diagonals *= coefficient;
    return sumMatrix;
}

template <class T>
std::ostream &operator<<(std::ostream &ostream, const DiagonalMatrix<T> &diagonalMatrix)
{
    for (int i = 0; i < diagonalMatrix.m; i++)
    {
        for (int j = 0; j < diagonalMatrix.m; j++)
        {
            if ((i - j <= (diagonalMatrix.k - 1) / 2) && (i - j >= -(diagonalMatrix.k - 1) / 2))
            {
                ostream << diagonalMatrix.diagonals->Get(diagonalMatrix.CalculateIndex(i, j)) << "  ";
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
std::istream &operator>>(std::istream &istream, DiagonalMatrix<T> &diagonalMatrix)
{
    int m = 0, k = 0, length = 0;
    std::cout << "Введите количество строк диагональной матрицы:" << std::endl;
    istream >> m;
    diagonalMatrix.m = m;
    std::cout << "Введите количество диагоналей матрицы (положительное нечетное число):" << std::endl;
    while (1) {
        istream >> k;
        if(k % 2) {
            break;
        }
        std::cout << "Значение введено некорректно" << std::endl;
    }
    diagonalMatrix.k = k;
    T value;
    for (int i = (k - 1) / 2; i >= -(k - 1) / 2; i--)
    {
        if (i >= 0)
        {
            length = m - i;
        }
        else
        {
            length = m + i;
        }
        std::cout << "Введите элементы диагонали (нумеруются с правой) номер " << (k + 1) / 2 - i << " в количестве " << length << ":" << std::endl;
        for (int j = 0; j < length; j++)
        {
            istream >> value;
            diagonalMatrix.diagonals->Append(value);
        }
    }
    return istream;
}

#endif