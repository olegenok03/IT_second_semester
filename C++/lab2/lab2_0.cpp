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
    friend ComplexNumber operator+(ComplexNumber const &first, ComplexNumber const &second);
    friend ComplexNumber operator-(ComplexNumber const &first, ComplexNumber const &second);
    friend ComplexNumber operator*(ComplexNumber const &first, ComplexNumber const &second);
    friend ComplexNumber operator/(ComplexNumber const &first, ComplexNumber &second);
    friend std::ostream &operator<<(std::ostream &ostream, const ComplexNumber &x);
    friend std::istream &operator>>(std::istream &istream, ComplexNumber &x);

public:
    ComplexNumber() : ComplexNumber(0.0, 0.0) {}
    ComplexNumber(double real, double imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }

    ComplexNumber getConjugate()
    {
        return ComplexNumber(real, -imaginary);
    }

    const ComplexNumber operator-() const
    {
        return ComplexNumber(-real, -imaginary);
    }

    ComplexNumber &operator+=(const ComplexNumber &x)
    {
        real += x.real;
        imaginary += x.imaginary;
        return *this;
    }

    ComplexNumber &operator-=(const ComplexNumber &x)
    {
        real -= x.real;
        imaginary -= x.imaginary;
        return *this;
    }

    ComplexNumber &operator*=(const ComplexNumber &x)
    {
        real = real * x.real - imaginary * x.imaginary;
        imaginary = real * x.imaginary + imaginary * x.real;
        return *this;
    }

    ComplexNumber &operator/=(ComplexNumber &x)
    {
        ComplexNumber newNumerator = *this * x.getConjugate();
        double newDenominator = (x * x.getConjugate()).real;
        real = newNumerator.real / newDenominator;
        imaginary = newNumerator.imaginary / newDenominator;
        return *this;
    }

private:
    double real;
    double imaginary;
};

ComplexNumber operator+(ComplexNumber const &first, ComplexNumber const &second)
{
    return ComplexNumber(first.real + second.real, first.imaginary + second.imaginary);
}

ComplexNumber operator-(ComplexNumber const &first, ComplexNumber const &second)
{
    return ComplexNumber(first.real - second.real, first.imaginary - second.imaginary);
}

ComplexNumber operator*(ComplexNumber const &first, ComplexNumber const &second)
{
    double newReal = first.real * second.real - first.imaginary * second.imaginary;
    double newImaginary = first.real * second.imaginary + first.imaginary * second.real;
    return ComplexNumber(newReal, newImaginary);
}

ComplexNumber operator/(ComplexNumber const &first, ComplexNumber &second)
{
    ComplexNumber newNumerator = first * second.getConjugate();
    double newDenominator = (second * second.getConjugate()).real;
    double newReal = newNumerator.real / newDenominator;
    double newImaginary = newNumerator.imaginary / newDenominator;
    return ComplexNumber(newReal, newImaginary);
}

std::ostream &operator<<(std::ostream &ostream, const ComplexNumber &x)
{
    return ostream << x.real << " + " << x.imaginary << " * i";
}

std::istream &operator>>(std::istream &istream, ComplexNumber &x)
{
    std::cout << "\t\t"
              << "Введите действительную и мнимую части числа через пробел:" << std::endl
              << "\t\t";
    return istream >> x.real >> x.imaginary;
}

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
        T *newItems = new T[newSize];
        for (int i = 0; (i < newSize) && (i < count); i++)
        {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
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
            this->count = 0;
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
            this->count = count;
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
        for (int i = startIndex; i <= endIndex; i++)
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
        while (cur != NULL)
        {
            cur = cur->prev;
            delete cur->next;
        }
    }

private:
    ItemOfList<T> *head;
    ItemOfList<T> *tail;
    int count;
};

template <class T>
class Sequence
{
public:
    virtual int GetLength() = 0;

    virtual int GetAllocatedSize() = 0;

    virtual T GetFirst() = 0;

    virtual T GetLast() = 0;

    virtual T Get(int index) = 0;

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    virtual Sequence<T> *Copy() = 0;

    virtual void Append(T value) = 0;

    virtual void Prepend(T value) = 0;

    virtual void InsertAt(int index, T value) = 0;

    virtual void Set(int index, T value) = 0;

    void Permutate(int firstIndex, int secondIndex)
    {
        T bubble = Get(firstIndex);
        Set(firstIndex, Get(secondIndex));
        Set(secondIndex, bubble);
    }

    virtual void LinearTransformation(int fromIndex, T coefficient, int toIndex) = 0;

    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;

    virtual Sequence<T> &operator=(Sequence<T> &x) = 0;

    virtual const Sequence<T> operator-() = 0;

    virtual const Sequence<T> operator+(Sequence<T> &x) = 0;

    virtual const Sequence<T> operator-(Sequence<T> &x) = 0;

    virtual const Sequence<T> operator*(T coefficient) = 0;

    virtual const Sequence<T> operator/(T coefficient) = 0;

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

//Sequence<class T>::~Sequence() {}

template <class T>
class ArraySequence : Sequence<T>
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

    ArraySequence(const Sequence<T> &sequence)
    {
        const ArraySequence<T> &arraySequence = dynamic_cast<const ArraySequence<T> &>(sequence);

        buffer = new DynamicArray<T>(sequence.GetAllocatedSize());
        allocated_size = sequence.GetAllocatedSize();
        for (int i = 0; i < sequence.GetLength(); i++)
        {
            Set(i, sequence.Get(i));
        }
    }

    virtual int GetLength() override
    {
        return buffer->count;
    }

    virtual int GetAllocatedSize() override
    {
        return allocated_size;
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
        return new ArraySequence<T>(DynamicArray<T>(buffer->items + startIndex, endIndex - startIndex));
    }

    virtual Sequence<T> *Copy() override
    {
        return new ArraySequence<T>(*this);
    }

    virtual void Append(T value) override
    {
        if (!allocated_size)
        {
            buffer->Resize(1);
        }
        else if (buffer->count == allocated_size)
        {
            buffer->Resize(buffer->count * 2);
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
            buffer->Resize(buffer->count * 2);
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
            buffer->Resize(buffer->count * 2);
        }
        buffer->InsertAt(index, value);
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

    virtual Sequence<T> &operator=(Sequence<T> &x) override
    {
        ArraySequence<T> temp = ArraySequence<T>(x);
        Swap(temp);
        return *this;
    }

    virtual const Sequence<T> operator-() override
    {
        Sequence<T> *res = new ArraySequence(*buffer);
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, -Get(i));
        }
        return *res;
    }

    virtual const Sequence<T> operator+(Sequence<T> &x) override
    {
        Sequence<T> *res = new ArraySequence(*buffer);
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, Get(i) + x.Get(i));
        }
        return *res;
    }

    virtual const Sequence<T> operator-(Sequence<T> &x) override
    {
        Sequence<T> *res = new ArraySequence(*buffer);
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, Get(i) - x.Get(i));
        }
        return *res;
    }

    virtual const Sequence<T> operator*(T coefficient) override
    {
        Sequence<T> *res = new ArraySequence(*buffer);
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, Get(i) * coefficient);
        }
        return *res;
    }

    virtual const Sequence<T> operator/(T coefficient) override
    {
        Sequence<T> *res = new ArraySequence(*buffer);
        for (int i = 0; i < GetLength(); i++)
        {
            res->Set(i, Get(i) / coefficient);
        }
        return *res;
    }

    ~ArraySequence() override
    {
        delete buffer;
    }

private:
    DynamicArray<T> *buffer;
    int allocated_size;

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

template <class T>
class ListSequence : Sequence<T>
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

    ListSequence(const ListSequence<T> &sequence) : ListSequence(*sequence.buffer)
    {
        /*buffer = new LinkedList<T>();
        for (int i = 0; i < sequence.GetLength(); i++)
        {
            Append(sequence.Get(i));
        }*/
    }

    virtual int GetLength() override
    {
        return buffer->count;
    }

    virtual int GetAllocatedSize() override
    {
        return buffer->count;
    }

    virtual T GetFirst() override
    {
        return buffer->GetFirst();
    }

    virtual T GetLast() override
    {
        return buffer->GetLast();
    }

    virtual T Get(int index) override
    {
        return buffer->Get(index);
    }

    virtual Sequence<T> *GetSubsequence(int startIndex, int endIndex) override
    {
        return new ListSequence(*buffer->GetSubList(startIndex, endIndex));
    }

    virtual Sequence<T> *Copy()
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

    virtual Sequence<T> &operator=(Sequence<T> &x) override
    {
        ListSequence<T> temp = ListSequence<T>(x);
        Swap(temp);
        return *this;
    }

    virtual const Sequence<T> operator-() override
    {
        Sequence<T> *res = new ListSequence();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Append(-Get(i));
        }
        return *res;
    }

    virtual const Sequence<T> operator+(Sequence<T> &x) override
    {
        Sequence<T> *res = new ListSequence();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Append(Get(i) + x.Get(i));
        }
        return *res;
    }

    virtual const Sequence<T> operator-(Sequence<T> &x) override
    {
        Sequence<T> *res = new ListSequence();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Append(Get(i) - x.Get(i));
        }
        return *res;
    }

    virtual const Sequence<T> operator*(T coefficient) override
    {
        Sequence<T> *res = new ListSequence();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Append(Get(i) * coefficient);
        }
        return *res;
    }

    virtual const Sequence<T> operator/(T coefficient) override
    {
        Sequence<T> *res = new ListSequence();
        for (int i = 0; i < GetLength(); i++)
        {
            res->Append(Get(i) / coefficient);
        }
        return *res;
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

template <class T>
class RectangularMatrix
{
    template <T> friend std::ostream &operator<<(std::ostream &ostream, const RectangularMatrix<T> &rectangularMatrix);
    template <T> friend std::istream &operator>>(std::istream &istream, RectangularMatrix<T> &rectangularMatrix);
    template <T> friend const RectangularMatrix<T> operator+(RectangularMatrix<T> &x1, RectangularMatrix<T> &x2);
    template <T> friend const RectangularMatrix<T> operator*(RectangularMatrix<T> &x, T coefficient);

public:
    RectangularMatrix()
    {
        rows = NULL;
        m = 0;
        n = 0;
    }
    RectangularMatrix(Sequence<T> *new_rows) : RectangularMatrix() //не копирует; если не пустой сиквенс, то rows = NULL
    {
        if (!new_rows->GetLength())
        {
            rows = new_rows;
        }
    }

    RectangularMatrix(const RectangularMatrix<T> &rectangularMatrix)
    {
        rows = rectangularMatrix.rows->Copy();
        m = rectangularMatrix->m;
        n = rectangularMatrix->n;
    }

    void RowPermutate(int firstIndex, int secondIndex)
    {
        for (int i = 0; i < n; i++)
        {
            rows->Permutate(firstIndex * n + i, secondIndex * n + i);
        }
    }

    void ColumnPermutate(int firstIndex, int secondIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->Permutate(firstIndex + i * n, secondIndex + i * n);
        }
    }

    void RowMultiple(int index, T coefficient)
    {
        for (int i = 0; i < n; i++)
        {
            rows->Set(index * n + i, rows->Get(index * n + i) * coefficient);
        }
    }

    void ColumnPermutate(int index, T coefficient)
    {
        for (int i = 0; i < m; i++)
        {
            rows->Set(index + i * n, rows->Get(index + i * n) * coefficient);
        }
    }

    void RowLinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        for (int i = 0; i < n; i++)
        {
            rows->LinearTransformation(fromIndex * n + i, coefficient, toIndex * n + i);
        }
    }

    void ColumnPermutate(int fromIndex, T coefficient, int toIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->LinearTransformation(fromIndex + i * n, coefficient, toIndex + i * n);
        }
    }

    RectangularMatrix<T> &operator=(RectangularMatrix<T> &rectangularMatrix)
    {
        delete rows;
        rows = rectangularMatrix.rows->Copy();
        m = rectangularMatrix->m;
        n = rectangularMatrix->n;
        return *this;
    }

    ~RectangularMatrix()
    {
        if (rows)
        {
            delete rows;
        }
    }

private:
    int m, n;
    Sequence<T> *rows;
};

template <class T>
const RectangularMatrix<T> operator+(RectangularMatrix<T> &x1, RectangularMatrix<T> &x2) //тот же тип, что и x1
{
    RectangularMatrix sumMatrix = RectangularMatrix(x1);
    *sumMatrix.rows += *x2.rows;
    return sumMatrix;
}

template <class T>
const RectangularMatrix<T> operator*(RectangularMatrix<T> &x, T coefficient)
{
    RectangularMatrix sumMatrix = RectangularMatrix(x);
    *sumMatrix.rows *= coefficient;
    return sumMatrix;
}

template <class T>
std::ostream &operator<<(std::ostream &ostream, const RectangularMatrix<T> &rectangularMatrix)
{
    for (int i = 0; i < rectangularMatrix.m; i++)
    {
        for (int j = 0; j < rectangularMatrix.n; j++)
        {
            ostream << rectangularMatrix.rows->Get(i * rectangularMatrix.n + j) << "  ";
        }
        ostream << std::endl;
    }
    return ostream;
}

template <class T>
std::istream &operator>>(std::istream &istream, RectangularMatrix<T> &rectangularMatrix)
{
    int m = 0, n = 0;
    std::cout << "Введите количество строк матрицы:" << std::endl;
    istream >> m;
    std::cout << "Введите количество столбцов матрицы:" << std::endl;
    istream >> n;
    T value;
    for (int i = 0; i < n; i++)
    {
        std::cout << std::endl
                  << "Введите " << n << " элементов строки номер " << i << ":" << std::endl;
        for (int j = 0; j < m; j++)
        {
            istream >> value;
            rectangularMatrix.rows->Append(value);
        }
    }
    return istream;
}

int main()
{
    ArraySequence <int> *a = new ArraySequence<int>(5, 5);
    ListSequence <ComplexNumber> *b = new ListSequence<ComplexNumber>(ComplexNumber(2.5, 7.5), 3);
    /*int a[2] = {2, 3};
    int b[0];
    LinkedList<int> list1(a, 2);
    LinkedList<int> list2(list1);
    LinkedList<int> list3(b, 0);
    std::cout << "Hello, world!" << std::endl;
    std::cout << list1.head->data << " " << (bool)list1.head->next << " " << (bool)list1.head->prev << " ";
    std::cout << list1.tail->data << " " << (bool)list1.tail->next << " " << (bool)list1.tail->prev << std::endl;
    std::cout << list2.head->data << " " << (bool)list2.head->next << " " << (bool)list2.head->prev << " ";
    std::cout << list2.tail->data << " " << (bool)list2.tail->next << " " << (bool)list2.tail->prev << std::endl;
    std::cout << (bool)list3.head << " " << (bool)list3.tail << std::endl;*/
    return 0;
}