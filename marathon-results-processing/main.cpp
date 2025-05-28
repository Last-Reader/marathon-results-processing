﻿#include <iostream>
#include <iomanip>
#include "marathon_result.h"
#include "file_reader.h"
#include "constants.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Laba ¹4. GIT\n";
    cout << "Variant ¹11\n"; // Óêàæèòå íîìåð âàðèàíòà
    cout << "Author: Nikita Polyakov\n\n";

    marathon_result* results[MAX_FILE_ROWS_COUNT];
    int size;

    try {
        read("data.txt", results, size);
        cout << "***** Result *****\n\n";

        for (int i = 0; i < size; i++) {
            /********** Ó÷àñòíèê **********/
            cout << "Uchastnik ¹" << results[i]->number << ":\n";
            cout << "FIO...........: "
                << results[i]->runner.last_name << " "
                << results[i]->runner.first_name << " "
                << results[i]->runner.patronymic << '\n';

            /********** Âðåìÿ ñòàðòà **********/
            cout << "Start.........: "
                << setw(2) << setfill('0') << results[i]->start.hours << ":"
                << setw(2) << setfill('0') << results[i]->start.minutes << ":"
                << setw(2) << setfill('0') << results[i]->start.seconds << '\n';

            /********** Âðåìÿ ôèíèøà **********/
            cout << "Finish.........: "
                << setw(2) << setfill('0') << results[i]->finish.hours << ":"
                << setw(2) << setfill('0') << results[i]->finish.minutes << ":"
                << setw(2) << setfill('0') << results[i]->finish.seconds << '\n';

            /********** Êëóá **********/
            cout << "Club..........: " << results[i]->club << "\n\n";
        }

        // Îñâîáîæäåíèå ïàìÿòè
        for (int i = 0; i < size; i++) {
            delete results[i];
        }
    }
    catch (const char* error) {
        cout << "Error: " << error << '\n';
    }

    return 0;
}