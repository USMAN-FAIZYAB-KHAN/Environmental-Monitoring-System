#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "date_util.h"

char* formatDate(const struct tm *date) {
    char* dateString = malloc(11); // YYYY-MM-DD + null terminator
    if (dateString != NULL) {
        strftime(dateString, 11, "%Y-%m-%d", date);
    }
    return dateString; // Remember to free this memory after use
}

char* getDate(int days) {
    time_t now = time(NULL);
    struct tm date = *localtime(&now);
    date.tm_mday += days;
    mktime(&date);
    return formatDate(&date);
}