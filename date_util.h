#include <time.h>
#ifndef DATE_UTIL_H
#define DATE_UTIL_H
char* formatDate(const struct tm *date);
char* getDate(int days);
#endif