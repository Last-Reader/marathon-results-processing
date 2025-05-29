#ifndef SORT_H
#define SORT_H

#include "marathon_result.h"

// ��� ��� ������� ���������
typedef int (*CompareFunction)(marathon_result*, marathon_result*);

// ��� ��� ������� ����������
typedef void (*SortFunction)(marathon_result* [], int, CompareFunction);

// ������� ����������
void bubble_sort(marathon_result* array[], int size, CompareFunction compare);
void quick_sort(marathon_result* array[], int size, CompareFunction compare);

// ������� ���������
int compare_by_time(marathon_result* a, marathon_result* b);
int compare_by_club_and_name(marathon_result* a, marathon_result* b);

#endif