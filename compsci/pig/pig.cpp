#include "./TwoDice.h"
#include <iostream>

void turn(int* player_score, TwoDice* dice) {
    int player_turn_score = 0;

    while (true) {
        dice->roll();
        int score = dice->score();

        std::cout << "Dice: " << dice->display() << "\n";
#ifdef _WIN32
        system("pause");
#endif

        if (TwoDice::SNAKE_EYES == score) {
            std::cout << "Womp womp, you rolled snake eyes :( back to zero\n";
            *player_score = 0;
            return;
        }

        if (TwoDice::DOUBLES == score) {
            std::cout << "Womp womp, you rolled doubles :( no extra points\n";
            return;
        }

        player_turn_score += score;

        std::cout << "Would you like to roll again? [y/n] ";
        char input;
        std::cin >> input;

        if ('y' != tolower(input)) {
            *player_score += player_turn_score;
            return;
        }
    }
}

const int WINNING_SCORE = 49;

int main() {
    srand(time(0));

    int player1_score = 0;
    int player2_score = 0;

    TwoDice dice;

    while (player1_score < WINNING_SCORE && player2_score < WINNING_SCORE) {
        std::cout << "\nPLAYER 1: \n";
        turn(&player1_score, &dice);
        std::cout << "Player 1's score is now " << player1_score << "\n";

        if (player1_score >= WINNING_SCORE) break;

        std::cout << "\nPLAYER 2: \n";
        turn(&player2_score, &dice);
        std::cout << "Player 2's score is now " << player2_score << "\n";
    }

    std::cout << "Player " << (player1_score > player2_score ? 1 : 2)
              << " wins the game!\n";
#ifdef _WIN32
    system("pause");
#endif

    return 0;
}
