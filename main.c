#include <stdio.h>
#include "student.h"

int main(void) {
    struct Student *s = create_student(1, "Alice", 15);
    if (s == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    printf("%d %s %d\n", s->id, s->name, s->grade);
    free_student(s);
    return 0;
}