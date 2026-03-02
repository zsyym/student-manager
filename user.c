#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

User *createUser(const char *username, const char *password, UserRole role)
{
    User *newUser = (User *)malloc(sizeof(User));
    if (newUser == NULL)
    {
        printf("内存分配失败!\n");
        return NULL;
    }
    strncpy(newUser->username, username, MAX_USERNAME_LEN - 1);
    newUser->username[MAX_USERNAME_LEN - 1] = '\0';
    strncpy(newUser->password, password, MAX_PASSWORD_LEN - 1);
    newUser->password[MAX_PASSWORD_LEN - 1] = '\0';
    newUser->role = role;
    newUser->next = NULL;
    newUser->prev = NULL;
    return newUser;
}
void insertUser(User **head, User *newUser)
{
    if (*head == NULL)
    {
        *head = newUser;
        return;
    }
    User *current = *head;
    while (current != NULL)
    {
        current = current->next;
    }
    current->next = newUser;
    newUser->prev = current;
}
User *findUser(User *head, const char *username)
{
    User *current = head;
    while (current != NULL)
    {
        if (strcmp(current->username, username) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

int authenticateUser(User *head, const char *username, const char *password, UserRole role)
{
    User *user = findUser(head, username);
    if (user == NULL)
    {
        return 0;
    }

    return (strcmp(user->password, password) == 0 && user->role == role);
}
void deleteUser(User **head, const char *username)
{
    if (*head == NULL)
        return;

    User *current = *head;

    while (current != NULL && strcmp(current->username, username) != 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("未找到用户 %s\n", username);
        return;
    }
    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else
    {
        *head = current->next;
    }
    free(current);
    printf("用户删除成功\n");
}
void updatePassword(User *head, const char *username, const char *newPassword)
{
    User *user = findUser(head, username);
    if (user == NULL)
    {
        printf("未找到用户\n");
        return;
    }
    strncpy(user->password, newPassword, MAX_PASSWORD_LEN - 1);
    user->password[MAX_PASSWORD_LEN - 1] = '\0';
    printf("密码修改成功\n");
}
int getUserCount(User *head)
{
    int count = 0;
    User *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void freeAllUsers(User *head)
{
    User *current = head;
    while (current != NULL)
    {
        User *temp = current;
        current = current->next;
        free(temp);
    }
}
void listAllUsers(User *head)
{
    if (head == NULL)
    {
        printf("用户列表为空！\n");
        return;
    }
    printf("\n+------------------------+-----------------+\n");
    printf("| 用户名                 | 角色            |\n");
    printf("+------------------------+-----------------+\n");

    User *current = head;
    while (current != NULL)
    {
        const char *roleStr;
        switch (current->role)
        {
        case STUDENT:
            roleStr = "学生";
            break;
        case TEACHER:
            roleStr = "教师";
            break;
        case ADMIN:
            roleStr = "管理员";
            break;
        default:
            roleStr = "未知";
            break;
        }
        printf("| %-22s | %-15s |\n", current->username, roleStr);
        current = current->next;
    }
    printf("+------------------------+-----------------+\n");
}