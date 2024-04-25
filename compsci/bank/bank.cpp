#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

const char CLEAR[] =
#ifdef _WIN32
    "cls";
#else
    "clear";
#endif

class BankAccount {
    const std::string DEFAULT_PASSWORD = "password";

  private:
    double balance_dollars;
    std::string password;

  public:
    BankAccount() : balance_dollars(0), password(DEFAULT_PASSWORD) {
        std::cout << "The account password is `" << DEFAULT_PASSWORD << "`\n";
    }

    void withdraw() {
        if (!confirm_password()) return;
        std::cout << "How many dollars will be withdrawn? ";
        double amount_dollars;
        std::cin >> amount_dollars;
        if (balance_dollars < amount_dollars) {
            std::cout << "The amount withdrawn is over the account balance.\n";
            return;
        }
        balance_dollars -= amount_dollars;
    }

    void deposit() {
        std::cout << "How many dollars will be withdrawn? ";
        double amount_dollars;
        std::cin >> amount_dollars;
        if (!confirm_password()) return;
        balance_dollars += amount_dollars;
    }

    void display_balance() {
        std::cout << "Account balance: $" << std::fixed << std::setprecision(2)
                  << balance_dollars << ".\n";
    }

    void change_password() {
        if (!confirm_password()) return;
        std::cout << "Enter new password: ";
        std::string new_password;
        std::cin >> new_password;
        password = new_password;
    }

    bool confirm_password() {
        if (ask_password() == password) return true;
        std::cout << "Incorrect password. Access denied.\n";
        return false;
    }

    static std::string ask_password() {
        std::cout << "Enter the account password: ";
        std::string password_attempt;
        std::cin >> password_attempt;
        return password_attempt;
    }
};

int main() {
    BankAccount account;
    bool running = true;
    while (running) {
        std::cout << "1. Change your password\n"
                  << "2. Make a deposit\n"
                  << "3. Make a withdrawal\n"
                  << "4. Display your balance\n"
                  << "5. Exit\n";
        char input;
        std::cin >> input;
        system(CLEAR);

        switch (input) {
        case '1': account.change_password(); break;
        case '2': account.deposit(); break;
        case '3': account.withdraw(); break;
        case '4': account.display_balance(); break;
        case '5': running = false; break;
        }
#ifdef _WIN32
        if (running) system("pause");
        system(CLEAR);
#endif
    }
    return 0;
}
