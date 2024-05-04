#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10
#define NAME_LENGTH 20
#define FILE_NAME "students.dat"

typedef struct {
    char name[NAME_LENGTH];
    int score;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent(char* name, int score) {
    if (studentCount < MAX_STUDENTS) {
        strcpy(students[studentCount].name, name);
        students[studentCount].score = score;
        studentCount++;
    } else {
        printf("더 이상 학생을 추가할 수 없습니다.\n");
    }
}

void saveStudents() {
    FILE* file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("파일을 저장할 수 없습니다.\n");
        return;
    }
    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf("학생 정보가 저장되었습니다.\n");
}

void loadStudents() {
    FILE* file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("파일을 불러올 수 없습니다.\n");
        return;
    }
    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);
    fclose(file);
    printf("학생 정보가 불러와졌습니다.\n");
}

int main() {
    char choice;
    char nameBuffer[256];
    int score;

    printf("학생 성적 관리 프로그램입니다.\n");

    while (1) {
        printf("\n학생 정보를 추가하시겠습니까? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'n' || choice == 'N') {
            break;
        }

        printf("학생 이름: ");
        scanf("%s", nameBuffer);
        printf("학생 성적: ");
        scanf("%d", &score);

        addStudent(nameBuffer, score);
    }

    saveStudents();
    loadStudents();

    printf("\n등록된 학생 목록:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("이름: %s, 성적: %d\n", students[i].name, students[i].score);
    }

    return 0;
}
