#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>  // For input validation

using namespace std;

// Struct to represent a student record
struct Student {
    string id;
    string name;
    vector<int> marks;  // Marks for 3 subjects
    int total;
    char grade;
};

// Function to calculate total and grade for a student
void calculateTotalAndGrade(Student& s) {
    s.total = 0;
    for (int mark : s.marks) {
        s.total += mark;
    }
    // Grade based on total (out of 300)
    if (s.total >= 240) s.grade = 'A';
    else if (s.total >= 180) s.grade = 'B';
    else if (s.total >= 120) s.grade = 'C';
    else if (s.total >= 60) s.grade = 'D';
    else s.grade = 'F';
}

// Function to add a new student
void addStudent(vector<Student>& students) {
    Student s;
    cout << "Enter Student ID: ";
    cin >> s.id;
    cout << "Enter Student Name: ";
    cin.ignore();  // Clear newline from previous input
    getline(cin, s.name);
    s.marks.resize(3);
    cout << "Enter marks for 3 subjects (0-100 each):" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Subject " << (i + 1) << ": ";
        cin >> s.marks[i];
        // Basic validation
        if (s.marks[i] < 0 || s.marks[i] > 100) {
            cout << "Invalid mark! Setting to 0." << endl;
            s.marks[i] = 0;
        }
    }
    calculateTotalAndGrade(s);
    students.push_back(s);
    cout << "Student added successfully!" << endl;
}

// Function to display all students
void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to display." << endl;
        return;
    }
    cout << "ID\tName\t\tMarks\t\tTotal\tGrade" << endl;
    cout << "-----------------------------------------------------" << endl;
    for (const auto& s : students) {
        cout << s.id << "\t" << s.name << "\t\t";
        for (int mark : s.marks) cout << mark << " ";
        cout << "\t" << s.total << "\t" << s.grade << endl;
    }
}

// Function to search students by ID or name
void searchStudent(const vector<Student>& students) {
    int choice;
    cout << "Search by: 1. ID  2. Name" << endl;
    cin >> choice;
    if (choice == 1) {
        string id;
        cout << "Enter ID: ";
        cin >> id;
        for (const auto& s : students) {
            if (s.id == id) {
                cout << "Found: " << s.id << ", " << s.name << ", Total: " << s.total << ", Grade: " << s.grade << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    } else if (choice == 2) {
        string name;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        for (const auto& s : students) {
            if (s.name == name) {
                cout << "Found: " << s.id << ", " << s.name << ", Total: " << s.total << ", Grade: " << s.grade << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    } else {
        cout << "Invalid choice." << endl;
    }
}

// Function to update a student by ID
void updateStudent(vector<Student>& students) {
    string id;
    cout << "Enter Student ID to update: ";
    cin >> id;
    for (auto& s : students) {
        if (s.id == id) {
            cout << "Updating " << s.name << endl;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, s.name);
            cout << "Enter new marks for 3 subjects:" << endl;
            for (int i = 0; i < 3; i++) {
                cout << "Subject " << (i + 1) << ": ";
                cin >> s.marks[i];
                if (s.marks[i] < 0 || s.marks[i] > 100) s.marks[i] = 0;
            }
            calculateTotalAndGrade(s);
            cout << "Student updated!" << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

// Function to save students to file
void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for saving." << endl;
        return;
    }
    for (const auto& s : students) {
        file << s.id << "," << s.name << ",";
        for (size_t i = 0; i < s.marks.size(); i++) {
            file << s.marks[i];
            if (i < s.marks.size() - 1) file << ",";
        }
        file << "," << s.total << "," << s.grade << endl;
    }
    file.close();
    cout << "Records saved to " << filename << endl;
}

// Function to load students from file
void loadFromFile(vector<Student>& students, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "File not found. Starting with empty records." << endl;
        return;
    }
    students.clear();
    string line;
    while (getline(file, line)) {
        Student s;
        size_t pos = 0;
        // Parse ID
        pos = line.find(",");
        s.id = line.substr(0, pos);
        line = line.substr(pos + 1);
        // Parse Name
        pos = line.find(",");
        s.name = line.substr(0, pos);
        line = line.substr(pos + 1);
        // Parse Marks
        s.marks.resize(3);
        for (int i = 0; i < 3; i++) {
            pos = line.find(",");
            s.marks[i] = stoi(line.substr(0, pos));
            line = line.substr(pos + 1);
        }
        // Parse Total and Grade
        pos = line.find(",");
        s.total = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        s.grade = line[0];
        students.push_back(s);
    }
    file.close();
    cout << "Records loaded from " << filename << endl;
}

// Main function with menu
int main() {
    vector<Student> students;
    string filename = "students.txt";
    loadFromFile(students, filename);  // Load on startup

    int choice;
    do {
        cout << "\nStudent Record Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Save Records" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(students); break;
            case 2: displayStudents(students); break;
            case 3: searchStudent(students); break;
            case 4: updateStudent(students); break;
            case 5: saveToFile(students, filename); break;
            case 6: saveToFile(students, filename); cout << "Exiting..." << endl; break;
            default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}