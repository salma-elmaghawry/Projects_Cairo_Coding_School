// Project 02: Browser Back Button (Stack)
// Cairo Coding School - Data Structures Practice Projects
#include <iostream>
#include <string>
using namespace std;

class Stack {
private:
    string pages[100];
    int    top;

public:
    Stack() { top = -1; }

    void push(string page) {
        if (top == 99) {
            cout << "History is full\n";
            return;
        }
        top++;
        pages[top] = page;
    }

    string pop() {
        string page = pages[top];
        top--;
        return page;
    }

    bool isEmpty() {
        return top == -1;
    }
};

int main() {
    Stack history;
    string current = "home";
    int choice;

    do {
        cout << "\n1. Visit page  2. Back  3. Current page  0. Exit\n";
        cout << "Choice: ";
        if (!(cin >> choice)) {         // the user typed letters, not a number
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        if (choice == 1) {
            string url;
            cout << "URL: ";
            cin >> url;
            history.push(current);      // save the page we are leaving
            current = url;
        } else if (choice == 2) {
            if (history.isEmpty()) {
                cout << "No previous page\n";
            } else {
                current = history.pop();
                cout << "You are now on: " << current << "\n";
            }
        } else if (choice == 3) {
            cout << "Current page: " << current << "\n";
        } else if (choice != 0) {
            cout << "Invalid choice\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
