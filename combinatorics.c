#include <math.h>
#include <Python.h>
#include <stdlib.h>

/**
Определение функций
*/

int Fibonacci(int n) /*Считает n-ое число Фибоначчи*/
{
	if (n < 1) /*Возвращает -1, если аргумент неправильный*/
		return -1;

	if ((n == 1)||(n == 2)) /*Первые два элемента последовательности Фибоначчи*/
		return 1;

	int a, b, c, i; /*Объявление переменных*/
	
	a = 1; /*Инициализация первых элементов*/
	b = 1;
	
	for (i = 3; i <= n; i++) /*Основной цикл*/
	{
		c = a + b; /*Вычисляем новый элемент последовательности*/
		a = b; /*Присваиваем текущий элемент последовательности переменной a*/
		b = c; /*Присваиваем новый элемент перемнной b*/
	}
	
	return b; /*Возвращаем последний вычисленный элемент последовательности*/
}

int PrimeQ(int n) /*Проверяет целое число на простоту*/
{
	if (n < 2) /*Простые числа начинаются с двойки*/
		return 0;
	int i, s; /*Объявление переменных*/

	s = round(sqrt(n)) + 1; /*sqrt*/
	
	for (i = 2; i <= s; i++)
		if (n % i == 0)
			return 0; /*Возвращаем 0, если нашли делитель*/
	return 1; 
}

int Prime(int n) /*Возвращет n-е простое число*/
{
	if (n < 1) /*Возвращает -1, если аргумент неправильный*/
		return -1;

	int *array; /*Объявление массива целых чисел*/
	int i, j, k; /*Объявление переменных*/

	array = malloc(sizeof(int) * n * n); /*Массив целых чисел длины n^2*/

	for (i = 0; i < n*n; i++) /*Заполняем массив единицами*/
		array[i] = 1;

	for (i = 2, k = 1; k <= n; i++) /*решето Эратосфена*/
		if (array[i] != 0)
		{
			k++;
			for (j = 2*i; j < n*n; j += i)
				array[j] = 0;
		}

	return i - 1; /*Возвращаем нужное простое число*/
}

int PowerMod(int a, int n, int m) /*Возводит в степень по модулю m*/
{
	if (n == 1)
		return a % m;
	int b;
	if (n % 2 == 0) {
		b = PowerMod(a, n/2, m);
		return b*b % m;
	} else {
		return a * PowerMod(a, n-1, m) % m;
	}
}

int DiscreteLog(int a, int b, int m) /*Логарифмирование в кольце вычетов*/
{
	int c = a;
	int n = 1;
	while(c != b)
	{
		c = c*a % m;
		n++;
	}
	return n;
}

int Inverse(int a, int m)
{

	int quotient, i, j, k;
	int oldr = a;
	int olds = 1;
	int oldt = 0;
	int r = m;
	int s = 0;
	int t = 1;	
	while (r != 0)
	{
		quotient = oldr / r;
		i = r;
		j = s;
		k = t;
		r = oldr - quotient * i;
		s = olds - quotient * j;
		t = oldt - quotient * k;
		oldr = i;
		olds = j;
		oldt = k;
	}
    return olds % m;
}

int* FactorInteger(int integer) /*Каноническое разложение целого числа*/
{
	int d, i, j, n, p, s; /*объявление переменных*/
	int *divisors;

	n = integer;
	s = integer; /*size, т.е. размер массива целых чисел*/

	divisors = malloc(sizeof(int) * 200); /*Массив простых делителей*/

	for (i = 2, j = 0; i <= s; i++) 
		if (n % i == 0) 
		{
			p = i;
			d = 0;
			do {
				n /= p; /*делим n на делитель p*/
				d += 1; /*увеличиваем степень делителя p на единицу*/
			} while (n % p == 0);
			divisors[j++] = p; /*добавляем делитель в список делителей*/
			divisors[j++] = d; /*добавляем степень делителя в список делителей*/
		}
	divisors[j] = 0;
	return divisors;
}

/**
Определение объектов Python
*/

static PyObject* c_fibonacci(PyObject* self, PyObject* args)
{
	int n; /*Объявление переменной*/

	if (!PyArg_ParseTuple(args, "i", &n)) /*Исключение ошибки аргумента*/
		return NULL;

	return Py_BuildValue("i", Fibonacci(n)); /*Возвращаем ответ с использованием функции Си*/
}

static PyObject* c_is_prime(PyObject* self, PyObject* args)
{
	int n; /*Объявление переменной*/

	if (!PyArg_ParseTuple(args, "i", &n)) /*Исключение ошибки аргумента*/
		return NULL;

	return Py_BuildValue("i", PrimeQ(n)); /*Возвращаем ответ с использованием функции Си*/
}

static PyObject* c_prime(PyObject* self, PyObject* args)
{
	int n; /*Объявление переменной*/

	if (!PyArg_ParseTuple(args, "i", &n)) /*Исключение ошибки аргумента*/
		return NULL;

	return Py_BuildValue("i", Prime(n)); /*Возвращаем ответ с использованием функции Си*/
}

static PyMethodDef combinatorics_methods[] = { /*Методы модуля*/
	{"c_fibonacci", c_fibonacci, METH_VARARGS, "Возвращает элемент последовательности Фибоначчи"},
	{"c_is_prime",  c_is_prime,  METH_VARARGS, "Проверяет, является ли число простым"},
	{"c_prime",     c_prime,     METH_VARARGS, "Возвращает простое число"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef combinatorics_module = {
	PyModuleDef_HEAD_INIT,
	"combinatorics",
	"Функции для решения комбинаторных задач", 
	-1,
	combinatorics_methods
};

PyMODINIT_FUNC PyInit_combinatorics(void)
{
    return PyModule_Create(&combinatorics_module);
}
