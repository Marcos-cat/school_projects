#include <iostream>

void print_arr(int list[], unsigned size) {
    std::cout << "[ ";
    for (int i = 0; i < size; i++) {
        std::cout << list[i] << " ";
    }
    std::cout << "]\n";
}

void sort_arr(int list[], unsigned size) {
    for (int i = 0; i < size; i++) {
        bool swapped = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                swapped = true;
                auto tmp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tmp;
            }
        }
        if (!swapped) break;
    }
}

int main() {
    unsigned len = 7;
    int list[] = {7, 5, -2, 18, 9, 0, -4};

    print_arr(list, len);

    sort_arr(list, len);

    print_arr(list, len);

    return 0;
}
