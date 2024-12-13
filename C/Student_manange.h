#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 10
#define NAME_LENGTH 50

// 学生结构体
typedef struct { 
    char name[NAME_LENGTH]; 
    int id; float score; 
    } Student;

void inputStudentInfo(); 
void printAllStudents(); 
void queryStudentInfo(); 
void modifyStudentScore(); 
void deleteStudent(); 
void menu();