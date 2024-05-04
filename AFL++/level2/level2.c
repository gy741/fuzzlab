#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USER_INPUT 256
#define MAX_LOG_LENGTH 512
#define MAX_LOG_ENTRIES 5

typedef struct {
    char entries[MAX_LOG_ENTRIES][MAX_LOG_LENGTH];
    int entryCount;
} LogData;

void initializeLogData(LogData *logData) {
    logData->entryCount = 0;
    for (int i = 0; i < MAX_LOG_ENTRIES; i++) {
        memset(logData->entries[i], 0, MAX_LOG_LENGTH);
    }
}

void loadLogEntriesFromFile(LogData *logData, const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        printf("Failed to open file: %s\n", fileName);
        return;
    }
    char buffer[MAX_LOG_LENGTH];
    while (fgets(buffer, MAX_LOG_LENGTH, file) && logData->entryCount < MAX_LOG_ENTRIES) {
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(logData->entries[logData->entryCount], buffer, 2 * MAX_LOG_LENGTH);
        logData->entries[logData->entryCount][MAX_LOG_LENGTH - 1] = '\0';
        logData->entryCount++;
    }
    fclose(file);
}

void printLogData(const LogData *logData) {
    printf("Log Entries:\n");
    for (int i = 0; i < logData->entryCount; i++) {
        printf("%d: %s\n", i + 1, logData->entries[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <log_file>\n", argv[0]);
        return 1;
    }

    LogData logData;
    initializeLogData(&logData);

    printf("Simple Logging System\n");
    loadLogEntriesFromFile(&logData, argv[1]);
    printLogData(&logData);

    return 0;
}