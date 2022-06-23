#ifndef ARRAYSEQUENCE
#define ARRAYSEQUENCE

#include <iostream>
#include <cstring>

#include "DynamicArray.h"
#include "Sequence.h"

template <class T>
class ArraySequence : public Sequence<T>
{
public:
    ArraySequence()
    {
        buffer = new DynamicArray<T>();
        allocated_size = 0;
    }

    ArraySequence(T *items, int count)
    {
        buffer = new DynamicArray<T>(items, count);
        allocated_size = count;
    }

    ArraySequence(T value, int count)
    {
        buffer = new DynamicArray<T>(value, count);
        allocated_size = count;
    }

    ArraySequence(const DynamicArray<T> &dynamicArray)
    {
        buffer = new DynamicArray<T>(dynamicArray);
        allocated_size = dynamicArray.count;
    }

    ArraySequence(const ArraySequence<T> &arraySequence)
    {
        buffer = new DynamicArray<T>(arraySequence.GetAllocatedSize());
        allocated_size = arraySequence.GetAllocatedSize();
        for (int i = 0; i < arraySequence.GetLength(); i++)
        {
            Set(i, arraySequence.Get(i));
        }
    }

    virtual int GetLength() const override
    {
        return buffer->count;
    }

    virtual int GetAllocatedSize() const override
    {
        return allocated_size;
    }

    virtual T GetFirst() const override
    {
        return buffer->Get(0);
    }

    virtual T GetLast() const override
    {
        return buffer->Get(buffer->count - 1);
    }

    virtual T Get(int index) const override
    {
        return buffer->Get(index);
    }

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) const override
    {
        return new ArraySequence<T>(DynamicArray<T>(buffer->items + startIndex, endIndex - startIndex));
    }

    virtual Sequence<T> *Copy() const override
    {
        return new ArraySequence<T>(*this);
    }

    virtual void Append(T value) override
    {
        if (!allocated_size)
        {
            Resize(1);
        }
        else if (buffer->count == allocated_size)
        {
            Resize(buffer->count * 2);
        }
        buffer->InsertAt(buffer->count, value);
    }

    virtual void Prepend(T value) override
    {
        if (!allocated_size)
        {
            Resize(1);
        }
        else if (buffer->count == allocated_size)
        {
            Resize(buffer->count * 2);
        }
        buffer->InsertAt(0, value);
    }

    virtual void InsertAt(int index, T value) override
    {
        if (!allocated_size)
        {
            Resize(1);
        }
        else if (buffer->count == allocated_size)
        {
            Resize(buffer->count * 2);
        }
        buffer->InsertAt(index, value);
    }

    virtual void RemoveLast()
    {
        buffer->RemoveLast();
        allocated_size = buffer->count;
    }

    virtual void RemoveFirst()
    {
        buffer->RemoveFirst();
        allocated_size = buffer->count;
    }

    virtual void Set(int index, T value) override
    {
        buffer->Set(index, value);
    }

    virtual void LinearTransformation(int fromIndex, T coefficient, int toIndex) override
    {
        buffer->LinearTransformation(fromIndex, coefficient, toIndex);
    }

    virtual Sequence<T> *Concat(Sequence<T> *list) override
    {
        ArraySequence<T> *res = new ArraySequence<T>(*buffer);
        for (int i = 0; i < list->GetLength(); i++)
        {
            res->Append(list->Get(i));
        }
        return res;
    }

    virtual Sequence<T> &operator=(const Sequence<T> &x) override
    {
        ArraySequence<T> temp = *(ArraySequence<T> *)x.Copy();
        Swap(temp);
        return *this;
    }

    ~ArraySequence() override
    {
        delete buffer;
    }

private:
    DynamicArray<T> *buffer;
    int allocated_size;

    void Resize(int newSize)
    {
        buffer->Resize(newSize);
        allocated_size = newSize;
    }

    void Swap(ArraySequence<T> &array)
    {
        DynamicArray<T> *bubble_buffer = buffer;
        int bubble_allocated_size = allocated_size;
        buffer = array.buffer;
        allocated_size = array.allocated_size;
        array.buffer = bubble_buffer;
        array.allocated_size = bubble_allocated_size;
    }
};

#endif