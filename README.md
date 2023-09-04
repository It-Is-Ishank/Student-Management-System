# Student Management System

A simple console-based Student Management System implemented in C.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Functionality](#functionality)
- [Input Validation](#input-validation)
- [File Handling](#file-handling)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This Student Management System is a basic console application that allows you to perform various operations related to student records. It provides functionalities to add, display, search, modify, and delete student records while ensuring data integrity.

## Features

- Add new student records.
- Display a list of all students.
- Search for a student by Student ID.
- Modify student information by Student ID.
- Delete a student record by Student ID.

## Prerequisites

- C Compiler (e.g., GCC)
- Windows (for conio.h functions) or a compatible environment

## Usage

1. Clone the repository:

   ```bash
   git clone <repository-url>
   ```
2. Compile the source code:
   ```bash
   gcc SMS.c -o SMS
   ```
3. Run the program:
   ```bash
   ./student_management
   ```

## Functionality
-**Add Student**: Add new student records to the system. Checks for duplicate Student IDs.

-**Display Students**: Display a list of all students in a tabular format.

-**Search Student**: Search for a student by Student ID. Displays the student's details if found.

-**Modify Student**: Modify student information by Student ID. Checks if the student exists before making changes.

-**Delete Student**: Delete a student record by Student ID.

**Input Validation**
The program includes input validation for Student ID, CGPA, and semester to ensure valid and positive integer or float values.
**File Handling**
Student data is stored in a text file (SDB.txt) in a structured format.
The program handles file creation and reading/writing data to maintain student records.
**Contributing**
Contributions are welcome! Feel free to open issues and submit pull requests to help improve this Student Management System.

**License**
This project is licensed under the MIT License.
