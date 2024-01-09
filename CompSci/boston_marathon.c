#include <stdio.h>

const double MILES_PER_KILOMETER = 1.0 / 1.61;
const int SECONDS_PER_MINUTE = 60;
const int MINUTES_PER_HOUR = 60;
const int SECONDS_PER_HOUR = SECONDS_PER_MINUTE * MINUTES_PER_HOUR;

int main() {
    char line[1024];

    printf("Input the distance in kilometers: ");
    fgets(line, 1024, stdin);
    double kilometers_ran;
    sscanf(line, "%lf", &kilometers_ran);

    printf("Input the race time in seconds: ");
    fgets(line, 1024, stdin);
    int total_seconds_ran;
    sscanf(line, "%d", &total_seconds_ran);

    double miles_ran = kilometers_ran * MILES_PER_KILOMETER;
    double hours_ran = (double)total_seconds_ran / SECONDS_PER_HOUR;
    double miles_per_hour_ran = miles_ran / hours_ran;

    int rounded_hours_ran = (int)(hours_ran);
    int rounded_minutes_ran =
        total_seconds_ran / SECONDS_PER_MINUTE % MINUTES_PER_HOUR;
    int seconds_ran = total_seconds_ran % SECONDS_PER_MINUTE;

    printf("\n");
    printf("Distance:      %.1f miles \n", miles_ran);
    printf("Average Speed: %.1f mph \n", miles_per_hour_ran);
    printf("Time:          %dh %dm %ds \n", rounded_hours_ran,
           rounded_minutes_ran, seconds_ran);

    return 0;
}
