## Задание

Написать программу на языке C/C++ для перемножения двух матриц.

**Исходные данные**: файл(ы) содержащие значения исходных матриц.

**Выходные данные**: файл со значениями результирующей матрицы, время выполнения, объем задачи.

Обязательна автоматизированная верификация результатов вычислений с помощью сторонних библиотек или стороннего ПО (например Matlab).

*При желании, в качестве экспериментальной задачи можно выбрать любую другую вычислительную задачи, которая подвержена распараллеливанию.*

## Исследование: зависимость времени выполнения вычислений от объема данных

Вычисления выполнялись на системе с 4-х ядерным процессором Intel Core i5-6400 с тактовой частотой 3,3 ГГц и оперативной памятью 8 Гб и тактовой частотой 2133 МГц.

_Таблица 1: время выполнения операции перемножения квадратных матриц N порядка_
|**N**   |**t, с** |
|:------:|:-------:|
|**50**  |0.0002219|
|**100** |0.0018168|
|**200** |0.0183377|
|**300** |0.0679793|
|**400** |0.163695 |
|**500** |0.337483 |
|**600** |0.635732 |
|**700** |1.08349  |
|**800** |1.7775   |
|**900** |5.41968  |
|**1000**|10.8214  |
|**1200**|18.7135  |
|**1400**|31.2999  |
|**1600**|47.7274  |
|**1800**|69.4258  |
|**2000**|94.72    |
|**2200**|129.212  |
|**2400**|173.375  |
|**2600**|226.4    |
|**2800**|285.31   |
|**3000**|367.101  |
|**3400**|532.277  |
|**3800**|763.552  |
|**4200**|1050.65  |
|**4600**|1396.65  |
|**5000**|1837.61  |

_График 1: зависимость времени (в секундах) выполнения операции умножения матриц от объёма операции_
![lab1](https://user-images.githubusercontent.com/90867530/208422715-89c1657e-ac0c-4ac8-bbfc-27cb4f2b7d9c.png)

На графике 1 рост времени выполенения операции экспоненциальный. Следовательно, последовательные вычисления удобны при небольших объемах данных (примерно до нескольких миллионов чисел), однако с ростом объёма данных, время выполнения экспоненциально растёт.
