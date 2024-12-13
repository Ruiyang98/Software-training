#ifndef USER_H
#define USER_H

#define MAX_RECORDS 100
#define MAX_USERS 10

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
    int user_id;
    Role role;
    ParkingRecord records[MAX_RECORDS];
    int record_count;
} User;

#endif
