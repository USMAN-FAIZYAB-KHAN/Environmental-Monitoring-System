#include "retrieve_data.h"
#include <time.h>
#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

// callback function to write the data fetched by the api to a file
size_t write_callback(void* contents, size_t size, size_t nmemb, FILE* file) {
    size_t written = fwrite(contents, size, nmemb, file);
    return written;
}


int access_weather_data(char * filename, char * date, int history) {
    
    // Initialize libcurl
    CURL* hnd = curl_easy_init();
    if (!hnd) {
        fprintf(stderr, "Error initializing libcurl.\n");
        return 1;  // Exit with an error code
    }


    // Open the file for writing
    FILE* json_file = fopen(filename, "w");
    if (!json_file) {
        fprintf(stderr, "Error opening the file for writing.\n");
        curl_easy_cleanup(hnd);
        return 1;  // Exit with an error code
    }

    // set the url with the date provided as an argument
    char url[100];
    if (! history) 
    {
        strcpy(url, "https://weatherapi-com.p.rapidapi.com/forecast.json?q=Karachi");
    }
    else
    {
        strcpy(url, "https://weatherapi-com.p.rapidapi.com/history.json?q=Karachi");
    }
    strcat(url, "&dt=");
    strcat(url, date);
    
    // Set the options for libcurl
    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, url);
    curl_easy_setopt(hnd, CURLOPT_SSL_VERIFYPEER, 0);


    // Set the headers
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "X-RapidAPI-Key: 6a53f96e8emshbd482eccd871b64p1f89eejsn5fef25e81b4a");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: weatherapi-com.p.rapidapi.com");
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

    // Set the write callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
    // Pass the file pointer to the callback function
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, json_file);

    // Perform the request
    CURLcode ret = curl_easy_perform(hnd);
    if (ret != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
        curl_easy_cleanup(hnd);
        fclose(json_file);
        return 1;  // Exit with an error code
    }

    // Clean up and close the file
    fclose(json_file);
    curl_easy_cleanup(hnd);
    curl_slist_free_all(headers);

    return 0;
}

