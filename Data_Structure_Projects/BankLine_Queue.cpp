// Project 03: Bank Waiting Line (Queue)
// Cairo Coding School - Data Structures Practice Projects
#include <iostream>
#include <string>
using namespace std;

class Queue {
private:
    string names[100];
    int    front;
    int    rear;

public:
    Queue() { front = 0; rear = -1; }

    void enqueue(string name) {
        if (rear == 99) {
            cout << "The line is full\n";
            return;
        }
        rear++;
        names[rear] = name;
    }

    string dequeue() {
        string name = names[front];
        front++;
        return name;
    }

    bool isEmpty() {
        return front > rear;
    }

    void show() {
        if (isEmpty()) {
            cout << "No customers waiting\n";
            return;
        }
        cout << "Waiting: ";
        for (int i = front; i <= rear; i++) {
            cout << names[i];
            if (i < rear) cout << ", ";
        }
        cout << "\n";
    }
};

int main() {
    Queue line;
    int choice;

    do {
        cout << "\n1. New customer  2. Serve next  3. Show line  0. Exit\n";
        cout << "Choice: ";
        if (!(cin >> choice)) {         // the user typed letters, not a number
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        if (choice == 1) {
            string name;
            cout << "Name: ";
            getline(cin >> ws, name);
            line.enqueue(name);
        } else if (choice == 2) {
            if (line.isEmpty()) {
                cout << "No customers waiting\n";
            } else {
                cout << "Now serving: " << line.dequeue() << "\n";
            }
        } else if (choice == 3) {
            line.show();
        } else if (choice != 0) {
            cout << "Invalid choice\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
