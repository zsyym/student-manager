#ifndef USER_H
#define USER_H

typedef enum
{
    STUDENT,
    TEACHER,
    ADMIN
} UserRole;

typedef struct User
{
    char username[50];
    char password[50];
    UserRole role;
    struct User *next;
    struct User *prev;
} User;

User *createUser(const char *username, const char *password, UserRole role);
void insertUser(User **head, User *newUser);
User *findUser(User *head, const char *username);
int authenticateUser(User *head, const char *username, const char *password, UserRole role);
void deleteUser(User **head, const char *username);
void updatePassword(User *head, const char *username, const char *newPassword);
void listAllUsers(User *head);
void freeAllUsers(User *head);
int getUserCount(User *head);

#endif