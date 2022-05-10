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

char *readline(const char *a)
{
	char buf[81] = {0};
	char *res = NULL;
	int len = 0;
	int n = 0;

	printf("%s", a);

	do
	{
		n = scanf("%80[^\n]", buf);
		if (n < 0)
		{
			if (!res)
			{
				return NULL;
			}
		}
		else if (n > 0)
		{
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res, str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		}
		else
		{
			scanf("%*c");
		}
	} while (n > 0);

	if (len > 0)
	{
		res[len] = '\0';
	}
	else
	{
		res = calloc(1, sizeof(char));
	}

	return res;
}

// 5.Interface

int DialogMenu(int intNumber, int doubleNumber)
{
	printf("	||Operations with polynomials||\n");
	printf("Wellcome to the main menu. Choose option by entering its number:\n");
	printf("1.Enter new polynomial\n");
	int i = 2;
	if (intNumber || doubleNumber)
	{
		printf("2.Print the polynomials\n", i++);
	}
	if ((intNumber >= 2) || (doubleNumber >= 2))
	{
		printf("3.Sum the polynomials\n", i++);
		printf("4.Multiply the polynomials\n", i++);
	}
	if (intNumber || doubleNumber)
	{
		printf("%d.Multiply the polynomial with a number\n", i++);
		printf("%d.Evaluate the polynomial\n", i++);
	}
	if ((intNumber >= 2) || (doubleNumber >= 2))
	{
		printf("%d.Compose the polynomials\n", i++);
	}
	if (intNumber || doubleNumber)
	{
		printf("%d.Delete the polynomial\n", i++);
	}
	printf("%d.Exit\n\n", i);
	char *choiceChar = readline("");
	int choice = atoi(choiceChar);
	free(choiceChar);
	if (choice != i)
	{
		printf("\n");
	}
	if (i == 2)
	{
		switch (choice)
		{
		case 1:
			return 1;
		case 2:
			return 9;
		default:
			return 0;
		}
	}
	else if (i == 6)
	{
		switch (choice)
		{
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 5;
		case 4:
			return 6;
		case 5:
			return 8;
		case 6:
			return 9;
		default:
			return 0;
		}
	}
	else if (i == 9)
	{
		return choice;
	}
}

bool choiceMessage(char *message, char *option1, char *option2)
{
	char *input = NULL;
	while (1)
	{
		printf("%s [%s/%s]\n", message, option1, option2);
		input = readline("");
		if (!strcmp(input, option1))
		{
			return 1;
		}
		else if (!strcmp(input, option2))
		{
			return 0;
		}
		else
		{
			printf("Error: incorrect input\n");
		}
	}
}

// 1.Ring

struct RingInfo
{
	char *type;
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
	char *type,
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

void RingDelete(struct RingInfo *ringInfo)
{
	free(ringInfo->zero);
	free(ringInfo->one);
	free(ringInfo);
}

// 2.Polynomial
// main
struct Polynomial
{
	struct RingInfo *ringInfo;
	void *coefficients;
	int degree;
};

struct Polynomial *PolCreate (
	struct RingInfo *ringInfo,
	void *coefficients,
	int degree
)
{
	struct Polynomial *res = malloc(sizeof(struct Polynomial));
	res->ringInfo = ringInfo;
	res->coefficients = coefficients;
	res->degree = degree;
	return res;
}

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

void Cut(struct Polynomial *p)
{
	int i = p->degree;
	while (i > 0 && !memcmp(p->coefficients + i * p->ringInfo->size, p->ringInfo->zero, p->ringInfo->size))
	{
		i--;
	}
	if (i != p->degree)
	{
		p->coefficients = realloc(p->coefficients, p->ringInfo->size * (i + 1));
		p->degree = i;
	}
}

void DataDelete(struct Data *data)
{
	for (int i = 0; i < data->number; i++)
	{
		free((data->polynomials + i)->coefficients);
	}
	free(data->polynomials);
	free(data);
}

void DataRealloc(struct Data *data)
{
	data->number++;
	data->polynomials = realloc(data->polynomials, data->number * sizeof(struct Polynomial));
}

void CpyPol(struct Polynomial *to, struct Polynomial *from) //нужен для перенесения основных резов операций
{
	to->ringInfo = from->ringInfo;
	to->degree = from->degree;
	if(to->coefficients)
	{
		free(to->coefficients);
	}
	to->coefficients = malloc(to->ringInfo->size * (to->degree + 1));
	memcpy(to->coefficients, from->coefficients, to->ringInfo->size * (to->degree + 1));
}

void FreePol(struct Polynomial *p) //нужен для topol, для удаления основных и побочных резов операций
{
	free(p->coefficients);
	free(p);
}

void PolInData(struct Data *data)
{
	DataRealloc(data);
	struct Polynomial *newPol = data->polynomials + data->number - 1;
	struct RingInfo *ringInfo = data->comRingInfo;
	newPol->ringInfo = ringInfo;
	int length = 0;
	bool err = 0;
	char *input = NULL;
	do
	{
		err = 0;
		input = readline("Enter the degree of the polynomial:\n");
		length = strlen(input);
		for (int i = 0; i < length; i++)
		{
			if ((input[i] > '9') || (input[i] < '0'))
			{
				err = 1;
				printf("Incorrect input\n");
				break;
			}
		}
	} while (err);
	newPol->degree = atoi(input);
	free(input);
	newPol->coefficients = malloc((newPol->degree + 1) * ringInfo->size);
	printf("Enter the coefficients (from the smallest degree to the biggest)\n");
	for (int i = 0; i <= newPol->degree; i++)
	{
		ringInfo->scan(newPol->coefficients + i * ringInfo->size); //здесь пока без фильтрации ввода
	}
	Cut(newPol);
}

void ResInData(struct Polynomial *res, struct Data *data)
{
	if (choiceMessage(
			"Do you want to write the result in data?",
			"yes",
			"no"))
	{
		DataRealloc(data);
		CpyPol(data->polynomials + data->number - 1, res);
	}
	FreePol(res);
}

void PolOutput(struct Polynomial *output)
{
	printf("The degree of the polynomial is %d\n", output->degree);
	printf("The coefficients are %s:\n(", output->ringInfo->type);
	for (int i = 0; i <= output->degree; i++)
	{
		output->ringInfo->print(output->coefficients + i * output->ringInfo->size);
		if (i != output->degree)
		{
			printf(", ");
		}
	}
	printf(")\n");
}

void DataOutput(struct Data *output)
{
	printf("The number of polynomials, which coefficients are %s, is %d\n", output->comRingInfo->type, output->number);
	printf("The polynomials are:\n\n");
	for (int i = 0; i < output->number; i++)
	{
		printf("%d. ", i + 1);
		PolOutput(output->polynomials + i);
		printf("\n");
	}
	printf("\n");
}

struct Polynomial *PolChoose(struct Data *data, int *number)
{
	printf("Choose the polynomial from the list below by entering its number.\n\n");
	DataOutput(data);
	char *input = NULL;
	int ans = 0;
	while(1)
	{
		input = readline("");
		ans = atoi(input);
		if((ans > 0) && (ans <= data->number))
		{
			break;
		}
		printf("Error: incorrect input\n");
	}
	if(number)
	{
		*number = ans;
	}
	return data->polynomials + ans - 1;
}

void DelPolFromData(struct Data *data)
{
	int number = 0;
	struct Polynomial *delPol = PolChoose(data, &number);
	free(delPol->coefficients);
	memmove(delPol, delPol + 1, (data->number - number) * sizeof(struct Polynomial));
	data->number--;
	data->polynomials = realloc(data->polynomials, data->number * sizeof(struct Polynomial));
}

/*
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
*/

//operations

struct Polynomial *Sum(struct Polynomial *p1, struct Polynomial *p2) //подразумеваем, что одной природы
{
	struct Polynomial *res = PolCreate(p1->ringInfo, NULL, p1->degree);
	size_t newSize = p1->ringInfo->size * (p1->degree + 1);
	if (p2->degree > res->degree)
	{
		res->degree = p2->degree;
		newSize = p2->ringInfo->size * (p2->degree + 1);
	}
	void *buf = NULL;
	res->coefficients = malloc(newSize);
	for (size_t i = 0; i < newSize; i += res->ringInfo->size)
	{
		if (i < p1->ringInfo->size * (p1->degree + 1))
		{
			if (i < p2->ringInfo->size * (p2->degree + 1))
			{
				buf = p1->ringInfo->sum(p1->coefficients + i, p2->coefficients + i);
				memcpy(res->coefficients + i, buf, res->ringInfo->size);
				free(buf);
			}
			else
			{
				memcpy(res->coefficients + i, p1->coefficients + i, res->ringInfo->size);
			}
		}
		else
		{
			memcpy(res->coefficients + i, p2->coefficients + i, res->ringInfo->size);
		}
	}
	Cut(res);
	return res;
}

struct Polynomial *Mult(struct Polynomial *p1, struct Polynomial *p2) //подразумеваем, что одной природы
{
	struct Polynomial *res = PolCreate(p1->ringInfo, NULL, p1->degree + p2->degree);
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
			buf1 = p1->ringInfo->mult(p1->coefficients + i * size, p2->coefficients + j * size);
			buf2 = p1->ringInfo->sum(buf1, res->coefficients + (i + j) * size);
			memcpy(res->coefficients + (i + j) * size, buf2, size);
			free(buf1);
			free(buf2);
		}
	}
	Cut(res);
	return res;
}

struct Polynomial *ToPol(void *a, struct RingInfo *ringInfo) //подразумеваем, что одной природы
{
	return PolCreate(ringInfo, a, 0);
}

struct Polynomial *Pow(struct Polynomial *p, int power)
{
	if (!power)
	{
		void *newOne = malloc(p->ringInfo->size);
		memcpy(newOne, p->ringInfo->one, p->ringInfo->size);
		return ToPol(newOne, p->ringInfo);
	}
	struct Polynomial *res = PolCreate(NULL, NULL, 0);
	struct Polynomial *buf = PolCreate(NULL, NULL, 0);
	CpyPol(res, p);
	for (int i = 1; i < power; i++)
	{
		CpyPol(buf, res);
		FreePol(res);
		res = Mult(buf, p);
	}
	FreePol(buf);
	return res;
}

struct Polynomial *Comp(struct Polynomial *p1, struct Polynomial *p2)
{ //мб сделать проверку на x?
	size_t size = p1->ringInfo->size;
	struct Polynomial *res = PolCreate(p1->ringInfo, malloc(size), 0);	
	memcpy(res->coefficients, res->ringInfo->zero, size);
	struct Polynomial *buf1 = NULL;
	struct Polynomial *buf2 = NULL;
	struct Polynomial *buf3 = NULL;
	struct Polynomial *buf4 = NULL;
	for (int i = 0; i <= p1->degree; i++)
	{
		if (memcmp(p1->coefficients + i * size, p1->ringInfo->zero, size))
		{
			buf1 = ToPol(p1->coefficients + i * size, p1->ringInfo);
			printf("!!!DEBUG!!!\nbuf1: ");
			PolOutput(buf1);
			buf2 = Pow(p2, i);
			buf3 = Mult(buf1, buf2);
			buf4 = Sum(res, buf3);
			CpyPol(res, buf4);
			FreePol(buf2);
			FreePol(buf3);
			FreePol(buf4);
			free(buf1);
		}
	}
	Cut(res);
	return res;
}

// 3.int

void scanInt(void *a)
{
	int *ia = (int *)a;
	scanf("%d%*c", ia);
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
		*a = 1;
	}
	return oneInt;
}

// 4.double

void scanDouble(void *a)
{
	double *da = (double *)a;
	scanf("%lf%*c", da);
}

void printDouble(void *a)
{
	double *da = (double *)a;
	printf("%lf", *da);
}

void *sumDouble(void *a1, void *a2)
{
	double *da1 = (double *)a1;
	double *da2 = (double *)a2;
	double *res = malloc(sizeof(double));
	*res = (*da1) + (*da2);
	return (void *)res;
}

void *multDouble(void *a1, void *a2)
{
	double *da1 = (double *)a1;
	double *da2 = (double *)a2;
	double *res = malloc(sizeof(double));
	*res = (*da1) * (*da2);
	return (void *)res;
}

void *powDouble(void *a1, int n)
{
	double *da1 = (double *)a1;
	double *res = malloc(sizeof(double));
	*res = 1;
	for (int i = 0; i < n; i++)
	{
		*res *= *da1;
	}
	return (void *)res;
}

void *zeroDouble;

void *ZeroDouble()
{
	if (!zeroDouble)
	{
		zeroDouble = malloc(sizeof(double));
		double *a = (double *)zeroDouble;
		*a = 0;
	}
	return zeroDouble;
}

void *oneDouble;

void *OneDouble()
{
	if (!oneDouble)
	{
		oneDouble = malloc(sizeof(double));
		double *a = (double *)oneDouble;
		*a = 0;
	}
	return oneDouble;
}

int main()
{
	struct RingInfo *ringInt = RingCreate("integers", sizeof(int), &scanInt, &printInt, &sumInt, ZeroInt(), &multInt, OneInt(), &powInt);
	struct RingInfo *ringDouble = RingCreate("reals", sizeof(double), &scanDouble, &printDouble, &sumDouble, ZeroDouble(), &multDouble, OneDouble(), &powDouble);
	struct Data *dataInt = DataCreate(ringInt, NULL, 0);
	struct Data *dataDouble = DataCreate(ringDouble, NULL, 0);
	void *constInt = NULL, *constDouble = NULL;
	int choice = 0;
	bool exitFlag = 0;
	while (!exitFlag)
	{
		choice = DialogMenu(dataInt->number, dataDouble->number);
		switch (choice)
		{
		case 1: // enter
			if (choiceMessage(
					"Do you want to enter polynomial with integer coefficients or with real coefficients?",
					"i",
					"r"))
			{
				PolInData(dataInt);
			}
			else
			{
				PolInData(dataDouble);
			}
			break;
		case 2: // print
			if (dataInt->number)
			{
				DataOutput(dataInt);
			}
			if (dataDouble->number)
			{
				DataOutput(dataDouble);
			}
			free(readline("Press enter to continue\n"));
			break;
		case 3: // sum
			if ((dataInt->number >= 2) && (dataDouble->number >= 2))
			{
				if (choiceMessage(
						"Do you want to sum polynomials with integer coefficients or with real coefficients?",
						"i",
						"r"))
				{
					struct Polynomial *sum = Sum(PolChoose(dataInt, NULL), PolChoose(dataInt, NULL));
					PolOutput(sum);
					ResInData(sum, dataInt);
				}
				else
				{
					struct Polynomial *sum = Sum(PolChoose(dataDouble, NULL), PolChoose(dataDouble, NULL));
					PolOutput(sum);
					ResInData(sum, dataDouble);
				}
			}
			else if (dataInt->number >= 2)
			{
				struct Polynomial *sum = Sum(PolChoose(dataInt, NULL), PolChoose(dataInt, NULL));
				PolOutput(sum);
				ResInData(sum, dataInt);
			}
			else
			{
				struct Polynomial *sum = Sum(PolChoose(dataDouble, NULL), PolChoose(dataDouble, NULL));
				PolOutput(sum);
				ResInData(sum, dataDouble);
			}
			break;
		case 4: // multiply
			if ((dataInt->number >= 2) && (dataDouble->number >= 2))
			{
				if (choiceMessage(
						"Do you want to multiple polynomials with integer coefficients or with real coefficients?",
						"i",
						"r"))
				{
					struct Polynomial *mult = Mult(PolChoose(dataInt, NULL), PolChoose(dataInt, NULL));
					PolOutput(mult);
					ResInData(mult, dataInt);
				}
				else
				{
					struct Polynomial *mult = Mult(PolChoose(dataDouble, NULL), PolChoose(dataDouble, NULL));
					PolOutput(mult);
					ResInData(mult, dataDouble);
				}
			}
			else if (dataInt->number >= 2)
			{
				struct Polynomial *mult = Mult(PolChoose(dataInt, NULL), PolChoose(dataInt, NULL));
				PolOutput(mult);
				ResInData(mult, dataInt);
			}
			else
			{
				struct Polynomial *mult = Mult(PolChoose(dataDouble, NULL), PolChoose(dataDouble, NULL));
				PolOutput(mult);
				ResInData(mult, dataDouble);
			}
			break;
		case 5: // multiply with a number
			if (dataInt->number && dataDouble->number)
			{
				if (choiceMessage(
						"Do you want to multiple polynomial with integer coefficients or with real coefficients?",
						"i",
						"r"))
				{
					void *multCoef = malloc(dataInt->comRingInfo->size);
					printf("Enter the coefficient:\n");
					dataInt->comRingInfo->scan(multCoef);
					struct Polynomial *polMultCoef = ToPol(multCoef, dataInt->comRingInfo);
					struct Polynomial *mult = Mult(polMultCoef, PolChoose(dataInt, NULL));
					PolOutput(mult);
					ResInData(mult, dataInt);
					FreePol(polMultCoef);
				}
				else
				{
					void *multCoef = malloc(dataDouble->comRingInfo->size);
					printf("Enter the coefficient:\n");
					dataDouble->comRingInfo->scan(multCoef);
					struct Polynomial *polMultCoef = ToPol(multCoef, dataDouble->comRingInfo);
					struct Polynomial *mult = Mult(polMultCoef, PolChoose(dataDouble, NULL));
					PolOutput(mult);
					ResInData(mult, dataDouble);
					FreePol(polMultCoef);
				}
			}
			else if (dataInt->number)
			{
				void *multCoef = malloc(dataInt->comRingInfo->size);
				printf("Enter the coefficient:\n");
				dataInt->comRingInfo->scan(multCoef);
				struct Polynomial *polMultCoef = ToPol(multCoef, dataInt->comRingInfo);
				struct Polynomial *mult = Mult(polMultCoef, PolChoose(dataInt, NULL));
				PolOutput(mult);
				ResInData(mult, dataInt);
				FreePol(polMultCoef);
			}
			else
			{
				void *multCoef = malloc(dataDouble->comRingInfo->size);
				printf("Enter the coefficient:\n");
				dataDouble->comRingInfo->scan(multCoef);
				struct Polynomial *polMultCoef = ToPol(multCoef, dataDouble->comRingInfo);
				struct Polynomial *mult = Mult(polMultCoef, PolChoose(dataDouble, NULL));
				PolOutput(mult);
				ResInData(mult, dataDouble);
				FreePol(polMultCoef);
			}
			break;
		case 6: // evaluate
			if (dataInt->number && dataDouble->number)
			{
				if (choiceMessage(
						"Do you want to evaluate polynomial with integer coefficients or with real coefficients?",
						"i",
						"r"))
				{
					void *value = malloc(dataInt->comRingInfo->size);
					printf("Enter the value:\n");
					dataInt->comRingInfo->scan(value);
					struct Polynomial *polValue = ToPol(value, dataInt->comRingInfo);
					struct Polynomial *comp = Comp(PolChoose(dataInt, NULL), polValue);
					PolOutput(comp);
					ResInData(comp, dataInt);
					FreePol(polValue);
				}
				else
				{
					void *value = malloc(dataDouble->comRingInfo->size);
					printf("Enter the value:\n");
					dataDouble->comRingInfo->scan(value);
					struct Polynomial *polValue = ToPol(value, dataDouble->comRingInfo);
					struct Polynomial *comp = Comp(PolChoose(dataDouble, NULL), polValue);
					PolOutput(comp);
					ResInData(comp, dataDouble);
					FreePol(polValue);
				}
			}
			else if (dataInt->number)
			{
				void *value = malloc(dataInt->comRingInfo->size);
				printf("Enter the value:\n");
				dataInt->comRingInfo->scan(value);
				struct Polynomial *polValue = ToPol(value, dataInt->comRingInfo);
				struct Polynomial *comp = Comp(PolChoose(dataInt, NULL), polValue);
				PolOutput(comp);
				ResInData(comp, dataInt);
				FreePol(polValue);
			}
			else
			{
				void *value = malloc(dataDouble->comRingInfo->size);
				printf("Enter the value:\n");
				dataDouble->comRingInfo->scan(value);
				struct Polynomial *polValue = ToPol(value, dataDouble->comRingInfo);
				struct Polynomial *comp = Comp(PolChoose(dataDouble, NULL), polValue);
				PolOutput(comp);
				ResInData(comp, dataDouble);
				FreePol(polValue);
			}
			break;
		case 7: // compose
			if ((dataInt->number >= 2) && (dataDouble->number >= 2))
			{
				if (choiceMessage(
						"Do you want to compose polynomials with integer coefficients or with real coefficients?",
						"i",
						"r"))
				{
					struct Polynomial *comp = Comp(PolChoose(dataInt, NULL), PolChoose(dataInt, NULL));
					PolOutput(comp);
					ResInData(comp, dataInt);
				}
				else
				{
					struct Polynomial *comp = Comp(PolChoose(dataDouble, NULL), PolChoose(dataDouble, NULL));
					PolOutput(comp);
					ResInData(comp, dataDouble);
				}
			}
			else if (dataInt->number >= 2)
			{
				struct Polynomial *comp = Comp(PolChoose(dataInt, NULL), PolChoose(dataInt, NULL));
				PolOutput(comp);
				ResInData(comp, dataInt);
			}
			else
			{
				struct Polynomial *comp = Comp(PolChoose(dataDouble, NULL), PolChoose(dataDouble, NULL));
				PolOutput(comp);
				ResInData(comp, dataDouble);
			}
			break;
		case 8: // delete
			if (dataInt->number && dataDouble->number)
			{
				if (choiceMessage(
						"Do you want to evaluate polynomial with integer coefficients or with real coefficients?",
						"i",
						"r"))
				{
					DelPolFromData(dataInt);
				}
				else
				{
					DelPolFromData(dataDouble);
				}
			}
			else if (dataInt->number)
			{
				DelPolFromData(dataInt);
			}
			else
			{
				DelPolFromData(dataDouble);
			}
			break;
		case 9: // exit
			exitFlag = 1;
			break;
		default:
			printf("Error: incorrect input\n");
			break;
		}
	}
	DataDelete(dataInt);
	DataDelete(dataDouble);
	RingDelete(ringDouble);
	RingDelete(ringInt);
}