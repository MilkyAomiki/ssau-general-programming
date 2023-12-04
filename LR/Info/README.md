# Лабы по Информатике ПМИ 1 курс

## Задания, вариант 22

### ЛР 1

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

### ЛР 2

### Два сплава

Имеется два сплава из двух металлов, соотношение этих металлов
в каждом из сплавов **известно**. Программа должна определять, какое
количество объёмных единиц первого и второго сплава нужно взять,
чтобы получить третий сплав с заданным соотношением этих
металлов.

**Входные данные**. Соотношение двух металлов в первом сплаве,
во втором сплаве и в требуемом сплаве, а также количество объёмных
единиц третьего сплава, которое требуется получить.
**Выходные данные**. Количество объёмных единиц первого и
второго сплава, которые следует соединить, для получения заданного
количества третьего сплава, либо сообщение о том, что получить
третий сплав из имеющихся двух невозможно.

Пример текстового интерфейса пользователя

``` bash
Alloys volume calculator
Input a proportion in the first alloy>0.25
Input a proportion in the second alloy>4.0
Input a required proportion>1.0
Input a required volume>1000
Volume of the first alloy: 500.0
Volume of the second alloy: 500.0
Continue? (Y/N)>Y
66
Input a proportion in the first alloy>0.5
Input a proportion in the second alloy>2.0
Input a required proportion>0.666666666666666
Input a required volume>1.5
Volume of the first alloy: 1.2
Volume of the second alloy: 0.3
Continue? (Y/N)>N
```

p.s.

``` c++
a* ratio1 + b*ratio2 = c*ratio3
a + b = c

c*ratio1-b*ratio1 + b*ratio2 = c*ratio3
a = c-b

b*ratio2 - b*ratio1 = c*ratio3 - c*ratio1
a = c-b

b*(ratio2 - ratio1) = c*(ratio3 - ratio1)
a = c-b

ratio1 + b*ratio2/a = ratio3/a
ratio1/b + ratio2/a = ratio3/a*b

500*0.25 + 4*500 = 
```
