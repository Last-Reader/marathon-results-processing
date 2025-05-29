#include <iostream>
#include <iomanip>
#include "marathon_result.h"
#include "file_reader.h"
#include "filter.h"
#include "sort.h"
#include "constants.h"
#include "processing.h"

using namespace std;

void process_data(marathon_result* results[], int size) {
    const char* best_time = find_best_time(results, size);
    cout << "\nЛучшее время марафона: " << best_time << endl;
}

// Функция для вывода результатов
void print_results(marathon_result* results[], int size) {
    cout << "\n***** Результаты марафона (" << size << " участников) *****\n\n";
    for (int i = 0; i < size; i++) {
        // Рассчет времени забега
        int hours = results[i]->finish.hours - results[i]->start.hours;
        int minutes = results[i]->finish.minutes - results[i]->start.minutes;
        int seconds = results[i]->finish.seconds - results[i]->start.seconds;

        // Корректировка отрицательных значений
        if (seconds < 0) {
            seconds += 60;
            minutes--;
        }
        if (minutes < 0) {
            minutes += 60;
            hours--;
        }

        cout << "Участник №" << results[i]->number << ":\n";
        cout << "ФИО...........: "
            << results[i]->runner.last_name << " "
            << results[i]->runner.first_name << " "
            << results[i]->runner.patronymic << '\n';

        cout << "Старт.........: "
            << setw(2) << setfill('0') << results[i]->start.hours << ":"
            << setw(2) << setfill('0') << results[i]->start.minutes << ":"
            << setw(2) << setfill('0') << results[i]->start.seconds << '\n';

        cout << "Финиш.........: "
            << setw(2) << setfill('0') << results[i]->finish.hours << ":"
            << setw(2) << setfill('0') << results[i]->finish.minutes << ":"
            << setw(2) << setfill('0') << results[i]->finish.seconds << '\n';

        cout << "Время.........: "
            << setw(2) << setfill('0') << hours << ":"
            << setw(2) << setfill('0') << minutes << ":"
            << setw(2) << setfill('0') << seconds << '\n';

        cout << "Клуб..........: " << results[i]->club << "\n\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    marathon_result* results[MAX_FILE_ROWS_COUNT];
    int size = 0;

    // Загрузка данных
    try {
        read("data.txt", results, size);
        cout << "Данные успешно загружены (" << size << " записей)\n";
    }
    catch (const char* error) {
        cout << "Ошибка: " << error << '\n';
        return 1;
    }

    // Массивы функций для меню
    SortFunction sort_functions[] = { bubble_sort, quick_sort };
    const char* sort_names[] = { "Сортировка пузырьком", "Быстрая сортировка" };

    CompareFunction compare_functions[] = { compare_by_time, compare_by_club_and_name };
    const char* compare_names[] = { "По времени забега", "По клубу и фамилии" };

    // Основной цикл программы
    while (true) {
        cout << "\nГлавное меню:\n";
        cout << "1. Вывести исходные данные\n";
        cout << "2. Фильтровать участников\n";
        cout << "3. Отсортировать данные\n";
        cout << "4. Выйти\n";
        cout << "5. Обработать данные (найти лучшее время)\n";
        cout << "Выберите действие: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // Вывод исходных данных
            print_results(results, size);
        }
        else if (choice == 2) {
            // Меню фильтрации
            cout << "\nФильтрация:\n";
            cout << "1. Участники из Спартака\n";
            cout << "2. Участники с результатом лучше 2:50:00\n";
            cout << "Выберите критерий: ";

            int filter_choice;
            cin >> filter_choice;

            if (filter_choice == 1) {
                int filtered_size;
                marathon_result** filtered = filter(
                    results,
                    size,
                    is_spartak_runner,
                    filtered_size
                );
                cout << "\nНайдено " << filtered_size << " участников из Спартака:\n";
                print_results(filtered, filtered_size);
                delete[] filtered;
            }
            else if (filter_choice == 2) {
                int filtered_size;
                marathon_result** filtered = filter(
                    results,
                    size,
                    has_better_time,
                    filtered_size
                );
                cout << "\nНайдено " << filtered_size << " участников с хорошим результатом:\n";
                print_results(filtered, filtered_size);
                delete[] filtered;
            }
            else {
                cout << "Неверный выбор!\n";
            }
        }
        else if (choice == 3) {
            // Выбор сортировки
            cout << "\nВыберите метод сортировки:\n";
            for (int i = 0; i < 2; i++) {
                cout << i + 1 << ". " << sort_names[i] << "\n";
            }
            cout << "Ваш выбор: ";

            int sort_choice;
            cin >> sort_choice;

            if (sort_choice < 1 || sort_choice > 2) {
                cout << "Неверный выбор!\n";
                continue;
            }

            // Выбор критерия
            cout << "\nВыберите критерий сортировки:\n";
            for (int i = 0; i < 2; i++) {
                cout << i + 1 << ". " << compare_names[i] << "\n";
            }
            cout << "Ваш выбор: ";

            int compare_choice;
            cin >> compare_choice;

            if (compare_choice < 1 || compare_choice > 2) {
                cout << "Неверный выбор!\n";
                continue;
            }

            // Применение сортировки
            sort_functions[sort_choice - 1](
                results,
                size,
                compare_functions[compare_choice - 1]
                );

            cout << "\nДанные успешно отсортированы!\n";
            print_results(results, size);
        }
        else if (choice == 4) {
            break;
        }
        else if (choice == 5) {
            process_data(results, size);
        }
        else {
            cout << "Неверный выбор!\n";
        }
    }

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        delete results[i];
    }

    return 0;
}