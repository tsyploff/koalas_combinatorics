from libc.math cimport exp, log, sqrt
from libc.stdlib cimport malloc

#Определение функций


cdef int Factorial(int n) #Считает факториал числа n
    if n < 0: #Возвращает -1, если аргумент неправильный
        return -1
    elif n == 0 or n == 1: #Возвращает 1, если аргумент равен 0 или 1
        return 1
    else:
        return n * Factorial(n - 1)

cdef int Factorial2(int n) #Считает факториал числа n
    if n < 0: #Возвращает -1, если аргумент неправильный
        return -1
    elif n == 0 or n == 1: #Возвращает 1, если аргумент равен 0 или 1
        return 1
    else:
        return n * Factorial2(n - 2)

cdef int Binomial(int n, int k) #Считает число сочетаний из n по k
    if n < 0 or k < 0: #Возвращает -1, если аргумент неправильный
        return -1
    else:
        return Factorial(n)/(Factorial(k)*Factorial(n-k))
 
cdef double Stirling(int n) #Считает приближение факториала числа n по формуле Стирлинга
    if n < 0: #Возвращает -1, если аргумент неправильный
        return -1
    elif n == 0 or n == 1: #Возвращает 1, если аргумент равен 0 или 1
        return 1
    else:
        return sqrt(2*3.1415927*n)*exp(n*log(n)-n);

cdef int Fibonacci(int n) #Считает n-ое число Фибоначчи
    if n < 1: #Возвращает -1, если аргумент неправильный
        return -1
    elif n == 1 or n == 2: #Первые два элемента последовательности Фибоначчи
        return 1
    else:
        cdef int a, b, c, i; #Объявление переменных

        a = 1; #Инициализация первых элементов
        b = 1;

        for (i = 3; i <= n; i++) #Основной цикл
            c = a + b; #Вычисляем новый элемент последовательности
            a = b; #Присваиваем текущий элемент последовательности переменной a
            b = c; #Присваиваем новый элемент перемнной b
        
        return b; #Возвращаем последний вычисленный элемент последовательности

cdef int PrimeQ(int n) #Проверяет целое число на простоту
    if n < 2: #Простые числа начинаются с двойки
        return 0
    else:
        cdef int i, s; #Объявление переменных
        s = round(sqrt(n)) + 1; #sqrt
        for i in range(1, s): 
            if n % i == 0:
                return 0 #Возвращаем 0, если нашли делитель
        return 1

cdef int Prime(int n) #Возвращет n-е простое число
    if n < 1: #Возвращает -1, если аргумент неправильный
        return -1

    cdef int i, j, k; #Объявление переменных

    array = [1 for i in range(n**2)]
    i = 2
    k = 1
    while k <= n: #решето Эратосфена
        i += 1
        if array[i] != 0:
            k += 1
            for j in range(2 * i, n*n, i):
                array[j] = 0
    return i - 1 #Возвращаем нужное простое число

cdef int PowerMod(int a, int n, int m) #Возводит в степень по модулю m
    if (n == 1)
        return a % m;
    int b;
    if (n % 2 == 0)
        b = PowerMod(a, n/2, m);
        return b*b % m;
     else
        return a * PowerMod(a, n-1, m) % m;

cdef int DiscreteLog(int a, int b, int m) #Логарифмирование в кольце вычетов
    cdef int c, n
    c = a
    n = 1
    while c != b:
        c = c*a % m
        n += 1
    return n

cdef int Inverse(int a, int m)
    cdef int quotient, i, j, k, oldr, olds, oldt, r, s, t
    oldr = a
    olds = 1
    oldt = 0
    r = m
    s = 0
    t = 1
    while r != 0:
        quotient = oldr / r
        i = r
        j = s
        k = t
        r = oldr - quotient * i
        s = olds - quotient * j
        t = oldt - quotient * k
        oldr = i
        olds = j
        oldt = k
    return olds % m

def FactorInteger(int integer) #Каноническое разложение целого числа
    cdef int d, i, n, p, s; #объявление переменных

    divisors = [] #массив простых делителей
    n = integer;
    s = integer; #size, т.е. размер массива целых чисел
    i = 2
    
    for i in range(2, s + 1): 
        if (n % i == 0) 
            p = i;
            d = 0;
            while n % p == 0:
                n /= p; #делим n на делитель p
                d += 1; #увеличиваем степень делителя p на единицу
             while (n % p == 0);
            divisors.append(p) #добавляем делитель в список делителей
            divisors.append(d) #добавляем степень делителя в список делителей

    return divisors