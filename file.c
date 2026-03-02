#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "student.h"
#include "user.h"

int saveStudentsToBinary(Student *head, const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        return 0;
    }

    Student *p = head;
    int count = 0;
    while (p != NULL)
    {
        // 按照你的格式写入：id, name, age, score
        if (fwrite(&(p->id), sizeof(int), 1, fp) != 1)
            break;
        if (fwrite(p->name, sizeof(char), 50, fp) != 50)
            break;
        if (fwrite(&(p->age), sizeof(int), 1, fp) != 1)
            break;
        if (fwrite(&(p->score), sizeof(float), 1, fp) != 1)
            break;

        count++;
        p = p->next;
    }

    fclose(fp);
    printf("成功保存 %d 条学生记录到二进制文件: %s\n", count, filename);
    return 1;
}
int loadStudentsFromBinary(Student **head, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return 0;
    }
    Student *temp = *head;
    while (temp != NULL)
    {
        Student *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;

    int count = 0;
    while (1)
    {
        int id, age;
        float score;
        char name[50];
        if (fread(&id, sizeof(int), 1, fp) != 1)
            break;

        if (fread(name, sizeof(char), 50, fp) != 50)
            break;

        if (fread(&age, sizeof(int), 1, fp) != 1)
            break;

        if (fread(&score, sizeof(float), 1, fp) != 1)
            break;
        name[49] = '\0';
        Student *s = createStudent(id, name, age, score);
        if (s)
        {
            if (*head == NULL)
            {
                *head = s;
            }
            else
            {
                Student *last = *head;
                while (last->next != NULL)
                    last = last->next;
                last->next = s;
                s->prev = last;
            }
            count++;
        }
    }

    fclose(fp);
    printf("成功加载 %d 条学生记录从二进制文件: %s\n", count, filename);
    return 1;
}
int loadUsersFromBinary(User **head, const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return 0;
    }
    User *temp = *head;
    while (temp != NULL)
    {
        User *next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;

    int count = 0;
    while (1)
    {
        char username[50];
        char password[50];
        int role;

        if (fread(username, sizeof(char), 50, fp) != 50)
            break;
        if (fread(password, sizeof(char), 50, fp) != 50)
            break;
        if (fread(&role, sizeof(int), 1, fp) != 1)
            break;
        username[49] = '\0';
        password[49] = '\0';

        User *u = (User *)malloc(sizeof(User));
        if (u)
        {
            strcpy(u->username, username);
            strcpy(u->password, password);
            u->role = (UserRole)role;
            u->next = NULL;
            u->prev = NULL;

            if (*head == NULL)
            {
                *head = u;
            }
            else
            {
                User *last = *head;
                while (last->next != NULL)
                    last = last->next;
                last->next = u;
                u->prev = last;
            }
            count++;
        }
    }

    fclose(fp);
    printf("成功加载 %d 条用户记录从二进制文件: %s\n", count, filename);
    return 1;
}
int saveUsersToBinary(User *head, const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        return 0;
    }

    User *p = head;
    int count = 0;
    while (p != NULL)
    {
        if (fwrite(p->username, sizeof(char), 50, fp) != 50)
            break;
        if (fwrite(p->password, sizeof(char), 50, fp) != 50)
            break;
        if (fwrite(&(p->role), sizeof(int), 1, fp) != 1)
            break;

        count++;
        p = p->next;
    }

    fclose(fp);
    printf("成功保存 %d 条用户记录到二进制文件: %s\n", count, filename);
    return 1;
}
int exportStudentScores(Student *head, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        return 0;
    }

    if (head == NULL)
    {
        fprintf(fp, "没有学生数据！\n");
        fclose(fp);
        return 1;
    }

    // 计算统计信息
    int count = 0;
    float sum = 0, max = 0, min = 1000;
    Student *p = head;

    while (p != NULL)
    {
        count++;
        sum += p->score;
        if (p->score > max)
            max = p->score;
        if (p->score < min)
            min = p->score;
        p = p->next;
    }
    float avg = count > 0 ? sum / count : 0;

    // 写入报告头
    fprintf(fp, "========================================\n");
    fprintf(fp, "        学生成绩统计报告\n");
    fprintf(fp, "========================================\n");
    fprintf(fp, "生成时间: %s %s\n", __DATE__, __TIME__);
    fprintf(fp, "\n");

    // 基本统计
    fprintf(fp, "【基本统计信息】\n");
    fprintf(fp, "学生总人数: %d\n", count);
    fprintf(fp, "总分: %.2f\n", sum);
    fprintf(fp, "平均分: %.2f\n", avg);
    fprintf(fp, "最高分: %.2f\n", max);
    fprintf(fp, "最低分: %.2f\n", min);
    fprintf(fp, "\n");

    // 成绩分布
    int excellent = 0, good = 0, pass = 0, fail = 0;
    p = head;
    while (p != NULL)
    {
        if (p->score >= 90)
            excellent++;
        else if (p->score >= 75)
            good++;
        else if (p->score >= 60)
            pass++;
        else
            fail++;
        p = p->next;
    }

    fprintf(fp, "【成绩分布】\n");
    fprintf(fp, "优秀(90-100): %d 人 (%.1f%%)\n", excellent, (float)excellent / count * 100);
    fprintf(fp, "良好(75-89):  %d 人 (%.1f%%)\n", good, (float)good / count * 100);
    fprintf(fp, "及格(60-74):  %d 人 (%.1f%%)\n", pass, (float)pass / count * 100);
    fprintf(fp, "不及格(<60):  %d 人 (%.1f%%)\n", fail, (float)fail / count * 100);
    fprintf(fp, "\n");

    // 详细列表
    fprintf(fp, "【详细成绩列表】\n");
    fprintf(fp, "+-----+----------------------+-----+--------+\n");
    fprintf(fp, "| ID  | 姓名                 | 年龄 | 成绩   |\n");
    fprintf(fp, "+-----+----------------------+-----+--------+\n");

    p = head;
    while (p != NULL)
    {
        fprintf(fp, "| %-3d | %-20s | %-3d | %-6.2f |\n",
                p->id, p->name, p->age, p->score);
        p = p->next;
    }
    fprintf(fp, "+-----+----------------------+-----+--------+\n");

    fclose(fp);
    printf("成功导出成绩报告到文件: %s\n", filename);
    return 1;
}