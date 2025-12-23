#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


// Struct to represent a student record
struct Student
{
    string id;
    string name;
    int marks[3];  // Marks for 3 subjects
    int total;
    int percentage;
    char grade;
};

//prototyping all the functions
void wrongOptionError();
void calculateTotalAndGrade(Student&);
void addStudent(vector<Student>&);
void displayStudents(vector<Student>&);
void searchStudent(vector<Student>&);
void updateStudent(vector<Student>&);
void saveToFile(vector<Student>&, string&);
void loadFromFile(vector<Student>&, string&);


// Main function with menu
int main()
{
	system("color 2");
    vector<Student> students;
    string filename = "students.txt";
    loadFromFile(students, filename);  // Load on startup

    int choice;
    do
    {
    	system("cls");
        cout << "\nStudent Record Management System" << endl << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Save Records" << endl;
        cout << "6. Exit" << endl << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1: addStudent(students); break;
            case 2: displayStudents(students); break;
            case 3: searchStudent(students); break;
            case 4: updateStudent(students); break;
            case 5: saveToFile(students, filename); break;
            case 6: saveToFile(students, filename); cout << "Exiting..." << endl; break;
            default: wrongOptionError(); break;
        }
    }while (choice != 6);
    
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
    // Percentage based on 300 marks
    s.percentage = ((float)s.total / 300) * 100;
    // Grade Calculation
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
void addStudent(vector<Student>& students)
{
	system("cls");
    Student s;
    cout << "Enter Student ID: ";
    cin >> s.id;
    cout << "Enter Student Name: ";
    cin.ignore();  // Clear newline from previous input
    getline(cin, s.name);
    cout << "Enter marks for 3 subjects (0-100 each):" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Subject " << (i + 1) << ": ";
        cin >> s.marks[i];
        // Basic validation
        if (s.marks[i] < 0 || s.marks[i] > 100)
        {
            cout << "Invalid mark! Setting to 0." << endl;
            s.marks[i] = 0;
        }
    }
    calculateTotalAndGrade(s);
    students.push_back(s);
    cout << "Student added successfully!" << endl;
    cout << endl << "Press Enter to Exit" << endl;
    cin.ignore();
    cin.get();
}

// Function to display all students
void displayStudents(vector<Student>& students)
{
	system("cls");
    if (students.empty())
    {
        cout << "No students to display." << endl;
        cout << endl << "Press Enter to Exit" << endl;
        cin.ignore();
        cin.get();
        return;
    }
    cout << "ID\tName\t\tMarks\t\tTotal\tPercentage\tGrade" << endl;
    cout << "-----------------------------------------------------------------------" << endl;
    for (auto& s : students)
    {
        cout << s.id << "\t" << s.name << setw(17 - s.name.size());
        for (int mark : s.marks) cout << mark << " ";
        cout << "\t" << s.total << setw(11) << s.percentage << setw(13) << s.grade << endl;
    }
    cout << endl << "Press Enter to Exit" << endl;
    cin.ignore();
    cin.get();
}

// Function to search students by ID or name
void searchStudent(vector<Student>& students)
{
	system("cls");
    int choice;
    cout << "Search by: 1. ID  2. Name" << endl;
    cin >> choice;
    if (choice == 1)
    {
        string id;
        cout << "Enter ID: ";
        cin >> id;
        for (const auto& s : students)
        {
            if (s.id == id)
            {
                cout << "Found: " << s.id << ", " << s.name << ", Total: " << s.total << ", Grade: " << s.grade << endl;
                cout << endl << "Press Enter to Exit" << endl;
                cin.ignore();
                cin.get();
                return;
            }
        }
        cout << "Student not found." << endl;
        cout << endl << "Press Enter to Exit" << endl;
        cin.ignore();
        cin.get();
    }
    else if (choice == 2)
    {
        string name;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        for (const auto& s : students)
        {
            if (s.name == name)
            {
                cout << "Found: " << s.id << ", " << s.name << ", Total: " << s.total << ", Grade: " << s.grade << endl;
                cout << endl << "Press Enter to Exit" << endl;
                cin.ignore();
                cin.get();
                return;
            }
        }
        cout << "Student not found." << endl;
        cout << endl << "Press Enter to Exit" << endl;
        cin.ignore();
        cin.get();
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}

// Function to update a student by ID
void updateStudent(vector<Student>& students)
{
	system("cls");
    string id;
    cout << "Enter Student ID to update: ";
    cin >> id;
    for (auto& s : students)
    {
        if (s.id == id)
        {
            cout << "Updating " << s.name << endl;
            cout << "Enter new Name: ";
            cin.ignore();
            getline(cin, s.name);
            cout << "Enter new marks for 3 subjects:" << endl;
            for (int i = 0; i < 3; i++)
            {
                cout << "Subject " << (i + 1) << ": ";
                cin >> s.marks[i];
                if (s.marks[i] < 0 || s.marks[i] > 100)
                    s.marks[i] = 0;
            }
            calculateTotalAndGrade(s);
            cout << "Student updated!" << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
    cout << endl << "Press Enter to Exit" << endl;
    cin.ignore();
    cin.get();
}

// Function to save students to file
void saveToFile(vector<Student>& students, string& filename)
{
    ofstream file(filename);
    system("cls");
    if (!file)
    {
        cout << "Error opening file for saving." << endl;
        return;
    }
    for (const auto& s : students)
    {
        file << s.id << "," << s.name << ",";
        for (int i = 0; i < 3; i++)
        {
            file << s.marks[i];
            if (i < 2) file << ",";
        }
        file << "," << s.total << "," << s.percentage << "," << s.grade << endl;
    }
    file.close();
    cout << "Records saved to "  << filename << endl;
    cout << endl << "Press Enter to Exit" << endl;
    cin.ignore();
    cin.get();
}

// Function to load students from file
void loadFromFile(vector<Student>& students, string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "File not found. Starting with empty records." << endl;
        return;
    }
    students.clear();
    string line;
    while (getline(file, line))
    {
        Student s;
        int pos = 0;
        // Parse ID
        pos = line.find(",");
        s.id = line.substr(0, pos);
        line = line.substr(pos + 1);
        // Parse Name
        pos = line.find(",");
        s.name = line.substr(0, pos);
        line = line.substr(pos + 1);
        // Parse Marks
        for (int i = 0; i < 3; i++)
        {
            pos = line.find(",");
            s.marks[i] = stoi(line.substr(0, pos));
            line = line.substr(pos + 1);
        }
        // Parse Total and Grade
        pos = line.find(",");
        s.total = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        pos = line.find(",");
        s.percentage = stoi(line.substr(0, pos));
        line = line.substr(pos + 1);
        s.grade = line[0];
        students.push_back(s);
    }
    file.close();
    cout << "Records loaded from " << filename << endl;
}
