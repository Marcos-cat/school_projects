// This program converts a Celsius temperature to a Fahrenheit temperature

#include <iostream> //Header file for input and output
using namespace std;

int main() {

    // Prompt user for input
    cout << endl << "Enter a temperature in Celsius: ";

    double celsius;
    cin >> celsius;

    // Calculate the Fahrenheit temperature
    double fahrenheit = 1.8 * celsius + 32;

    // Print the resulting Fahrenheit temperature
    cout << "The Fahrenheit temperature is: " << fahrenheit << endl;

    return 0;
}
