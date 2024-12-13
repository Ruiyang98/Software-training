#include "Student_manange.h"


// 全局学生数组
Student students[MAX_STUDENTS];
int student_count = 0;


void inputStudentInfo() {
    if (student_count >= MAX_STUDENTS) {
        printf("学生数组已满，无法添加更多学生。\n");
        return;
    }
    Student new_student;
    printf("请输入学生姓名: ");
    scanf("%s", new_student.name);
    printf("请输入学生学号: ");
    while (scanf("%d", &new_student.id) != 1) {
        printf("输入无效，请输入正确的学号: ");
        while (getchar() != '\n'); // 清除输入缓冲区
    }
    printf("请输入学生成绩: ");
    while (scanf("%f", &new_student.score) != 1) {
        printf("输入无效，请输入正确的成绩: ");
        while (getchar() != '\n'); // 清除输入缓冲区
    }
    students[student_count++] = new_student;
    printf("学生信息已添加。\n");
}

void printAllStudents() {
    if (student_count == 0) {
        printf("没有学生记录。\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        printf("姓名: %s, 学号: %d, 成绩: %.2f\n", students[i].name, students[i].id, students[i].score);
    }
}

void queryStudentInfo() {
    if (student_count == 0) {
        printf("没有学生记录。\n");
        return;
    }
    int query_id;
    printf("请输入要查询的学生学号: ");
    while (scanf("%d", &query_id) != 1) {
        printf("输入无效，请输入正确的学号: ");
        while (getchar() != '\n'); // 清除输入缓冲区
    }
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == query_id) {
            printf("姓名: %s, 成绩: %.2f\n", students[i].name, students[i].score);
            return;
        }
    }
    printf("未找到学号为 %d 的学生。\n", query_id);
}

void modifyStudentScore() {
    if (student_count == 0) {
        printf("没有学生记录。\n");
        return;
    }
    int modify_id;
    printf("请输入要修改成绩的学生学号: ");
    while (scanf("%d", &modify_id) != 1) {
        printf("输入无效，请输入正确的学号: ");
        while (getchar() != '\n'); // 清除输入缓冲区
    }
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == modify_id) {
            printf("请输入新的成绩: ");
            while (scanf("%f", &students[i].score) != 1) {
                printf("输入无效，请输入正确的成绩: ");
                while (getchar() != '\n'); // 清除输入缓冲区
            }
            printf("学生成绩已修改。\n");
            return;
        }
    }
    printf("未找到学号为 %d 的学生。\n", modify_id);
}

void deleteStudent() {
    if (student_count == 0) {
        printf("没有学生记录。\n");
        return;
    }
    int delete_id;
    printf("请输入要删除的学生学号: ");
    while (scanf("%d", &delete_id) != 1) {
        printf("输入无效，请输入正确的学号: ");
        while (getchar() != '\n'); // 清除输入缓冲区
    }
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == delete_id) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("学生信息已删除。\n");
            return;
        }
    }
    printf("未找到学号为 %d 的学生。\n", delete_id);
}

void menu() {
    int choice;
    while (1) {
        printf("\n学生管理系统\n");
        printf("1. 输入学生信息\n");
        printf("2. 输出所有学生信息\n");
        printf("3. 查询学生信息\n");
        printf("4. 修改学生成绩\n");
        printf("5. 删除学生信息\n");
        printf("6. 退出\n");
        printf("请选择操作: ");
        while (scanf("%d", &choice) != 1) {
            printf("输入无效，请输入数字: ");
            while (getchar() != '\n'); // 清除输入缓冲区
        }
        switch (choice) {
            case 1:
                inputStudentInfo();
                break;
            case 2:
                printAllStudents();
                break;
            case 3:
                queryStudentInfo();
                break;
            case 4:
                modifyStudentScore();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("退出系统。\n");
                return;
            default:
                printf("无效的选择，请重新输入。\n");
                break;
        }
    }
}

int main() {
    menu();
    return 0;
}
