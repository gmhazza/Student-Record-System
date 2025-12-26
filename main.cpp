#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int maxStudents = 100;  // Maximum students allowed

// Struct to represent a student record
struct Student
{
    int id;
    string name;
    int marks[3];  // Marks for 3 subjects
    int total;
    int percentage;
    char grade;
};

// Prototyping all the functions
void wrongOptionError();
void calculateTotalAndGrade(Student&);
void addStudent(Student[], int&);
void displayStudents(Student[], int);
void searchStudent(Student[], int);
void updateStudent(Student[], int&);
void saveToFile(Student[], int, string&);
void loadFromFile(Student[], int&, string&);


// Main function with menu
int main()
{
    Student students[maxStudents];
    int studentCount = 0;
    string filename = "students.txt";
    loadFromFile(students, studentCount, filename);  // Load on startup

    int choice;
    do
    {
        system("cls");
        cout << "\nStudent Result Management System" << endl << endl;
        cout << "1. Add Student Result" << endl;
        cout << "2. Display All Students Result" << endl;
        cout << "3. Search Student Result" << endl;
        cout << "4. Update Student Result" << endl;
        cout << "5. Save Records" << endl;
        cout << "6. Exit" << endl << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: addStudent(students, studentCount); break;
            case 2: displayStudents(students, studentCount); break;
            case 3: searchStudent(students, studentCount); break;
            case 4: updateStudent(students, studentCount); break;
            case 5: saveToFile(students, studentCount, filename); break;
            case 6: saveToFile(students, studentCount, filename); cout << "Exiting..." << endl; break;
            default: wrongOptionError(); break;
        }
    } while (choice != 6);

    return 0;
}

// Function which will be called if wrong option is entered
void wrongOptionError()
{
    system("cls");
    cout << "Wrong Option Entered... " << endl;
    cout << endl << "Press Enter to Exit" << endl;
    cin.ignore();
    cin.get();
}

// Function to calculate total and grade for a student
void calculateTotalAndGrade(Student& s) {
    s.total = 0;
    for (int i = 0; i < 3; i++)
    {
        s.total += s.marks[i];
    }
    s.percentage = ((float)s.total / 300) * 100;
    if (s.total >= 240)
        s.grade = 'A';
    else if (s.total >= 180)
        s.grade = 'B';
    else if (s.total >= 120)
        s.grade = 'C';
    else if (s.total >= 60)
        s.grade = 'D';
    else
        s.grade = 'F';
}

// Function to add a new student
void addStudent(Student students[], int& studentCount)
{
    system("cls");
    if (studentCount >= maxStudents) {
        cout << "Cannot add more students. Array full!" << endl;
        cin.ignore();
        cin.get();
        return;
    }
    Student s;
    cout << "Enter Student ID: ";
    cin >> s.id;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, s.name);
    cout << "Enter marks for 3 subjects (0-100 each):" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Subject " << (i + 1) << ": ";
        cin >> s.marks[i];
        if (s.marks[i] < 0 || s.marks[i] > 100)
        {
            cout << "Invalid mark! Setting to 0." << endl;
            s.marks[i] = 0;
        }
    }
    calculateTotalAndGrade(s);
    students[studentCount++] = s;
    cout << "Student added successfully!" << endl;
    cout << endl << "Press Enter to Exit" << endl;
    cin.ignore();
    cin.get();
}

// Function to display all students
void displayStudents(Student students[], int studentCount)
{
    system("cls");
    if (studentCount == 0)
    {
        cout << "No students to display." << endl;
        cin.ignore();
        cin.get();
        return;
    }
    cout << "ID\tName\t\tMarks\t\tTotal\tPercentage\tGrade" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    for (int i = 0; i < studentCount; i++)
    {
        cout << students[i].id << "\t" << students[i].name << setw(17 - students[i].name.size());
        for (int mark : students[i].marks) cout << mark << " ";
        cout << "\t" << students[i].total << setw(11) << students[i].percentage << setw(13) << students[i].grade << endl;
    }
    cout << endl << "Press Enter to Exit" << endl;
    cin.ignore();
    cin.get();
}

// Function to search students by ID or name
void searchStudent(Student students[], int studentCount)
{
    system("cls");
    int choice;
    cout << "Search by: 1. ID  2. Name" << endl;
    cin >> choice;
    if (choice == 1)
    {
        int id;
        cout << "Enter ID: ";
        cin >> id;
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].id == id)
            {
                cout << "Found: " << students[i].id << ", " << students[i].name << ", Total: " << students[i].total << ", Grade: " << students[i].grade << endl;
                cin.ignore();
                cin.get();
                return;
            }
        }
        cout << "Student not found." << endl;
        cin.ignore();
        cin.get();
    }
    else if (choice == 2)
    {
        string name;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].name == name)
            {
                cout << "Found: " << students[i].id << ", " << students[i].name << ", Total: " << students[i].total << ", Grade: " << students[i].grade << endl;
                cin.ignore();
                cin.get();
                return;
            }
        }
        cout << "Student not found." << endl;
        cin.ignore();
        cin.get();
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}

// Function to update a student by ID
void updateStudent(Student students[], int& studentCount)
{
    system("cls");
    int id;
    cout << "Enter Student ID to update: ";
    cin >> id;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == id)
        {
            cout << "Updating " << students[i].name << endl;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, students[i].name);
            cout << "Enter new marks for 3 subjects:" << endl;
            for (int j = 0; j < 3; j++)
            {
                cout << "Subject " << (j + 1) << ": ";
                cin >> students[i].marks[j];
                if (students[i].marks[j] < 0 || students[i].marks[j] > 100)
                    students[i].marks[j] = 0;
            }
            calculateTotalAndGrade(students[i]);
            cout << "Student updated!" << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
    cin.ignore();
    cin.get();
}

// Function to save students to file
void saveToFile(Student students[], int studentCount, string& filename)
{
    ofstream file(filename);
    system("cls");
    if (!file)
    {
        cout << "Error opening file for saving." << endl;
        return;
    }
    for (int i = 0; i < studentCount; i++)
    {
        file << students[i].id << "," << students[i].name << ",";
        for (int j = 0; j < 3; j++)
        {
            file << students[i].marks[j];
            if (j < 2) file << ",";
        }
        file << "," << students[i].total << "," << students[i].percentage << "," << students[i].grade << endl;
    }
    file.close();
    cout << "Records saved to " << filename << endl;
    cin.ignore();
    cin.get();
}

// Function to load students from file
void loadFromFile(Student students[], int& studentCount, string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "File not found. Starting with empty records." << endl;
        return;
    }
    studentCount = 0;
    string line;
    while (getline(file, line) && studentCount < maxStudents)
    {
        Student s;
        int pos = 0;
        pos = line.find(",");
        s.id = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);

        pos = line.find(",");
        s.name = line.substr(0, pos);
        line = line.substr(pos + 1);

        for (int i = 0; i < 3; i++)
        {
            pos = line.find(",");
            s.marks[i] = stoi(line.substr(0, pos));
            line = line.substr(pos + 1);
        }

        pos = line.find(",");
        s.total = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(",");
        s.percentage = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        s.grade = line[0];

        students[studentCount++] = s;
    }
    file.close();
    cout << "Records loaded from " << filename << endl;
}
