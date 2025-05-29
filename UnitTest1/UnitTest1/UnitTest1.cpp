#include "pch.h"
#include "CppUnitTest.h"
#include "D:\Programm\Project\GitLaba\marathon-results-processing\marathon-results-processing\marathon_result.h"
#include "D:\Programm\Project\GitLaba\marathon-results-processing\marathon-results-processing\file_reader.h"
#include "D:\Programm\Project\GitLaba\marathon-results-processing\marathon-results-processing\processing.h"
#include "D:\Programm\Project\GitLaba\marathon-results-processing\marathon-results-processing\processing.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
    TEST_CLASS(MarathonProcessingTests)
    {
    public:
        TEST_METHOD(TestSingleValidResult)
        {
            // ���������� ������
            participant_name runner = { "������", "����", "��������" };
            time_mark start = { 0, 0, 0 };
            time_mark finish = { 2, 30, 15 };  // 2 ���� 30 ����� 15 ������

            marathon_result result = {
                1,          // �����
                runner,     // ���
                start,      // �����
                finish,     // �����
                "�������"   // ����
            };

            marathon_result* results[] = { &result };

            // ����� ����������� �������
            const char* best_time = find_best_time(results, 1);

            // �������� ����������
            Assert::AreEqual("02:30:15", best_time);
        }

        TEST_METHOD(TestMultipleResults)
        {
            // ���������� ������
            participant_name runner1 = { "������", "����", "��������" };
            participant_name runner2 = { "�������", "�����", "���������" };
            participant_name runner3 = { "��������", "�������", "����������" };

            marathon_result result1 = {
                1,
                runner1,
                {0, 0, 0},     // �����
                {3, 45, 0},    // ����� (3� 45�)
                "�����"
            };

            marathon_result result2 = {
                2,
                runner2,
                {0, 0, 0},
                {2, 15, 30},   // ����� (2� 15� 30�)
                "����"
            };

            marathon_result result3 = {
                3,
                runner3,
                {0, 0, 0},
                {4, 10, 5},    // ����� (4� 10� 5�)
                "���������"
            };

            marathon_result* results[] = { &result1, &result2, &result3 };

            // ����� ����������� �������
            const char* best_time = find_best_time(results, 3);

            // �������� ����������
            Assert::AreEqual("02:15:30", best_time);
        }
        TEST_METHOD(TestBoundaryValues)
        {
            participant_name runner1 = { "�������", "�����", "���������" };
            participant_name runner2 = { "�������", "�����", "���������" };

            marathon_result result1 = {
                10,
                runner1,
                {0, 0, 0},         // �����
                {23, 59, 59},      // �����
                "�������"
            };

            marathon_result result2 = {
                11,
                runner2,
                {0, 0, 0},
                {0, 0, 1},         // ����� (1 �������)
                "�������"
            };

            marathon_result* results[] = { &result1, &result2 };

            // ����� ����������� �������
            const char* best_time = find_best_time(results, 2);

            // �������� ����������
            Assert::AreEqual("00:00:01", best_time);
        }

        TEST_METHOD(TestZeroTime)
        {
            participant_name runner = { "��������", "�������", "����������" };

            marathon_result result = {
                7,
                runner,
                {0, 0, 0},
                {0, 0, 0},     // ����� � ������� �����
                "������ �������"
            };

            marathon_result* results[] = { &result };
            
            // ����� ����������� �������
            const char* best_time = find_best_time(results, 1);

            // �������� ����������
            Assert::AreEqual("00:00:00", best_time);
        }
    };
}