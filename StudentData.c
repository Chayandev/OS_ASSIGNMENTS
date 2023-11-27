#include <stdio.h>
#include <stdlib.h>

// Structure to represent a student
struct Student {
    int rollNumber;
    char name[50];
    float marks;
};

// Function to add a new student record to the file
void addStudent(FILE *file) {
    struct Student student;

    printf("Enter Roll Number: ");
    scanf("%d", &student.rollNumber);
    printf("Enter Name: ");
    scanf("%s", student.name);
    printf("Enter Marks: ");
    scanf("%f", &student.marks);

    // Append the student record to the file
    fwrite(&student, sizeof(struct Student), 1, file);

    printf("Student record added successfully!\n");
}

// Function to display all student records from the file
void displayStudents(FILE *file) {
    struct Student student;

    rewind(file); // Move the file cursor to the beginning

    printf("\nStudent Records:\n");
    printf("Roll Number\tName\t\tMarks\n");

    // Read and display each student record
    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        printf("%d\t\t%s\t\t%.2f\n", student.rollNumber, student.name, student.marks);
    }
}

// Function to search for a student by roll number
void searchStudent(FILE *file) {
    int targetRollNumber;
    struct Student student;

    printf("Enter Roll Number to search: ");
    scanf("%d", &targetRollNumber);

    rewind(file); // Move the file cursor to the beginning

    // Search for the student by roll number
    while (fread(&student, sizeof(struct Student), 1, file) == 1) {
        if (student.rollNumber == targetRollNumber) {
            printf("\nStudent Found:\n");
            printf("Roll Number\tName\t\tMarks\n");
            printf("%d\t\t%s\t\t%.2f\n", student.rollNumber, student.name, student.marks);
            return;
        }
    }

    printf("Student with Roll Number %d not found.\n", targetRollNumber);
}

int main() {
    FILE *file;
    int choice;

    // Open the file in binary mode for reading and writing
    file = fopen("student.dat", "ab+");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    do {
        // Display menu
        printf("\nStudent Information System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(file);
                break;
            case 2:
                displayStudents(file);
                break;
            case 3:
                searchStudent(file);
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    // Close the file
    fclose(file);

    return 0;
}
