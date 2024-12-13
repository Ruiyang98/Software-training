#ifndef USER_H
#define USER_H

#define MAX_RECORDS 100
#define MAX_USERS 10
#define MAX_USERNAME 20
#define MAX_PASSWORD 20
#define MAX_LICENSE_PLATE 20

typedef enum {
    ADMIN,
    USER
} Role;

typedef struct {
    int record_id;
    char license_plate[20];
    char entry_time[20];
    char exit_time[20];
} ParkingRecord;

typedef struct {
    int user_id; //自动存储，用于查询
    Role role; //权限
    char username[MAX_USERNAME]; //用户名
    char password[MAX_PASSWORD]; //密码
    char license_plate[MAX_LICENSE_PLATE]; //绑定的车牌号
    ParkingRecord records[MAX_RECORDS]; //一个用户可以有多个记录
} User;

int registerUser(void);
void bindLicensePlate(char *username, char *license_plate);
int queryRecords(char *username);
int viewUsers(void);

#endif
