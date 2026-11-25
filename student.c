#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

struct Student *create_student(int id, const char *name, int grade) {
    struct Student *student = malloc(sizeof(struct Student));
    if (student == NULL) {
        return NULL;
    }
    student->name = malloc(strlen(name) + 1);
    if (student->name == NULL) {
        free(student);
        return NULL;
    }
    strcpy(student->name, name);
    student->id = id;
    student->grade = grade;
    student->next = NULL;
    return student;
}

void free_student(struct Student *student) {
    if (student != NULL) {
        free(student->name);
        free(student);
    }
}

void append_student(struct Student **head, struct Student *new_student) {
    if (new_student == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = new_student;
        return;
    }
    struct Student *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_student;
}

void print_students(const struct Student *head) {
    const struct Student *current = head;
    if (head == NULL) {
        printf("Student list is empty\n");
        return;
    }
    while (current != NULL) {
        printf("%d %s %d\n", current->id, current->name, current->grade);
        current = current->next;
    }
}

void free_students(struct Student *head) {
    struct Student *current = head;
    while (current != NULL) {
        struct Student *next = current->next;
        free_student(current);
        current = next;
    }
}

struct Student *find_student(struct Student *head, int id) {
    struct Student *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int delete_student(struct Student **head, int id) {
    struct Student *previous = NULL;
    struct Student *current = *head;

    while (current != NULL) {
        if (current->id == id) {
            if (previous == NULL) {
                *head = current->next;
            } else {
                previous->next = current->next;
            }
            free_student(current);
            return 0;
        }
        previous = current;
        current = current->next;
    }
    return -1;
}

int count_students(const struct Student *head) {
    int count = 0;
    const struct Student *current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

double average(const struct Student *head) {
    int count = count_students(head);
    if (count == 0) {
        return 0.0;
    }
    int total = 0;
    const struct Student *current = head;
    while (current != NULL) {
        total += current->grade;
        current = current->next;
    }
    return (double)total / count;
}

const struct Student *best_student(const struct Student *head) {
    if (head == NULL) {
        return NULL;
    }
    const struct Student *best = head;
    const struct Student *current = head->next;
    while (current != NULL) {
        if (current->grade > best->grade) {
            best = current;
        }
        current = current->next;
    }
    return best;
}

const struct Student *worst_student(const struct Student *head) {
    if (head == NULL) {
        return NULL;
    }
    const struct Student *worst = head;
    const struct Student *current = head->next;
    while (current != NULL) {
        if (current->grade < worst->grade) {
            worst = current;
        }
        current = current->next;
    }
    return worst;
}

int save_students(const struct Student *head, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return -1;
    }
    const struct Student *current = head;
    while (current != NULL) {
        fprintf(f, "%d %d\n%s\n", current->id, current->grade, current->name);
        current = current->next;
    }
    fclose(f);
    return 0;
}

struct Student *load_students(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return NULL;
    }
    struct Student *head = NULL;
    int id;
    int grade;
    char name[50];
    while(fscanf(f, "%d %d", &id, &grade) == 2) {
        fgetc(f);
        if (fgets(name, sizeof(name), f) == NULL) {
            break;
        }
        name[strcspn(name, "\n")] = '\0';
        struct Student *s = create_student(id, name, grade);
        if (s == NULL) {
            free_students(head);
            fclose(f);
            return NULL;
        }
        append_student(&head, s);
    }
    fclose(f);
    return head;
}