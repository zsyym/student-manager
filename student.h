#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student
{
    int id;
    char name[50];
    int age;
    float score;
    struct Student *next;
} Student;

Student *createStudent(int id, const char *name, int age, float score);
void insertStudent(Student **head, Student *newNode);
void printStudents(Student *head);
void deleteStudent(Student **head, int id);
Student *findStudent(Student *head, int id);
#endif