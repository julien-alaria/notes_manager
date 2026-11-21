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