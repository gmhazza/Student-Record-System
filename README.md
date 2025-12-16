# 📚 Student Record Management System (C++)

A **console-based Student Record Management System** written in **C++**, designed for beginners and first-semester BSSE students. This project allows users to manage student records efficiently using basic programming concepts such as **structures, vectors, file handling, functions, and loops**.

---

## ✨ Features

* ➕ Add new student records
* 📋 Display all students in tabular form
* 🔍 Search students by **ID** or **Name**
* ✏️ Update existing student records
* 💾 Save records to a file (`students.txt`)
* 📂 Load records automatically on program startup
* 🎓 Automatic calculation of **Total Marks, Percentage, and Grade**
* ⏳ Animated text effects using delay

---

## 🛠️ Technologies & Concepts Used

* **Language:** C++
* **Core Concepts:**

  * Structures (`struct`)
  * Vectors (`std::vector`)
  * File Handling (`fstream`)
  * Functions & Prototyping
  * Loops & Conditional Statements
  * Arrays
  * Basic Input Validation
  * Console formatting (`iomanip`)

---

## 📂 File Structure

```
📁 Student-Record-Management-System
│
├── main.cpp        # Main source file
├── students.txt    # Data file (auto-generated)
├── README.md       # Project documentation
```

---

## ▶️ How to Compile and Run

### Using g++ (Recommended)

```bash
g++ main.cpp -o student_manager
./student_manager
```

### Using Code::Blocks / Visual Studio

* Create a new **C++ Console Project**
* Paste the code into `main.cpp`
* Build & Run the project

> ⚠️ Note: This project uses `system("cls")` and `system("color 2")`, which work best on **Windows**.

---

## 📊 Grading Criteria

| Total Marks | Grade |
| ----------- | ----- |
| 240 – 300   | A     |
| 180 – 239   | B     |
| 120 – 179   | C     |
| 60 – 119    | D     |
| Below 60    | F     |

---

## 🧠 How the System Works

1. Program loads existing student data from `students.txt`
2. User interacts with a **menu-driven interface**
3. Student data is stored in a `vector<Student>`
4. Each record includes:

   * ID
   * Name
   * Marks (3 subjects)
   * Total
   * Percentage
   * Grade
5. On exit, data is saved back to the file

---

## 📌 Sample Record Format (students.txt)

```
1,Ali Ahmed,85,90,78,253,84,A
2,Sara Khan,70,65,80,215,71,B
```

---

## 👨‍🎓 Author

**Muhammad Hazza Shabir**

**Abdul Manan**
BS Software Engineering (1st Semester)

---

## 📜 License

This project is created for **educational purposes** and is free to use, modify, and share.

---

⭐ *If you like this project, don’t forget to star the repository!*
