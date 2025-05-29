#include "processing.h"
#include <cstdio>
#include <climits>
#include <cstring>

// Вспомогательная функция
static int time_to_seconds(time_mark t) {
    return t.hours * 3600 + t.minutes * 60 + t.seconds;
}

const char* find_best_time(marathon_result* array[], int size) {
    static char result[9] = "00:00:00";

    if (size == 0) {
        return result;
    }

    int best_time = INT_MAX;

    for (int i = 0; i < size; i++) {
        int start = time_to_seconds(array[i]->start);
        int finish = time_to_seconds(array[i]->finish);
        int duration = finish - start;

        if (duration < best_time && duration >= 0) {
            best_time = duration;
        }
    }

    int hours = best_time / 3600;
    int minutes = (best_time % 3600) / 60;
    int seconds = best_time % 60;

    snprintf(result, sizeof(result), "%02d:%02d:%02d", hours, minutes, seconds);
    return result;
}