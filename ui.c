#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ui.h"
#include "file.h"
void clearScreen()
{
    system("clear");
}

void printHeader()
{
    printf("╔════════════════════════════════════════════╗\n");
    printf("║       学生信息管理系统 v2.0                ║\n");
    printf("╚════════════════════════════════════════════╝\n");
}

void printMainMenu()
{
    printf("\n请选择登录角色：\n");
    printf("  ┌────────────────────────────────────┐\n");
    printf("  │ 1. 学生登录                         │\n");
    printf("  │ 2. 教师登录                         │\n");
    printf("  │ 3. 管理员登录                       │\n");
    printf("  │ 4. 注册新账号                       │\n");
    printf("  │ 5. 忘记密码                         │\n");
    printf("  │ 0. 退出系统                         │\n");
    printf("  └────────────────────────────────────┘\n");
    printf("请选择: ");
}

int loginMenu(User *userHead, UserRole role)
{
    char username[50];
    char password[50];

    printf("\n┌────────────────────────────────────┐\n");
    printf("│          %s登录                │\n",
           role == STUDENT ? "学生" : (role == TEACHER ? "教师" : "管理员"));
    printf("└────────────────────────────────────┘\n");

    printf("用户名: ");
    scanf("%49s", username);
    printf("密码: ");
    scanf("%49s", password);

    if (authenticateUser(userHead, username, password, role))
    {
        printf("\n✅ 登录成功！\n");
        return 1;
    }
    else
    {
        printf("\n❌ 用户名或密码错误！\n");
        return 0;
    }
}

int registerUser(User **userHead, UserRole role)
{
    char username[50];
    char password[50];
    char confirm[50];

    printf("\n┌────────────────────────────────────┐\n");
    printf("│      注册新%s账号              │\n",
           role == STUDENT ? "学生" : (role == TEACHER ? "教师" : "管理员"));
    printf("└────────────────────────────────────┘\n");

    printf("请输入用户名: ");
    scanf("%49s", username);

    if (findUser(*userHead, username) != NULL)
    {
        printf("\n❌ 用户名已存在！\n");
        return 0;
    }

    printf("请输入密码: ");
    scanf("%49s", password);
    printf("确认密码: ");
    scanf("%49s", confirm);

    if (strcmp(password, confirm) != 0)
    {
        printf("\n❌ 两次输入的密码不一致！\n");
        return 0;
    }

    User *newUser = createUser(username, password, role);
    if (newUser != NULL)
    {
        insertUser(userHead, newUser);
        printf("\n✅ 注册成功！请登录\n");
        return 1;
    }

    return 0;
}

int forgotPassword(User *userHead, UserRole role)
{
    char username[50];

    printf("\n┌────────────────────────────────────┐\n");
    printf("│            找回密码                  │\n");
    printf("└────────────────────────────────────┘\n");

    printf("请输入用户名: ");
    scanf("%49s", username);

    User *user = findUser(userHead, username);
    if (user == NULL || user->role != role)
    {
        printf("\n❌ 用户不存在！\n");
        return 0;
    }

    printf("\n🔑 您的密码是: %s\n", user->password);
    return 1;
}

// 学生端查询菜单
void studentQueryMenu(Student *head)
{
    int choice;
    int id;
    char name[50];
    Student *found;

    do
    {
        printf("\n┌────────────────────────────────────┐\n");
        printf("│            成绩查询                  │\n");
        printf("├────────────────────────────────────┤\n");
        printf("│ 1. 按学号查询                        │\n");
        printf("│ 2. 按姓名查询                        │\n");
        printf("│ 3. 查看所有成绩                      │\n");
        printf("│ 4. 返回上一级                        │\n");
        printf("└────────────────────────────────────┘\n");
        printf("请选择: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            printf("请输入学号: ");
            scanf("%d", &id);
            found = findStudent(head, id);
            if (found)
            {
                printf("\n┌────────────────────────────────────┐\n");
                printf("│          学生信息                    │\n");
                printf("├────────────────────────────────────┤\n");
                printf("│ 学号: %-30d │\n", found->id);
                printf("│ 姓名: %-30s │\n", found->name);
                printf("│ 年龄: %-30d │\n", found->age);
                printf("│ 成绩: %-30.2f │\n", found->score);
                printf("└────────────────────────────────────┘\n");
            }
            else
            {
                printf("\n❌ 未找到该学生\n");
            }
            break;

        case 2:
            printf("请输入姓名: ");
            scanf("%49s", name);
            found = NULL;
            Student *current = head;
            while (current != NULL)
            {
                if (strcmp(current->name, name) == 0)
                {
                    found = current;
                    break;
                }
                current = current->next;
            }
            if (found)
            {
                printf("\n┌────────────────────────────────────┐\n");
                printf("│          学生信息                    │\n");
                printf("├────────────────────────────────────┤\n");
                printf("│ 学号: %-30d │\n", found->id);
                printf("│ 姓名: %-30s │\n", found->name);
                printf("│ 年龄: %-30d │\n", found->age);
                printf("│ 成绩: %-30.2f │\n", found->score);
                printf("└────────────────────────────────────┘\n");
            }
            else
            {
                printf("\n❌ 未找到该学生\n");
            }
            break;

        case 3:
            printStudents(head);
            break;
        }

        if (choice != 4 && choice != 0)
        {
            printf("\n按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }

    } while (choice != 4);
}

void studentScoreAnalysis(Student *head)
{
    int count;
    float avg, max, min, sum;
    getScoreStatistics(head, &count, &avg, &max, &min, &sum);

    printf("\n┌────────────────────────────────────┐\n");
    printf("│          成绩统计分析                │\n");
    printf("├────────────────────────────────────┤\n");
    printf("│ 学生总人数: %-26d │\n", count);
    printf("│ 总分: %-30.2f │\n", sum);
    printf("│ 平均分: %-28.2f │\n", avg);
    printf("│ 最高分: %-28.2f │\n", max);
    printf("│ 最低分: %-28.2f │\n", min);
    printf("└────────────────────────────────────┘\n");

    if (count > 0)
    {
        int excellent = 0, good = 0, pass = 0, fail = 0;
        Student *current = head;
        while (current != NULL)
        {
            if (current->score >= 90)
                excellent++;
            else if (current->score >= 75)
                good++;
            else if (current->score >= 60)
                pass++;
            else
                fail++;
            current = current->next;
        }

        printf("\n成绩分布:\n");
        printf("  ⭐ 优秀(90-100): %2d 人 (%5.1f%%)\n", excellent, (float)excellent / count * 100);
        printf("  ✅ 良好(75-89):  %2d 人 (%5.1f%%)\n", good, (float)good / count * 100);
        printf("  📝 及格(60-74):  %2d 人 (%5.1f%%)\n", pass, (float)pass / count * 100);
        printf("  ❌ 不及格(<60):  %2d 人 (%5.1f%%)\n", fail, (float)fail / count * 100);
    }
}

void studentMenu(Student **studentHead, User *currentUser)
{
    int choice;

    do
    {
        clearScreen();
        printHeader();
        printf("\n👤 欢迎您，%s (学生)\n", currentUser->username);
        printf("\n┌────────────────────────────────────┐\n");
        printf("│            学生端菜单                │\n");
        printf("├────────────────────────────────────┤\n");
        printf("│ 1. 成绩查询                          │\n");
        printf("│ 2. 成绩分析                          │\n");
        printf("│ 3. 查看班内排名                      │\n");
        printf("│ 4. 修改密码                          │\n");
        printf("│ 0. 退出登录                          │\n");
        printf("└────────────────────────────────────┘\n");
        printf("请选择: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = -1;
        }

        switch (choice)
        {
        case 1:
            studentQueryMenu(*studentHead);
            break;
        case 2:
            studentScoreAnalysis(*studentHead);
            break;
        case 3:
            printf("\n┌────────────────────────────────────┐\n");
            printf("│            班内排名                  │\n");
            printf("└────────────────────────────────────┘\n");
            sortByScore(*studentHead, 0); // 降序排列
            printStudents(*studentHead);
            break;
        case 4:
        {
            char newPwd[50], confirm[50];
            printf("\n请输入新密码: ");
            scanf("%49s", newPwd);
            printf("确认新密码: ");
            scanf("%49s", confirm);
            if (strcmp(newPwd, confirm) == 0)
            {
                strcpy(currentUser->password, newPwd);
                printf("\n✅ 密码修改成功！\n");
            }
            else
            {
                printf("\n❌ 两次输入不一致！\n");
            }
        }
        break;
        }

        if (choice != 0)
        {
            printf("\n按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }

    } while (choice != 0);
}

// 教师端学生管理
void teacherStudentManagement(Student **head)
{
    int choice;
    int id, age, position;
    char name[50];
    float score;
    Student *newNode;

    do
    {
        printf("\n┌────────────────────────────────────┐\n");
        printf("│          学生信息管理                │\n");
        printf("├────────────────────────────────────┤\n");
        printf("│ 1. 添加学生                          │\n");
        printf("│ 2. 删除学生                          │\n");
        printf("│ 3. 修改学生信息                      │\n");
        printf("│ 4. 查找学生                          │\n");
        printf("│ 5. 显示所有学生                      │\n");
        printf("│ 6. 插入学生到指定位置                │\n");
        printf("│ 7. 返回上一级                        │\n");
        printf("└────────────────────────────────────┘\n");
        printf("请选择: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            printf("请输入学号: ");
            scanf("%d", &id);
            if (findStudent(*head, id) != NULL)
            {
                printf("\n❌ 学号已存在！\n");
                break;
            }
            printf("请输入姓名: ");
            scanf("%49s", name);
            printf("请输入年龄: ");
            scanf("%d", &age);
            printf("请输入成绩: ");
            scanf("%f", &score);

            newNode = createStudent(id, name, age, score);
            if (newNode)
            {
                insertStudent(head, newNode);
                printf("\n✅ 学生添加成功！\n");
            }
            break;

        case 2:
            printf("请输入要删除的学生学号: ");
            scanf("%d", &id);
            deleteStudent(head, id);
            break;

        case 3:
            printf("请输入要修改的学生学号: ");
            scanf("%d", &id);
            updateStudent(*head, id);
            break;

        case 4:
            printf("请输入要查找的学生学号: ");
            scanf("%d", &id);
            {
                Student *found = findStudent(*head, id);
                if (found)
                {
                    printf("\n┌────────────────────────────────────┐\n");
                    printf("│          学生信息                    │\n");
                    printf("├────────────────────────────────────┤\n");
                    printf("│ 学号: %-30d │\n", found->id);
                    printf("│ 姓名: %-30s │\n", found->name);
                    printf("│ 年龄: %-30d │\n", found->age);
                    printf("│ 成绩: %-30.2f │\n", found->score);
                    printf("└────────────────────────────────────┘\n");
                }
                else
                {
                    printf("\n❌ 未找到该学生\n");
                }
            }
            break;

        case 5:
            printStudents(*head);
            break;

        case 6:
            printf("请输入插入位置 (0-%d): ", getStudentCount(*head));
            scanf("%d", &position);
            printf("请输入学号: ");
            scanf("%d", &id);
            if (findStudent(*head, id) != NULL)
            {
                printf("\n❌ 学号已存在！\n");
                break;
            }
            printf("请输入姓名: ");
            scanf("%49s", name);
            printf("请输入年龄: ");
            scanf("%d", &age);
            printf("请输入成绩: ");
            scanf("%f", &score);

            newNode = createStudent(id, name, age, score);
            if (newNode)
            {
                insertStudentAtPosition(head, position, newNode);
                printf("\n✅ 学生插入成功！\n");
            }
            break;
        }

        if (choice != 7)
        {
            printf("\n按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }

    } while (choice != 7);
}

void teacherScoreAnalysis(Student *head)
{
    int choice;

    do
    {
        printf("\n┌────────────────────────────────────┐\n");
        printf("│            成绩分析                  │\n");
        printf("├────────────────────────────────────┤\n");
        printf("│ 1. 基本统计信息                      │\n");
        printf("│ 2. 按学号排序                        │\n");
        printf("│ 3. 按姓名排序                        │\n");
        printf("│ 4. 按年龄排序                        │\n");
        printf("│ 5. 按成绩排序（升序）                │\n");
        printf("│ 6. 按成绩排序（降序）                │\n");
        printf("│ 7. 分页显示                          │\n");
        printf("│ 8. 返回上一级                        │\n");
        printf("└────────────────────────────────────┘\n");
        printf("请选择: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            studentScoreAnalysis(head);
            break;
        case 2:
            sortById(head, 1);
            printf("\n✅ 已按学号升序排序\n");
            printStudents(head);
            break;
        case 3:
            sortByName(head, 1);
            printf("\n✅ 已按姓名升序排序\n");
            printStudents(head);
            break;
        case 4:
            sortByAge(head, 1);
            printf("\n✅ 已按年龄升序排序\n");
            printStudents(head);
            break;
        case 5:
            sortByScore(head, 1);
            printf("\n✅ 已按成绩升序排序\n");
            printStudents(head);
            break;
        case 6:
            sortByScore(head, 0);
            printf("\n✅ 已按成绩降序排序\n");
            printStudents(head);
            break;
        case 7:
        {
            int pageSize;
            printf("请输入每页显示条数: ");
            scanf("%d", &pageSize);
            showStudentsByPage(head, pageSize);
        }
        break;
        }

        if (choice != 8)
        {
            printf("\n按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }

    } while (choice != 8);
}

void teacherExportData(Student *head)
{
    int choice;
    char filename[100];

    printf("\n┌────────────────────────────────────┐\n");
    printf("│            数据导出                  │\n");
    printf("├────────────────────────────────────┤\n");
    printf("│ 1. 导出到二进制文件                  │\n");
    printf("│ 2. 导出成绩统计报告                   │\n");
    printf("└────────────────────────────────────┘\n");
    printf("请选择: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        return;
    }

    printf("请输入文件名: ");
    scanf("%99s", filename);

    switch (choice)
    {
    case 1:
        saveStudentsToBinary(head, filename);
        break;
    case 2:
        exportStudentScores(head, filename);
        break;
    default:
        printf("\n❌ 无效选择\n");
    }
}

void teacherMenu(Student **studentHead, User *currentUser)
{
    int choice;

    do
    {
        clearScreen();
        printHeader();
        printf("\n👨‍🏫 欢迎您，%s (教师)\n", currentUser->username);
        printf("\n┌────────────────────────────────────┐\n");
        printf("│            教师端菜单                │\n");
        printf("├────────────────────────────────────┤\n");
        printf("│ 1. 学生信息管理                      │\n");
        printf("│ 2. 查看班内成绩                      │\n");
        printf("│ 3. 成绩分析                          │\n");
        printf("│ 4. 学生信息下载至文件                │\n");
        printf("│ 5. 修改密码                          │\n");
        printf("│ 0. 退出登录                          │\n");
        printf("└────────────────────────────────────┘\n");
        printf("请选择: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = -1;
        }

        switch (choice)
        {
        case 1:
            teacherStudentManagement(studentHead);
            break;
        case 2:
            printStudents(*studentHead);
            break;
        case 3:
            teacherScoreAnalysis(*studentHead);
            break;
        case 4:
            teacherExportData(*studentHead);
            break;
        case 5:
        {
            char newPwd[50], confirm[50];
            printf("\n请输入新密码: ");
            scanf("%49s", newPwd);
            printf("确认新密码: ");
            scanf("%49s", confirm);
            if (strcmp(newPwd, confirm) == 0)
            {
                strcpy(currentUser->password, newPwd);
                printf("\n✅ 密码修改成功！\n");
            }
            else
            {
                printf("\n❌ 两次输入不一致！\n");
            }
        }
        break;
        }

        if (choice != 0)
        {
            printf("\n按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }

    } while (choice != 0);
}

// 管理员端用户管理
void adminUserManagement(User **head)
{
    int choice;
    char username[50];
    char password[50];
    int role;

    do
    {
        printf("\n┌────────────────────────────────────┐\n");
        printf("│            用户管理                  │\n");
        printf("├────────────────────────────────────┤\n");
        printf("│ 1. 查看所有用户                      │\n");
        printf("│ 2. 添加用户                          │\n");
        printf("│ 3. 删除用户                          │\n");
        printf("│ 4. 修改用户密码                      │\n");
        printf("│ 5. 返回上一级                        │\n");
        printf("└────────────────────────────────────┘\n");
        printf("请选择: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = 0;
        }

        switch (choice)
        {
        case 1:
            listAllUsers(*head);
            break;

        case 2:
            printf("请输入用户名: ");
            scanf("%49s", username);
            if (findUser(*head, username) != NULL)
            {
                printf("\n❌ 用户名已存在！\n");
                break;
            }
            printf("请输入密码: ");
            scanf("%49s", password);
            printf("请选择角色 (0-学生, 1-教师, 2-管理员): ");
            scanf("%d", &role);

            if (role >= 0 && role <= 2)
            {
                User *newUser = createUser(username, password, (UserRole)role);
                if (newUser)
                {
                    insertUser(head, newUser);
                    printf("\n✅ 用户添加成功！\n");
                }
            }
            else
            {
                printf("\n❌ 无效的角色！\n");
            }
            break;

        case 3:
            printf("请输入要删除的用户名: ");
            scanf("%49s", username);
            deleteUser(head, username);
            break;

        case 4:
            printf("请输入用户名: ");
            scanf("%49s", username);
            printf("请输入新密码: ");
            scanf("%49s", password);
            updatePassword(*head, username, password);
            break;
        }

        if (choice != 5)
        {
            printf("\n按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }

    } while (choice != 5);
}

void adminBulkOperations(User **userHead, Student **studentHead)
{
    int choice;
    char filename[100];

    printf("\n┌────────────────────────────────────┐\n");
    printf("│            批量操作                  │\n");
    printf("├────────────────────────────────────┤\n");
    printf("│ 1. 从文件导入学生数据                │\n");
    printf("│ 2. 从文件导入用户数据                │\n");
    printf("│ 3. 导出所有学生数据                  │\n");
    printf("│ 4. 导出所有用户数据                  │\n");
    printf("│ 5. 返回上一级                        │\n");
    printf("└────────────────────────────────────┘\n");
    printf("请选择: ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n')
            ;
        return;
    }

    if (choice == 5)
        return;

    printf("请输入文件名: ");
    scanf("%99s", filename);

    switch (choice)
    {
    case 1:
        loadStudentsFromBinary(studentHead, filename);
        break;

    case 2:
        loadUsersFromBinary(userHead, filename);
        break;

    case 3:
        saveStudentsToBinary(*studentHead, filename);
        break;

    case 4:
        saveUsersToBinary(*userHead, filename);
        break;

    default:
        printf("\n❌ 无效选择\n");
    }
}

void adminMenu(User **userHead, Student **studentHead)
{
    int choice;

    do
    {
        clearScreen();
        printHeader();
        printf("\n👑 欢迎您，%s (管理员)\n", (*userHead)->username);
        printf("\n┌────────────────────────────────────┐\n");
        printf("│          管理员端菜单                │\n");
        printf("├────────────────────────────────────┤\n");
        printf("│ 1. 用户管理（增删改查）              │\n");
        printf("│ 2. 学生信息管理                      │\n");
        printf("│ 3. 批量操作（导入/导出）             │\n");
        printf("│ 4. 成绩申诉处理                      │\n");
        printf("│ 5. 查看待办事项                      │\n");
        printf("│ 0. 退出登录                          │\n");
        printf("└────────────────────────────────────┘\n");
        printf("请选择: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            choice = -1;
        }

        switch (choice)
        {
        case 1:
            adminUserManagement(userHead);
            break;
        case 2:
            teacherStudentManagement(studentHead);
            break;
        case 3:
            adminBulkOperations(userHead, studentHead);
            break;
        case 4:
            printf("\n┌────────────────────────────────────┐\n");
            printf("│          成绩申诉处理                │\n");
            printf("├────────────────────────────────────┤\n");
            printf("│ 暂无待处理的申诉                    │\n");
            printf("└────────────────────────────────────┘\n");
            break;
        case 5:
            printf("\n┌────────────────────────────────────┐\n");
            printf("│          待办事项                    │\n");
            printf("├────────────────────────────────────┤\n");
            printf("│ 1. 今日新注册用户: %d                │\n", rand() % 10);
            printf("│ 2. 待处理申诉: 0                     │\n");
            printf("│ 3. 建议定期备份数据                  │\n");
            printf("└────────────────────────────────────┘\n");
            break;
        }

        if (choice != 0)
        {
            printf("\n按回车键继续...");
            while (getchar() != '\n')
                ;
            getchar();
        }

    } while (choice != 0);
}