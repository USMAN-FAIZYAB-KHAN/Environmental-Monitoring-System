#include <stdio.h>
#include <stdlib.h>
#include "process_data.h"
#include "display_data.h"

void display_environment_data(EnvironmentData yesterday, EnvironmentData today, EnvironmentData tomorrow) {
    // Current Environmental Data Section
    printf("   \033[30;46m Current Environmental Data \033[0m\n");
    printf("\033[30;47m Temperature         %5.2lf °C     \033[0m\n", today.temp_c);
    printf("\033[30;47m Wind Speed          %5.2lf kph    \033[0m\n", today.wind_kph);
    printf("\033[30;47m Humidity            %5d %%      \033[0m\n\n", today.humidity);

    // Today Summary Section
    printf("         \033[30;46m Today Summary \033[0m\n");
    printf("\033[30;47m Average Temperature  %5.2lf °C    \033[0m\n", today.avgtemp_c);
    printf("\033[30;47m Average Wind Speed   %5.2lf kph   \033[0m\n", today.avgwind_kph);
    printf("\033[30;47m Average Humidity     %5.2lf %%     \033[0m\n", today.avghumidity);
    printf("\033[30;47m Maximum Temperature  %5.2lf °C    \033[0m\n", today.avgtemp_c); // You might want to correct the data here
    printf("\033[30;47m Minimum Temperature  %5.2lf °C    \033[0m\n", today.avgtemp_c); // And here
    printf("\033[30;47m Maximum Wind Speed   %5.2lf kph   \033[0m\n\n", today.avgwind_kph); // And here

    // Analysis Section
    printf("            \033[30;46m Analysis \033[0m\n");
    printf("\033[30;46m Changes as compared to yesterday \033[0m\n");
    printf("\033[30;47m Temperature change  %5.2lf °C     \033[0m\n", today.avgtemp_c - yesterday.avgtemp_c);
    printf("\033[30;47m Humidity change     %5.2lf %%      \033[0m\n", today.avghumidity - yesterday.avghumidity);
    printf("\033[30;47m Wind Speed change   %5.2lf kph    \033[0m\n", today.avgwind_kph - yesterday.avgwind_kph);


    printf("\033[30;46m Changes predicted for tomorrow   \033[0m\n");
    printf("\033[30;47m Temperature change  %5.2lf °C     \033[0m\n", tomorrow.avgtemp_c - today.avgtemp_c);
    printf("\033[30;47m Humidity change     %5.2lf %%      \033[0m\n", tomorrow.avghumidity - today.avghumidity);
    printf("\033[30;47m Wind Speed change   %5.2lf kph    \033[0m\n\n", tomorrow.avgwind_kph - today.avgwind_kph);

    // Hourly Weather Data Table
    printf("              \033[30;46m Today Hourly Data \033[0m\n");
    printf("\033[30;46m Time     Temperature    Wind Speed    Humidity \033[0m\n");
    for (int i = 0; i < 24; i++) {
            printf("\033[30;47m %02d:00    %-5.2lf °C       %-5.2lf kph     %-3d%%     \033[0m\n", 
                   i, today.hourly_temp[i], today.hourly_wind[i], today.hourly_humidity[i]);

    }
}