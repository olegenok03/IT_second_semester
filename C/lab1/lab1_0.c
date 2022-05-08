#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <readline/readline.h>

/*
Многочлены
Коэффициенты: int или double
Аргументы: int или double
Функции: +, *, *a, P(a), P1(P2(x))
Базовые функции с числами (int или double): +, *, ^ (на основе *, только для "P(a)")
Нейтральные элементы (числа): 0, 1
Базовые функции со структурами: + (на основе ]), * (на основе ]), ^ (на основе * и ] ), ] (обрезание хвостов)
Нейтральные элементы (структуры): 0, x


FreePol (только коэфы и сам полином, вместе с topol пока чистятся числа - пусть так и остается) - переделать под работу с массивом

Нейтральные структуры пока не нужны
Добавить const
Сделать для дабла
*/

// 0.Readline

char *readline(const char *a) {
        char buf[81] = {0};
        char *res = NULL;
        int len = 0;
        int n = 0;
 
        printf("%s", a);
 
        do {
                n = scanf("%80[^\n]", buf);
                if (n < 0) {
                        if (!res) {
                                return NULL;
                        }
                }
                else if (n > 0) {
                        int chunk_len = strlen(buf);
                        int str_len = len + chunk_len;
                        res = realloc(res, str_len + 1);
                        memcpy(res + len, buf, chunk_len);
                        len = str_len;
                }
                else {
                        scanf("%*c");
                }
        } while (n > 0);
 
        if (len > 0) {
                res[len] = '\0';
        }
        else {
                res = calloc(1, sizeof(char));
        }
 
        return res;
}

// 1.Ring

struct RingInfo
{
	char* type;
	size_t size;
	void (*scan)(void *);
	void (*print)(void *);
	void *(*sum)(void *, void *);
	void *zero;
	void *(*mult)(void *, void *);
	void *one;
	void *(*pow)(void *, int);
};

struct RingInfo *RingCreate(
	char* type,
	size_t size,
	void (*scan)(void *),
	void (*print)(void *),
	void *(*sum)(void *, void *),
	void *zero,
	void *(*mult)(void *, void *),
	void *one,
	void *(*pow)(void *, int))
{
	struct RingInfo *ringInfo = malloc(sizeof(struct RingInfo));
	ringInfo->type = type;
	ringInfo->size = size;
	ringInfo->scan = scan;
	ringInfo->print = print;
	ringInfo->sum = sum;
	ringInfo->zero = zero;
	ringInfo->mult = mult;
	ringInfo->one = one;
	ringInfo->pow = pow;
}

// 2.Polynomial

struct Polynomial
{
	struct RingInfo *ringInfo;
	void *coefficients;
	int degree;
};

struct Data
{
	struct RingInfo *comRingInfo;
	struct Polynomial *polynomials;
	int number;
};

struct Data *DataCreate(
	struct RingInfo *comRingInfo,
	struct Polynomial *polynomials,
	int number)
{
	struct Data *data = malloc(sizeof(struct Data));
	data->comRingInfo = comRingInfo;
	data->polynomials = polynomials;
	data->number = number;
}


struct Polynomial *the_zero;

struct Polynomial *Zero(struct RingInfo *ringInfo)
{
	if (!the_zero)
	{
		the_zero = malloc(sizeof(struct Polynomial));
		the_zero->ringInfo = ringInfo;
		the_zero->coefficients = ringInfo->zero; //прям указатель? внимательнее с этим
		the_zero->degree = 0;
	}
	return the_zero;
}

struct Polynomial *the_x;

struct Polynomial *X(struct RingInfo *ringInfo)
{
	if (!the_x)
	{
		the_x = malloc(sizeof(struct Polynomial));
		the_x->ringInfo = ringInfo;
		the_x->coefficients = malloc(ringInfo->size * 2);
		memcpy(the_x->coefficients, ringInfo->zero, ringInfo->size);
		memcpy(the_x->coefficients + ringInfo->size, ringInfo->one, ringInfo->size);
		the_x->degree = 1;
	}
	return the_x;
}

void Cut(struct Polynomial *p)
{
	int i = p->degree;
	while (i > 0 && memcmp(p->coefficients + i * p->ringInfo->size, p->ringInfo->zero, p->ringInfo->size))
	{
		i--;
	}
	if (i != p->degree)
	{
		p->coefficients = realloc(p->coefficients, p->ringInfo->size * (i + 1));
		p->degree = i;
	}
}

void CpyPol (struct Polynomial *to, struct Polynomial *from)
{
	to->ringInfo = from->ringInfo;
	to->degree = from->degree;
	to->coefficients = realloc(to->coefficients, to->ringInfo->size * (to->degree + 1));
	memcpy(to->coefficients, from->coefficients, to->ringInfo->size * (to->degree + 1));
}

void FreePol (struct Polynomial *p)
{
	free(p->coefficients);
	free(p);
}

struct Polynomial *Sum(struct Polynomial *p1, struct Polynomial *p2) //подразумеваем, что одной природы
{
	struct Polynomial *res = malloc(sizeof(struct Polynomial));
	res->ringInfo = p1->ringInfo;
	res->degree = p1->degree;
	size_t newSize = sizeof(p1->coefficients);
	if (p2->degree > res->degree)
	{
		res->degree = p2->degree;
		newSize = sizeof(p2->coefficients);
	}
	void *buf = NULL;
	res->coefficients = malloc(newSize);
	for (size_t i = 0; i < newSize; i += p1->ringInfo->size)
	{
		buf = p1->ringInfo->sum(p1->coefficients + i, p1->coefficients + i);
		memcpy(res->coefficients + i, buf, p1->ringInfo->size);
		free(buf);
	}
	Cut(res);
	return res;
}

struct Polynomial *Mult(struct Polynomial *p1, struct Polynomial *p2) //подразумеваем, что одной природы
{
	struct Polynomial *res = malloc(sizeof(struct Polynomial));
	res->ringInfo = p1->ringInfo;
	res->degree = p1->degree + p2->degree;
	size_t size = p1->ringInfo->size;
	size_t newSize = (res->degree + 1) * size;
	void *buf1 = NULL;
	void *buf2 = NULL;
	res->coefficients = malloc(newSize);
	for (int i = 0; i <= res->degree; i++)
	{
		memcpy(res->coefficients + i * size, p1->ringInfo->zero, size);
	}
	for (int i = 0; i <= p1->degree; i++)
	{
		for (int j = 0; j <= p2->degree; j++)
		{
			buf1 = p1->ringInfo->mult(p1->coefficients + i * size, p1->coefficients + j * size);
			buf2 = p1->ringInfo->sum(buf1, res->coefficients + (i + j) * size);
			memcpy(res->coefficients + (i + j) * size, buf2, size);
			free(buf1);
			free(buf2);
		}
	}
	Cut(res);
	return res;
}

struct Polynomial *ToPol(void *a, struct RingInfo *ringInfo)
{ //подразумеваем, что одной природы
	struct Polynomial *res = malloc(sizeof(struct Polynomial));
	res->ringInfo = ringInfo;
	res->coefficients = a; //прям указатель? внимательнее с этим
	res->degree = 0;
	return res;
}

struct Polynomial *Pow(struct Polynomial *p, int power)
{
	if (!power)
	{
		return ToPol(p->ringInfo->one, p->ringInfo);
	}
	struct Polynomial *res = malloc(sizeof(struct Polynomial));
	struct Polynomial *buf = malloc(sizeof(struct Polynomial));
	CpyPol(res, p);
	for (int i = 1; i < power; i++)
	{
		CpyPol(buf, res);
		FreePol(res);
		res = Mult(buf, p);
		FreePol(buf);
	}
	return res;
}

struct Polynomial *Comp(struct Polynomial *p1, struct Polynomial *p2)
{ //мб сделать проверку на x?
	struct Polynomial *res = malloc(sizeof(struct Polynomial));
	res->ringInfo = p1->ringInfo;
	res->degree = p1->degree * p2->degree;
	size_t size = res->ringInfo->size;
	struct Polynomial *buf1 = malloc(sizeof(struct Polynomial));
	struct Polynomial *buf2 = malloc(sizeof(struct Polynomial));
	struct Polynomial *buf3 = malloc(sizeof(struct Polynomial));
	struct Polynomial *buf4 = malloc(sizeof(struct Polynomial));
	for (int i = 0; i <= res->degree; i++)
	{
		memcpy(res->coefficients + i * size, res->ringInfo->zero, size);
	}
	for (int i = 0; i <= p1->degree; i++)
	{
		if (memcmp(p1->coefficients + i * size, p1->ringInfo->zero, size))
		{
			buf1 = ToPol(p1->coefficients + i * size, p1->ringInfo);
			for (int j = 0; j <= p2->degree; j++)
			{
				if (memcmp(p2->coefficients + j * size, p2->ringInfo->zero, size))
				{
					buf2 = Pow(p2, i);
					buf3 = Mult(buf1, buf2);
					buf4 = Sum(res, buf3);
					FreePol(res);
					CpyPol(res, buf4);
					FreePol(buf2);
					FreePol(buf3);
					FreePol(buf4);
				}
			}
			FreePol(buf1);
		}
	}
	Cut(res);
	return res;
}

struct Polynomial *Input (struct RingInfo *ringInfo)
{
	struct Polynomial *res = malloc(sizeof(struct Polynomial));
	res->ringInfo = ringInfo;
	int length = 0;
	bool err = 0;
	char *input = NULL;
	do {
			input = readline("Enter the degree of the polynomial:\n");
			length = strlen(input);
			for(int i = 0; i < length; i++) {
				if((input[i] > '9') || (input[i] < '0')){
					err = 1;
					printf("Incorrect input\n");
					break;
				}
			}
	} while (err);
	res->degree = atoi(input);
	res->coefficients = malloc((res->degree + 1) * ringInfo->size);
	for(int i = 0; i <= res->degree; i++) {
		ringInfo->scan(res->coefficients + i * ringInfo->size); //здесь пока без фильтрации ввода
	}
	Cut(res);
	return res;
}

void Output(struct Polynomial *output) {
	printf("The degree of the polynomial is %d\n", output->degree);
	printf("The coefficients are %s:\n", output->ringInfo->type);
	for(int i = 0; i <= output->degree; i++) {
		output->ringInfo->print(output->coefficients + i * output->ringInfo->size);
		if(i != output->degree) {
			printf(" ");
		}
	}
	printf("\n");
}

// 3.int

void scanInt(void *a)
{
	int *ia = (int *)a;
	scanf("%d", ia);
}

void printInt(void *a)
{
	int *ia = (int *)a;
	printf("%d", *ia);
}

void *sumInt(void *a1, void *a2)
{
	int *ia1 = (int *)a1;
	int *ia2 = (int *)a2;
	int *res = malloc(sizeof(int));
	*res = (*ia1) + (*ia2);
	return (void *)res;
}

void *multInt(void *a1, void *a2)
{
	int *ia1 = (int *)a1;
	int *ia2 = (int *)a2;
	int *res = malloc(sizeof(int));
	*res = (*ia1) * (*ia2);
	return (void *)res;
}

void *powInt(void *a1, int n)
{
	int *ia1 = (int *)a1;
	int *res = malloc(sizeof(int));
	*res = 1;
	for (int i = 0; i < n; i++)
	{
		*res *= *ia1;
	}
	return (void *)res;
}

void *zeroInt;

void *ZeroInt()
{
	if (!zeroInt)
	{
		zeroInt = malloc(sizeof(int));
		int *a = (int *)zeroInt;
		*a = 0;
	}
	return zeroInt;
}

void *oneInt;

void *OneInt()
{
	if (!oneInt)
	{
		oneInt = malloc(sizeof(int));
		int *a = (int *)oneInt;
		*a = 0;
	}
	return oneInt;
}

// 4.double

int main()
{
	struct RingInfo *ringInt = Create("integers", sizeof(int), &scanInt, &printInt, &sumInt, ZeroInt(), &multInt, OneInt(), &powInt);
	
}