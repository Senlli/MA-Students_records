# 🎓 Student Management System in C++

This is a console-based Student Management System built in C++. The program allows users to manage student records with features like loading from a file, displaying records, adding, updating, and deleting students, as well as saving changes to a file.

## 💡 Features

- 📥 Load student data from `records.txt`
- 📋 Display all student records in a formatted table
- ➕ Add new students with input validation
- ✏️ Update existing students by ID
- ❌ Delete students by ID
- 💾 Save all changes to `records.txt`
- 📊 Automatically calculates average score and assigns letter grade (A–F)
- ✅ Input validation:
  - Unique numeric student IDs
  - Names must contain only letters and spaces
  - Scores between 0–100
  - Minimum of 3 scores per student
- 💬 Clear and friendly console interface

## 📁 File Format

The student data is stored in a file named `records.txt`, with the following structure:

**Example:**

1981,Sarah Paulson,89,92,87
1999,Sabrina Carpenter,93,88,94

## 🛠 Technologies Used

- C++ (C++11+ standard)
- Standard Template Library (STL): `vector`, `string`, `fstream`, `iomanip`
- CMake & CLion (or any compatible IDE)

## 🚀 How to Run

1. Make sure the file `records.txt` is in the same directory as the executable.
2. Compile and run the project.
3. Use the numeric menu to choose an option.

## 📦 Menu Options

	1.	Load Students from File
	2.	Save Students to File
	3.	Display All Records
	4.	Add a Student
	5.	Update Student
	6.	Delete Student
	7.	Save and Exit

## 👩‍💻 Author

Created with 💜 by Annie Castillo Diaz  
*Computer Programming – Semester 3*

---

Feel free to fork or modify for educational purposes!
