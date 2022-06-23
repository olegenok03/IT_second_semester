#ifndef VECTORMATRIX
#define VECTORMATRIX

#include <iostream>

#include "Sequence.h"

template <class T>
class Vector;

template <class T>
std::ostream &operator<<(std::ostream &ostream, const Vector<T> &vector);
template <class T>
std::istream &operator>>(std::istream &istream, Vector<T> &vector);
template <class T>
const Vector<T> operator+(Vector<T> &x1, Vector<T> &x2);
template <class T>
const Vector<T> operator*(Vector<T> &x, T coefficient);
template <class T>
const T operator*(Vector<T> &x1, Vector<T> &x2);

template <class T>
class Vector
{
    friend std::ostream &operator<< <T>(std::ostream &ostream, const Vector<T> &vector);
    friend std::istream &operator>><T>(std::istream &istream, Vector<T> &vector);
    friend const Vector<T> operator+<T>(Vector<T> &x1, Vector<T> &x2);
    friend const Vector<T> operator*<T>(Vector<T> &x, T coefficient);
    friend const T operator*<T>(Vector<T> &x1, Vector<T> &x2);

public:
    Vector()
    {
        coordinates = NULL;
        n = 0;
    }

    Vector(Sequence<T> *new_coordinates) : Vector() //не копирует; если не пустой сиквенс, то coordinates = NULL
    {
        if (!new_coordinates->GetLength())
        {
            coordinates = new_coordinates;
        }
    }

    Vector(const Vector<T> &vector)
    {
        coordinates = vector.coordinates->Copy();
        n = vector.n;
    }

    int GetDimension()
    {
        return n;
    }

    Vector<T> &operator=(const Vector<T> &vector)
    {
        if (coordinates)
        {
            delete coordinates;
        }
        coordinates = vector.coordinates->Copy();
        n = vector.n;
        return *this;
    }

    ~Vector()
    {
        if (coordinates)
        {
            delete coordinates;
        }
    }

private:
    int n;
    Sequence<T> *coordinates;
};

template <class T>
const Vector<T> operator+(Vector<T> &x1, Vector<T> &x2) //тот же тип, что и x1
{
    Vector<T> sumMatrix = Vector<T>(x1);
    *sumMatrix.coordinates += *x2.coordinates;
    return sumMatrix;
}

template <class T>
const Vector<T> operator*(Vector<T> &x, T coefficient)
{
    Vector<T> resMatrix = Vector<T>(x);
    *resMatrix.coordinates *= coefficient;
    return resMatrix;
}

template <class T>
const T operator*(Vector<T> &x1, Vector<T> &x2)
{
    T res = x1.coordinates->GetFirst() * x2.coordinates->GetFirst();
    for (int i = 1; i < x1.GetDimension(); i++)
    {
        res += x1.coordinates->Get(i) * x2.coordinates->Get(i);
    }
    return res;
}

template <class T>
std::ostream &operator<<(std::ostream &ostream, const Vector<T> &vector)
{
    ostream << "(";
    for (int i = 0; i < vector.n; i++)
    {
        ostream << vector.coordinates->Get(i) << ", ";
    }
    ostream << ")";
    return ostream;
}

template <class T>
std::istream &operator>>(std::istream &istream, Vector<T> &vector)
{
    int n = 0;
    std::cout << "Введите размерность пространства:" << std::endl;
    istream >> n;
    vector.n = n;
    T value;
    std::cout << "Введите черед пробел координаты вектора в количестве " << n << ":" << std::endl;
    for (int i = 0; i < n; i++)
    {
        istream >> value;
        vector.coordinates->Append(value);
    }
    return istream;
}

#endif