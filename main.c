#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "user.h"
#include "file.h"
#include "ui.h"

// 数据文件路径
#define STUDENT_DATA_FILE "students.dat"
#define USER_DATA_FILE "users.dat"

// 初始化默认数据
void initDefaultData(User **userHead, Student **studentHead)
{
    // 创建默认管理员账号
    if (findUser(*userHead, "admin") == NULL)
    {
        User *admin = createUser("admin", "admin123", ADMIN);
        if (admin)
            insertUser(userHead, admin);
    }

    // 创建默认教师账号
    if (findUser(*userHead, "teacher") == NULL)
    {
        User *teacher = createUser("teacher", "teacher123", TEACHER);
        if (teacher)
            insertUser(userHead, teacher);
    }

    // 创建默认学生账号
    if (findUser(*userHead, "student") == NULL)
    {
        User *student = createUser("student", "student123", STUDENT);
        if (student)
            insertUser(userHead, student);
    }

    // 添加示例学生数据
    if (*studentHead == NULL)
    {
        insertStudent(studentHead, createStudent(1001, "张三", 18, 85.5));
        insertStudent(studentHead, createStudent(1002, "李四", 19, 92.0));
        insertStudent(studentHead, createStudent(1003, "王五", 18, 78.5));
        insertStudent(studentHead, createStudent(1004, "赵六", 20, 88.0));
        insertStudent(studentHead, createStudent(1005, "钱七", 19, 95.5));
    }
}

int main()
{
    User *userHead = NULL;
    Student *studentHead = NULL;
    int choice;

    // 尝试从文件加载数据
    loadUsersFromBinary(&userHead, USER_DATA_FILE);
    loadStudentsFromBinary(&studentHead, STUDENT_DATA_FILE);

    // 初始化默认数据
    initDefaultData(&userHead, &studentHead);

    while (1)
    {
        clearScreen();
        printHeader();
        printMainMenu();

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = -1;
        }

        switch (choice)
        {
        case 1: // 学生登录
            if (loginMenu(userHead, STUDENT))
            {
                User *current = findUser(userHead, "student");
                studentMenu(&studentHead, current);
            }
            break;

        case 2: // 教师登录
            if (loginMenu(userHead, TEACHER))
            {
                User *current = findUser(userHead, "teacher");
                teacherMenu(&studentHead, current);
            }
            break;

        case 3: // 管理员登录
            if (loginMenu(userHead, ADMIN))
            {
                User *current = findUser(userHead, "admin");
                adminMenu(&userHead, &studentHead);
            }
            break;

        case 4: // 注册新账号
        {
            int role;
            printf("\n选择注册角色 (0-学生, 1-教师, 2-管理员): ");
            scanf("%d", &role);
            if (role >= 0 && role <= 2)
            {
                registerUser(&userHead, (UserRole)role);
                saveUsersToBinary(userHead, USER_DATA_FILE);
            }
        }
        break;

        case 5: // 忘记密码
        {
            int role;
            printf("\n选择角色 (0-学生, 1-教师, 2-管理员): ");
            scanf("%d", &role);
            if (role >= 0 && role <= 2)
            {
                forgotPassword(userHead, (UserRole)role);
            }
        }
        break;

        case 0: // 退出系统
            printf("\n正在保存数据...\n");
            saveStudentsToBinary(studentHead, STUDENT_DATA_FILE);
            saveUsersToBinary(userHead, USER_DATA_FILE);

            // 释放内存
            freeAllStudents(studentHead);
            freeAllUsers(userHead);

            printf("\n感谢使用学生信息管理系统！\n");
            return 0;

        default:
            printf("\n无效选择，请重试\n");
        }

        if (choice != 0)
        {
            printf("\n按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }
    }

    return 0;
}