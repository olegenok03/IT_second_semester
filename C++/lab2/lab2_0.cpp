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
#include <stdbool.h>
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

    return ostream << "(" << x.real << ",  " << x.imaginary << ")";
}

std::istream &operator>>(std::istream &istream, ComplexNumber &x)
{
    std::cout << "Введите действительную и мнимую части числа через пробел: ";
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
        //delete subList;
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
class RectangularMatrix;

template <class T>
std::ostream &operator<<(std::ostream &ostream, const RectangularMatrix<T> &rectangularMatrix);
template <class T>
std::istream &operator>>(std::istream &istream, RectangularMatrix<T> &rectangularMatrix);
template <class T>
const RectangularMatrix<T> operator+(RectangularMatrix<T> &x1, RectangularMatrix<T> &x2);
template <class T>
const RectangularMatrix<T> operator*(RectangularMatrix<T> &x, T coefficient);

template <class T>
class RectangularMatrix
{
    friend std::ostream &operator<< <T>(std::ostream &ostream, const RectangularMatrix<T> &rectangularMatrix);
    friend std::istream &operator>><T>(std::istream &istream, RectangularMatrix<T> &rectangularMatrix);
    friend const RectangularMatrix<T> operator+<T>(RectangularMatrix<T> &x1, RectangularMatrix<T> &x2);
    friend const RectangularMatrix<T> operator*<T>(RectangularMatrix<T> &x, T coefficient);

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
        m = rectangularMatrix.m;
        n = rectangularMatrix.n;
    }

    int GetHeight()
    {
        return m;
    }

    int GetWidth()
    {
        return n;
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

    void ColumnMultiple(int index, T coefficient)
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

    void ColumnLinearTransformation(int fromIndex, T coefficient, int toIndex)
    {
        for (int i = 0; i < m; i++)
        {
            rows->LinearTransformation(fromIndex + i * n, coefficient, toIndex + i * n);
        }
    }

    RectangularMatrix<T> &operator=(const RectangularMatrix<T> &rectangularMatrix)
    {
        if (rows)
        {
            delete rows;
        }
        rows = rectangularMatrix.rows->Copy();
        m = rectangularMatrix.m;
        n = rectangularMatrix.n;
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
    RectangularMatrix<T> sumMatrix = RectangularMatrix<T>(x1);
    *sumMatrix.rows += *x2.rows;
    return sumMatrix;
}

template <class T>
const RectangularMatrix<T> operator*(RectangularMatrix<T> &x, T coefficient)
{
    RectangularMatrix<T> sumMatrix = RectangularMatrix<T>(x);
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
    rectangularMatrix.m = m;
    rectangularMatrix.n = n;
    T value;
    for (int i = 0; i < m; i++)
    {
        std::cout << "Введите элементы строки номер " << i + 1 << " в количестве " << n << ":" << std::endl;
        for (int j = 0; j < n; j++)
        {
            istream >> value;
            rectangularMatrix.rows->Append(value);
        }
    }
    return istream;
}

int EnterInt(int minInt, int maxInt)
{
    int number = 0;
    bool cond1 = 0, cond2 = 0, error = 0;
    do
    {
        error = 0;
        std::cin >> number;
        cond1 = number < minInt;
        cond2 = minInt <= maxInt && number > maxInt;
        if (cond1 || cond2)
        {
            std::cout << "Значение введено некорректно" << std::endl;
            error = 1;
        }
    } while (error);
    return number;
}

void ASIntCheck()
{
    int n1 = 0, n2 = 0;
    bool error = 0;

    std::cout << "  ~ Проверка работы ArraySequence <int> ~" << std::endl;

    std::cout << "Введите количество элементов последовательности (целое число не меньше 1):" << std::endl;
    n1 = EnterInt(1, 0);
    Sequence<int> *a1 = new ArraySequence<int>(n1);
    std::cout << "Введите целые числа в количестве " << n1 << ":" << std::endl;
    std::cin >> *a1;
    std::cout << std::endl;

    std::cout << "Введите начальный индекс подпоследовательности (целое число от 0 до " << a1->GetLength() - 1 << "):" << std::endl;
    n1 = EnterInt(0, a1->GetLength() - 1);
    std::cout << "Введите конечный индекс подпоследовательности (целое число от " << n1 << " до " << a1->GetLength() - 1 << "):" << std::endl;
    n2 = EnterInt(n1, a1->GetLength() - 1);
    Sequence<int> *a2 = a1->GetSubsequence(n1, n2 + 1);
    std::cout << std::endl;

    std::cout << "Полученные последовательности:" << std::endl;
    std::cout << *a1 << std::endl;
    std::cout << *a2 << std::endl;

    std::cout << "Проверка методов для последовательности 2" << std::endl;
    std::cout << "Длина: ";
    std::cout << a2->GetLength() << std::endl;
    std::cout << "Первый элемент: ";
    std::cout << a2->GetFirst() << std::endl;
    std::cout << "Последний элемент: ";
    std::cout << a2->GetLast() << std::endl;
    std::cout << "Введите индекс выводимого элемента:" << std::endl;
    n1 = EnterInt(0, a2->GetLength() - 1);
    std::cout << "Элемент с индексом " << n1 << ": ";
    std::cout << a2->Get(n1) << std::endl;

    std::cout << "Введите элемент для вставки в конец последовательности:" << std::endl;
    std::cin >> n1;
    a2->Append(n1);
    std::cout << "Полученная последовательность:" << std::endl;
    std::cout << *a2 << std::endl;

    std::cout << "Введите элемент для вставки в начало последовательности:" << std::endl;
    std::cin >> n1;
    a2->Prepend(n1);
    std::cout << "Полученная последовательность:" << std::endl;
    std::cout << *a2 << std::endl;

    std::cout << "Введите элемент для вставки в последовательность по индексу:" << std::endl;
    std::cin >> n2;
    std::cout << "Введите индекс:" << std::endl;
    n1 = EnterInt(0, a2->GetLength());
    a2->InsertAt(n1, n2);
    std::cout << "Полученная последовательность:" << std::endl;
    std::cout << *a2 << std::endl;

    Sequence<int> *a3 = a1->Concat(a2);

    std::cout << "Конкатенация двух последовательностей:" << std::endl;
    std::cout << *a3 << std::endl;
    delete a1;
    delete a2;
    delete a3;
}

void LSDoubleCheck()
{
    int n1 = 0, n2 = 0;
    double value;
    bool error = 0;

    std::cout << "  ~ Проверка работы ListSequence <double> ~" << std::endl;

    std::cout << "Введите количество элементов последовательности (целое число не меньше 1):" << std::endl;
    n1 = EnterInt(1, 0);
    Sequence<double> *a1 = new ListSequence<double>(0.0, n1);
    std::cout << "Введите вещественные числа в количестве " << n1 << ":" << std::endl;
    std::cin >> *a1;
    std::cout << std::endl;

    std::cout << "Введите начальный индекс подпоследовательности (целое число от 0 до " << a1->GetLength() - 1 << "):" << std::endl;
    n1 = EnterInt(0, a1->GetLength() - 1);
    std::cout << "Введите конечный индекс подпоследовательности (целое число от " << n1 << " до " << a1->GetLength() - 1 << "):" << std::endl;
    n2 = EnterInt(n1, a1->GetLength() - 1);
    Sequence<double> *a2 = a1->GetSubsequence(n1, n2 + 1);
    std::cout << std::endl;

    std::cout << "Полученные последовательности:" << std::endl;
    std::cout << *a1 << std::endl;
    std::cout << *a2 << std::endl;

    std::cout << "Проверка методов для последовательности 2" << std::endl;
    std::cout << "Длина: ";
    std::cout << a2->GetLength() << std::endl;
    std::cout << "Первый элемент: ";
    std::cout << a2->GetFirst() << std::endl;
    std::cout << "Последний элемент: ";
    std::cout << a2->GetLast() << std::endl;
    std::cout << "Введите индекс выводимого элемента:" << std::endl;
    n1 = EnterInt(0, a2->GetLength() - 1);
    std::cout << "Элемент с индексом " << n1 << ": ";
    std::cout << a2->Get(n1) << std::endl;

    std::cout << "Введите элемент для вставки в конец последовательности:" << std::endl;
    std::cin >> value;
    a2->Append(value);
    std::cout << "Полученная последовательность:" << std::endl;
    std::cout << *a2 << std::endl;

    std::cout << "Введите элемент для вставки в начало последовательности:" << std::endl;
    std::cin >> value;
    a2->Prepend(value);
    std::cout << "Полученная последовательность:" << std::endl;
    std::cout << *a2 << std::endl;

    std::cout << "Введите элемент для вставки в последовательность по индексу:" << std::endl;
    std::cin >> value;
    std::cout << "Введите индекс:" << std::endl;
    n1 = EnterInt(0, a2->GetLength());
    a2->InsertAt(n1, value);
    std::cout << "Полученная последовательность:" << std::endl;
    std::cout << *a2 << std::endl;

    Sequence<double> *a3 = a1->Concat(a2);

    std::cout << "Конкатенация двух последовательностей:" << std::endl;
    std::cout << *a3 << std::endl;
    delete a1;
    delete a2;
    delete a3;
}

void RMComplexCheck()
{
    int n1 = 0, n2 = 0;
    bool error = 0;
    ComplexNumber coefficient = ComplexNumber();
    std::cout << "  ~ Проверка работы  RectangularMatrix <ComplexNumber>, построенной на ArraySequence ~" << std::endl;

    std::cout << "Ввод первой матрицы" << std::endl;
    RectangularMatrix<ComplexNumber> *a1 = new RectangularMatrix<ComplexNumber>(new ArraySequence<ComplexNumber>());
    std::cin >> *a1;
    std::cout << std::endl;

    std::cout << "Ввод второй матрицы" << std::endl;
    RectangularMatrix<ComplexNumber> *a2 = new RectangularMatrix<ComplexNumber>(new ArraySequence<ComplexNumber>());
    std::cin >> *a2;
    std::cout << std::endl;

    std::cout << "Полученные матрицы:" << std::endl;
    std::cout << *a1 << std::endl;
    std::cout << *a2 << std::endl;

    std::cout << "      Проверка методов матрицы 1" << std::endl;

    std::cout << "Высота: ";
    std::cout << a1->GetHeight() << std::endl;
    std::cout << "Ширина: ";
    std::cout << a1->GetWidth() << std::endl;

    std::cout << "  -Перестановка столбцов-" << std::endl;
    std::cout << "Введите индекс первого столбца:" << std::endl;
    n1 = EnterInt(0, a1->GetWidth() - 1);
    std::cout << "Введите индекс второго столбца:" << std::endl;
    n2 = EnterInt(0, a1->GetWidth() - 1);
    a1->ColumnPermutate(n1, n2);
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << *a1 << std::endl;

    std::cout << "  -Умножение строки на число-" << std::endl;
    std::cout << "Введите индекс строки:" << std::endl;
    n1 = EnterInt(0, a1->GetHeight() - 1);
    std::cout << "Введите коэффициент:" << std::endl;
    std::cin >> coefficient;
    a1->RowMultiple(n1, coefficient);
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << *a1 << std::endl;

    std::cout << "  -Прибавление к столбцу другого столбца, умноженного на число-" << std::endl;
    std::cout << "Введите индекс первого столбца:" << std::endl;
    n1 = EnterInt(0, a1->GetWidth() - 1);
    std::cout << "Введите индекс второго столбца:" << std::endl;
    n2 = EnterInt(0, a1->GetWidth() - 1);
    std::cout << "Введите коэффициент:" << std::endl;
    std::cin >> coefficient;
    a1->ColumnLinearTransformation(n2, coefficient, n1);
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << *a1 << std::endl;

    std::cout << "      Проверка операций над матрицей 2" << std::endl;

    std::cout << "  -Умножение матрицы на число-" << std::endl;
    std::cout << "Введите коэффициент:" << std::endl;
    std::cin >> coefficient;
    RectangularMatrix<ComplexNumber> a3 = *a2 * coefficient;
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << a3 << std::endl;

    std::cout << "  -Сложение матриц-" << std::endl;
    if ((a1->GetHeight() == a2->GetHeight()) && (a1->GetWidth() == a2->GetWidth()))
        a3 = *a1 + *a2;
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << a3 << std::endl;

    delete a1;
    delete a2;
}

int main()
{
    //ASIntCheck();
    LSDoubleCheck();
    //RMComplexCheck();
    return 0;
}