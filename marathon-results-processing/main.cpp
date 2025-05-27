#include <iostream>
#include "marathon_result.h"
#include "file_reader.h"
#include "constants.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Laba �4. GIT\n";
    cout << "Variant 11\n"; // ������� ����� ������ ��������
    cout << "Author: Polyakov Nikita\n\n"; // ������� ���� ���

    marathon_result* results[MAX_FILE_ROWS_COUNT];
    int size;

    try {
        read("data.txt", results, size);

        // ����� ���� ����������
        for (int i = 0; i < size; i++) {
            cout << "Number: " << results[i]->number << endl;
            cout << "FIO: "
                << results[i]->runner.last_name << " "
                << results[i]->runner.first_name << " "
                << results[i]->runner.patronymic << endl;

            cout << "Start: "
                << results[i]->start.hours << ":"
                << results[i]->start.minutes << ":"
                << results[i]->start.seconds << endl;

            cout << "Finish: "
                << results[i]->finish.hours << ":"
                << results[i]->finish.minutes << ":"
                << results[i]->finish.seconds << endl;

            cout << "Club: " << results[i]->club << endl;
            cout << "----------------------------------\n";
        }

        // ������� ������
        for (int i = 0; i < size; i++) {
            delete results[i];
        }
    }
    catch (const char* error) {
        cout << "Error: " << error << endl;
    }

    return 0;
}