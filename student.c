#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

#define MAX_NAME_LEN 50

Student *createStudent(int id, const char *name, int age, float score)
{
    Student *newNode = (Student *)malloc(sizeof(Student));
    if (newNode == NULL)
    {
        printf("内存分配失败！\n");
        return NULL;
    }
    newNode->id = id;
    strncpy(newNode->name, name, MAX_NAME_LEN - 1);
    newNode->name[MAX_NAME_LEN - 1] = '\0';
    newNode->age = age;
    newNode->score = score;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insertStudent(Student **head, Student *newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    Student *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

void insertStudentAtPosition(Student **head, int position, Student *newNode)
{
    if (position < 0 || newNode == NULL)
        return;

    if (position == 0)
    {
        newNode->next = *head;
        if (*head != NULL)
            (*head)->prev = newNode;
        *head = newNode;
        return;
    }

    Student *current = *head;
    int i = 0;
    while (current != NULL && i < position - 1)
    {
        current = current->next;
        i++;
    }

    if (current == NULL)
    {
        printf("位置超出范围，插入到末尾\n");
        insertStudent(head, newNode);
        return;
    }

    newNode->next = current->next;
    newNode->prev = current;
    if (current->next != NULL)
        current->next->prev = newNode;
    current->next = newNode;
}

void printStudents(Student *head)
{
    if (head == NULL)
    {
        printf("学生列表为空！\n");
        return;
    }

    printf("\n+-----+----------------------+-----+--------+\n");
    printf("| ID  | 姓名                 | 年龄 | 成绩   |\n");
    printf("+-----+----------------------+-----+--------+\n");

    Student *current = head;
    while (current != NULL)
    {
        printf("| %-3d | %-20s | %-3d | %-6.2f |\n",
               current->id, current->name, current->age, current->score);
        current = current->next;
    }
    printf("+-----+----------------------+-----+--------+\n");
}

void deleteStudent(Student **head, int id)
{
    if (*head == NULL)
        return;

    Student *current = *head;

    while (current != NULL && current->id != id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("未找到ID为%d的学生\n", id);
        return;
    }

    if (current->prev != NULL)
        current->prev->next = current->next;
    else
        *head = current->next;

    if (current->next != NULL)
        current->next->prev = current->prev;

    free(current);
    printf("学生信息删除成功！\n");
}

void deleteAllStudents(Student **head)
{
    Student *current = *head;
    Student *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

Student *findStudent(Student *head, int id)
{
    Student *current = head;
    while (current != NULL)
    {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}

void updateStudent(Student *head, int id)
{
    Student *student = findStudent(head, id);
    if (student == NULL)
    {
        printf("未找到ID为%d的学生\n", id);
        return;
    }

    printf("当前学生信息：\n");
    printf("ID: %d, 姓名: %s, 年龄: %d, 成绩: %.2f\n",
           student->id, student->name, student->age, student->score);

    int choice;
    printf("\n选择要修改的字段：\n");
    printf("1. 姓名\n");
    printf("2. 年龄\n");
    printf("3. 成绩\n");
    printf("4. 全部修改\n");
    printf("0. 取消\n");
    printf("请选择: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("输入无效\n");
        while (getchar() != '\n')
            ;
        return;
    }

    switch (choice)
    {
    case 1:
        printf("输入新姓名: ");
        scanf("%49s", student->name);
        break;
    case 2:
        printf("输入新年龄: ");
        scanf("%d", &student->age);
        break;
    case 3:
        printf("输入新成绩: ");
        scanf("%f", &student->score);
        break;
    case 4:
        printf("输入新姓名: ");
        scanf("%49s", student->name);
        printf("输入新年龄: ");
        scanf("%d", &student->age);
        printf("输入新成绩: ");
        scanf("%f", &student->score);
        break;
    case 0:
        return;
    default:
        printf("无效选择\n");
        return;
    }

    printf("学生信息更新成功！\n");
}

int getStudentCount(Student *head)
{
    int count = 0;
    Student *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

float getAverageScore(Student *head)
{
    if (head == NULL)
        return 0;

    float sum = 0;
    int count = 0;
    Student *current = head;

    while (current != NULL)
    {
        sum += current->score;
        count++;
        current = current->next;
    }

    return count > 0 ? sum / count : 0;
}

float getHighestScore(Student *head)
{
    if (head == NULL)
        return 0;

    float max = head->score;
    Student *current = head->next;

    while (current != NULL)
    {
        if (current->score > max)
            max = current->score;
        current = current->next;
    }

    return max;
}

float getLowestScore(Student *head)
{
    if (head == NULL)
        return 0;

    float min = head->score;
    Student *current = head->next;

    while (current != NULL)
    {
        if (current->score < min)
            min = current->score;
        current = current->next;
    }

    return min;
}

void getScoreStatistics(Student *head, int *count, float *avg, float *max, float *min, float *sum)
{
    *count = 0;
    *sum = 0;
    *max = 0;
    *min = 1000;

    Student *current = head;
    while (current != NULL)
    {
        (*count)++;
        *sum += current->score;
        if (current->score > *max)
            *max = current->score;
        if (current->score < *min)
            *min = current->score;
        current = current->next;
    }

    *avg = *count > 0 ? *sum / *count : 0;
    if (*min == 1000)
        *min = 0;
}

// 冒泡排序（双向链表）
void sortById(Student *head, int ascending)
{
    if (head == NULL)
        return;

    int swapped;
    Student *current;
    Student *last = NULL;

    do
    {
        swapped = 0;
        current = head;

        while (current->next != last)
        {
            int needSwap = ascending ? (current->id > current->next->id) : (current->id < current->next->id);

            if (needSwap)
            {
                // 交换数据（不交换节点）
                int tempId = current->id;
                char tempName[50];
                strcpy(tempName, current->name);
                int tempAge = current->age;
                float tempScore = current->score;

                current->id = current->next->id;
                strcpy(current->name, current->next->name);
                current->age = current->next->age;
                current->score = current->next->score;

                current->next->id = tempId;
                strcpy(current->next->name, tempName);
                current->next->age = tempAge;
                current->next->score = tempScore;

                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void sortByName(Student *head, int ascending)
{
    if (head == NULL)
        return;

    int swapped;
    Student *current;
    Student *last = NULL;

    do
    {
        swapped = 0;
        current = head;

        while (current->next != last)
        {
            int needSwap = ascending ? (strcmp(current->name, current->next->name) > 0) : (strcmp(current->name, current->next->name) < 0);

            if (needSwap)
            {
                // 交换数据
                int tempId = current->id;
                char tempName[50];
                strcpy(tempName, current->name);
                int tempAge = current->age;
                float tempScore = current->score;

                current->id = current->next->id;
                strcpy(current->name, current->next->name);
                current->age = current->next->age;
                current->score = current->next->score;

                current->next->id = tempId;
                strcpy(current->next->name, tempName);
                current->next->age = tempAge;
                current->next->score = tempScore;

                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void sortByAge(Student *head, int ascending)
{
    if (head == NULL)
        return;

    int swapped;
    Student *current;
    Student *last = NULL;

    do
    {
        swapped = 0;
        current = head;

        while (current->next != last)
        {
            int needSwap = ascending ? (current->age > current->next->age) : (current->age < current->next->age);

            if (needSwap)
            {
                // 交换数据
                int tempId = current->id;
                char tempName[50];
                strcpy(tempName, current->name);
                int tempAge = current->age;
                float tempScore = current->score;

                current->id = current->next->id;
                strcpy(current->name, current->next->name);
                current->age = current->next->age;
                current->score = current->next->score;

                current->next->id = tempId;
                strcpy(current->next->name, tempName);
                current->next->age = tempAge;
                current->next->score = tempScore;

                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void sortByScore(Student *head, int ascending)
{
    if (head == NULL)
        return;

    int swapped;
    Student *current;
    Student *last = NULL;

    do
    {
        swapped = 0;
        current = head;

        while (current->next != last)
        {
            int needSwap = ascending ? (current->score > current->next->score) : (current->score < current->next->score);

            if (needSwap)
            {
                // 交换数据
                int tempId = current->id;
                char tempName[50];
                strcpy(tempName, current->name);
                int tempAge = current->age;
                float tempScore = current->score;

                current->id = current->next->id;
                strcpy(current->name, current->next->name);
                current->age = current->next->age;
                current->score = current->next->score;

                current->next->id = tempId;
                strcpy(current->next->name, tempName);
                current->next->age = tempAge;
                current->next->score = tempScore;

                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void showStudentsByPage(Student *head, int pageSize)
{
    if (head == NULL)
    {
        printf("学生列表为空！\n");
        return;
    }

    int total = getStudentCount(head);
    int pages = (total + pageSize - 1) / pageSize;
    int currentPage = 1;
    char choice;

    Student *current = head;

    do
    {
        printf("\n===== 第 %d 页 / 共 %d 页 =====\n", currentPage, pages);
        printf("+-----+----------------------+-----+--------+\n");
        printf("| ID  | 姓名                 | 年龄 | 成绩   |\n");
        printf("+-----+----------------------+-----+--------+\n");

        Student *pageStart = current;
        int count = 0;
        Student *temp = pageStart;

        while (temp != NULL && count < pageSize)
        {
            printf("| %-3d | %-20s | %-3d | %-6.2f |\n",
                   temp->id, temp->name, temp->age, temp->score);
            temp = temp->next;
            count++;
        }
        printf("+-----+----------------------+-----+--------+\n");

        printf("\n导航: [n]下一页 [p]上一页 [q]退出: ");
        scanf(" %c", &choice);

        if (choice == 'n' && currentPage < pages)
        {
            // 移动到下一页起始位置
            for (int i = 0; i < pageSize && current != NULL; i++)
                current = current->next;
            currentPage++;
        }
        else if (choice == 'p' && currentPage > 1)
        {
            // 移动到上一页起始位置
            for (int i = 0; i < pageSize * 2 && current != NULL && current->prev != NULL; i++)
                current = current->prev;
            currentPage--;
        }

    } while (choice != 'q');
}

void freeAllStudents(Student *head)
{
    Student *current = head;
    while (current != NULL)
    {
        Student *temp = current;
        current = current->next;
        free(temp);
    }
}
