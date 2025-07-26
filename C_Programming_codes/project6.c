#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define FILENAME "students.dat"

typedef struct {
    int roll_no;
    char name[MAX_NAME_LENGTH];
    int age;
    float marks;
} Student;

// Function declarations
void add_student();
void display_students();
void search_student();
void delete_student();
void menu();
void pause();

// Helper I/O
void clear_screen();
void flush_input();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    do {
        clear_screen();
        printf("========== Student Management System ==========\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student by Roll No\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        flush_input();

        switch(choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
                pause();
        }
    } while(choice != 5);
}

void add_student() {
    FILE *fp = fopen(FILENAME, "ab");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    Student s;
    printf("\nEnter Student Roll No: ");
    scanf("%d", &s.roll_no);
    flush_input();

    printf("Enter Name: ");
    fgets(s.name, MAX_NAME_LENGTH, stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully!\n");
    pause();
}

void display_students() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    Student s;
    int count = 0;

    printf("\n%-10s %-20s %-10s %-10s\n", "Roll No", "Name", "Age", "Marks");
    printf("-----------------------------------------------------\n");

    while(fread(&s, sizeof(Student), 1, fp)) {
        printf("%-10d %-20s %-10d %-10.2f\n", s.roll_no, s.name, s.age, s.marks);
        count++;
    }

    if (count == 0) {
        printf("\nNo records found.\n");
    }

    fclose(fp);
    pause();
}

void search_student() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    int roll;
    int found = 0;
    Student s;

    printf("\nEnter Roll No to Search: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll_no == roll) {
            printf("\nStudent Found:\n");
            printf("Roll No : %d\n", s.roll_no);
            printf("Name    : %s\n", s.name);
            printf("Age     : %d\n", s.age);
            printf("Marks   : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent with roll number %d not found.\n", roll);
    }

    fclose(fp);
    pause();
}

void delete_student() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        perror("Temporary file creation failed");
        fclose(fp);
        return;
    }

    int roll;
    int found = 0;
    Student s;

    printf("\nEnter Roll No to Delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll_no == roll) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found) {
        printf("\nStudent deleted successfully.\n");
    } else {
        printf("\nStudent with roll number %d not found.\n", roll);
    }

    pause();
}

// Utility functions

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pause() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar();
}

void flush_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
