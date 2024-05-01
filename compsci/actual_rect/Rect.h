#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

class Rect {
    double length = 0;
    double width = 0;

    bool is_valid_rectange() { return width > 0 && length > 0; }

    void ensure_defined() {
        if (!is_valid_rectange()) {
            std::cout << "Please define a rectangle.\n";
            define_rectangle();
        }
    }

  public:
    Rect() {}

    void define_rectangle() {
        while (true) {
            std::cout << "Enter length then width: ";
            std::cin >> length >> width;
            if (is_valid_rectange()) break;
            std::cout << "Please enter positive values for length and width.\n";
        }
    }

    void display_perimeter() {
        ensure_defined();
        double perimeter = 2 * (length + width);
        std::cout << "Perimeter = " << std::fixed << std::setprecision(1)
                  << perimeter << "\n";
    }

    void display_diagonal() {
        ensure_defined();

        double diagonal = sqrt(length * length + width * width);
        std::cout << "Diagonal = " << std::fixed << std::setprecision(1)
                  << diagonal << "\n";
    }

    void compare_area(Rect other) {
        double area = length * width;
        double other_area = other.length * other.width;
        std::string comparison = area == other_area  ? "the same area as"
                                 : area > other_area ? "more area than"
                                                     : "less area than";

        std::cout << "The first rectangle has " << comparison << " the second";
    }
};

