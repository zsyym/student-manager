#ifndef UI_H
#define UI_H

#include "student.h"
#include "user.h"

// 主界面
void printHeader();
void printMainMenu();
void clearScreen();

// 登录注册界面
int loginMenu(User *userHead, UserRole role);
int registerUser(User **userHead, UserRole role);
int forgotPassword(User *userHead, UserRole role);

// 学生端界面
void studentMenu(Student **studentHead, User *currentUser);
void studentQueryMenu(Student *head);
void studentScoreAnalysis(Student *head);

// 教师端界面
void teacherMenu(Student **studentHead, User *currentUser);
void teacherStudentManagement(Student **head);
void teacherScoreAnalysis(Student *head);
void teacherExportData(Student *head);

// 管理员端界面
void adminMenu(User **userHead, Student **studentHead);
void adminUserManagement(User **head);
void adminBulkOperations(User **userHead, Student **studentHead);

#endif