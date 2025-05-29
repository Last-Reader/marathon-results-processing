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
            // Подготовка данных
            participant_name runner = { "Иванов", "Иван", "Иванович" };
            time_mark start = { 0, 0, 0 };
            time_mark finish = { 2, 30, 15 };  // 2 часа 30 минут 15 секунд

            marathon_result result = {
                1,          // номер
                runner,     // ФИО
                start,      // старт
                finish,     // финиш
                "Спартак"   // клуб
            };

            marathon_result* results[] = { &result };

            // Вызов тестируемой функции
            const char* best_time = find_best_time(results, 1);

            // Проверка результата
            Assert::AreEqual("02:30:15", best_time);
        }

        TEST_METHOD(TestMultipleResults)
        {
            // Подготовка данных
            participant_name runner1 = { "Петров", "Петр", "Петрович" };
            participant_name runner2 = { "Сидоров", "Сидор", "Сидорович" };
            participant_name runner3 = { "Николаев", "Николай", "Николаевич" };

            marathon_result result1 = {
                1,
                runner1,
                {0, 0, 0},     // старт
                {3, 45, 0},    // финиш (3ч 45м)
                "Зенит"
            };

            marathon_result result2 = {
                2,
                runner2,
                {0, 0, 0},
                {2, 15, 30},   // финиш (2ч 15м 30с)
                "ЦСКА"
            };

            marathon_result result3 = {
                3,
                runner3,
                {0, 0, 0},
                {4, 10, 5},    // финиш (4ч 10м 5с)
                "Локомотив"
            };

            marathon_result* results[] = { &result1, &result2, &result3 };

            // Вызов тестируемой функции
            const char* best_time = find_best_time(results, 3);

            // Проверка результата
            Assert::AreEqual("02:15:30", best_time);
        }
        TEST_METHOD(TestBoundaryValues)
        {
            participant_name runner1 = { "Федоров", "Федор", "Федорович" };
            participant_name runner2 = { "Семенов", "Семен", "Семенович" };

            marathon_result result1 = {
                10,
                runner1,
                {0, 0, 0},         // старт
                {23, 59, 59},      // финиш
                "Спартак"
            };

            marathon_result result2 = {
                11,
                runner2,
                {0, 0, 0},
                {0, 0, 1},         // финиш (1 секунда)
                "Торпедо"
            };

            marathon_result* results[] = { &result1, &result2 };

            // Вызов тестируемой функции
            const char* best_time = find_best_time(results, 2);

            // Проверка результата
            Assert::AreEqual("00:00:01", best_time);
        }

        TEST_METHOD(TestZeroTime)
        {
            participant_name runner = { "Васильев", "Василий", "Васильевич" };

            marathon_result result = {
                7,
                runner,
                {0, 0, 0},
                {0, 0, 0},     // финиш в нулевое время
                "Крылья Советов"
            };

            marathon_result* results[] = { &result };
            
            // Вызов тестируемой функции
            const char* best_time = find_best_time(results, 1);

            // Проверка результата
            Assert::AreEqual("00:00:00", best_time);
        }
    };
}