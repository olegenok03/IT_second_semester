#include <iostream>

class example
{
public:
    example(int a)
    {
        z = new int(a);
    }
    example(const example &x) {
        z = new int(*x.z);
    }
    ~example()
    {
        std::cout << "Деструктор ex " << *z << std::endl;
        delete z;
    }

    example &operator=(example &x)
    {
        example temp = example(*x.z);
        Swap(temp);
        return *this;
    }
    void Swap(example &x)
    {
        int *buf = z;
        z = x.z;
        x.z = buf;
    }
    int *z;
};

/*class example2 {
    public:
        example2(const example &x) {
            std::cout << "Копирующий конструктор ex2 " << *x.z + 1<<std::endl;
            ex = new example(x);
        }
        example2 *returnExPointer() {
            std::cout << "Функция" << std::endl;
            return new example2(example(*ex));
        }
        example2 returnEx(example2 *t) {
            std::cout << "Функция2" << std::endl;
            return example2(*ex);
        }
        ~example2() {
            std::cout << "Деструктор ex2 " <<*ex->z<<std::endl;
            delete ex;
        }
        example *ex;
};*/

int main()
{
    example x1(1);
    example x2 = x1;
}