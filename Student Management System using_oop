#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
private:
    int id;
    string name;
    int grade;
    vector<string> courses;

public:
    Student(int id, string name, int grade) {
        this->id = id;
        this->name = name;
        this->grade = grade;
    }

  
    int getId() { return id; }
    string getName() { return name; }
    int getGrade() { return grade; }

 
    void addCourse(string course) {
        courses.push_back(course);
    }

    void deleteCourse(string course) {
        for (int i = 0; i < courses.size(); i++) {
            if (courses[i] == course) {
                courses.erase(courses.begin() + i);
                cout << "Course deleted successfully\n";
                return;
            }
        }
        cout << "Course not found\n";
    }

    void display() {
        cout << "ID: " << id << ", Name: " << name << ", Grade: " << grade << "\nCourses: ";
        if (courses.empty()) {
            cout << "None";
        } else {
            for (int i = 0; i < courses.size(); i++) {
                cout << courses[i] << " ";
            }
        }
        cout << "\n";
    }
};

class StudentManager {
private:
    vector<Student> students;

public:
    void addStudent() {
        int id, grade;
        string name;
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Grade: ";
        cin >> grade;

         cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
         cout << "Enter Grade: ";  
         cin >> grade;
        

        students.push_back(Student(id, name, grade));
        cout << "Student added successfully\n";
    }

    void deleteStudent() {
        int id;
        cout << "Enter ID of student to delete: ";
        cin >> id;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                students.erase(students.begin() + i);
                cout << "Student deleted successfully\n";
                return;
            }
        }
        cout << "Student not found!\n";
    }

    void addCourseToStudent() {
        int id;
        cout << "Enter student ID: ";
        cin >> id;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                string course;
                cout << "Enter course name: ";
                getline(cin, course);
                students[i].addCourse(course);
                cout << "Course added successfully\n";
                return;
            }
        }
        cout << "Student not found\n";
    }

    void deleteCourseFromStudent() {
        int id;
        cout << "Enter student ID: ";
        cin >> id;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                string course;
                cout << "Enter course name to delete: ";
                getline(cin, course);
                students[i].deleteCourse(course);
                return;
            }
        }
        cout << "Student not found\n";
    }

    void displayAllStudents() {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }

        cout << "\n--- List of Students ---\n";
        for (int i = 0; i < students.size(); i++) {
            students[i].display();
        }
    }
};

void menu() {
    StudentManager manager;
    int choice;
    do {
        cout << "\n===== Student Management System  =====\n";
        cout << "1. Add Student\n";
        cout << "2. Delete Student\n";
        cout << "3. Add Course to Student\n";
        cout << "4. Delete Course from Student\n";
        cout << "5. Display All Students\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: manager.addStudent(); break;
            case 2: manager.deleteStudent(); break;
            case 3: manager.addCourseToStudent(); break;
            case 4: manager.deleteCourseFromStudent(); break;
            case 5: manager.displayAllStudents(); break;
            case 6: cout << "Goodbye\n"; break;
            default: cout << "Invalid choice\n";
        }
    } while (choice != 6);
}


int main() {
    menu();
    return 0;
}
