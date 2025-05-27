#ifndef MARATHON_RESULT_H
#define MARATHON_RESULT_H

#include "constants.h"

struct time_mark {
    int hours;
    int minutes;
    int seconds;
};

struct participant_name {
    char last_name[MAX_STRING_SIZE];
    char first_name[MAX_STRING_SIZE];
    char patronymic[MAX_STRING_SIZE];
};

struct marathon_result {
    int number;                 // Порядковый номер
    participant_name runner;    // ФИО участника
    time_mark start;            // Время старта
    time_mark finish;           // Время финиша
    char club;   // Название клуба (может содержать пробелы)
};

#endif