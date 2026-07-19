/*
====================================================================
  Project : Student Grades System  (Instructor Solution)
  Topics  : OOP + Sorting + Searching + Recursion + Big O
  School  : Cairo Coding School
====================================================================
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================= OOP PART =================
class Student
{
public:
    string name;
    int id;
    double grade;

    void print()
    {
        cout << id << " | " << name << " | " << grade << endl;
    }
};

// ================= SORTING (Session 14) =================

// Bubble Sort - O(n^2)
// Sorts students by grade in DESCENDING order (highest first)
void sortByGradeDesc(vector<Student> &students)
{
    int n = students.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // Note: '<' instead of '>' makes the sort DESCENDING
            if (students[j].grade < students[j + 1].grade)
            {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

// Selection Sort - O(n^2)
// Sorts students by id in ASCENDING order (needed for Binary Search!)
void sortByIdAsc(vector<Student> &students)
{
    int n = students.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (students[j].id < students[minIndex].id)
                minIndex = j;
        }
        swap(students[minIndex], students[i]);
    }
}

// Selection Sort - O(n^2)
// Sorts students by name in ASCENDING order (needed for Binary Search by name!)
void sortByNameAsc(vector<Student> &students)
{
    int n = students.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (students[j].name < students[minIndex].name)
                minIndex = j;
        }
        swap(students[minIndex], students[i]);
    }
}

// ================= SEARCHING (Session 13) =================

// Linear Search - O(n)
// Works on UNSORTED data. Searches by name, counts comparisons.
int linearSearchByName(vector<Student> &students, string target, int &comparisons)
{
    comparisons = 0;
    for (int i = 0; i < (int)students.size(); i++)
    {
        comparisons++;
        if (students[i].name == target)
            return i; // Found, return index
    }
    return -1; // Not found
}

// Binary Search - O(log n)
// Works ONLY on data sorted by id. Counts comparisons.
int binarySearchById(vector<Student> &students, int targetId, int &comparisons)
{
    comparisons = 0;
    int left = 0;
    int right = students.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        comparisons++;

        if (students[mid].id == targetId)
            return mid; // Found
        else if (students[mid].id < targetId)
            left = mid + 1; // Search in the right half
        else
            right = mid - 1; // Search in the left half
    }
    return -1; // Not found
}

// Binary Search - O(log n)
// Works ONLY on data sorted by name. Counts comparisons.
int binarySearchByName(vector<Student> &students, string targetName, int &comparisons)
{
    comparisons = 0;
    int left = 0;
    int right = students.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        comparisons++;

        if (students[mid].name == targetName)
            return mid; // Found
        else if (students[mid].name < targetName)
            left = mid + 1; // Search in the right half
        else
            right = mid - 1; // Search in the left half
    }
    return -1; // Not found
}

// ================= RECURSION (Session 14) =================

// Recursive function - O(n)
// Adds the grades one by one, just like nSum from the session
double totalGrades(vector<Student> &students, int n)
{
    // Base condition: no students left -> total is 0
    if (n == 0)
        return 0;

    // Recursive case: last grade + total of the rest
    return students[n - 1].grade + totalGrades(students, n - 1);
}

// ================= DISPLAY HELPERS =================

void displayAll(vector<Student> &students)
{
    if (students.empty())
    {
        cout << "No students yet!\n";
        return;
    }
    cout << "\nID | Name | Grade\n";
    cout << "------------------\n";
    for (int i = 0; i < (int)students.size(); i++)
        students[i].print();
}

void displayRanking(vector<Student> &students)
{
    sortByGradeDesc(students); // Bubble Sort O(n^2)
    cout << "\n===== Class Ranking =====\n";
    for (int i = 0; i < (int)students.size(); i++)
    {
        cout << "Rank " << i + 1 << ": ";
        students[i].print();
    }
}

void displayStatistics(vector<Student> &students)
{
    if (students.empty())
    {
        cout << "No students yet!\n";
        return;
    }

    // Find highest and lowest - O(n)
    int highest = 0, lowest = 0;
    for (int i = 1; i < (int)students.size(); i++)
    {
        if (students[i].grade > students[highest].grade)
            highest = i;
        if (students[i].grade < students[lowest].grade)
            lowest = i;
    }

    // Average using the RECURSIVE function
    double total = totalGrades(students, students.size());
    double average = total / students.size();

    cout << "\n===== Statistics =====\n";
    cout << "Highest: " << students[highest].name
         << " (" << students[highest].grade << ")\n";
    cout << "Lowest : " << students[lowest].name
         << " (" << students[lowest].grade << ")\n";
    cout << "Average: " << average << endl;
}

// ================= MAIN PROGRAM =================
int main()
{
    vector<Student> students;
    int choice;

    do
    {
        cout << "\n===== Student Grades System =====\n";
        cout << "1. Add student\n";
        cout << "2. Display all students\n";
        cout << "3. Ranking (sort by grade - descending)\n";
        cout << "4. Linear Search by name\n";
        cout << "5. Binary Search by id\n";
        cout << "6. Statistics (highest / lowest / average)\n";
        cout << "7. Binary Search by name\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1)
        {
            Student s;
            cout << "Name : ";
            cin >> s.name;
            cout << "ID   : ";
            cin >> s.id;
            cout << "Grade: ";
            cin >> s.grade;
            students.push_back(s);
            cout << "Student added!\n";
        }
        else if (choice == 2)
        {
            displayAll(students);
        }
        else if (choice == 3)
        {
            displayRanking(students);
        }
        else if (choice == 4)
        {
            string target;
            cout << "Enter name to search: ";
            cin >> target;

            int comparisons;
            // Linear Search - O(n): checks elements one by one
            int index = linearSearchByName(students, target, comparisons);

            if (index != -1)
            {
                cout << "Found: ";
                students[index].print();
            }
            else
                cout << "Not found.\n";

            cout << "Linear Search made " << comparisons << " comparisons. [O(n)]\n";
        }
        else if (choice == 5)
        {
            int targetId;
            cout << "Enter id to search: ";
            cin >> targetId;

            // IMPORTANT: Binary Search needs the array sorted by id first!
            sortByIdAsc(students); // Selection Sort O(n^2)

            int comparisons;
            // Binary Search - O(log n): cuts the range in half each time
            int index = binarySearchById(students, targetId, comparisons);

            if (index != -1)
            {
                cout << "Found: ";
                students[index].print();
            }
            else
                cout << "Not found.\n";

            cout << "Binary Search made " << comparisons << " comparisons. [O(log n)]\n";
        }
        else if (choice == 6)
        {
            displayStatistics(students);
        }
        else if (choice == 7)
        {
            string targetName;
            cout << "Enter name to search: ";
            cin >> targetName;

            // IMPORTANT: Binary Search needs the array sorted by name first!
            sortByNameAsc(students); // Selection Sort O(n^2)

            int comparisons;
            // Binary Search - O(log n): cuts the range in half each time
            int index = binarySearchByName(students, targetName, comparisons);

            if (index != -1)
            {
                cout << "Found: ";
                students[index].print();
            }
            else
                cout << "Not found.\n";

            cout << "Binary Search made " << comparisons << " comparisons. [O(log n)]\n";
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
