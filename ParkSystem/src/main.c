#include "../include/user.h"
#include <stdio.h>

// 主函数
int main() {
    User users[MAX_USERS];
    int user_count = 2;

    // 初始化用户
    initUser(&users[0], 1, ADMIN);
    initUser(&users[1], 2, USER);

    // 添加停车记录
    addParkingRecord(&users[0], 1, "ABC123", "2024-01-01 08:00", "2024-01-01 12:00");
    addParkingRecord(&users[1], 2, "XYZ789", "2024-01-01 09:00", "2024-01-01 11:00");

    // 查看所有记录（管理员）
    if (isAdmin(&users[0])) {
        printf("管理员查看所有记录:\n");
        viewAllRecords(users, user_count);
    }

    // 普通用户查看自己的记录
    printf("用户查看自己的记录:\n");
    viewUserRecords(&users[1]);

    // 管理员删除记录
    if (isAdmin(&users[0])) {
        deleteParkingRecord(users, user_count, 2);
        printf("管理员删除记录后查看所有记录:\n");
        viewAllRecords(users, user_count);
    }

    return 0;
}
