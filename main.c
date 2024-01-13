#include "retrieve_data.h"
#include "analyze_data.h"
#include "process_data.h"
#include "display_data.h"
#include <stdlib.h>
#include <stdio.h>
#include "date_util.h"



int main() {
    // getting the environment data for today
    access_weather_data("Data/response_today.json", getDate(0), 0);
    // getting the environment data for yesterday
    access_weather_data("Data/response_yesterday.json", getDate(-1), 1);
    // getting the environment data for tomorrow
    access_weather_data("Data/response_tomorrow.json", getDate(1), 0);

    // processing the data
    EnvironmentData yesterday = process_weather_data("./Data/response_yesterday.json", 1);
    EnvironmentData today = process_weather_data("./Data/response_today.json", 0);
    EnvironmentData tomorrow = process_weather_data("./Data/response_tomorrow.json", 0);

    
    FILE * fp = fopen("./Data/processed_data.txt", "w");
    analyze_environment_data(yesterday, today, tomorrow, fp);
    display_environment_data(yesterday, today, tomorrow);
    fclose(fp);
    
    return 0;
}