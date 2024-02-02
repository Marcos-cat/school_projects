// This program converts a Celsius temperature to a Fahrenheit temperature

#include <stdio.h> //Header file for input and output
#include <stdlib.h>

int main() {
    // Prompt user for input
    printf("Enter a temperature in Celsius: ");

    char line[1024];
    fgets(line, 1024, stdin);
    double celsius = strtod(line, NULL);

    // Calculate the Fahrenheit temperature
    double fahrenheit = 1.8 * celsius + 32;

    // Print the resulting Fahrenheit temperature
    printf("The Fahrenheit temperature is: %g", fahrenheit);

    return 0;
}
