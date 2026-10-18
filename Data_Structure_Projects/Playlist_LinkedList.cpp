// Project 01: My Playlist (Linked List)
// Cairo Coding School - Data Structures Practice Projects
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string song;
    Node*  next;
};

class Playlist {
private:
    Node* head;

public:
    Playlist() { head = nullptr; }

    // Free every node when the program ends
    ~Playlist() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addSong(string name) {
        Node* newNode = new Node;
        newNode->song = name;
        newNode->next = nullptr;

        if (head == nullptr) {          // empty playlist
            head = newNode;
            return;
        }

        Node* temp = head;              // walk to the last node
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void removeSong(string name) {
        if (head == nullptr) {
            cout << "Playlist is empty\n";
            return;
        }

        if (head->song == name) {       // the song is in the head
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            cout << "Removed: " << name << "\n";
            return;
        }

        Node* previous = head;          // keep the node before the one we delete
        while (previous->next != nullptr && previous->next->song != name) {
            previous = previous->next;
        }

        if (previous->next == nullptr) {
            cout << "Song not found\n";
            return;
        }

        Node* toDelete = previous->next;
        previous->next = toDelete->next;
        delete toDelete;
        cout << "Removed: " << name << "\n";
    }

    void show() {
        if (head == nullptr) {
            cout << "Playlist is empty\n";
            return;
        }

        Node* temp = head;
        int number = 1;
        while (temp != nullptr) {
            cout << number << ". " << temp->song << "\n";
            temp = temp->next;
            number++;
        }
    }
};

int main() {
    Playlist playlist;
    int choice;

    do {
        cout << "\n1. Add song  2. Remove song  3. Show playlist  0. Exit\n";
        cout << "Choice: ";
        if (!(cin >> choice)) {         // the user typed letters, not a number
            cin.clear();
            cin.ignore(1000, '\n');
            choice = -1;
        }

        if (choice == 1) {
            string name;
            cout << "Song name: ";
            getline(cin >> ws, name);
            playlist.addSong(name);
        } else if (choice == 2) {
            string name;
            cout << "Song name: ";
            getline(cin >> ws, name);
            playlist.removeSong(name);
        } else if (choice == 3) {
            playlist.show();
        } else if (choice != 0) {
            cout << "Invalid choice\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
