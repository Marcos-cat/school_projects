#include "strings.h"
#include "vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string string;
typedef struct vector vector;

const char* FILE_PATH =
#ifdef __linux__
    "./cellphone.txt";
#else
    "U:\\cellphone.txt";
#endif

const char* CLEAR =
#ifdef __linux__
    "clear";
#else
    "cls";
#endif

typedef struct contact {
    string nickname;
    string firstname;
    string lastname;
    string phonenum;
    string email;
} contact;

contact parse_contact(const string string) {
    struct string fields[5] = {0};

    size_t field_start = 0;
    for (size_t field_i = 0; field_i < 5; field_i++) {
        for (size_t i = field_start; i < string.len; i++) {
            if (' ' == string.str[i]) {
                fields[field_i] =
                    string_new(string.str + field_start, i - field_start);

                field_start = i + 1;
                break;
            }

            if (i == string.len - 1) {
                fields[field_i] = string_new(
                    string.str + field_start, string.len - field_start
                );
            }
        }
    }

    return (contact){
        .nickname = fields[0],
        .firstname = fields[1],
        .lastname = fields[2],
        .phonenum = fields[3],
        .email = fields[4],
    };
}

void contact_free(contact contact) {
    string_free(&contact.nickname);
    string_free(&contact.firstname);
    string_free(&contact.lastname);
    string_free(&contact.phonenum);
    string_free(&contact.email);
}

void print_contact_info(const contact contact, FILE* stream) {
    fprintf(
        stream, "%.*s %.*s %.*s %.*s %.*s", (int)contact.nickname.len,
        contact.nickname.str, (int)contact.firstname.len, contact.firstname.str,
        (int)contact.lastname.len, contact.lastname.str,
        (int)contact.phonenum.len, contact.phonenum.str, (int)contact.email.len,
        contact.email.str
    );
}

int read_contacts(vector* contact_list) {
    FILE* contact_file = fopen(FILE_PATH, "r");

    if (!contact_file) return -1;

    while (true) {
        string line = string_readline(contact_file);
        if (NULL == line.str) break;
        contact new_contact = parse_contact(line);
        vector_push(contact_list, &new_contact);
        string_free(&line);
    }

    fclose(contact_file);

    return 0;
}

void write_contacts(vector* contact_list) {
    FILE* contact_file = fopen(FILE_PATH, "w");
    if (!contact_file) return;

    for (size_t i = 0; i < contact_list->len; i++) {
        print_contact_info(*(contact*)vector_at(contact_list, i), contact_file);
        if (i < contact_list->len - 1) fputc('\n', contact_file);
    }

    fclose(contact_file);
}

void add_contact(vector* contact_list) {
    printf("Enter nickname: ");
    string nickname = string_readline(stdin);
    printf("Enter firstname: ");
    string firstname = string_readline(stdin);
    printf("Enter lastname: ");
    string lastname = string_readline(stdin);
    printf("Enter phonenumber: ");
    string phonenum = string_readline(stdin);
    printf("Enter email: ");
    string email = string_readline(stdin);

    contact new_contact = {
        .nickname = nickname,
        .firstname = firstname,
        .lastname = lastname,
        .phonenum = phonenum,
        .email = email,
    };

    vector_push(contact_list, &new_contact);
}

void display_contacts(vector* contact_list) {
    if (1 == contact_list->len) {
        printf("There is 1 contact.\n\n");
    } else {
        printf("There are %ld contacts.\n\n", contact_list->len);
    }

    for (size_t i = 0; i < contact_list->len; i++) {
        print_contact_info(*(contact*)vector_at(contact_list, i), stdout);
        fputc('\n', stdout);
    }
    fputc('\n', stdout);
}

int index_of_nickname(vector* contact_list, const string nickname) {
    for (size_t i = 0; i < contact_list->len; i++) {
        if (string_cmp(
                nickname, ((contact*)vector_at(contact_list, i))->nickname
            ) == 0)
            return i;
    }
    return -1;
}

void delete_contact(vector* contact_list) {
    printf("Enter the nickname to delete: ");
    string nickname = string_readline(stdin);
    int index = index_of_nickname(contact_list, nickname);
    if (-1 == index) {
        printf(
            "No contact with the nickname `%.*s` exists.\n", (int)nickname.len,
            nickname.str
        );
        return;
    }

    contact_free(*(contact*)vector_at(contact_list, index));
    vector_del(contact_list, index);

    puts("Contact successfully deleted.");

    string_free(&nickname);
}

void search_contacts(vector* contact_list) {
    printf("Enter the lastname of the contact: ");
    string lastname = string_readline(stdin);

    vector matches_indices = vector_new(sizeof(size_t));

    for (size_t i = 0; i < contact_list->len; i++) {
        if (string_cmp(
                lastname, ((contact*)vector_at(contact_list, i))->lastname
            ) == 0) {
            vector_push(&matches_indices, &i);
        }
    }

    if (0 == matches_indices.len) {
        printf(
            "No contact has the lastname `%.*s`.\n", (int)lastname.len,
            lastname.str
        );
        return;
    }

    for (size_t i = 0; i < matches_indices.len; i++) {
        size_t index = *(size_t*)vector_at(&matches_indices, i);
        print_contact_info(*(contact*)vector_at(contact_list, index), stdout);
        fputc('\n', stdout);
    }

    string_free(&lastname);
}

const char NICKNAME[] = "nickname";
const char FIRSTNAME[] = "firstname";
const char LASTNAME[] = "lastname";
const char PHONENUMBER[] = "phonenumber";
const char EMAIL[] = "email";

void edit_contact(vector* contact_list) {
    printf("Enter the nickname of the person to edit: ");
    string nickname = string_readline(stdin);
    int index = index_of_nickname(contact_list, nickname);

    if (-1 == index) {
        printf(
            "No contact with nickname `%.*s` exists.\n", (int)nickname.len,
            nickname.str
        );
        return;
    }

    contact* contact = vector_at(contact_list, index);
    print_contact_info(*contact, stdout);
    fputc('\n', stdout);

    printf("Which field do you want to edit? "
           "[nickname|firstname|lastname|phonenumber|email]: ");
    string field = string_readline(stdin);

    printf("What should the new value be? ");
    string new_value = string_readline(stdin);
    string old_value;

    if (0 == string_cmp_lit(field, NICKNAME)) {
        old_value = contact->nickname;
        contact->nickname = new_value;
    } else if (0 == string_cmp_lit(field, FIRSTNAME)) {
        old_value = contact->firstname;
        contact->firstname = new_value;
    } else if (0 == string_cmp_lit(field, LASTNAME)) {
        old_value = contact->lastname;
        contact->lastname = new_value;
    } else if (0 == string_cmp_lit(field, PHONENUMBER)) {
        old_value = contact->phonenum;
        contact->phonenum = new_value;
    } else if (0 == string_cmp_lit(field, EMAIL)) {
        old_value = contact->email;
        contact->email = new_value;
    } else {
        printf(
            "`%.*s` is not a vaild field. Nothing was edited.\n",
            (int)field.len, field.str
        );
    }

    string_free(&nickname);
    string_free(&old_value);
    string_free(&field);
}

int contact_cmp(const void* contact1, const void* contact2) {
    return string_cmp(
        ((contact*)contact1)->nickname, ((contact*)contact2)->nickname
    );
}

int main() {
    vector contact_list = vector_new(sizeof(contact));

    int err = read_contacts(&contact_list);
    if (err) {
        puts("File read failed.");
        return EXIT_FAILURE;
    }

    vector_sort(&contact_list, &contact_cmp);

    void (*operations[])(vector*) = {
        add_contact,  delete_contact,  display_contacts,
        edit_contact, search_contacts, write_contacts,
    };

    size_t num_operations = sizeof(operations) / sizeof(void*);

    while (true) {
        printf("Actions: Add(1) Delete(2) Display(3) Edit(4) Search(5) "
               "Save Changes(6) Press any other key to Exit: ");

        char line[4];
        fgets(line, sizeof(line), stdin);
        int choice = line[0] - '1';

        if (0 > choice || choice >= num_operations) break;

        system(CLEAR);

        operations[choice](&contact_list);

        vector_sort(&contact_list, &contact_cmp);

#ifndef __linux__
        system("pause");
        system(CLEAR);
#endif
    }

    return EXIT_SUCCESS;
}
