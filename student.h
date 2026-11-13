#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    int id;
    char *name;
    int grade;
    struct Student *next;
};

struct Student *create_student(int id, const char *name, int grade);
void free_student(struct Student *student);

#endif