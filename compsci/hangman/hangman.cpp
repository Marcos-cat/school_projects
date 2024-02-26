#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

string stolower(string s) {
    string output = "";
    for (int i = 0; i < s.length(); i++) {
        output += tolower(s[i]);
    }
    return output;
}

char unique_user_guess(string guesses) {
    char guess;
    while (true) {
        cout << "Guess: ";
        cin >> guess;
        guess = tolower(guess);

        bool guess_is_unique = guesses.find(guess) == -1;
        if (guess_is_unique) {
            break;
        } else {
            cout << guess << " has already been guessed. Try again.\n";
        }
    }

    return guess;
}

string generate_board(string word, string guesses) {
    string board = "";
    for (auto _ : word) {
        board += "_ ";
    }

    for (char guess : guesses) {
        int guess_pos = -1;
        while (true) {
            guess_pos = word.find(guess, guess_pos + 1);
            if (guess_pos == -1) {
                break;
            }
            board[guess_pos * 2] = word[guess_pos];
        }
    }

    return board;
}

int main() {
    string word = "";
    cout << "Input: ";
    cin >> word;

    word = stolower(word);

    string guesses = "";
    char guess = unique_user_guess(guesses);
    guesses += guess;

    string board = generate_board(word, guesses);

    cout << board;

    return 0;
}
