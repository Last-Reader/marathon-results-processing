#ifndef FILTER_H
#define FILTER_H

#include "marathon_result.h"

marathon_result** filter(marathon_result* array[], int size, bool (*check)(marathon_result* element), int& result_size);

/*
  filter:
    Функция фильтрует массив участников марафона, создавая новый массив
    с участниками, удовлетворяющими заданному условию

Параметры:
    array       - исходный массив указателей на участников
    size        - размер исходного массива
    check       - указатель на функцию-предикат для проверки элементов
    result_size - параметр для возврата размера результирующего массива

Возвращаемое значение:
    Указатель на массив указателей на участников, удовлетворяющих условию
*/


bool is_spartak_runner(marathon_result* element);

/*
  is_spartak_runner:
    Проверяет, является ли участник членом клуба "Спартак"

Параметры:
    element - указатель на элемент для проверки

Возвращаемое значение:
    true, если участник из "Спартака", иначе false
*/


bool has_better_time(marathon_result* element);

/*
  has_better_time:
    Проверяет, показал ли участник результат лучше 2:50:00

Параметры:
    element - указатель на элемент для проверки

Возвращаемое значение:
    true, если время забега < 2:50:00, иначе false
*/

#endif