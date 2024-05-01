#include <cstdlib>
#include <iostream>
#include <string>

class TwoDice {
    int dice1 = 1;
    int dice2 = 1;

    int diceValue() { return (rand() % 6) + 1; }

  public:
    static const int SNAKE_EYES = -1;
    static const int DOUBLES = 0;

    TwoDice() {}

    void roll() {
        dice1 = diceValue();
        dice2 = diceValue();
    }

    /*
     * Returns `-1` if both dice are `1`.
     * Returns `0` if both dice are the same (doubles).
     * Returns the sum of the rolls otherwise
     */
    int score() {
        if (1 == dice1 && 1 == dice2) return SNAKE_EYES;
        if (dice1 == dice2) return DOUBLES;
        return dice1 + dice2;
    }

    std::string display() {
        return std::to_string(dice1) + " " + std::to_string(dice2);
    }
};
