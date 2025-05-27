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
    int number;                 // ���������� �����
    participant_name runner;    // ��� ���������
    time_mark start;            // ����� ������
    time_mark finish;           // ����� ������
    char club;   // �������� ����� (����� ��������� �������)
};

#endif