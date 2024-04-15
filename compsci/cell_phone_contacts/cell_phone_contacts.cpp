#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;

const char CLEAR[] =
#if defined(__linux__)
    "clear";
#else
    "cls";
#endif

const char FILE_PATH[] =
#if defined(__linux__)
    "./cellphone.txt";
#else
    "U:\\cellphone.txt";
#endif

struct contact {
    string nickname;
    string firstname;
    string lastname;
    string phonenumber;
    string email;
};

string stringify_contact(struct contact* contact) {
    string contact_str = "";
    contact_str += contact->nickname + " ";
    contact_str += contact->firstname + " ";
    contact_str += contact->lastname + " ";
    contact_str += contact->phonenumber + " ";
    contact_str += contact->email;
    return contact_str;
}

std::vector<struct contact*> g_contacts;

void sort_contacts() {
    for (int i = 0; i < g_contacts.size(); i++) {
        bool swapped = false;
        for (int j = 0; j < g_contacts.size() - i - 1; j++) {
            if (g_contacts[j]->nickname.compare(g_contacts[j + 1]->nickname) <
                0) {
                swapped = true;
                auto tmp = g_contacts[j];
                g_contacts[j] = g_contacts[j + 1];
                g_contacts[j + 1] = tmp;
            }
        }
        if (!swapped) break;
    }
}

void add_contact() {
    string firstname, lastname, nickname, phonenumber, email;
    cout << "Enter the nickname: ";
    cin >> nickname;
    cout << "Enter the first name: ";
    cin >> firstname;
    cout << "Enter the last name: ";
    cin >> lastname;
    cout << "Enter the phone number: ";
    cin >> phonenumber;
    cout << "Enter the email: ";
    cin >> email;

    auto new_contact =
        new contact{nickname, firstname, lastname, phonenumber, email};

    g_contacts.push_back(new_contact);

    sort_contacts();
}

int find_nickname_index(string nickname) {
    for (int i = 0; i < g_contacts.size(); i++) {
        if (g_contacts[i]->nickname == nickname) return i;
    }
    return -1;
}

void delete_contact() {
    cout << "Enter the nickname of the person to delete: ";
    string nickname;
    cin >> nickname;
    int contact_index = find_nickname_index(nickname);

    if (-1 == contact_index) {
        cout
            << "No contact was deleted because no contact with matching nickname exists.\n";
        return;
    }

    delete g_contacts[contact_index];
    g_contacts.erase(g_contacts.begin() + contact_index);
    cout << "Contact " << nickname << " was successfully deleted.\n";
}

void display_contacts() {
    for (auto contact : g_contacts) cout << stringify_contact(contact) << "\n";
}

void edit_contact() {
    cout << "Enter the nickname of the person to edit: ";
    string nickname;
    cin >> nickname;
    int contact_index = find_nickname_index(nickname);

    if (-1 == contact_index) {
        cout
            << "No contact was edited because no contact with matching nickname exists.\n";
        return;
    }

    auto contact = g_contacts[contact_index];

    cout << stringify_contact(contact) << "\n";
    cout
        << "Which field do you want to edit? [nickname|firstname|lastname|phonenumber|email]: ";

    string field;
    cin >> field;
    cout << "What should the new value be? ";
    string new_value;
    cin >> new_value;

    if ("nickname" == field) {
        contact->nickname = new_value;
    } else if ("firstname" == field) {
        contact->firstname = new_value;
    } else if ("lastname" == field) {
        contact->lastname = new_value;
    } else if ("phonenumber" == field) {
        contact->phonenumber = new_value;
    } else if ("email" == field) {
        contact->email = new_value;
    } else {
        cout << "`" << field << "` is not a vaild field. Nothing was edited.";
    }

    sort_contacts();
}

void save_contacts() {
    std::ofstream contact_file(FILE_PATH);
    for (int i = 0; i < g_contacts.size(); i++) {
        contact_file << stringify_contact(g_contacts[i]);
        if (i < g_contacts.size() - 1) contact_file << "\n";
    }
    cout << "Contacts successfully saved to file.\n";
    contact_file.close();
}

void search_contacts() {
    cout << "Enter the lastname: ";
    string lastname;
    cin >> lastname;

    std::vector<struct contact*> matching_contacts;
    for (auto contact : g_contacts) {
        if (contact->lastname == lastname) matching_contacts.push_back(contact);
    }

    if (matching_contacts.empty()) {
        cout << "No contact has the lastname `" << lastname << "`.\n";
        return;
    }

    cout << matching_contacts.size() << " contacts match:\n";
    for (auto contact : matching_contacts) {
        cout << stringify_contact(contact) << "\n";
    }
}

int main() {
    std::ifstream contacts_file(FILE_PATH);

    while (!contacts_file.eof()) {
        struct contact* next_contact = new contact{};
        contacts_file >> next_contact->nickname;
        contacts_file >> next_contact->firstname;
        contacts_file >> next_contact->lastname;
        contacts_file >> next_contact->phonenumber;
        contacts_file >> next_contact->email;

        g_contacts.push_back(next_contact);
    }
    sort_contacts();

    bool running = true;
    while (running) {
        cout
            << "Actions: Add(1) Delete(2) Display(3) Edit(4) Search(5) Save Changes(6) Press any other key to Exit: ";
        char action;
        cin >> action;

        system(CLEAR);

        switch (action) {
        case '1': add_contact(); break;
        case '2': delete_contact(); break;
        case '3': display_contacts(); break;
        case '4': edit_contact(); break;
        case '5': search_contacts(); break;
        case '6': save_contacts(); break;
        default: running = false;
        }

#if defined(_WIN32)
        system("pause");
        system(CLEAR);
#endif
    }

    for (auto contact : g_contacts) delete contact;

    return EXIT_SUCCESS;
}
