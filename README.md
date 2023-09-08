# Student Management System

A simple console-based Student Management System implemented in C.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Functionality](#functionality)
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
- File Handling Basics

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
   ./SMS
   ```

## Functionality
-**Add Student**: Add new student records to the system. Checks for duplicate Student IDs.

-**Display Students**: Display a list of all students in a tabular format.

-**Search Student**: Search for a student by Student ID. Displays the student's details if found.

-**Modify Student**: Modify student information by Student ID. Checks if the student exists before making changes.

-**Delete Student**: Delete a student record by Student ID.


## File Handling
Student data is stored in a text file (SDB.txt) in a structured format.
The program handles file creation and reading/writing data to maintain student records.
## Contributing

Contributions are welcome! If you'd like to contribute to this project, please follow these guidelines:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/your-feature-name`.
3. Make your changes and commit them: `git commit -m 'Add some feature'`.
4. Push to the branch: `git push origin feature/your-feature-name`.
5. Open a pull request to the `main` branch of this repository.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
