#ifndef RETRIEVE_DATA_H
#define RETRIEVE_DATA_H

// Function declaration for accessing weather data using a third-party API
// Parameters:
//   - filename: Name of the file to save the API response
//   - date: Date for which weather data is requested
//   - history: Flag indicating whether to fetch historical data
// Returns:
//   - 0 on success, 1 on failure
int access_weather_data(char * filename, char * date, int history);

#endif // End of RETRIEVE_DATA_H
