#ifndef FILE_READER_H
#define FILE_READER_H

#include "marathon_result.h"

// Чтение данных из файла
void read(const char* file_name, marathon_result* array[], int& size);

#endif