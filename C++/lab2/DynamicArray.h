#ifndef DYNAMICARRAY
#define DYNAMICARRAY

#include <iostream>
#include <cstring>

template <class T>
class ArraySequence;

template <class T>
class DynamicArray
{
    friend class ArraySequence<T>;

public:
    DynamicArray()
    {
        items = NULL;
        this->count = 0;
    }

    DynamicArray(int count)
    {
        if (!count)
        {
            items = NULL;
            this->count = 0;
        }
        else
        {
            items = new T[count];
            this->count = count;
        }
    }

    DynamicArray(T *items, int count) : DynamicArray(count)
    {
        if (count)
        {
            memcpy(this->items, items, count * sizeof(T));
        }
    }

    DynamicArray(T value, int count) : DynamicArray(count)
    {
        for (int i = 0; i < count; i++)
        {
            items[i] = value;
        }
    }

    DynamicArray(const DynamicArray<T> &dynamicArray) : DynamicArray(dynamicArray.items, dynamicArray.count) {}

    int GetSize()
    {
        return count;
    }

    T Get(int index)
    {
        return items[index];
    }

    void Set(int index, T value)
    {
        items[index] = value;
    }

    void Resize(int newSize)
    {
        if (newSize != count)
        {
            T *newItems = new T[newSize];
            for (int i = 0; (i < newSize) && (i < count); i++)
            {
                newItems[i] = items[i];
            }
            delete[] items;
            items = newItems;
        }
    }

    void InsertAt(int index, T value)
    { //считаем, что память выделили извне
        for (int i = count - 1; i >= index; i--)
        {
            items[i + 1] = items[i];
        }
        items[index] = value;
        count++;
    }

    void RemoveLast()
    {
        Resize(--count);
    }

    void RemoveFirst()
    {
        for (int i = 0; i < count - 1; i++)
        {
            items[i] = items[i + 1];
        }
        Resize(--count);
    }

    void LinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        items[toIndex] += items[fromIndex] * coefficient;
    }

    ~DynamicArray()
    {
        if (items)
        {
            delete[] items;
        }
    }

private:
    T *items;
    int count;
};

#endif