#ifndef SEQUENCE
#define SEQUENCE

#include <iostream>

template <class T>
class Sequence
{
public:
    virtual int GetLength() const = 0;

    virtual int GetAllocatedSize() const = 0;

    virtual T GetFirst() const = 0;

    virtual T GetLast() const = 0;

    virtual T Get(int index) const = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) const = 0;

    virtual Sequence<T> *Copy() const = 0;

    virtual void Append(T value) = 0;

    virtual void Prepend(T value) = 0;

    virtual void InsertAt(int index, T value) = 0;

    virtual void RemoveLast() = 0;

    virtual void RemoveFirst() = 0;

    virtual void Set(int index, T value) = 0;

    void Permutate(int firstIndex, int secondIndex)
    {
        if (firstIndex != secondIndex)
        {
            T bubble = Get(firstIndex);
            Set(firstIndex, Get(secondIndex));
            Set(secondIndex, bubble);
        }
    }

    virtual void LinearTransformation(int fromIndex, T coefficient, int toIndex) = 0;

    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;

    virtual Sequence<T> &operator=(const Sequence<T> &x) = 0;

    Sequence<T> &operator-()
    {
        Sequence<T> *res = Copy();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, -Get(i));
        }
        return *res;
    }

    Sequence<T> &operator+(Sequence<T> &x)
    {
        Sequence<T> *res = Copy();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, Get(i) + x.Get(i));
        }
        return *res;
    }

    Sequence<T> &operator-(Sequence<T> &x)
    {
        Sequence<T> *res = Copy();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, Get(i) - x.Get(i));
        }
        return *res;
    }

    Sequence<T> &operator*(T coefficient)
    {
        Sequence<T> *res = Copy();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, Get(i) * coefficient);
        }
        return *res;
    }

    Sequence<T> &operator/(T coefficient)
    {
        Sequence<T> *res = Copy();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, Get(i) / coefficient);
        }
        return *res;
    }

    Sequence<T> &operator+=(Sequence<T> &x)
    {
        for (int i = 0; i < GetLength(); i++)
        {
            Set(i, Get(i) + x.Get(i));
        }
        return *this;
    }

    Sequence<T> &operator-=(Sequence<T> &x)
    {
        for (int i = 0; i < GetLength(); i++)
        {
            Set(i, Get(i) + x.Get(i));
        }
        return *this;
    }

    Sequence<T> &operator*=(T coefficient)
    {
        for (int i = 0; i < GetLength(); i++)
        {
            Set(i, Get(i) * coefficient);
        }
        return *this;
    }

    Sequence<T> &operator/=(T coefficient)
    {
        for (int i = 0; i < GetLength(); i++)
        {
            Set(i, Get(i) / coefficient);
        }
        return *this;
    }

    virtual ~Sequence() = 0;
};

template <class T>
Sequence<T>::~Sequence() {}

template <class T>
std::ostream &operator<<(std::ostream &ostream, const Sequence<T> &sequence)
{
    for (int i = 0; i < sequence.GetLength(); i++)
    {
        ostream << sequence.Get(i) << " ";
    }
    return ostream;
}

template <class T>
std::istream &operator>>(std::istream &istream, Sequence<T> &sequence)
{
    for (int i = 0; i < sequence.GetLength(); i++)
    {
        T value = sequence.Get(i);
        istream >> value;
        sequence.Set(i, value);
    }
    return istream;
}

#endif