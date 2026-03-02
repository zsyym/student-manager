#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "student.h"
#include "user.h"

// 学生数据文件操作
int saveStudentsToBinary(Student *head, const char *filename);
int loadStudentsFromBinary(Student **head, const char *filename);
int saveStudentsToText(Student *head, const char *filename);
int loadStudentsFromText(Student **head, const char *filename);
int saveStudentsToCSV(Student *head, const char *filename);

// 用户数据文件操作
int saveUsersToBinary(User *head, const char *filename);
int loadUsersFromBinary(User **head, const char *filename);
int saveUsersToText(User *head, const char *filename);
int loadUsersFromText(User **head, const char *filename);

// 数据导出功能
int exportStudentScores(Student *head, const char *filename);

#endif