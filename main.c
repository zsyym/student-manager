#include <stdio.h>
#include "student.h"

int main()
{
    Student *head = NULL;

    insertStudent(&head, createStudent(1, "Alice", 20, 88));
    insertStudent(&head, createStudent(2, "Bob", 21, 90));
    insertStudent(&head, createStudent(3, "Cindy", 19, 95));

    printStudents(head);

    deleteStudent(&head, 2);

    printStudents(head);

    return 0;
}
