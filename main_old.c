int main(void) {
    struct Student *head = NULL;
    const char *names[3] = {"Alice", "Bob", "Claire"};
    int grades[3] = {20, 12, 19};

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

    printf("Average: %.2f\n", average(head));

    const struct Student *best = best_student(head);
    if (best != NULL) {
        printf("Best: %s %d\n", best->name, best->grade);
    }
    const struct Student *worst = worst_student(head);
    if (worst != NULL) {
        printf("Worst: %s %d\n", worst->name, worst->grade);
    }

    found = find_student(head, 99);
    if (found != NULL) {
        printf("%s\n", found->name);
    } else {
        printf("Not found\n");
    }

    if (delete_student(&head, 2) == 0) {
        printf("Deleted 2\n");
    } else {
        printf("Delete 2 failed\n");
    }

    print_students(head);

    if (delete_student(&head, 1) == 0) {
        printf("Deleted 1\n");
    } else {
        printf("Delete 1 failed\n");
    }
    print_students(head);

    if (delete_student(&head, 99) == 0) {
        printf("Deleted 99\n");
    } else {
        printf("Delete 99 failed\n");
    }

    free_students(head);
    return 0;
}