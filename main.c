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
        printf("3. Find by id\n");
        printf("4. Delete student\n");
        printf("5. Show average\n");
        printf("6. Show best\n");
        printf("7. Show worst\n");
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

            case 3: {
                int id;
                if (read_int("Id : ", &id) != 0) {
                    break;
                }
                struct Student *found = find_student(head, id);
                if (found == NULL) {
                    printf("Student not found\n");
                    break;
                }
                printf("%d %s %d\n", found->id, found->name, found->grade);
                break;
            }
            case 4: {
                int id;
                if (read_int("Id : ", &id) != 0) {
                    break;
                }
                if (delete_student(&head, id) == 0) {
                    printf("Deleted\n");
                } else {
                    printf("Student not found\n");
                }
                break;
            }
            case 5:
            if (head == NULL) {
                printf("Student list is empty\n");
                break;
            }
            printf("Average: %.2f\n", average(head));
                break;

            case 6: {
                const struct Student *best = best_student(head);
                if (best == NULL) {
                    printf("Student list is empty\n");
                    break;
                }
                printf("Best: %s %d\n", best->name, best->grade);
                break;
            }
            case 7: {
                const struct Student *worst = worst_student(head);
                if (worst == NULL) {
                    printf("Worst student list is empty\n");
                    break;
                }
                printf("Worst: %s %d\n", worst->name, worst->grade);
                break;
            }

            case 0:
                break;

            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    free_students(head);
    return 0;
}