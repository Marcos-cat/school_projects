#include "./Rect.h"
#include <iostream>

int main() {
    Rect rect1, rect2;

    bool running = true;
    while (running) {
        std::cout << "1. Define Rectangles\n"
                     "2. Show Perimeters\n"
                     "3. Show Diagonals\n"
                     "4. Compare Areas\n"
                     "5. Exit\n";
        uint input = 0;
        std::cin >> input;
        switch (input) {
        case 1:
            rect1.define_rectangle();
            rect2.define_rectangle();
            break;
        case 2:
            rect1.display_perimeter();
            rect2.display_perimeter();
            break;
        case 3:
            rect1.display_diagonal();
            rect2.display_diagonal();
            break;
        case 4: rect1.compare_area(rect2); break;
        case 5: running = false; break;
        default: std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}
