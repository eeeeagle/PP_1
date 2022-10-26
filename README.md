## Задание

Написать программу на языке C/C++ для перемножения двух матриц.

**Исходные данные**: файл(ы) содержащие значения исходных матриц.

**Выходные данные**: файл со значениями результирующей матрицы, время выполнения, объем задачи.

Обязательна автоматизированная верификация результатов вычислений с помощью сторонних библиотек или стороннего ПО (например Matlab).

*При желании, в качестве экспериментальной задачи можно выбрать любую другую вычислительную задачи, которая подвержена распараллеливанию.*

## Исследование: зависимость времени выполнения вычислений от объема данных

Вычисления выполнялись на системе с 4-х ядерным процессором Intel Core i5-6400 с тактовой частотой 3,3 ГГц и оперативной памятью 8 Гб и тактовой частотой 2133 МГц.

_Таблица 1: время (в секундах) выполнения операции умножения квадратных матриц N порядка_
|**N**   |**50**   |**100**  |**200**  |**400** |**800**|**1600**|**3200**|
|:------:|:-------:|:-------:|:-------:|:------:|:-----:|:------:|:------:|
|**100** |0.0004455|-        |        -|-       |-      |-       |-       |
|**200** |0.0008851|0.0039356|       - |-       |-      |-       |-       |
|**400** |0.0017712|0.0074988|0.0363236|-       |-      |-       |-       |
|**800** |0.0035879|0.0158907|0.0738133|0.346546|-      |-       |-       |
|**1600**|0.0073669|0.0319319|0.151718 |0.773607|4.35233|-       |-       |
|**3200**|0.0148123|0.0678273|0.308918 |1.46577 |9.84342|92.6786 |-       |
|**6400**|0.0295878|0.127999 |0.589093 |2.83629 |18.348 |197.023 |836.374 |

`N` - порядок матрицы

Так, для произведения матриц порядка 100 и 400 время, затраченное на перемножение матриц, составило _0.0074988_ секунды.

_График 1: зависимость времени (в секундах) выполнения операции умножения матриц от объёма операции; объём: (50 x 100; 50 x 6400) чисел_

![50x(100-6400)](https://user-images.githubusercontent.com/90867530/197342419-872e8476-f66c-4103-8be0-0826681de195.png)

_График 2: зависимость времени (в секундах) выполнения операции умножения матриц от объёма операции; объём: (6400 x 50; 6400 x 3200) чисел_

![6400x(50-3200)](https://user-images.githubusercontent.com/90867530/197342423-5c739e68-9bc1-41f5-b637-10d2c945654b.png)

На графике 1 рост времени ближе к линейному, а на графике 2 - явно экспоненциальный. Следовательно, последовательные вычисления удобны при небольших объемах данных (примерно до нескольких миллионов чисел), однако с ростом объёма данных, время выполнения экспоненциально растёт.
