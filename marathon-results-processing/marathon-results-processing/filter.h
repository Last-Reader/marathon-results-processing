#ifndef FILTER_H
#define FILTER_H

#include "marathon_result.h"

marathon_result** filter(marathon_result* array[], int size, bool (*check)(marathon_result* element), int& result_size);

/*
  filter:
    ������� ��������� ������ ���������� ��������, �������� ����� ������
    � �����������, ���������������� ��������� �������

���������:
    array       - �������� ������ ���������� �� ����������
    size        - ������ ��������� �������
    check       - ��������� �� �������-�������� ��� �������� ���������
    result_size - �������� ��� �������� ������� ��������������� �������

������������ ��������:
    ��������� �� ������ ���������� �� ����������, ��������������� �������
*/


bool is_spartak_runner(marathon_result* element);

/*
  is_spartak_runner:
    ���������, �������� �� �������� ������ ����� "�������"

���������:
    element - ��������� �� ������� ��� ��������

������������ ��������:
    true, ���� �������� �� "��������", ����� false
*/


bool has_better_time(marathon_result* element);

/*
  has_better_time:
    ���������, ������� �� �������� ��������� ����� 2:50:00

���������:
    element - ��������� �� ������� ��� ��������

������������ ��������:
    true, ���� ����� ������ < 2:50:00, ����� false
*/

#endif