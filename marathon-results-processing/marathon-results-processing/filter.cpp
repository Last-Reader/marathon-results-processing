#include "filter.h"
#include <cstring>
#include <iostream>

marathon_result** filter(marathon_result* array[], int size, bool (*check)(marathon_result* element), int& result_size)
{
    marathon_result** result = new marathon_result * [size];
    result_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (check(array[i]))
        {
            result[result_size++] = array[i];
        }
    }
    return result;
}

bool is_spartak_runner(marathon_result* element)
{
    return strcmp(element->club, "Спартак") == 0;
}

bool has_better_time(marathon_result* element)
{
    // Рассчет времени забега в секундах
    int start_seconds = element->start.hours * 3600 +
        element->start.minutes * 60 +
        element->start.seconds;

    int finish_seconds = element->finish.hours * 3600 +
        element->finish.minutes * 60 +
        element->finish.seconds;

    int total_seconds = finish_seconds - start_seconds;
    int max_seconds = 2 * 3600 + 50 * 60; // 2:50:00 в секундах

    return total_seconds < max_seconds;
}