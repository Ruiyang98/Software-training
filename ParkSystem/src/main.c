#include "user.h"
#include <stdio.h>

void printMenu() {
    printf("\n菜单:\n");
    printf("1. 注册新用户\n");
    printf("2. 绑定车牌号\n");
    printf("3. 查询用户记录\n");
    printf("4. 查看所有用户信息\n");
    printf("5. 退出\n");
    printf("选择: ");
}

int main() {
    int choice;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            char username[MAX_USERNAME];
            char license_plate[MAX_LICENSE_PLATE];
            printf("请输入用户名: ");
            scanf("%s", username);
            printf("请输入车牌号: ");
            scanf("%s", license_plate);
            bindLicensePlate(username, license_plate);
        } else if (choice == 3) {
            char username[MAX_USERNAME];
            printf("请输入用户名: ");
            scanf("%s", username);
            queryRecords(username);
        } else if (choice == 4) {
            viewUsers();
        } else if (choice == 5) {
            break;
        } else {
            printf("无效选择\n");
        }
    }

    return 0;
}
