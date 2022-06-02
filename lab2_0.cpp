//нужно ли поле count списку? Должен ли он быть двусвязным?
//вопрос по исключениям
//зачем Рословцеву ссылка?
//как работает переключение? какие поля должны быть sequence-ах?
//функция очистки???
// memcpy - можно ли использовать?
//сдвиг в dynamic array, метод увеличения размера при необходимости у ArraySequence
//сделать sequence-ы френдами в низших классах, а все их поля сделать приватными?

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
        items = new T[count];
        this->count = count;
    }

    DynamicArray(const DynamicArray<T> &dynamicArray)
    {
        DynamicArray(dynamicArray->items, dynamicArray->count);
    }

    T Get(int index)
    {
        return items[index];
    }

    int GetSize()
    {
        return count;
    }

    void Set(int index, T value)
    {
        items[index] = value;
    }

    void Resize(int newSize)
    {
        T *newItems = new T[newSize];
        for (int i = 0; (i < newSize) && (i < count); i++)
        {
            newItems[i] = items[i];
        }
        delete items;
        items = newItems;
        //count = newSize;
    }

    void Shift(int index) { //считаем, что память выделили извне
        for(int i = count - 1; i >= index; i--) {
            items[i + 1] = items[i];
        }
    }

    void InsertAt(int index, T value) { //считаем, что память выделили извне
        Shift(index);
        Set(index, value);
        count++;
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

    LinkedList(T *items, int count)//мыбы реализовать через append?
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

    LinkedList(const LinkedList<T> &list)//мыбы тоже через append?
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

    LinkedList<T> *GetSubList(int startIndex, int endIndex)
    {
        ItemOfList<T> *start = head;
        ItemOfList<T> *end = head;
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

    void InsertAt(T value, int index)
    {
        if (!index)
        {
            Append(value);
        }
        else if (index == count - 1)
        {
            Prepend(value);
        }
        else
        {
            ItemOfList<T> *prevItem = head;
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
        LinkedList<T> *res = new LinkedList<T>(this);
        for(int i = 0; i < list->count; i++) {
            res->Append(list->Get(i));
        }
        return res;
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

    int GetLength() = 0;

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
    ArraySequence(T *items, int count)
    {
        buffer = new DynamicArray<T>(items, count);
        actual_size = count;
    }

    ArraySequence()
    {
        buffer = new DynamicArray<T>();
        actual_size = 0;
    }

    ArraySequence(const DynamicArray<T> &dynamicArray)
    {
        buffer = new DynamicArray<T>(dynamicArray);
        actual_size = dynamicArray->count;
    }

    virtual T GetFirst() override
    {
        return buffer->Get(0);
    }

    virtual T GetLast() override
    {
        return buffer->Get(buffer->count - 1);
    }

    virtual T Get(int index) override
    {
        return buffer->Get(index);
    }

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) override
    {
        return DynamicArray(buffer->items + startIndex, endIndex - startIndex);
    }

    virtual int GetLength() override {
        return buffer->count;
    }

    virtual void Append(T value) override
    {
        if(!actual_size) {
            buffer->Resize(1);
        }
        else if(buffer->count == actual_size) {
            buffer->Resize(buffer->GetSize() * 2);
        }
        buffer->InsertAt(buffer->count, value);
    }

    virtual void Prepend(T value) override
    {
        if(!actual_size) {
            buffer->Resize(1);
        }
        else if(buffer->count == actual_size) {
            buffer->Resize(buffer->GetSize() * 2);
        }
        buffer->InsertAt(0, value);
    }

    virtual void InsertAt(T value, int index) override
    {
        if(!actual_size) {
            buffer->Resize(1);
        }
        else if(buffer->count == actual_size) {
            buffer->Resize(buffer->GetSize() * 2);
        }
        buffer->InsertAt(index, value);
    }

    virtual Sequence<T> *Concat(Sequence<T> *list) override
    {
        ArraySequence<T> *res = new ArraySequence<T>(buffer);
        for(int i = 0; i < list->GetLength(); i++) {
            res->Append(list->Get(i));
        }
        return res;
    }

private:
    DynamicArray<T> *buffer;
    int actual_size;
};

int main()
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