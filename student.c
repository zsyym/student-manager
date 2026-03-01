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
Student *findStudent(Student *head, int id)
{
    Student *p = head;
    while (p != NULL)
    {
        if (p->id == id)
        {
            printf("找到该学生");
            return p;
        }
        p = p->next;
    }
    printf("未找到这学生");
    return NULL;
}
void updateStudent(Student *head, int id)
{
    Student *s = findStudent(head, id);
    if (s == NULL)
    {
        return;
    }
    printf("输入新信息:\n");
    printf("姓名: ");
    scanf("%s", s->name);

    printf("年龄: ");
    scanf("%d", &s->age);

    printf("成绩: ");
    scanf("%f", &s->score);

    printf("修改成功\n");
}
int getStudentCount(Student *head)
{
    int count = 0;
    Student *p = head;
    while (p != NULL)
    {
        count++;
        p = p->next;
    }
    return count;
}
float getAverageScore(Student *head)
{
    int count = 0;
    float sum = 0.0;
    Student *p = head;
    while (p != NULL)
    {
        sum += p->score;
        count++;
        p = p->next;
    }
    return (count == 0) ? 0 : sum / count;
}
float getHighestScore(Student *head)
{
    if (head == NULL)
        return 0.0;

    float highest = head->score;
    Student *p = head->next;
    while (p != NULL)
    {
        if (p->score > highest)
        {
            highest = p->score;
        }
        p = p->next;
    }
    return highest;
}
