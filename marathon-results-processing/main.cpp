#include <iostream>
#include <iomanip>
#include "marathon_result.h"
#include "file_reader.h"
#include "constants.h"

using namespace std;

int main() {
    cout << "Laboratory work #4. GIT\n";
    cout << "Variant #1\n";
    cout << "Author: Nikita Polyakov\n";
    cout << "Group: 24PI\n";

    marathon_result* results[MAX_FILE_ROWS_COUNT];
    int size;

    try {
        read("data.txt", results, size);
        cout << "***** Result *****\n\n";

        for (int i = 0; i < size; i++) {
            /********** Участник **********/
            cout << "Uchastnik №" << results[i]->number << ":\n";
            cout << "FIO...........: "
                << results[i]->runner.last_name << " "
                << results[i]->runner.first_name << " "
                << results[i]->runner.patronymic << '\n';

            /********** Время старта **********/
            cout << "Start.........: "
                << setw(2) << setfill('0') << results[i]->start.hours << ":"
                << setw(2) << setfill('0') << results[i]->start.minutes << ":"
                << setw(2) << setfill('0') << results[i]->start.seconds << '\n';

            /********** Время финиша **********/
            cout << "Finish.........: "
                << setw(2) << setfill('0') << results[i]->finish.hours << ":"
                << setw(2) << setfill('0') << results[i]->finish.minutes << ":"
                << setw(2) << setfill('0') << results[i]->finish.seconds << '\n';

            /********** Клуб **********/
            cout << "Club..........: " << results[i]->club << "\n\n";
        }

        // Освобождение памяти
        for (int i = 0; i < size; i++) {
            delete results[i];
        }
    }
    catch (const char* error) {
        cout << "Error: " << error << '\n';
    }
    return 0;
}