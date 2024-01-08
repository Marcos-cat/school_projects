// This program converts a Celsius temperature to a Fahrenheit temperature

#include <iostream> //Header file for input and output
using namespace std;

int main() {
    double celsius, fahrenheit; // Declare two double vars for data

    // Prompt user for input
    cout << endl << "Enter a temperature in Celsius : ";
    cin >> celsius;

    // Calculate the Fahrenheit temperature
    fahrenheit = 1.8 * celsius + 32;

    // Print the resulting Fahrenheit temperature
    cout << "The Fahrenheit temperature is : " << fahrenheit << endl;

    return 0;
}
