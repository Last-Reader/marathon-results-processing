#include "sort.h"
#include <cstring>
#include <iostream>

//--- ���������� ������� ��������� ---

// ��������� �� ������� ������
int compare_by_time(marathon_result* a, marathon_result* b) {
    // ������� ������� � �������� ��� a
    int a_time = (a->finish.hours - a->start.hours) * 3600 +
        (a->finish.minutes - a->start.minutes) * 60 +
        (a->finish.seconds - a->start.seconds);

    // ������� ������� � �������� ��� b
    int b_time = (b->finish.hours - b->start.hours) * 3600 +
        (b->finish.minutes - b->start.minutes) * 60 +
        (b->finish.seconds - b->start.seconds);

    return a_time - b_time; // ��� ���������� �� �����������
}

// ��������� �� ����� � �������
int compare_by_club_and_name(marathon_result* a, marathon_result* b) {
    // ������� ���������� �����
    int club_cmp = strcmp(a->club, b->club);
    if (club_cmp != 0) return club_cmp;

    // ���� ����� ����������, ���������� �������
    return strcmp(a->runner.last_name, b->runner.last_name);
}

//--- ���������� ���������� ---

// ���������� ���������
void bubble_sort(marathon_result* array[], int size, CompareFunction compare) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(array[j], array[j + 1]) > 0) {
                // ������ ������� ���������
                marathon_result* temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// ��������������� ������� ��� ������� ����������
int partition(marathon_result* array[], int low, int high, CompareFunction compare) {
    marathon_result* pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compare(array[j], pivot) <= 0) {
            i++;
            marathon_result* temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    marathon_result* temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

// �������� ������� ������� ����������
void quick_sort_recursive(marathon_result* array[], int low, int high, CompareFunction compare) {
    if (low < high) {
        int pi = partition(array, low, high, compare);
        quick_sort_recursive(array, low, pi - 1, compare);
        quick_sort_recursive(array, pi + 1, high, compare);
    }
}

// ������� ��� ������� ����������
void quick_sort(marathon_result* array[], int size, CompareFunction compare) {
    quick_sort_recursive(array, 0, size - 1, compare);
}