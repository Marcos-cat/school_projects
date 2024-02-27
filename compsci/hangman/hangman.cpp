#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

const uint MAX_INCORRECT_GUESSES = 6;
const string HANGMAN[] = {
    " o  \n\n\n",

    " o  \n"
    " |  \n\n",

    " o  \n"
    "-|  \n\n",

    " o  \n"
    "-|- \n\n",

    " o  \n"
    "-|- \n"
    "/   \n",

    " o  \n"
    "-|- \n"
    "/ \\ \n",
};

string stolower(string s) {
    string output = "";
    for (char c : s) output += tolower(c);
    return output;
}

char unique_user_guess(string guesses) {
    char guess;
    while (true) {
        cout << "Guess: ";
        cin >> guess;
        guess = tolower(guess);

        bool guess_is_unique = guesses.find(guess) == -1;
        if (guess_is_unique) break;
        else cout << guess << " has already been guessed. Try again.\n";
    }

    return guess;
}

string generate_board(string word, string guesses) {
    string board = "";
    for (auto _ : word) board += "_ ";

    for (char guess : guesses) {
        int guess_pos = -1;
        while (true) {
            guess_pos = word.find(guess, guess_pos + 1);
            if (guess_pos == -1) break;
            board[guess_pos * 2] = word[guess_pos];
        }
    }

    return board;
}

bool word_is_guessed(string word, string guesses) {
    for (char c : word) if (guesses.find(c) == string::npos) return false;
    return true;
}

bool print_game_state(string word, string guesses) {
    // system("cls");
    system("clear");

    string board = generate_board(word, guesses);

    char last_guess = guesses.back();
    bool last_guess_was_incorrect = word.find(last_guess) == string::npos;
    uint incorrect_guesses = 0;
    for (char c : guesses) if (word.find(c) == string::npos) incorrect_guesses++;

    if(incorrect_guesses > 0) cout << HANGMAN[incorrect_guesses-1];
    cout << board << "\n";

    cout << "Incorrect Guesses: " << incorrect_guesses << "\n";
    cout << "Guesses: " << guesses << "\n";

    cout << last_guess << (last_guess_was_incorrect ? " was incorrect \n" : " was correct! \n");
    return incorrect_guesses >= MAX_INCORRECT_GUESSES;
}

int main() {
    bool running = true;
    while (running) {

        string word = "";
        cout << "Input: ";
        cin >> word;
        // system("cls");
        system("clear");

        word = stolower(word);

        string guesses = "";

        cout << generate_board(word, "") << "\n";

        bool game_is_lost = false;

        while (!word_is_guessed(word, guesses) && !game_is_lost) {
            char guess = unique_user_guess(guesses);
            guesses += guess;

            game_is_lost = print_game_state(word, guesses);
        }

        if (!game_is_lost) {
            cout << "You won! Nice job \n";
            cout << "It took you " << guesses.length() << " guesses \n";
        } else {
            cout << "You lost :(  L+Bozo+Ratio  womp womp \n";
        }

        cout << "Want to play again? ";
        char input;
        cin >> input;
        if (tolower(input) != 'y') running = false;
        // system("clear");
    }

    // system("pause");
    return 0;
}
