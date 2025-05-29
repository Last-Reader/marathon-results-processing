#ifndef PROCESSING_H
#define PROCESSING_H

#include "D:\Programm\Project\GitLaba\marathon-results-processing\marathon-results-processing/marathon_result.h"

#ifdef __cplusplus
extern "C" {
#endif

	const char* find_best_time(struct marathon_result* array[], int size);

#ifdef __cplusplus
}
#endif

#endif