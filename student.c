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