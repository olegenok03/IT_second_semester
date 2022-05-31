//нужно ли поле count списку? Должен ли он быть двусвязным?
//вопрос по исключениям
//зачем Рословцеву ссылка?
//как работает переключение? какие поля должны быть sequence-ах?
//функция очистки???
//memcpy - можно ли использовать?
//сдвиг в dynamic array, метод увеличения размера при необходимости у ArraySequence

#include <iostream>
#include <cstring>

template <class T>
class DynamicArray
{
public:
    DynamicArray(T *items, int count)
    {
        this->items = new T[count];
        memcpy(this->items, items, count * sizeof(T));
        this->count = count;
    }

    DynamicArray(int count)
    {
        this->items = new T[count];
        this->count = count;
    }

    DynamicArray(const DynamicArray<T> &dynamicArray)
    {
        this->count = dynamicArray->count;
        this->items = new T[this->count];
        for (int i = 0; i < this->count; i++)
        {
            this->items[i] = dynamicArray->items[i];
        }
    }

    T Get(int index)
    {
        return this->items[index];
    }

    int GetSize()
    {
        return count;
    }

    void Set(int index, T value)
    {
        this->items[index] = value;
    }

    void Resize(int newSize)
    {
        T *newItems = new T[newSize];
        for (int i = 0; (i < newSize) && (i < this->count); i++)
        {
            newItems[i] = this->items[i];
        }
        delete (this->items);
        this->items = newItems;
        this->count = newSize;
    }

private:
    T *items;
    int count;
};

template <class T>
class LinkedList;

template <class T>
class ItemOfList
{
    friend class LinkedList<T>;

public:
    // private:
    T data;
    ItemOfList<T> *next; //!!!
    ItemOfList<T> *prev; //!!!

    ItemOfList(T data, ItemOfList *next, ItemOfList *prev)
    {
        this->data = data;
        this->next = next;
        this->prev = prev;
    }
};

template <class T>
class LinkedList
{
public:
    LinkedList(ItemOfList<T> *head, ItemOfList<T> *tail, int count)
    {
        this->head = head;
        this->tail = tail;
        this->count = count;
    }

    LinkedList()
    {
        LinkedList(NULL, NULL, 0);
    }

    LinkedList(T *items, int count)
    {

        if (!count)
        {
            LinkedList();
        }
        else
        {
            ItemOfList<T> *head = new ItemOfList<T>(items[0], NULL, NULL);
            ItemOfList<T> *last = head;
            for (int i = 1; i < count; i++)
            {
                last->next = new ItemOfList(ItemOfList<T>(items[i], NULL, last));
                last = last->next;
            }
            LinkedList(head, tail, count);
        }
    }

    LinkedList(const LinkedList<T> &list)
    {
        ItemOfList<T> *cur = list.head;
        if (!cur)
        {
            LinkedList();
        }
        else
        {
            ItemOfList<T> *head = new ItemOfList<T>(cur->data, NULL, NULL);
            // cur = cur->next;
            ItemOfList<T> *last = head;
            for (int i = 1; i < list.count; i++)
            {                    // while(cur) {}
                cur = cur->next; //убрать
                last->next = new ItemOfList<T>(cur->data, NULL, last);
                last = last->next;
                // cur = cur->next;
            }
            LinkedList(head, tail, count);
        }
    }

    T GetFirst()
    {
        return this->head->data;
    }

    T GetLast()
    {
        return this->tail->data;
    }

    T Get(int index)
    {
        ItemOfList<T> *cur = this->head;
        for (int i = 1; i <= index; i++)
        {
            cur = cur->next;
        }
        return cur->data;
    }

    LinkedList<T> *GetSubList(int startIndex, int endIndex)
    {
        ItemOfList<T> *start = this->head;
        ItemOfList<T> *end = this->head;
        for (int i = 1; i <= startIndex; i++)
        {
            start = start->next;
        }
        for (int i = 1; i <= endIndex; i++)
        {
            end = end->next;
        }
        return LinkedList(LinkedList(start, end, endIndex - startIndex));
    }

    int GetLength()
    {
        return count;
    }

    void Append(T value)
    {
        ItemOfList<T> *newItem = new ItemOfList<T>(value, NULL, this->tail);
        if (this->tail)
        {
            this->tail->next = newItem;
        }
        else
        {
            this->head = newItem;
        }
        this->tail = newItem;
    }

    void Prepend(T value)
    {
        ItemOfList<T> *newItem = new ItemOfList<T>(value, this->head, NULL);
        if (this->head)
        {
            this->head->prev = newItem;
        }
        else
        {
            this->tail = newItem;
        }
        this->head = newItem;
    }

    void InsertAt(T value, int index)
    {
        if (!index)
        {
            this->Append(value);
        }
        else if (index == this->count - 1)
        {
            this->Prepend(value);
        }
        else
        {
            ItemOfList<T> *prevItem = this->head;
            for (int i = 1; i <= index - 1; i++)
            {
                prevItem = prevItem->next;
            }
            ItemOfList<T> *nextItem = prevItem->next;
            ItemOfList<T> *newItem = new ItemOfList<T>(value, prevItem, nextItem);
            prevItem->next = newItem;
            nextItem->prev = newItem;
        }
    }

    LinkedList<T> *Concat(LinkedList<T> *list)
    {
        if (!list->head)
        {
            return new LinkedList<T>(this);
        }
        if (!this->head)
        {
            return new LinkedList<T>(list);
        }
        LinkedList<T> *first = new LinkedList<T>(this);
        LinkedList<T> *second = new LinkedList<T>(list);
        second->head->prev = first->tail;
        first->tail->next = second->head;
        first->tail = second->tail;
        first->count += second->count;
        return first;
    }

    // private:
    ItemOfList<T> *head;
    ItemOfList<T> *tail;
    int count;
};

template <class T>
class Sequence
{
public:
    virtual T GetFirst() = 0;

    virtual T GetLast() = 0;

    virtual T Get(int index) = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    virtual void Append(T value) = 0;

    virtual void Prepend(T value) = 0;

    virtual void InsertAt(T value, int index) = 0;

    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;
};

template <class T>
class ArraySequence : Sequence<T>
{
    public:
        ArraySequence(T *items, int count) {
            this->buffer = new DynamicArray<T>(items, count);
        }

        ArraySequence() {
            this->buffer = new DynamicArray<T>();
        }

        ArraySequence(const DynamicArray <T> &dynamicArray) {
            this->buffer = new DynamicArray<T>(dynamicArray);
        }

        virtual T GetFirst() override {
            return this->buffer->Get(0);
        }

        virtual T GetLast() override {
            return this->buffer->Get(this->buffer->count - 1);
        }

        virtual T Get(int index) override {
            return this->buffer->Get(index);
        }

        virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) override {
            return DynamicArray(this->buffer->items + startIndex, endIndex - startIndex);
        }

        virtual void Append(T value) override {

        }

        virtual void Prepend(T value) override {

        }

        virtual void InsertAt(T value, int index) override {

        }

        virtual Sequence<T> *Concat(Sequence<T> *list) override {

        }
    private:
        DynamicArray<T> *buffer;
}

int
main()
{
    int a[2] = {2, 3};
    int b[0];
    LinkedList<int> list1(a, 2);
    LinkedList<int> list2(list1);
    LinkedList<int> list3(b, 0);
    std::cout << "Hello, world!" << std::endl;
    std::cout << list1.head->data << " " << (bool)list1.head->next << " " << (bool)list1.head->prev << " ";
    std::cout << list1.tail->data << " " << (bool)list1.tail->next << " " << (bool)list1.tail->prev << std::endl;
    std::cout << list2.head->data << " " << (bool)list2.head->next << " " << (bool)list2.head->prev << " ";
    std::cout << list2.tail->data << " " << (bool)list2.tail->next << " " << (bool)list2.tail->prev << std::endl;
    std::cout << (bool)list3.head << " " << (bool)list3.tail << std::endl;
    return 0;
}