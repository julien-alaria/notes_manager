#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    int id;
    char *name;
    int grade;
    struct Student *next;
};

struct Student *create_student(int id, const char *name, int grade);
struct Student *find_student(struct Student *head, int id);
void free_student(struct Student *student);
void append_student(struct Student **head, struct Student *new_student);
void print_students(const struct Student *head);
void free_students(struct Student *head);
int delete_student(struct Student **head, int id);

#endif