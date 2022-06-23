//выделение памяти по степеням двойки???
//диагональная матрица некорректно работает с комплексными числами, т.к. нельзя определить нули для всех T

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
#include "Test.h"

int main()
{
    // ASIntCheck();
    // LSDoubleCheck();
    // RMComplexCheck();
    // QMIntCheck();
    // TMIntCheck();
    //DMIntCheck();
    VectorIntCheck();

    return 0;
}