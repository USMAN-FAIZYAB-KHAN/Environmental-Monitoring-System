#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process_data.h"
#include <cjson/cJSON.h>


EnvironmentData process_weather_data(char *filename, int history) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error opening the file for reading.\n");
        exit(1);  // Exit with an error code
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *file_contents = malloc(file_size * sizeof(char));

    fread(file_contents, sizeof(char), file_size, fp);

    EnvironmentData weather;

    cJSON *json = cJSON_Parse(file_contents);
    free(file_contents);
    if (!history) {
        cJSON *current = cJSON_GetObjectItem(json, "current");
        weather.temp_c = cJSON_GetObjectItem(current, "temp_c")->valuedouble;
        weather.wind_kph = cJSON_GetObjectItem(current, "wind_kph")->valuedouble;
        weather.humidity = cJSON_GetObjectItem(current, "humidity")->valueint;
    } else {
        weather.temp_c = 0;
        weather.wind_kph = 0;
        weather.humidity = 0;
    }

    cJSON *forecast = cJSON_GetObjectItem(json, "forecast");
    cJSON *forecastday = cJSON_GetObjectItem(forecast, "forecastday");
    cJSON *day = cJSON_GetArrayItem(forecastday, 0);
    cJSON *day_data = cJSON_GetObjectItem(day, "day");
    cJSON *hourly = cJSON_GetObjectItem(day, "hour");

    weather.avgtemp_c = cJSON_GetObjectItem(day_data, "avgtemp_c")->valuedouble;  
    weather.avghumidity = cJSON_GetObjectItem(day_data, "avghumidity")->valuedouble;
    weather.avgwind_kph = cJSON_GetObjectItem(day_data, "maxwind_kph")->valuedouble;
    weather.maxtemp_c = cJSON_GetObjectItem(day_data, "maxtemp_c")->valuedouble;
    weather.mintemp_c = cJSON_GetObjectItem(day_data, "mintemp_c")->valuedouble;

    cJSON *curr = NULL;
    for (int i=0; i<24; i++) {
        curr = cJSON_GetArrayItem(hourly, i);
        weather.hourly_temp[i] = cJSON_GetObjectItem(curr, "temp_c")->valuedouble;
        weather.hourly_wind[i] = cJSON_GetObjectItem(curr, "wind_kph")->valuedouble;
        weather.hourly_humidity[i] = cJSON_GetObjectItem(curr, "humidity")->valuedouble;
    }

    return weather;

    cJSON_Delete(json);
    fclose(fp);
}
