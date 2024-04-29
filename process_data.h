#ifndef ANALYZE_DATA_H
#define ANALYZE_DATA_H

typedef struct {
    double temp_c;
    double wind_kph;
    int humidity;
    double hourly_temp[24];
    double hourly_wind[24];
    int hourly_humidity[24];
    double avgtemp_c;
    double avghumidity;
    double avgwind_kph;
    double maxtemp_c;
    double mintemp_c;
    double maxwind_kph;
} EnvironmentData;

EnvironmentData process_weather_data(char *filename, int history);
#endif