#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cctype>  // Para isalpha e isspace
using namespace std;

// Struct to hold student information
struct Student {
    int id;
    string name;
    vector<float> scores;
    float average;
    char grade;
};

// Function declarations
void displayMenu();
void loadStudents(vector<Student>& students);
void saveStudents(const vector<Student>& students);
void displayStudents(const vector<Student>& students);
void addStudent(vector<Student>& students);
void updateStudent(vector<Student>& students);
void deleteStudent(vector<Student>& students);
float calculateAverage(const vector<float>& scores);
char assignGrade(float average);
bool idExists(const vector<Student>& students, int id);
void clearInput();
bool isValidName(const string& name);

int main() {
    vector<Student> students;
    loadStudents(students); // Load existing records from file

    int choice;
    do {
        displayMenu();

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input. Please enter a number from 1 to 7.\n";
            continue;
        }

        if (choice < 1 || choice > 7) {
            cout << "Invalid choice. Please choose a number from 1 to 7.\n";
            continue;
        }

        switch (choice) {
            case 1: loadStudents(students); break;
            case 2: saveStudents(students); break;
            case 3: displayStudents(students); break;
            case 4: addStudent(students); break;
            case 5: updateStudent(students); break;
            case 6: deleteStudent(students); break;
            case 7: saveStudents(students); cout << "Goodbye!\n"; break;
        }

    } while (choice != 7);

    return 0;
}

/**
 * Displays the main menu options.
 */
void displayMenu() {
    cout << "\n1. Load Students from File\n";
    cout << "2. Save Students to File\n";
    cout << "3. Display All Records\n";
    cout << "4. Add a Student\n";
    cout << "5. Update Student\n";
    cout << "6. Delete Student\n";
    cout << "7. Save and Exit\n";
    cout << "Choose an option: ";
}

/**
 * Calculates the average from a list of scores.
 */
float calculateAverage(const vector<float>& scores) {
    float total = 0;
    for (float score : scores) total += score;
    return scores.empty() ? 0 : total / scores.size();
}

/**
 * Returns the letter grade based on average score.
 */
char assignGrade(float avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}

/**
 * Checks whether a student ID already exists.
 */
bool idExists(const vector<Student>& students, int id) {
    for (const auto& s : students)
        if (s.id == id) return true;
    return false;
}

/**
 * Clears invalid input from cin.
 */
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Loads student records from "records.txt" into memory.
 */
void loadStudents(vector<Student>& students) {
    ifstream file("records.txt");
    students.clear();

    if (!file) {
        cout << "No records found. Starting fresh.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Student s;

        getline(ss, temp, ',');
        s.id = stoi(temp);
        getline(ss, s.name, ',');

        s.scores.clear();
        while (getline(ss, temp, ',')) {
            s.scores.push_back(stof(temp));
        }

        s.average = calculateAverage(s.scores);
        s.grade = assignGrade(s.average);
        students.push_back(s);
    }

    file.close();
    cout << "Records loaded.\n";
}

/**
 * Saves all student records to "records.txt".
 */
void saveStudents(const vector<Student>& students) {
    ofstream file("records.txt");

    for (const auto& s : students) {
        file << s.id << "," << s.name;
        for (float score : s.scores)
            file << "," << score;
        file << "\n";
    }

    file.close();
    cout << "Records saved successfully.\n";
}

/**
 * Displays student records in a formatted table.
 */
void displayStudents(const vector<Student>& students) {
    cout << "\nID      Name                 Avg   Grade\n";
    cout << "--------------------------------------------\n";
    for (const auto& s : students) {
        cout << left << setw(8) << s.id
             << setw(20) << s.name
             << setw(6) << fixed << setprecision(1) << s.average
             << s.grade << "\n";
    }
}

/**
 * Validate that the name contains only letters and spaces.
 */
bool isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }
    return !name.empty();
}

/**
 * Adds a new student after collecting valid input.
 */
void addStudent(vector<Student>& students) {
    Student s;
    cout << "Enter student ID: ";
    while (true) {
        string input;
        cin >> input;

        // Check that input has only digits
        bool allDigits = true;
        for (char c : input) {
            if (!isdigit(c)) {
                allDigits = false;
                break;
            }
        }

        if (!allDigits) {
            cout << "Invalid ID. Only numbers allowed. Try again: ";
            clearInput();
            continue;
        }

        s.id = stoi(input);
        if (idExists(students, s.id)) {
            cout << "Duplicate ID. Try again: ";
            clearInput();
            continue;
        }

        break;
    }

    clearInput();
    cout << "Enter name: ";
    while (true) {
        getline(cin, s.name);
        if (!isValidName(s.name)) {
            cout << "Invalid name. Only letters and spaces allowed. Try again: ";
        } else {
            break;
        }
    }

    s.scores.clear();
    float score;
    cout << "Enter at least 3 scores (0–100). Type -1 to stop:\n";

    while (true) {
        cout << "Score #" << s.scores.size() + 1 << ": ";
        cin >> score;

        if (score == -1 && s.scores.size() >= 3) break;

        if (cin.fail() || score < 0 || score > 100) {
            clearInput();
            cout << "Invalid score. Must be between 0–100.\n";
        } else {
            s.scores.push_back(score);
        }
    }

    s.average = calculateAverage(s.scores);
    s.grade = assignGrade(s.average);
    students.push_back(s);
    cout << "Student added successfully!\n";
}

/**
 * Updates a student's name and scores by searching via ID.
 */
void updateStudent(vector<Student>& students) {
    int id;
    cout << "Enter ID to update: ";
    while (!(cin >> id)) {
        clearInput();
        cout << "Invalid input. Please enter a valid numeric ID: ";
    }

    for (auto& s : students) {
        if (s.id == id) {
            clearInput();
            cout << "Enter new name: ";
            while (true) {
                getline(cin, s.name);
                if (!isValidName(s.name)) {
                    cout << "Invalid name. Only letters and spaces allowed. Try again: ";
                } else {
                    break;
                }
            }

            s.scores.clear();
            float score;
            cout << "Enter at least 3 new scores (0–100). Type -1 to stop:\n";

            while (true) {
                cout << "Score #" << s.scores.size() + 1 << ": ";
                cin >> score;

                if (score == -1 && s.scores.size() >= 3) break;

                if (cin.fail() || score < 0 || score > 100) {
                    clearInput();
                    cout << "Invalid score.\n";
                } else {
                    s.scores.push_back(score);
                }
            }

            s.average = calculateAverage(s.scores);
            s.grade = assignGrade(s.average);
            cout << "Student updated successfully!\n";
            return;
        }
    }

    cout << "Student ID not found.\n";
}

/**
 * Deletes a student by searching with ID.
 */
void deleteStudent(vector<Student>& students) {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->id == id) {
            students.erase(it);
            cout << "Student removed successfully!\n";
            return;
        }
    }

    cout << "Student ID not found.\n";
}