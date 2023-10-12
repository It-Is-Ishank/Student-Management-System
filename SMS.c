#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

struct Student
{
    int SID;
    char name[100];
    float CGPA;
    int currSem;
};

void addStudent(struct Student *studentArray[], int *studentCount)
{
    if (*studentCount < MAX_STUDENTS)
    {
        struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));

        // Get the student data from user input
        printf("Enter Student ID: ");
        scanf("%d", &newStudent->SID);
        printf("Enter Student Name: ");
        scanf(" %[^\n]s", newStudent->name); // Read the entire line, including spaces
        printf("Enter CGPA: ");
        scanf("%f", &newStudent->CGPA);
        printf("Enter Current Semester: ");
        scanf("%d", &newStudent->currSem);

        // Add the new student to the array
        studentArray[*studentCount] = newStudent;
        (*studentCount)++;
    }
    else
    {
        printf("Student limit reached.!!\n");
    }
}
int compareStudentID(const void *a, const void *b)
{
    const struct Student *studentA = *(const struct Student **)a;
    const struct Student *studentB = *(const struct Student **)b;

    return studentA->SID - studentB->SID;
}

void deleteStudent(struct Student *studentArray[], int *studentCount, int targetSID)
{
    int indexToDelete = -1;

    // Find the index of the student with the target SID
    for (int i = 0; i < *studentCount; i++)
    {
        if (studentArray[i]->SID == targetSID)
        {
            indexToDelete = i;
            break;
        }
    }

    if (indexToDelete == -1)
    {
        printf("Student with SID %d not found.\n", targetSID);
        return;
    }

    // Free the memory allocated for the student to be deleted
    free(studentArray[indexToDelete]);

    // Move the remaining students to fill the gap
    for (int i = indexToDelete; i < *studentCount - 1; i++)
    {
        studentArray[i] = studentArray[i + 1];
    }

    // Decrement the student count
    (*studentCount)--;

    printf("Student with SID %d deleted successfully.\n", targetSID);
}

void saveStudents(struct Student *studentArray[], int studentCount)
{

    qsort(studentArray, studentCount, sizeof(struct Student *), compareStudentID);

    FILE *file = fopen("SDB.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Save the student count as the first line
    fprintf(file, "%d\n", studentCount);

    for (int i = 0; i < studentCount; i++)
    {
        // Save each student's data, separated by a delimiter character (e.g., ';')
        fprintf(file, "%d; %s; %.2f; %d\n", studentArray[i]->SID, studentArray[i]->name, studentArray[i]->CGPA, studentArray[i]->currSem);
    }

    fclose(file);
}

void loadStudents(struct Student *studentArray[], int *studentCount)
{
    FILE *file = fopen("SDB.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Read the student count from the first line
    if (fscanf(file, "%d", studentCount) != 1)
    {
        printf("Error reading student count.\n");
        fclose(file);
        return;
    }

    // Consume the newline character after the student count
    int newlineChar = fgetc(file);

    for (int i = 0; i < *studentCount; i++)
    {
        // Allocate memory for a new student object
        studentArray[i] = (struct Student *)malloc(sizeof(struct Student));

        // Read each field, separating them by a delimiter character (e.g., ';')
        if (fscanf(file, "%d", &studentArray[i]->SID) != 1 ||
            fscanf(file, "; %49[^;]", studentArray[i]->name) != 1 ||
            fscanf(file, "; %f", &studentArray[i]->CGPA) != 1 ||
            fscanf(file, "; %d", &studentArray[i]->currSem) != 1)
        {
            printf("Error reading student data.\n");
            break;
        }
    }

    fclose(file);
}

void fetchStudents(struct Student *studentArray[])
{
    FILE *file = fopen("SDB.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    // Read the student count from the first line
    if (fscanf(file, "%d", 10) != 1)
    {
        printf("Error reading student count.\n");
        fclose(file);
        return;
    }

    // Consume the newline character after the student count
    int newlineChar = fgetc(file);

    fclose(file);
}

void clearScreen()
{
    printf("\033[H\033[J");
}

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

// Function to display students in a tabular format on Windows
// Function to display students in a tabular format
void displayStudentsTable(struct Student *studentArray[], int studentCount)
{
    clearScreen(); // Clear the terminal screen

    // Define table headers
    printf("Student ID\tName\t\t   CGPA\t\tSemester\n");

    for (int i = 0; i < studentCount; i++)
    {
        // Set cursor position for each row
        int row = i + 3; // Start from the fourth row
        gotoxy(1, row);

        // Display student data with a fixed tab width for the "Name" column
        printf("%d\t\t%-20s%.2f\t%d\n", studentArray[i]->SID, studentArray[i]->name, studentArray[i]->CGPA, studentArray[i]->currSem);
    }

    // Move cursor to a new line
    int newRow = studentCount + 4; // Move to the next line after the table
    gotoxy(1, newRow);
}

void modifyStudent(struct Student *studentArray[], int studentCount, int targetSID)
{
    displayStudentsTable(studentArray, studentCount);
    int found = 0;

    // Search for the student with the target SID
    for (int i = 0; i < studentCount; i++)
    {
        if (studentArray[i]->SID == targetSID)
        {
            found = 1;
            // Allow the user to modify the student's information
            printf("Modifying student with SID %d:\n", targetSID);
            printf("Enter new name: ");
            scanf(" %[^\n]s", studentArray[i]->name);
            printf("Enter new CGPA: ");
            scanf("%f", &studentArray[i]->CGPA);
            printf("Enter new semester: ");
            scanf("%d", &studentArray[i]->currSem);
            printf("Student information updated successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Student with SID %d not found.\n", targetSID);
    }
}

int main()
{
    struct Student *studentArray[MAX_STUDENTS];
    int studentCount = 0;

    loadStudents(studentArray, &studentCount); // Load student data from file

    int choice;
    int target;
    do
    {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Save Students\n");
        printf("4. Delete a Student\n");
        printf("5. Modify Details of a Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (studentCount < MAX_STUDENTS)
            {
                addStudent(studentArray, &studentCount);
            }
            else
            {
                printf("Student limit reached.\n");
            }
            break;
        case 2:
            if (studentCount > 0)
            {
                displayStudentsTable(studentArray, studentCount);
                // pressAnyKeyToContinue(); // Wait for user input before returning to the menu
            }
            else
            {
                printf("No students found.\n");
            }
            break;
        case 3:
            saveStudents(studentArray, studentCount); // Save students to file
            printf("Student data saved successfully.\n");
            // pressAnyKeyToContinue();
            break;
        case 4:
            displayStudentsTable(studentArray, studentCount);

            printf("\n\nEnter the SID to delete : ");
            scanf("%d", &target);
            deleteStudent(studentArray, &studentCount, target);
            // pressAnyKeyToContinue();
            break;
        case 5:
            displayStudentsTable(studentArray, studentCount);

            printf("Enter the SID to Modify :");
            scanf("%d", &target);
            modifyStudent(studentArray, studentCount, target);
            break;

        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

        // pressAnyKeyToContinue(); // Wait for user input before returning to the menu

    } while (choice != 6);

    // Free dynamically allocated memory for student objects
    for (int i = 0; i < studentCount; i++)
    {
        free(studentArray[i]);
    }

    return 0;
}
