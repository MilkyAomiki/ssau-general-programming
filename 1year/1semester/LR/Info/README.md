# Лабы по Информатике ПМИ 1 курс

Написаны в vscode, скомпилированны с g++ (конфиг в .vscode/tasks.json)

## Задания

## ЛР 1 (вариант 22)

### Скатерть Улама и треугольник Клаубера

Программа должна определять, сколько простых чисел содержится
среди заданного количества начальных элементов последовательности
`an = n (n – 1) + k` для заданного `k`.

Простое число – это натуральное
число, имеющее ровно два различных натуральных делителя.
Элементы последовательности нумеруются с единицы.

**Входные данные**. Целое положительное число k и количество
элементов последовательности, которые нужно проверить.
**Выходные данные**. Количество элементов последовательности,
являющихся простыми числами.

Пример текстового интерфейса пользователя

``` bash

Primality test for elements a(n) = n (n - 1) + k
Input a positive integer k>5
Input the number of elements>10
The number of primes: 6
Continue? (Y/N)>Y
Input a positive integer k>11
Input the number of elements>10
The number of primes: 10
Continue? (Y/N)>N

```

## ЛР 2 (вариант 6)

### Система линейных алгебраических уравнений

Программа должна решать систему линейных алгебраических
уравнений вида

``` bash
| a_11x_1+a_12x_2 = b_1;
| a_21x_1+a_22x_2 = b_2;
```

**Входные данные.** Целые числа a_ij и b_i.
**Выходные данные.** Все возможные пары значений x_1 и x_2,
удовлетворяющие обоим уравнениям системы, либо сообщение о том,
что таких пар бесконечно много.

``` bash
System of linear equations solver
Input a(1, 1)>1
Input a(1, 2)>2
Input a(2, 1)>3
Input a(2, 2)>4
Input b(1)>5
Input b(2)>6
Solution: (-4.0, 4.5)
Continue? (Y/N)>Y
Input a(1, 1)>1
Input a(1, 2)>2
Input a(2, 1)>2
Input a(2, 2)>4
Input b(1)>3
Input b(2)>3
No solution
Continue? (Y/N)>N
```

## ЛР 3 (Вариант 29)

### Калькулятор матриц

Состоянием программы является матрица размером `2×2`,
элементами которой являются дробные числа.

Программа должна позволять пользователю складывать эту матрицу с другими матрицами такого же размера и умножать эту матрицу на другие матрицы такого же размера, изменяя при этом своё состояние.

Программа должна визуализировать результат каждой операции.

**Входные данные**. Операции с текущей матрицей и квадратные
матрицы из дробных чисел, с которыми нужно выполнять эти
операции.
113
**Выходные данные**. Состояние матрицы после каждой операции.

Пример текстового интерфейса пользователя

``` bash
Matrix calculator
Current state:
0.0 0.0
0.0 0.0
Input an operation (+/*)>+
Input an operand
Input the element #(1, 1)>1.5
Input the element #(1, 2)>2.5
Input the element #(2, 1)>3.5
Input the element #(2, 2)>4.5
Current state:
1.5 2.5
3.5 4.5
Continue? (Y/N)>Y
Input an operation (+/*)>*
Input an operand
Input the element #(1, 1)>5
Input the element #(1, 2)>6
Input the element #(2, 1)>7
Input the element #(2, 2)>8
Current state:
25.0 29.0
49.0 57.0
Continue? (Y/N)>N
```

## ЛР 4 (Вариант 24)

### Копирование файлов

Программа должна создавать новый файл с заданным именем,
содержимое которого полностью совпадает с содержимым другого
файла с заданным именем.

**Входные данные**. Исходный файл, заданный своим именем, а
также имя нового файла.
**Выходные данные**. Копия исходного файла с заданным именем.

Пример текстового интерфейса пользователя

``` bash
File copy
Input a source filename>The Jungle Book.txt
Input a destination filename>The Jungle Book (1).txt
Operation has been completed successfully
Continue? (Y/N)>Y
Input a source filename>Jane Eyre.txt
Input a destination filename>Jane Eyre (1).txt
Operation has been completed successfully
Continue? (Y/N)>N
```