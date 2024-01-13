#include <stdio.h>
#include "process_data.h"

#ifndef ANALYZE
#define ANALYZE
void analyze_environment_data(EnvironmentData yesterday, EnvironmentData today, EnvironmentData tomorrow, FILE* output_file_path);
#endif