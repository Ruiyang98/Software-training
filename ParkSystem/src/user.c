#include "user.h"
#include <stdio.h>
#include <string.h>

User users[MAX_USERS];
int user_count = 0;

// 注册新用户
int registerUser(void) {
    if (user_count >= MAX_USERS) {
        printf("用户已满，无法添加新用户\n");
        return 0;
    }

    User* user = &users[user_count];
    user->user_id = user_count + 1;

    printf("请输入用户名: ");
    scanf("%s", user->username);

    printf("请输入密码: ");
    scanf("%s", user->password);

    user_count++;
    printf("用户注册成功，用户ID: %d\n", user->user_id);
    return 1;
}


// 绑定车牌号
void bindLicensePlate(char* username, char* license_plate) {
    int user_found = 0;
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            user_found = 1;
            strncpy(users[i].license_plate, license_plate, MAX_LICENSE_PLATE);
            printf("车牌号绑定成功\n");
            return;
        }
    }

    if (!user_found) {
        printf("用户未找到\n");
    }
}

// 根据用户名查询记录 
int queryRecords(char* username) { 
    for (int i = 0; i < user_count; i++) { 
        if (strcmp(users[i].username, username) == 0) { 
            if (users[i].role == ADMIN) { 
                printf("管理员身份，查看所有记录:\n"); 
                //viewAllRecords();  //调用查询所有记录
            } else { 
                printf("普通用户身份，查看用户记录:\n"); 
                //viewUserRecords(username);  //查询单个用户的记录
            }        
        return 1; } 
    } 
    printf("用户未找到\n"); 
    return 0; 
}

int viewUsers() {
    for (int i = 0; i < user_count; i++) {
        printf("用户ID: %d, 用户名: %s, 车牌号: %s\n", users[i].user_id, users[i].username, users[i].license_plate[0] ? users[i].license_plate : "未绑定"); 
    } 
    return user_count; 
}