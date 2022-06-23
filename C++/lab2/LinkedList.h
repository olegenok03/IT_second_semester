#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>

template <class T>
class LinkedList;

template <class T>
class ItemOfList
{
    friend class LinkedList<T>;

private:
    T data;
    ItemOfList<T> *next;
    ItemOfList<T> *prev;

    ItemOfList(T data, ItemOfList *next, ItemOfList *prev)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

template <class T>
class ListSequence;

template <class T>
class LinkedList
{
    friend class ListSequence<T>;

public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    LinkedList(T *items, int count)
    {

        if (!count)
        {
            head = NULL;
            tail = NULL;
            this->count = 0;
        }
        else
        {
            ItemOfList<T> *first = new ItemOfList<T>(items[0], NULL, NULL);
            ItemOfList<T> *last = first;
            for (int i = 1; i < count; i++)
            {
                last->next = new ItemOfList<T>(items[i], NULL, last);
                last = last->next;
            }
            head = first;
            tail = last;
            this->count = count;
        }
    }

    LinkedList(T value, int count)
    {
        if (!count)
        {
            head = NULL;
            tail = NULL;
            this->count = 0;
        }
        else
        {
            ItemOfList<T> *first = new ItemOfList<T>(value, NULL, NULL);
            ItemOfList<T> *last = first;
            for (int i = 1; i < count; i++)
            {
                last->next = new ItemOfList<T>(value, NULL, last);
                last = last->next;
            }
            head = first;
            tail = last;
            this->count = count;
        }
    }

    LinkedList(const LinkedList<T> &list)
    {
        ItemOfList<T> *cur = list.head;
        if (!cur)
        {
            head = NULL;
            tail = NULL;
            count = 0;
        }
        else
        {
            ItemOfList<T> *first = new ItemOfList<T>(cur->data, NULL, NULL);
            // cur = cur->next;
            ItemOfList<T> *last = first;
            for (int i = 1; i < list.count; i++)
            {                    // while(cur) {}
                cur = cur->next; //убрать
                last->next = new ItemOfList<T>(cur->data, NULL, last);
                last = last->next;
                // cur = cur->next;
            }
            head = first;
            tail = last;
            count = list.count;
        }
    }

    T GetFirst()
    {
        return head->data;
    }

    T GetLast()
    {
        return tail->data;
    }

    T Get(int index)
    {
        ItemOfList<T> *cur = head;
        for (int i = 1; i <= index; i++)
        {
            cur = cur->next;
        }
        return cur->data;
    }

    LinkedList<T> *GetSubList(int startIndex, int endIndex) //!!!
    {
        LinkedList<T> *res = new LinkedList();
        for (int i = startIndex; i < endIndex; i++)
        {
            res->Append(Get(i));
        }
        return res;
    }

    int GetLength()
    {
        return count;
    }

    void Set(int index, T value)
    {
        ItemOfList<T> *cur = head;
        for (int i = 1; i <= index; i++)
        {
            cur = cur->next;
        }
        cur->data = value;
    }

    void Append(T value)
    {
        ItemOfList<T> *newItem = new ItemOfList<T>(value, NULL, tail);
        if (tail)
        {
            tail->next = newItem;
        }
        else
        {
            head = newItem;
        }
        tail = newItem;
        count++;
    }

    void Prepend(T value)
    {
        ItemOfList<T> *newItem = new ItemOfList<T>(value, head, NULL);
        if (head)
        {
            head->prev = newItem;
        }
        else
        {
            tail = newItem;
        }
        head = newItem;
        count++;
    }

    void InsertAt(int index, T value)
    {
        if (!index)
        {
            Prepend(value);
        }
        else if (index == count)
        {
            Append(value);
        }
        else
        {
            ItemOfList<T> *prevItem = head;
            for (int i = 1; i <= index - 1; i++)
            {
                prevItem = prevItem->next;
            }
            ItemOfList<T> *nextItem = prevItem->next;
            ItemOfList<T> *newItem = new ItemOfList<T>(value, nextItem, prevItem);
            prevItem->next = newItem;
            nextItem->prev = newItem;
            count++;
        }
    }

    void RemoveLast()
    {
        if (tail && tail->prev)
        {
            tail = tail->prev;
            delete tail->next;
            tail->next = NULL;
            count--;
        }
        else if (tail)
        {
            delete tail;
            head = NULL;
            tail = NULL;
            count--;
        }
    }

    void RemoveFirst()
    {
        if (head && head->next)
        {
            head = head->next;
            delete head->prev;
            head->prev = NULL;
            count--;
        }
        else if (head)
        {
            delete head;
            head = NULL;
            tail = NULL;
            count--;
        }
    }

    LinkedList<T> *Concat(LinkedList<T> *list) //а зочем?..
    {
        LinkedList<T> *res = new LinkedList<T>(*this);
        for (int i = 0; i < list->count; i++)
        {
            res->Append(list->Get(i));
        }
        return res;
    }

    void LinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        Set(toIndex, Get(toIndex) + Get(fromIndex) * coefficient);
    }

    ~LinkedList()
    {
        ItemOfList<T> *cur = tail;
        while (cur != head)
        {
            cur = cur->prev;
            delete cur->next;
        }
        if (head)
        {
            delete head;
        }
    }

private:
    ItemOfList<T> *head;
    ItemOfList<T> *tail;
    int count;
};

#endif