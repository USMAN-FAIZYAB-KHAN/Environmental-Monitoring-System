#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "analyze_data.h"

// Function to analyze environmental data and log anomalies
void analyze_environment_data(EnvironmentData yesterday, EnvironmentData today, EnvironmentData tomorrow, FILE* output_file_path) {
    fprintf(output_file_path, "Current Environmental Data:\n");
    fprintf(output_file_path, "Temperature: %.2lf °C\n", today.temp_c);
    fprintf(output_file_path, "Wind Speed: %.2lf kph\n", today.wind_kph);
    fprintf(output_file_path, "Humidity: %d %% \n\n", today.humidity);

    fprintf(output_file_path, "Today Summary\n");
    fprintf(output_file_path, "Average Temperature: %.2lf °C\n", today.avgtemp_c);
    fprintf(output_file_path, "Average Wind Speed: %.2lf kph\n", today.avgwind_kph);
    fprintf(output_file_path, "Average Humidity: %.2lf %%\n", today.avghumidity);
    fprintf(output_file_path, "Maximum Temperature: %.2lf °C\n", today.avgtemp_c);
    fprintf(output_file_path, "Minimum Temperature: %.2lf °C\n", today.avgtemp_c);
    fprintf(output_file_path, "Maximum Wind Speed: %.2lf kph\n\n", today.avgtemp_c);

    fprintf(output_file_path, "Analysis:\n");
    fprintf(output_file_path, "Changes as compared to yesterday:\n");
    fprintf(output_file_path, "Temperature change: %.2lf °C\n", today.avgtemp_c - yesterday.avgtemp_c);
    fprintf(output_file_path, "Humidity change: %.2lf %%\n", today.avghumidity - yesterday.avghumidity);
    fprintf(output_file_path, "Wind Speed change: %.2lf kph\n\n", today.avgwind_kph - yesterday.avgwind_kph);
    fprintf(output_file_path, "Changes predicted for tomorrow:\n");
    fprintf(output_file_path, "Temperature change: %.2lf °C\n", tomorrow.avgtemp_c - today.avgtemp_c);
    fprintf(output_file_path, "Humidity change: %.2lf %%\n", tomorrow.avghumidity - today.avghumidity);
    fprintf(output_file_path, "Wind Speed change: %.2lf kph\n\n", tomorrow.avgwind_kph - today.avgwind_kph);

    fprintf(output_file_path, "Hourly Weather Data:\n");
    fprintf(output_file_path, "Time     Temperature    Wind Speed    Humidity\n");
    for (int i=0; i<24; i++) {
        fprintf(output_file_path, "%02d%-7s%-5.2lf%-11s%-5.2lf%-9s%-3d%-s\n", i, ":00", today.hourly_temp[i], " °C", today.hourly_wind[i], " kph", today.hourly_humidity[i], "%");
    }

    // Thresholds
    const double upper_threshold_temp = 40.0; // Temperature upper limit
    const double lower_threshold_temp = 10.0; // Temperature lower limit
    const double upper_threshold_wind = 50.0; // Wind speed upper limit
    const double lower_threshold_wind = 2.0;  // Wind speed lower limit
    const int upper_threshold_humidity = 90;  // Humidity upper limit
    const int lower_threshold_humidity = 10;  // Humidity lower limit

    // Get the current time
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    FILE *fp = fopen("anomalies.log", "a");
    // Check and log temperature anomaly
    if (today.temp_c > upper_threshold_temp) {
        fprintf(fp, "[%s] High Temperature Anomaly Detected: %.2lf °C. Advice: Keep hydrated and avoid prolonged sun exposure.\n", buffer, today.temp_c);
        system("notify-send -u critical --icon=dialog-warning \"High Temperature Anomaly Detected!\" \"<b>Advice: </b> Keep hydrated and avoid prolonged sun exposure.\"");
    } else if (today.temp_c < lower_threshold_temp) {
        fprintf(fp, "[%s] Low Temperature Anomaly Detected: %.2lf °C. Advice: Dress warmly and avoid prolonged exposure to cold.\n", buffer, today.temp_c);
        system("notify-send -u critical --icon=dialog-warning \"Low Temperature Anomaly Detected!\" \"<b>Advice: </b> Dress warmly and avoid prolonged exposure to cold.\"");
    }

    // Check and log wind speed anomaly
    if (today.wind_kph > upper_threshold_wind) {
        fprintf(fp, "[%s] High Wind Speed Anomaly Detected: %.2lf kph. Advice: Be cautious of strong winds, secure loose objects.\n", buffer, today.wind_kph);
        system("notify-send -u critical --icon=dialog-warning \"High Wind Speed Anomaly Detected!\" \"<b>Advice: </b> Be cautious of strong winds, secure loose objects.\"");    
    } else if (today.wind_kph < lower_threshold_wind) {
        fprintf(fp, "[%s] Low Wind Speed Anomaly Detected: %.2lf kph. Advice: Expect stagnant air conditions.\n", buffer, today.wind_kph);
        system("notify-send -u critical --icon=dialog-warning \"Low Wind Speed Anomaly Detected!\" \"<b>Advice: </b> Expect stagnant air conditions.\"");        
    }

    // Check and log humidity anomaly
    if (today.humidity > upper_threshold_humidity) {
        fprintf(fp, "[%s] High Humidity Anomaly Detected: %d%%. Advice: Expect muggy conditions, stay cool and hydrated.\n", buffer, today.humidity);
        system("notify-send -u critical --icon=dialog-warning \"High Humidity Anomaly Detected!\" \"<b>Advice: </b> Expect muggy conditions, stay cool and hydrated.\"");        
    
    } else if (today.humidity < lower_threshold_humidity) {
        fprintf(fp, "[%s] Low Humidity Anomaly Detected: %d%%. Advice: Be aware of dry conditions, moisturize and stay hydrated.\n", buffer, today.humidity);
        system("notify-send -u critical --icon=dialog-warning \"Low Humidity Anomaly Detected!\" \"<b>Advice: </b> Be aware of dry conditions, moisturize and stay hydrated.\"");        

    }
}