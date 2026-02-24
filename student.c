#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

Student *createStudent(int id, const char *name, int age, float score)
{
    Student *s = (Student *)malloc(sizeof(Student));
    s->id = id;
    strcpy(s->name, name);
    s->age = age;
    s->score = score;
    s->next = NULL;
    return s;
}

void insertStudent(Student **head, Student *newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    Student *p = *head;
    while (p->next != NULL)
    {
        p = p->next;
    }
    p->next = newNode;
}

void printStudents(Student *head)
{
    Student *p = head;
    while (p != NULL)
    {
        printf("ID:%d Name:%s Age:%d Score:%.2f\n", p->id, p->name, p->age, p->score);
        p = p->next;
    }
}
void deleteStudent(Student **head, int id)
{
    Student *cur = *head;
    Student *pre = NULL;
    while (cur != NULL)
    {
        if (cur->id == id)
        {
            if (pre == NULL)
            {
                *head = cur->next;
            }
            else
            {
                pre->next = cur->next;
            }
            free(cur);
            printf("删除成功\n");
            return;
        }
        pre = cur;
        cur = cur->next;
    }
    printf("未找到该学生\n");
}
