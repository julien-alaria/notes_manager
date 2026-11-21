#include <stdio.h>
#include "student.h"

int main(void) {
    struct Student *head = NULL;
    const char *names[3] = {"Alice", "Bob", "Claire"};
    int grades[3] = {15, 12, 18};

    for (int i = 0; i < 3; i++) {
        struct Student *s = create_student(i+1, names[i], grades[i]);
        if (s == NULL) {
            printf("malloc failed\n");
            free_students(head);
            return 1;
        }
        append_student(&head, s);
    }

    struct Student *found = find_student(head, 2);
    if (found != NULL) {
        printf("%s\n", found->name);
    } else {
        printf("Not found\n");
    }

    if (delete_student(&head, 2) == 0) {
        printf("Deleted 2\n");
    } else {
        printf("Deleted 2 failed\n");
    }

    print_students(head);

    found = find_student(head, 99);
    if (found != NULL) {
        printf("%s", found->name);
    } else {
        printf("Not found\n");
    }

    if (delete_student(&head, 1) == 0) {
        printf("Deletd 1\n");
    } else {
        printf("Deleted 1 failed\n");
    }
    free_students(head);

    if (delete_student(&head, 99) == 0) {
        printf("Deleted 99\n");
    } else {
        printf("Delete 99 failed\n");
    }
    free_students(head);

    return 0;
}