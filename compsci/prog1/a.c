#include <math.h>
#include <stdio.h>

int main() {
    printf("Enter 3 numbers (seperated by spaces): ");

    char line[1024];
    fgets(line, 1024, stdin);
    int a, b, c;
    sscanf(line, "%d %d %d", &a, &b, &c);

    printf("a = %d, b = %d, c = %d \n", a, b, c);

    printf("Answer #1 = %g \n", 3 * (a + b) - ((double)c / 4));
    printf("Answer #2 = %g \n", sqrt(a * a + b * b));
    printf("Answer #3 = %g \n", pow(a, b * c) / 4);
    printf("Answer #4 = %g \n", (-b + sqrt(b * b - 4 * a * c)) / (2 * a));

    return 0;
}
