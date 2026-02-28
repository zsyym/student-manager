#include <stdio.h>
#include <stdlib.h>
#include "file.h"

void saveToFile(Student *head)
{
    FILE *fp = fopen("/Users/macbookair/Desktop/student-manager/students.dat", "wb");
    if (fp == NULL)
    {
        perror("文件打开失败");
        return;
    }
    Student *p = head;
    while (p != NULL)
    {
        fwrite(&(p->id), sizeof(int), 1, fp);
        fwrite(p->name, sizeof(char), 50, fp);
        fwrite(&(p->age), sizeof(int), 1, fp);
        fwrite(&(p->score), sizeof(float), 1, fp);

        p = p->next;
    }
    fclose(fp);
    printf("保存成功\n");
}
Student *loadFromFile()
{
    FILE *fp = fopen("/Users/macbookair/Desktop/student-manager/students.dat", "rb");
    if (fp == NULL)
    {
        perror("加载文件失败");
        return NULL;
    }

    Student *head = NULL;

    while (1)
    {
        int id, age;
        float score;
        char name[50];

        // ⭐ 每一步都检查
        if (fread(&id, sizeof(int), 1, fp) != 1)
            break;

        if (fread(name, sizeof(char), 50, fp) != 50)
            break;

        if (fread(&age, sizeof(int), 1, fp) != 1)
            break;

        if (fread(&score, sizeof(float), 1, fp) != 1)
            break;

        Student *s = createStudent(id, name, age, score);
        insertStudent(&head, s);
    }

    fclose(fp);
    printf("加载完成\n");
    return head;
}
