#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
#include <Windows.h>


//void displayStudents(void);
//void searchStudent(void);
//void modifyStudent(void);
//void deleteStudent(void);

struct Student {
    int SID; // Student ID
    char name[50]; // Student name
    float CGPA; // Cumulative Grade Point Average
    int currSem; // Current semester
};


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int isDuplicateSID(int sidToCheck) {
    struct Student s;
    FILE *file = fopen("SDB.txt", "r");
    
    if (file == NULL) {
        // If the file doesn't exist, create it
        file = fopen("SDB.txt", "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return 0; 
        } else {
            fclose(file);
            return 0; // File is newly created, so no duplicates
        }
    }

    while (fscanf(file, "%d %*s %*f %*d", &s.SID) != EOF) {
        if (s.SID == sidToCheck) {
            fclose(file);
            return 1; // Duplicate SID found
        }
    }

    fclose(file);
    return 0; // No duplicate SID found
}

void insertStudent(struct Student student) {
    struct Student s;
    FILE *file = fopen("SDB.txt", "r+");
    
    if (file == NULL) {
        // If the file doesn't exist, create it
        file = fopen("SDB.txt", "w");
        if (file == NULL) {
            printf("Error creating file.\n");
            return;
        }
    }

    while (fscanf(file, "%d %*s %*f %*d", &s.SID) != EOF) {
        if (s.SID > student.SID) {
            // Move the file pointer back to the beginning of the line
            fseek(file, -14, SEEK_CUR); // Adjust based on your data format
            break;
        }
    }

    // Insert the student at the correct position
    fprintf(file, "%d %s %.2f %d\n", student.SID, student.name, student.CGPA, student.currSem);

    fclose(file);
}

int getPositiveIntInput(const char* prompt) {
    int value;
    do {
        printf("%s", prompt);
        if (scanf("%d", &value) != 1 || value <= 0) {
            printf("Invalid input. Please enter a positive integer.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    } while (1);
    return value;
}

// Function to validate and get a float input
float getFloatInput(const char* prompt) {
    float value;
    do {
        printf("%s", prompt);
        if (scanf("%f", &value) != 1) {
            printf("Invalid input. Please enter a valid float value.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    } while (1);
    return value;
}


void addStudent() {
    struct Student student;

    system("cls");

    printf("Add Student:\n");
    student.SID = getPositiveIntInput("Enter Student ID: ");

    // Check for duplicate SID
    if (isDuplicateSID(student.SID)) {
        printf("Student with the same ID already exists.\n");
        printf("Press any key to continue...");
        _getch();
        return;
    }

    printf("Enter student name: ");
    scanf("%s", student.name); // Use %s for reading names without spaces
    student.CGPA = getFloatInput("Enter CGPA: ");
      student.currSem = getPositiveIntInput("Enter current semester: ");

    // Insert the student in sorted order
    insertStudent(student);

    printf("Student added successfully!\n");
    printf("Press any key to continue...");
    _getch();
}


void displayStudents() {
    struct Student s;

    system("cls");

    FILE *file = fopen("SDB.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        printf("Press any key to continue...");
        _getch();
        return;
    }

    // Print column headers using gotoxy
    gotoxy(5, 1);
    printf("Student ID");
    gotoxy(20, 1);
    printf("Name");
    gotoxy(35, 1);
    printf("CGPA");
    gotoxy(50, 1);
    printf("Current Semester");

    int row = 3; // Starting row for data

    while (fscanf(file, "%d %s %f %d", &s.SID, &s.name, &s.CGPA, &s.currSem) != EOF) {
        // Print data using gotoxy
        gotoxy(5, row);
        printf("%d", s.SID);
        gotoxy(20, row);
        printf("%s", s.name);
        gotoxy(35, row);
        printf("%.2f", s.CGPA);
        gotoxy(50, row);
        printf("%d", s.currSem);

        row++; // Move to the next row
    }

    fclose(file);

    // Wait for a keypress and return to the main menu
    gotoxy(0, row + 1);
    
}


void searchStudent(){
    int targetSId;
    struct Student s;

    system("cls");

    s.SID = getPositiveIntInput("Enter SID to Search: ");

    FILE *file = fopen("SDB.txt","r");
    if (file == NULL ){
        printf("\nError opening the file.\n");
        return;
    }

    int flag=0;
    while(fscanf(file,"%d %s %f %d",&s.SID,&s.name,&s.CGPA,&s.currSem) != EOF){
        if(s.SID == targetSId){
            flag =1;
            printf("Student Found.\n");
            printf("Student ID: %d\n", s.SID);
            printf("Name: %s\n", s.name);
            printf("CGPA: %.2f\n", s.CGPA);
            printf("Current Semester: %d\n", s.currSem);
            break;
        }
    }
    if(!flag){
        printf("Student with id %d not found in DB.\n",targetSId);
    }

    fclose(file);

    printf("Press any key to continue...");
    _getch();



};

void modifyStudent(){
    int targetSID;
    struct Student student;

    system("cls");

    displayStudents();

    targetSID = getPositiveIntInput("Enter SID to Modify Data: ");
    
    FILE* file = fopen("SDB.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE* tempFile = fopen("temp_database.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    int found = 0; // To track if the student was found
    while (fscanf(file, "%d %s %f %d", &student.SID, student.name, &student.CGPA, &student.currSem) != EOF) {
        if (student.SID == targetSID) {
            found = 1;
            printf("Enter updated student name: ");
            scanf("%s", student.name);
            printf("Enter updated CGPA: ");
            scanf("%f", &student.CGPA);
            printf("Enter updated current semester: ");
            scanf("%d", &student.currSem);
        }
        fprintf(tempFile, "%d %s %.2f %d\n", student.SID, student.name, student.CGPA, student.currSem);
    }

    if (!found) {
        printf("Student with ID %d not found.\n", targetSID);
    } else {
        printf("Student information updated successfully!\n");
    }

    fclose(file);
    fclose(tempFile);

    remove("SDB.txt");
    rename("temp_database.txt", "SDB.txt");

    printf("Press any key to continue...");
    _getch();


};

void deleteStudent(){
    int targetSID;
    struct Student student;

    system("cls");

    displayStudents();


    printf("Enter Student ID to delete: ");
    scanf("%d", &targetSID);

    FILE* file = fopen("SDB.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE* tempFile = fopen("temp_database.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    int found = 0; // To track if the student was found
    while (fscanf(file, "%d %s %f %d", &student.SID, student.name, &student.CGPA, &student.currSem) != EOF) {
        if (student.SID == targetSID) {
            found = 1;
            printf("Student with ID %d has been deleted.\n", targetSID);
            continue; // Skip writing this student's data to the temporary file
        }
        fprintf(tempFile, "%d %s %.2f %d\n", student.SID, student.name, student.CGPA, student.currSem);
    }

    if (!found) {
        printf("Student with ID %d not found.\n", targetSID);
    }

    fclose(file);
    fclose(tempFile);

    // Rename the temporary file to the original file
    remove("SDB.txt");
    rename("temp_database.txt", "SDB.txt");

};








int main() {
    int choice;

    while (1) {
        system("cls"); // Clear the console screen

        printf("\nStudent Management System Menu:\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Modify Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                printf("Press any key to continue...");
                _getch();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                modifyStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                system("cls");
                printf("Exiting program. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }


    }

    return 0;
}