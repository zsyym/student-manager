#include <stdio.h>
#include "student.h"

int main()
{
    Student *head = NULL;

    insertStudent(&head, createStudent(1, "Alice", 20, 88));
    insertStudent(&head, createStudent(2, "Bob", 21, 90));
    insertStudent(&head, createStudent(3, "Cindy", 19, 95));

    printStudents(head);

    Student *result = findStudent(head, 2);

    if (result != NULL)
    {
        printf("\n查询成功:\n");
        printf("ID:%d Name:%s Age:%d Score:%.2f\n",
               result->id, result->name, result->age, result->score);
    }
    else
    {
        printf("未找到该学生\n");
    }

    return 0;
}
