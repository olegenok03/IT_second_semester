#ifndef COMPLEXNUMBER
#define COMPLEXNUMBER

#include <iostream>

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

#endif