#ifndef STUDENT_H
#define STUDENT_H

typedef struct Student
{
    int id;
    char name[50];
    int age;
    float score;
    struct Student *next;
    struct Student *prev;
} Student;

Student *createStudent(int id, const char *name, int age, float score);
void insertStudent(Student **head, Student *newNode);
void printStudents(Student *head);
void deleteStudent(Student **head, int id);
Student *findStudent(Student *head, int id);
void updateStudent(Student *head, int id);
int getStudentCount(Student *head);
float getAverageScore(Student *head);
float getHighestScore(Student *head);
void sortScoreAsc(Student *head);
void sortScoreDesc(Student *head);
void showStudentsByPage(Student *head, int pageSize);
void freeAllStudents(Student *head);
void insertStudentAtPosition(Student **head, int position, Student *newNode);
void deleteAllStudents(Student **head);
void getScoreStatistics(Student *head, int *count, float *avg, float *max, float *min, float *sum);
void sortById(Student *head, int ascending);
void sortByName(Student *head, int ascending);
void sortByAge(Student *head, int ascending);
void sortByScore(Student *head, int ascending);

#endif