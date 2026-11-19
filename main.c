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
    print_students(head);
    free_students(head);
    return 0;
}