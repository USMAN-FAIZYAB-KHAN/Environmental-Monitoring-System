#include <time.h>

#ifndef DATE_UTIL_H
#define DATE_UTIL_H

// Function to format a date represented by a struct tm into a string
// Returns a dynamically allocated string that needs to be freed after use
char* formatDate(const struct tm *date);

// Function to get the formatted date of a specified number of days from the current date
// Returns a dynamically allocated string that needs to be freed after use
char* getDate(int days);

#endif
