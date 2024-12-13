#include <stdio.h>

typedef struct {
    char name[50];
    int id;
    float score;
} Student;

int main() {
    // 创建多个结构体变量
    Student student1 = {"Alice", 1001, 95.5};
    Student student2 = {"Bob", 1002, 88.0};
    Student student3 = {"Charlie", 1003, 92.5};

    // 输出学生信息
    printf("学生1: 姓名: %s, 学号: %d, 成绩: %.2f\n", student1.name, student1.id, student1.score);
    printf("学生2: 姓名: %s, 学号: %d, 成绩: %.2f\n", student2.name, student2.id, student2.score);
    printf("学生3: 姓名: %s, 学号: %d, 成绩: %.2f\n", student3.name, student3.id, student3.score);

    // 修改学生成绩
    student1.score = 97.0;
    student2.score = 89.5;

    // 输出修改后的学生信息
    printf("\n修改后的学生信息:\n");
    printf("学生1: 姓名: %s, 学号: %d, 成绩: %.2f\n", student1.name, student1.id, student1.score);
    printf("学生2: 姓名: %s, 学号: %d, 成绩: %.2f\n", student2.name, student2.id, student2.score);

    return 0;
}
