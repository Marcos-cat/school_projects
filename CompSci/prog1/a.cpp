#include <cmath>
#include <cstdio>
#include <iostream>

int main() {
    printf("Enter 3 numbers (seperated by spaces): ");

    int a, b, c;
    std::cin >> a >> b >> c;
    printf("a = %d, b = %d, c = %d \n", a, b, c);

    double answer1 = 3 * (a + b) - (double(c) / 4);
    double answer2 = sqrt(a * a + b * b);
    double answer3 = pow(a, b * c) / 4;
    double answer4 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

    printf("Answer #1 = %g \n", answer1);
    printf("Answer #2 = %g \n", answer2);
    printf("Answer #3 = %g \n", answer3);
    printf("Answer #4 = %g \n", answer4);

    return 0;
}
