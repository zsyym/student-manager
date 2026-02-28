#include <stdio.h>
#include "student.h"
#include "file.h"

int main()
{

    Student *head = loadFromFile();

    if (head == NULL)
        printf("当前无数据\n");

    insertStudent(&head, createStudent(1, "Alice", 20, 88));
    insertStudent(&head, createStudent(2, "Bob", 21, 90));

    printStudents(head);

    saveToFile(head);

    return 0;
}
