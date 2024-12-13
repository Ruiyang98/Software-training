#include "user.h"
#include <stdio.h>
#include <string.h>

// 初始化用户
void initUser(User* user, int user_id, Role role) {
    user->user_id = user_id;
    user->role = role;
    user->record_count = 0;
}

// 添加停车记录
void addParkingRecord(User* user, int record_id, const char* license_plate, const char* entry_time, const char* exit_time) {
    if (user->record_count < MAX_RECORDS) {
        ParkingRecord* record = &user->records[user->record_count++];
        record->record_id = record_id;
        strncpy(record->license_plate, license_plate, sizeof(record->license_plate));
        strncpy(record->entry_time, entry_time, sizeof(record->entry_time));
        strncpy(record->exit_time, exit_time, sizeof(record->exit_time));
    } else {
        printf("记录已满，无法添加新的停车记录\n");
    }
}

// 查看所有停车记录（仅限管理员）
void viewAllRecords(User* users, int user_count) {
    for (int i = 0; i < user_count; i++) {
        for (int j = 0; j < users[i].record_count; j++) {
            ParkingRecord* record = &users[i].records[j];
            printf("User ID: %d, Record ID: %d, License Plate: %s, Entry Time: %s, Exit Time: %s\n",
                   users[i].user_id, record->record_id, record->license_plate, record->entry_time, record->exit_time);
        }
    }
}

// 查看用户自己的停车记录
void viewUserRecords(User* user) {
    for (int i = 0; i < user->record_count; i++) {
        ParkingRecord* record = &user->records[i];
        printf("Record ID: %d, License Plate: %s, Entry Time: %s, Exit Time: %s\n",
               record->record_id, record->license_plate, record->entry_time, record->exit_time);
    }
}

// 检查是否为管理员
int isAdmin(User* user) {
    return user->role == ADMIN;
}

// 管理员删除任意停车记录
void deleteParkingRecord(User* users, int user_count, int record_id) {
    for (int i = 0; i < user_count; i++) {
        for (int j = 0; j < users[i].record_count; j++) {
            if (users[i].records[j].record_id == record_id) {
                for (int k = j; k < users[i].record_count - 1; k++) {
                    users[i].records[k] = users[i].records[k + 1];
                }
                users[i].record_count--;
                printf("记录已删除，记录ID: %d\n", record_id);
                return;
            }
        }
    }
    printf("记录未找到，记录ID: %d\n", record_id);
}
