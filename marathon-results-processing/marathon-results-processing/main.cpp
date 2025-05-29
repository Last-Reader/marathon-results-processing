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
    cout << "\n������ ����� ��������: " << best_time << endl;
}

// ������� ��� ������ �����������
void print_results(marathon_result* results[], int size) {
    cout << "\n***** ���������� �������� (" << size << " ����������) *****\n\n";
    for (int i = 0; i < size; i++) {
        // ������� ������� ������
        int hours = results[i]->finish.hours - results[i]->start.hours;
        int minutes = results[i]->finish.minutes - results[i]->start.minutes;
        int seconds = results[i]->finish.seconds - results[i]->start.seconds;

        // ������������� ������������� ��������
        if (seconds < 0) {
            seconds += 60;
            minutes--;
        }
        if (minutes < 0) {
            minutes += 60;
            hours--;
        }

        cout << "�������� �" << results[i]->number << ":\n";
        cout << "���...........: "
            << results[i]->runner.last_name << " "
            << results[i]->runner.first_name << " "
            << results[i]->runner.patronymic << '\n';

        cout << "�����.........: "
            << setw(2) << setfill('0') << results[i]->start.hours << ":"
            << setw(2) << setfill('0') << results[i]->start.minutes << ":"
            << setw(2) << setfill('0') << results[i]->start.seconds << '\n';

        cout << "�����.........: "
            << setw(2) << setfill('0') << results[i]->finish.hours << ":"
            << setw(2) << setfill('0') << results[i]->finish.minutes << ":"
            << setw(2) << setfill('0') << results[i]->finish.seconds << '\n';

        cout << "�����.........: "
            << setw(2) << setfill('0') << hours << ":"
            << setw(2) << setfill('0') << minutes << ":"
            << setw(2) << setfill('0') << seconds << '\n';

        cout << "����..........: " << results[i]->club << "\n\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    marathon_result* results[MAX_FILE_ROWS_COUNT];
    int size = 0;

    // �������� ������
    try {
        read("data.txt", results, size);
        cout << "������ ������� ��������� (" << size << " �������)\n";
    }
    catch (const char* error) {
        cout << "������: " << error << '\n';
        return 1;
    }

    // ������� ������� ��� ����
    SortFunction sort_functions[] = { bubble_sort, quick_sort };
    const char* sort_names[] = { "���������� ���������", "������� ����������" };

    CompareFunction compare_functions[] = { compare_by_time, compare_by_club_and_name };
    const char* compare_names[] = { "�� ������� ������", "�� ����� � �������" };

    // �������� ���� ���������
    while (true) {
        cout << "\n������� ����:\n";
        cout << "1. ������� �������� ������\n";
        cout << "2. ����������� ����������\n";
        cout << "3. ������������� ������\n";
        cout << "4. �����\n";
        cout << "5. ���������� ������ (����� ������ �����)\n";
        cout << "�������� ��������: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            // ����� �������� ������
            print_results(results, size);
        }
        else if (choice == 2) {
            // ���� ����������
            cout << "\n����������:\n";
            cout << "1. ��������� �� ��������\n";
            cout << "2. ��������� � ����������� ����� 2:50:00\n";
            cout << "�������� ��������: ";

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
                cout << "\n������� " << filtered_size << " ���������� �� ��������:\n";
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
                cout << "\n������� " << filtered_size << " ���������� � ������� �����������:\n";
                print_results(filtered, filtered_size);
                delete[] filtered;
            }
            else {
                cout << "�������� �����!\n";
            }
        }
        else if (choice == 3) {
            // ����� ����������
            cout << "\n�������� ����� ����������:\n";
            for (int i = 0; i < 2; i++) {
                cout << i + 1 << ". " << sort_names[i] << "\n";
            }
            cout << "��� �����: ";

            int sort_choice;
            cin >> sort_choice;

            if (sort_choice < 1 || sort_choice > 2) {
                cout << "�������� �����!\n";
                continue;
            }

            // ����� ��������
            cout << "\n�������� �������� ����������:\n";
            for (int i = 0; i < 2; i++) {
                cout << i + 1 << ". " << compare_names[i] << "\n";
            }
            cout << "��� �����: ";

            int compare_choice;
            cin >> compare_choice;

            if (compare_choice < 1 || compare_choice > 2) {
                cout << "�������� �����!\n";
                continue;
            }

            // ���������� ����������
            sort_functions[sort_choice - 1](
                results,
                size,
                compare_functions[compare_choice - 1]
                );

            cout << "\n������ ������� �������������!\n";
            print_results(results, size);
        }
        else if (choice == 4) {
            break;
        }
        else if (choice == 5) {
            process_data(results, size);
        }
        else {
            cout << "�������� �����!\n";
        }
    }

    // ������������ ������
    for (int i = 0; i < size; i++) {
        delete results[i];
    }

    return 0;
}