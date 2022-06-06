//вопрос по исключениям
//зачем Рословцеву ссылка?
// memcpy - можно ли использовать?
//сделать sequence-ы френдами в низших классах, а все их поля сделать приватными?
//выделение памяти по степеням двойки???
//двойной конструктор для матрицы???

//на данный момент ArraySequence обращается к полю items

//вызов деструктора целевого АТД по требованию пользователя и по завершении программы
//метод для сложения с sequence-ом той же длины, умноженным на T (подразумевая, что длина обязательно такая же)
//разобраться с идентификаторами доступа (см комментарий выше)

#include <iostream>
#include <cstring>

class ComplexNumber
{
public:
    ComplexNumber(double real, double imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }

    ComplexNumber getConjugate()
    { //в принципе нужно только для /
        return ComplexNumber(real, -imaginary);
    }

    ComplexNumber operator +(ComplexNumber x)
    {
        return ComplexNumber(this->real + x.real, this->imaginary + x.imaginary);
    }

    ComplexNumber operator *(ComplexNumber x)
    {
        double newReal = this->real * x.real - this->imaginary * x.imaginary;
        double newImaginary = this->real * x.imaginary + this->imaginary * x.real;
        return ComplexNumber(newReal, newImaginary);
    }

    ComplexNumber operator /(ComplexNumber x)
    { //паприкола
        ComplexNumber newNumerator = *this * x.getConjugate();
        double newDenominator = (x * x.getConjugate()).real;
        double newReal = newNumerator.real / newDenominator;
        double newImaginary = newNumerator.imaginary / newDenominator;
        return ComplexNumber(newReal, newImaginary);
    }

    // private:
    double real;
    double imaginary;
};

std::ostream &operator <<(std::ostream &ostream, const ComplexNumber &x)
{
    return ostream << x.real << " + " << x.imaginary << " * i";
}

std::istream &operator >>(std::istream &istream, ComplexNumber &x)
{
    std::cout << "\t\t" << "Введите действительную и мнимую части числа через пробел:" << std::endl << "\t\t";
    return istream >> x.real >> x.imaginary;
}

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

    DynamicArray(int count)//зочем?
    {
        items = new T[count];
        this->count = count;
    }

    DynamicArray()
    {
        items = NULL;
        this->count = 0;
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
        // count = newSize;
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

    void LinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        items[toIndex] += items[fromIndex] * coefficient;
    }

    void Clear() {//насколько адекватно?
        delete items;
        items = NULL;
        count = 0;
    }

    ~DynamicArray()
    {
        delete items;
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

    LinkedList(T *items, int count) //мыбы реализовать через append?
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

    LinkedList(const LinkedList<T> &list) //мыбы тоже через append?
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

    LinkedList<T> *Concat(LinkedList<T> *list) //а зочем?..
    {
        LinkedList<T> *res = new LinkedList<T>(this);
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

    void Clear() {
        ItemOfList<T> *cur = tail;
        while (cur != NULL)
        {
            cur = cur->prev;
            delete cur->next;
        }
        head = NULL;
        tail = NULL;
        count = 0;
    }

    ~LinkedList()
    {
        ItemOfList<T> *cur = tail;
        while (cur != NULL)
        {
            cur = cur->prev;
            delete cur->next;
        }
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

    virtual int GetLength() = 0;

    virtual int GetAllocatedSize() = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    virtual void Append(T value) = 0;

    virtual void Prepend(T value) = 0;

    virtual void InsertAt(int index, T value) = 0;

    virtual void Set(int index, T value) = 0;

    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;

    virtual void LinearTransformation(int fromIndex, T coefficient, int toIndex) = 0;

    virtual Sequence<T> &operator =(Sequence<T> x) = 0;

    virtual Sequence<T> operator +(Sequence<T> x) = 0;

    virtual Sequence<T> operator -(Sequence<T> x) = 0;

    virtual Sequence<T> operator *(T coefficient) = 0;

    virtual Sequence<T> operator /(T coefficient) = 0;

    virtual Sequence<T> &operator +=(Sequence<T> x) = 0;

    virtual Sequence<T> &operator -=(Sequence<T> x) = 0;

    virtual Sequence<T> &operator *=(T coefficient) = 0;

    virtual Sequence<T> &operator /=(T coefficient) = 0;

    virtual void Clear() = 0;

    virtual ~Sequence() = 0;
};

template <class T>
class ArraySequence : Sequence<T>
{
public:
    ArraySequence(T *items, int count)
    {
        buffer = new DynamicArray<T>(items, count);
        allocated_size = count;
    }

    ArraySequence()
    {
        buffer = new DynamicArray<T>();
        allocated_size = 0;
    }

    ArraySequence(const DynamicArray<T> &dynamicArray)
    {
        buffer = new DynamicArray<T>(dynamicArray);
        allocated_size = dynamicArray->count;
    }

    ArraySequence(int count) {
        T items[count];
        std::cout << '\t' << "Введите " << count << " чисел:" << std::endl;
        for(int i = 0; i < count; i++) {
            std::cin >> items[i];
        }
        ArraySequence(items, count);
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

    virtual int GetLength() override
    {
        return buffer->count;
    }

    virtual int GetAllocatedSize() override
    {
        return allocated_size;
    }

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) override
    {
        return new DynamicArray(buffer->items + startIndex, endIndex - startIndex);
    }

    virtual void Append(T value) override
    {
        if (!allocated_size)
        {
            buffer->Resize(1);
        }
        else if (buffer->count == allocated_size)
        {
            buffer->Resize(buffer->GetSize() * 2);
        }
        buffer->InsertAt(buffer->count, value);
    }

    virtual void Prepend(T value) override
    {
        if (!allocated_size)
        {
            buffer->Resize(1);
        }
        else if (buffer->count == allocated_size)
        {
            buffer->Resize(buffer->GetSize() * 2);
        }
        buffer->InsertAt(0, value);
    }

    virtual void InsertAt(int index, T value) override
    {
        if (!allocated_size)
        {
            buffer->Resize(1);
        }
        else if (buffer->count == allocated_size)
        {
            buffer->Resize(buffer->GetSize() * 2);
        }
        buffer->InsertAt(index, value);
    }

    virtual void Set(int index, T value) override
    {
        buffer->Set(index, value);
    }

    virtual Sequence<T> *Concat(Sequence<T> *list) override
    {
        ArraySequence<T> *res = new ArraySequence<T>(buffer);
        for (int i = 0; i < list->GetLength(); i++)
        {
            res->Append(list->Get(i));
        }
        return res;
    }

    virtual void LinearTransformation(int fromIndex, T coefficient, int toIndex) override
    {
        buffer->LinearTransformation(fromIndex, coefficient, toIndex);
    }

    virtual Sequence<T> &operator =(Sequence<T> x) override
    {
        Clear();
        allocated_size = x.GetAllocatedSize;
        buffer->Resize(allocated_size);
        for(int i = 0; i < x->GetLength(); i++) {
            Append(x.Get(i));
        }
    }

    virtual Sequence<T> operator +(Sequence<T> x) override
    {
        Sequence<T> res = ArraySequence(buffer);
        for(int i = 0; i < res->GetLength; i++) {
            res->Set(i, Get(i) + x->Get(i));
        }
        return res;
    }

    virtual Sequence<T> operator -(Sequence<T> x) override
    {
        Sequence<T> res = ArraySequence(buffer);
        for(int i = 0; i < res->GetLength; i++) {
            res->Set(i, Get(i) - x->Get(i));
        }
        return res;
    }

    virtual Sequence<T> operator *(T coefficient) override
    {
        Sequence<T> res = ArraySequence(buffer);
        for(int i = 0; i < res->GetLength; i++) {
            res->Set(i, Get(i) * coefficient);
        }
        return res;
    }

    virtual Sequence<T> operator /(T coefficient) override
    {
        Sequence<T> res = ArraySequence(buffer);
        for(int i = 0; i < res->GetLength; i++) {
            res->Set(i, Get(i) / coefficient);
        }
        return res;
    }

        virtual Sequence<T> &operator +=(Sequence<T> x) override
    {
        for(int i = 0; i < buffer->count; i++) {
            buffer->Set(i, Get(i) + x->Get(i));
        }
        return *this;
    }

    virtual Sequence<T> &operator -=(Sequence<T> x) override
    {
        for(int i = 0; i < buffer->count; i++) {
            buffer->Set(i, Get(i) + x->Get(i));
        }
        return *this;
    }

    virtual Sequence<T> &operator *=(T coefficient) override
    {
        for(int i = 0; i < buffer->count; i++) {
            buffer->Set(i, Get(i) * coefficient);
        }
        return *this;
    }

    virtual Sequence<T> &operator /=(T coefficient) override
    {
        for(int i = 0; i < buffer->count; i++) {
            buffer->Set(i, Get(i) / coefficient);
        }
        return *this;
    }

    virtual void Clear() override
    {
        buffer->Clear;
        allocated_size = 0;
    }

    ~ArraySequence()
    {
        delete buffer;
    }

private:
    DynamicArray<T> *buffer;
    int allocated_size;
};

template <class T>
class ListSequence : Sequence<T>
{
public:
    ListSequence(T *items, int count)
    {
        buffer = new LinkedList<T>(items, count);
    }

    ListSequence()
    {
        buffer = new LinkedList<T>();
    }

    ListSequence(const LinkedList<T> &list)
    {
        buffer = new LinkedList<T>(list);
    }

    ListSequence(int count) {
        T items[count];
        std::cout << '\t' << "Введите " << count << " чисел:" << std::endl;
        for(int i = 0; i < count; i++) {
            std::cin >> items[i];
        }
        ListSequence(items, count);
    }

    virtual T GetFirst() override
    {
        return buffer->GetFirst;
    }

    virtual T GetLast() override
    {
        return buffer->GetLast;
    }

    virtual T Get(int index) override
    {
        return buffer->Get(index);
    }

    virtual int GetLength() override
    {
        return buffer->count;
    }

    virtual int GetAllocatedSize() override
    {
        return buffer->count;
    }
    
    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) override
    {
        return buffer->GetSubList(startIndex, endIndex);
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

    virtual void Set(int index, T value) override
    {
        buffer->Set(index, value);
    }

    virtual Sequence<T> *Concat(Sequence<T> *list) override
    {
        ListSequence<T> *res = new ListSequence<T>(buffer);
        for (int i = 0; i < list->GetLength(); i++)
        {
            res->Append(list->Get(i));
        }
        return res;
    }

    virtual void LinearTransformation(int fromIndex, T coefficient, int toIndex) override
    {
        buffer->LinearTransformation(fromIndex, coefficient, toIndex);
    }

    virtual Sequence<T> &operator =(Sequence<T> x) override
    {
        Clear();
        for(int i = 0; i < x->GetLength(); i++) {
            Append(x.Get(i));
        }
    }

    virtual Sequence<T> operator +(Sequence<T> x) override
    {
        Sequence<T> res = ListSequence();
        for(int i = 0; i < res->GetLength; i++) {
            res->Append(Get(i) + x->Get(i));
        }
        return res;
    }

    virtual Sequence<T> operator -(Sequence<T> x) override
    {
        Sequence<T> res = ListSequence();
        for(int i = 0; i < res->GetLength; i++) {
            res->Append(Get(i) - x->Get(i));
        }
        return res;
    }

    virtual Sequence<T> operator *(T coefficient) override
    {
        Sequence<T> res = ListSequence();
        for(int i = 0; i < res->GetLength; i++) {
            res->Append(Get(i) * coefficient);
        }
        return res;
    }

    virtual Sequence<T> operator /(T coefficient) override
    {
        Sequence<T> res = ListSequence();
        for(int i = 0; i < res->GetLength; i++) {
            res->Append(Get(i) / coefficient);
        }
        return res;
    }

    virtual Sequence<T> &operator +=(Sequence<T> x) override
    {
        for(int i = 0; i < buffer->count; i++) {
            buffer->Set(i, Get(i) + x->Get(i));
        }
        return *this;
    }

    virtual Sequence<T> &operator -=(Sequence<T> x) override
    {
        for(int i = 0; i < buffer->count; i++) {
            buffer->Set(i, Get(i) + x->Get(i));
        }
        return *this;
    }

    virtual Sequence<T> &operator *=(T coefficient) override
    {
        for(int i = 0; i < buffer->count; i++) {
            buffer->Set(i, Get(i) * coefficient);
        }
        return *this;
    }

    virtual Sequence<T> &operator /=(T coefficient) override
    {
        for(int i = 0; i < buffer->count; i++) {
            buffer->Set(i, Get(i) / coefficient);
        }
        return *this;
    }

    virtual void Clear() override
    {
        buffer->Clear;
    }

    ~ListSequence()
    {
        delete buffer;
    }

private:
    LinkedList<T> *buffer;
};

template <class T> std::ostream &operator <<(std::ostream &ostream, const Sequence<T> &sequence)
{
    for(int i = 0; i < sequence.GetLength; i++) {
        ostream << sequence.Get(i) << " ";
    }
    ostream << std::endl;
    return ostream;
}

template <class T> class RectangularMatrix {
    private:
        int m, n;
        //Sequence <S
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