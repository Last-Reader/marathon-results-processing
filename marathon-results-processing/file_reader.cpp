#include "file_reader.h"
#include "constants.h"
#include <fstream>
#include <cstring>
#include <limits>

// ����������� ������ ������� (��:��:��) � ��������� time_mark
time_mark convert_time(char* str) {
    time_mark result;
    char* context = nullptr;
    char* token = strtok_s(str, ":", &context);
    result.hours = token ? atoi(token) : 0;
    token = strtok_s(nullptr, ":", &context);
    result.minutes = token ? atoi(token) : 0;
    token = strtok_s(nullptr, ":", &context);
    result.seconds = token ? atoi(token) : 0;
    return result;
}

// ������� ������ ������ �� �����
void read(const char* file_name, marathon_result* array[], int& size) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        size = 0;
        char tmp_buffer[MAX_STRING_SIZE];

        while (file.good()) {
            marathon_result* item = new marathon_result;

            // ������ ������
            if (!(file >> item->number)) {
                delete item;
                break;
            }

            // ������ ���
            if (!(file >> item->runner.last_name)) break;
            if (!(file >> item->runner.first_name)) break;
            if (!(file >> item->runner.patronymic)) break;

            // ������ ������� ������
            if (!(file >> tmp_buffer)) break;
            item->start = convert_time(tmp_buffer);

            // ������ ������� ������
            if (!(file >> tmp_buffer)) break;
            item->finish = convert_time(tmp_buffer);

            // ������� �������� � ������ �����
            file.ignore(1, ' '); // ������� ������ �������
            file.getline(item->club, MAX_STRING_SIZE, '\n'); // ������ �� ����� ������

            array[size++] = item;
        }
        file.close();
    }
    else {
        throw "������ �������� �����";
    }
}