#ifndef TEST
#define TEST

#include <iostream>
#include <stdbool.h>
#include <cstring>

#include "ComplexNumber.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "ListSequence.h"
#include "RectangularMatrix.h"
#include "QuadraticMatrix.h"
#include "TriangularMatrix.h"
#include "DiagonalMatrix.h"
#include "Vector.h"

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

    std::cout << "  ~ Проверка работы ArraySequence<int> ~" << std::endl;

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

    std::cout << "  ~ Проверка работы ListSequence<double> ~" << std::endl;

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
    ComplexNumber coefficient = ComplexNumber();
    std::cout << "  ~ Проверка работы RectangularMatrix<ComplexNumber>, построенной на ArraySequence ~" << std::endl;

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
    {
        a3 = *a1 + *a2;
        std::cout << "Полученная матрица:" << std::endl;
        std::cout << a3 << std::endl;
    }
    else
    {
        std::cout << "Операция сложения не определена для матриц разного размера:" << std::endl;
    }

    delete a1;
    delete a2;
}

void QMIntCheck()
{
    int n1 = 0, n2 = 0, coefficient = 0;
    std::cout << "  ~ Проверка работы QuadraticMatrix<int>, построенной на ListSequence ~" << std::endl;

    std::cout << "Ввод первой матрицы" << std::endl;
    QuadraticMatrix<int> *a1 = new QuadraticMatrix<int>(new ListSequence<int>());
    std::cin >> *a1;
    std::cout << std::endl;

    std::cout << "Ввод второй матрицы" << std::endl;
    QuadraticMatrix<int> *a2 = new QuadraticMatrix<int>(new ListSequence<int>());
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
    QuadraticMatrix<int> a3 = *a2 * coefficient;
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << a3 << std::endl;

    std::cout << "  -Сложение матриц-" << std::endl;
    if (a1->GetHeight() == a2->GetHeight())
    {
        a3 = *a1 + *a2;
        std::cout << "Полученная матрица:" << std::endl;
        std::cout << a3 << std::endl;
    }
    else
    {
        std::cout << "Операция сложения не определена для матриц разного размера:" << std::endl;
    }

    delete a1;
    delete a2;
}

void TMIntCheck()
{
    int n1 = 0, n2 = 0, coefficient = 0;
    std::cout << "  ~ Проверка работы TriangularMatrix<int>, построенной на ListSequence ~" << std::endl;

    std::cout << "Ввод первой матрицы" << std::endl;
    TriangularMatrix<int> *a1 = new TriangularMatrix<int>(new ListSequence<int>());
    std::cin >> *a1;
    std::cout << std::endl;

    std::cout << "Ввод второй матрицы" << std::endl;
    TriangularMatrix<int> *a2 = new TriangularMatrix<int>(new ListSequence<int>());
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
    std::cout << "Введите индекс второго столбца (должен быть не больше индекса первого):" << std::endl;
    n2 = EnterInt(0, n1);
    std::cout << "Введите коэффициент:" << std::endl;
    std::cin >> coefficient;
    a1->ColumnLinearTransformation(n2, coefficient, n1);
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << *a1 << std::endl;

    std::cout << "      Проверка операций над матрицей 2" << std::endl;

    std::cout << "  -Умножение матрицы на число-" << std::endl;
    std::cout << "Введите коэффициент:" << std::endl;
    std::cin >> coefficient;
    TriangularMatrix<int> a3 = *a2 * coefficient;
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << a3 << std::endl;

    std::cout << "  -Сложение матриц-" << std::endl;
    if (a1->GetHeight() == a2->GetHeight())
    {
        a3 = *a1 + *a2;
        std::cout << "Полученная матрица:" << std::endl;
        std::cout << a3 << std::endl;
    }
    else
    {
        std::cout << "Операция сложения не определена для матриц разного размера:" << std::endl;
    }

    delete a1;
    delete a2;
}

void DMIntCheck()
{
    int n1 = 0, n2 = 0, coefficient = 0;
    std::cout << "  ~ Проверка работы DiagonalMatrix<int>, построенной на ArraySequence ~" << std::endl;

    std::cout << "Ввод первой матрицы" << std::endl;
    DiagonalMatrix<int> *a1 = new DiagonalMatrix<int>(new ArraySequence<int>());
    std::cin >> *a1;
    std::cout << std::endl;

    std::cout << "Ввод второй матрицы" << std::endl;
    DiagonalMatrix<int> *a2 = new DiagonalMatrix<int>(new ArraySequence<int>());
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

    std::cout << "  -Умножение строки на число-" << std::endl;
    std::cout << "Введите индекс строки:" << std::endl;
    n1 = EnterInt(0, a1->GetHeight() - 1);
    std::cout << "Введите коэффициент:" << std::endl;
    std::cin >> coefficient;
    a1->RowMultiple(n1, coefficient);
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << *a1 << std::endl;

    std::cout << "      Проверка операций над матрицей 2" << std::endl;

    std::cout << "  -Умножение матрицы на число-" << std::endl;
    std::cout << "Введите коэффициент:" << std::endl;
    std::cin >> coefficient;
    DiagonalMatrix<int> a3 = *a2 * coefficient;
    std::cout << "Полученная матрица:" << std::endl;
    std::cout << a3 << std::endl;

    std::cout << "  -Сложение матриц-" << std::endl;
    if (a1->GetHeight() == a2->GetHeight())
    {
        a3 = *a1 + *a2;
        std::cout << "Полученная матрица:" << std::endl;
        std::cout << a3 << std::endl;
    }
    else
    {
        std::cout << "Операция сложения не определена для матриц разного размера:" << std::endl;
    }

    delete a1;
    delete a2;
}

void VectorIntCheck()
{
    int n1 = 0, n2 = 0, coefficient = 0;
    std::cout << "  ~ Проверка работы Vector<int>, построенного на ArraySequence ~" << std::endl;

    std::cout << "Ввод первого вектора" << std::endl;
    Vector<int> *a1 = new Vector<int>(new ArraySequence<int>());
    std::cin >> *a1;
    std::cout << std::endl;

    std::cout << "Ввод второго вектора" << std::endl;
    Vector<int> *a2 = new Vector<int>(new ArraySequence<int>());
    std::cin >> *a2;
    std::cout << std::endl;

    std::cout << "Полученные векторы:" << std::endl;
    std::cout << *a1 << std::endl;
    std::cout << *a2 << std::endl;

    std::cout << "      Проверка операций над векторами" << std::endl;

    std::cout << "Размерность первого вектора: ";
    std::cout << a1->GetDimension() << std::endl;
    std::cout << "Размерность второго вектора: ";
    std::cout << a2->GetDimension() << std::endl;

    std::cout << "  -Умножение первого вектора на число-" << std::endl;
    std::cout << "Введите коэффициент:" << std::endl;
    std::cin >> coefficient;
    Vector<int> a3 = *a1 * coefficient;
    std::cout << "Полученный вектор:" << std::endl;
    std::cout << a3 << std::endl;

    std::cout << "  -Сложение векторов-" << std::endl;
    if (a1->GetDimension() == a2->GetDimension())
    {
        a3 = *a1 + *a2;
        std::cout << "Полученный вектор:" << std::endl;
        std::cout << a3 << std::endl;
    }
    else
    {
        std::cout << "Операция сложения не определена для векторов разной размерности:" << std::endl;
    }

    delete a1;
    delete a2;
}

#endif