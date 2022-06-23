#ifndef LISTSEQUENCE
#define LISTSEQUENCE

#include <iostream>

#include "LinkedList.h"
#include "Sequence.h"

template <class T>
class ListSequence : public Sequence<T>
{
public:
    ListSequence()
    {
        buffer = new LinkedList<T>();
    }

    ListSequence(T *items, int count)
    {
        buffer = new LinkedList<T>(items, count);
    }

    ListSequence(T value, int count)
    {
        buffer = new LinkedList<T>(value, count);
    }

    ListSequence(const LinkedList<T> &list)
    {
        buffer = new LinkedList<T>(list);
    }

    ListSequence(const ListSequence<T> &listSequence) : ListSequence(*listSequence.buffer)
    {
        /*buffer = new LinkedList<T>();
        for (int i = 0; i < sequence.GetLength(); i++)
        {
            Append(sequence.Get(i));
        }*/
    }

    virtual int GetLength() const override
    {
        return buffer->count;
    }

    virtual int GetAllocatedSize() const override
    {
        return buffer->count;
    }

    virtual T GetFirst() const override
    {
        return buffer->GetFirst();
    }

    virtual T GetLast() const override
    {
        return buffer->GetLast();
    }

    virtual T Get(int index) const override
    {
        return buffer->Get(index);
    }

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) const override
    {
        LinkedList<T> *subList = buffer->GetSubList(startIndex, endIndex);
        Sequence<T> *res = new ListSequence(*subList);
        delete subList;
        return res;
    }

    virtual Sequence<T> *Copy() const override
    {
        return new ListSequence(*this);
    }

    virtual void Append(T value) override
    {
        buffer->Append(value);
    }

    virtual void Prepend(T value) override
    {
        buffer->Prepend(value);
    }

    virtual void InsertAt(int index, T value) override
    {
        buffer->InsertAt(index, value);
    }

    virtual void RemoveLast()
    {
        buffer->RemoveLast();
    }

    virtual void RemoveFirst()
    {
        buffer->RemoveFirst();
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
        ListSequence<T> *res = new ListSequence<T>(*buffer);
        for (int i = 0; i < list->GetLength(); i++)
        {
            res->Append(list->Get(i));
        }
        return res;
    }

    virtual Sequence<T> &operator=(const Sequence<T> &x) override
    {
        ListSequence<T> temp = *(ListSequence<T> *)x.Copy();
        Swap(temp);
        return *this;
    }

    ~ListSequence() override
    {
        delete buffer;
    }

private:
    LinkedList<T> *buffer;

    void Swap(ListSequence<T> &list)
    {
        LinkedList<T> *bubble_buffer = buffer;
        buffer = list.buffer;
        list.buffer = bubble_buffer;
    }
};

#endif