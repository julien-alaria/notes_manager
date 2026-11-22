#include <stdio.h>
#include <string.h>
#include "student.h"

static void empty_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int read_int(const char *prompt, int *out) {
    char line[64];
    printf("%s", prompt);
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return -1;
    }
    if (strchr(line, '\n') == NULL) {
        empty_buffer();
    }
    if (sscanf(line, "%d", out) != 1) {
        printf("Invalid input\n");
        return -1;
    }
    return 0;
}

static int read_string(const char *prompt, char *out, size_t size) {
    printf("%s", prompt);
    if (fgets(out, (int)size, stdin) == NULL) {
        return -1;
    }
    if (strchr(out, '\n') == NULL) {
        empty_buffer();
    }
    out[strcspn(out, "\n")] = '\0';
    if (out[0] == '\0') {
        printf("Invalid input\n");
        return -1;
    }
    return 0;
}

int main(void) {
    struct Student *head = NULL;
    int choice;

    do {
        printf("Menu\n");
        printf("1. Add student\n");
        printf("2. Show students\n");
        printf("0. Quit\n");
        if (read_int("Enter your choice : ", &choice) != 0) {
            choice = -1;
        }
        switch (choice) {
            case 1: {
                int id;
                int grade;
                char name[50];

                if (read_int("Id : ", &id) != 0) {
                    break;
                }
                if (read_string("Name : ", name, sizeof(name)) != 0) {
                    break;
                }
                if (read_int("Grade : ", &grade) != 0) {
                    break;
                }
                if (grade < 0 || grade > 20) {
                    printf("Invalid grade\n");
                    break;
                }
                if (find_student(head, id) != NULL) {
                    printf("Id already exists\n");
                    break;
                }
                struct Student *s = create_student(id, name, grade);
                if (s == NULL) {
                    printf("malloc failed\n");
                    break;
                }
                append_student(&head, s);
                break;
            }

            case 2:
                print_students(head);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    free_students(head);
    return 0;
}