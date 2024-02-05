#include <cstdio>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

using std::cin;
using std::cout;
using std::string;

const int WINNING_SCORE = 5;
enum class RPS { Rock, Paper, Scissors };

std::optional<RPS> classify_input(string input) {
    if (input == "R" || input == "r") {
        return RPS::Rock;
    }
    if (input == "P" || input == "p") {
        return RPS::Paper;
    }
    if (input == "S" || input == "s") {
        return RPS::Scissors;
    }

    return std::nullopt;
}

RPS random_RPS() {
    int random = rand() % 3;
    switch (random) {
    case 0:
        return RPS::Rock;
    case 1:
        return RPS::Paper;
    default:
        return RPS::Scissors;
    }
}

enum class Result { Tie, Win, Lose };

Result first_wins(RPS first_choice, RPS second_choice) {
    if (first_choice == second_choice) {
        return Result::Tie;
    } else if ((first_choice == RPS::Rock && second_choice == RPS::Scissors) ||
               (first_choice == RPS::Paper && second_choice == RPS::Rock) ||
               (first_choice == RPS::Scissors && second_choice == RPS::Paper)) {
        return Result::Win;
    } else {
        return Result::Lose;
    }
}

string to_string_RPS(RPS rps) {
    switch (rps) {
    case RPS::Rock:
        return "Rock";
    case RPS::Paper:
        return "Paper";
    case RPS::Scissors:
        return "Scissors";
    }

    return "Infallible";
}

void rock_paper_scissors() {
    int computer_score = 0;
    int user_score = 0;

    while (user_score < WINNING_SCORE && computer_score < WINNING_SCORE) {
        std::optional<RPS> user_choice = std::nullopt;
        while (!user_choice.has_value()) {
            cout << "Choose [R]ock, [P]aper, or [S]cissors: ";
            string user_input;
            cin >> user_input;

            user_choice = classify_input(user_input);

            if (!user_choice.has_value()) {
                cout << "Bad input: '" << user_input << "'. Please input again.\n";
            }
        }

        RPS computer_choice = random_RPS();

        Result computer_result = first_wins(computer_choice, user_choice.value());

        switch (computer_result) {

        case Result::Tie:
            cout << "Tie! You both chose " << to_string_RPS(computer_choice) << "\n";
            break;
        case Result::Win:
            cout << "Computer Wins! The computer's " << to_string_RPS(computer_choice)
                 << " beat your " << to_string_RPS(user_choice.value()) << "\n";
            computer_score++;
            break;
        case Result::Lose:
            cout << "You Win! Your " << to_string_RPS(user_choice.value())
                 << " beat the computer's " << to_string_RPS(computer_choice) << "\n";
            user_score++;
            break;
        }

        char buf[1024];
        sprintf(buf, "SCORE- Computer: %d, You: %d\n", computer_score, user_score);
        cout << buf;
    }

    cout << (computer_score == WINNING_SCORE ? "The computer won!" : "You won!") << "\n";
}

std::optional<double> classify_grade(string grade) {
    std::unordered_map<string, double> map = {
        {"A+", 4.0}, {"A", 4.0}, {"A-", 3.7}, {"B+", 3.3}, {"B", 3.0}, {"B-", 2.7},
        {"C+", 2.3}, {"C", 2.0}, {"C-", 1.7}, {"D+", 1.3}, {"D", 1.0}, {"E", 0.0},
    };

    auto it = map.find(grade);
    if (it != map.end()) {
        auto value = it->second;
        return value;
    }

    return std::nullopt;
}

void gpa_calculator() {
    cout << "Enter the number of classes that you take: ";
    int classes;
    cin >> classes;

    double gpa_total_points = 0;

    for (int i = 0; i < classes; i++) {
        std::optional<double> gpa_grade_score = std::nullopt;
        double point_level;
        while (!gpa_grade_score.has_value()) {
            cout << "Enter the point level and grade for the class: ";
            string letter_grade;
            cin >> point_level >> letter_grade;
            gpa_grade_score = classify_grade(letter_grade);

            if (!gpa_grade_score.has_value()) {
                cout << "Bad grade value, please input again.\n";
            }
        }

        gpa_total_points += gpa_grade_score.value();

        if (point_level == 0.3) {
            gpa_total_points += 0.6;
        } else if (point_level == 0.4) {
            gpa_total_points += 1.0;
        }
    }

    double gpa = gpa_total_points / classes;

    cout << "Your GPA is: " << std::fixed << std::setprecision(2) << gpa << "\n";
}

int main() {
    srand(time(0));
    bool running = true;

    while (running) {
        cout << "Select [1]Rock Paper Scissors [2]GPA Calculator [3]Quit: ";
        char user_input;
        cin >> user_input;

        switch (user_input) {
        case '1':
            rock_paper_scissors();
            break;
        case '2':
            gpa_calculator();
            break;
        case '3':
            running = false;
            break;
        default:
            cout << "Bad input: '" << user_input << "'. Please try again.\n";
            break;
        }
    }

    cout << "Quitting\n";

    // system("pause");
    return 0;
}
