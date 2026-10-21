// Project 02: Contact Management Database System (C++ + SQLite)
// Cairo Coding School - Database Projects
#include <iostream>
#include <iomanip>
#include <string>
#include "sqlite3.h"
using namespace std;

// ---------- input helpers ----------

string readLine(string prompt) {
    cout << prompt;
    string text;
    getline(cin, text);
    return text;
}

int readInt(string prompt) {
    while (true) {
        string text = readLine(prompt);
        try {
            size_t used;
            int value = stoi(text, &used);
            if (used == text.size()) return value;
        } catch (...) {}
        cout << "Please enter a valid number.\n";
    }
}

// ---------- validation ----------

bool isValidPhone(string phone) {
    if (phone.size() < 7 || phone.size() > 15) return false;
    for (int i = 0; i < (int)phone.size(); i++) {
        char c = phone[i];
        if (c == '+' && i == 0) continue;      // allow +20...
        if (c < '0' || c > '9') return false;
    }
    return true;
}

bool isValidEmail(string email) {
    if (email.empty()) return true;            // email is optional
    size_t at  = email.find('@');
    size_t dot = email.rfind('.');
    return at != string::npos && at > 0 && dot != string::npos && dot > at + 1 && dot < email.size() - 1;
}

// ---------- database class ----------

class ContactBook {
private:
    sqlite3* db;

    // Runs SQL that returns no rows and needs no input values (CREATE, PRAGMA, ...)
    bool execute(const char* sql) {
        char* error = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &error) != SQLITE_OK) {
            cout << "SQL error: " << error << "\n";
            sqlite3_free(error);
            return false;
        }
        return true;
    }

    // Reads a TEXT column safely (NULL becomes "-")
    string columnText(sqlite3_stmt* stmt, int col) {
        const unsigned char* text = sqlite3_column_text(stmt, col);
        if (text == nullptr || text[0] == '\0') return "-";
        return string((const char*)text);
    }

    void printHeader() {
        cout << left << setw(5) << "ID" << setw(22) << "Name" << setw(16) << "Phone"
             << setw(28) << "Email" << "Address\n";
        cout << string(90, '-') << "\n";
    }

    void printRow(sqlite3_stmt* stmt) {
        cout << left << setw(5)  << sqlite3_column_int(stmt, 0)
             << setw(22) << columnText(stmt, 1)
             << setw(16) << columnText(stmt, 2)
             << setw(28) << columnText(stmt, 3)
             << columnText(stmt, 4) << "\n";
    }

public:
    ContactBook() { db = nullptr; }

    bool open(string fileName) {
        if (sqlite3_open(fileName.c_str(), &db) != SQLITE_OK) {
            cout << "Cannot open database: " << sqlite3_errmsg(db) << "\n";
            return false;
        }
        return execute(
            "CREATE TABLE IF NOT EXISTS contacts ("
            "  contact_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "  name       VARCHAR(100) NOT NULL,"
            "  phone      VARCHAR(20)  NOT NULL UNIQUE,"
            "  email      VARCHAR(100),"
            "  address    VARCHAR(200),"
            "  created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
            ");");
    }

    void close() {
        if (db != nullptr) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    ~ContactBook() { close(); }

    // 1. Add New Contact
    void addContact(string name, string phone, string email, string address) {
        sqlite3_stmt* stmt;
        // ? = placeholder. Values are bound separately, so user input can never change the SQL.
        sqlite3_prepare_v2(db,
            "INSERT INTO contacts (name, phone, email, address) VALUES (?, ?, ?, ?);",
            -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, name.c_str(),    -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, phone.c_str(),   -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, email.c_str(),   -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, address.c_str(), -1, SQLITE_TRANSIENT);

        int result = sqlite3_step(stmt);
        if (result == SQLITE_DONE)
            cout << "Contact added with ID " << sqlite3_last_insert_rowid(db) << ".\n";
        else if (result == SQLITE_CONSTRAINT)
            cout << "A contact with this phone number already exists.\n";
        else
            cout << "Error: " << sqlite3_errmsg(db) << "\n";
        sqlite3_finalize(stmt);
    }

    // 2. Display All Contacts
    void displayAll() {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "SELECT contact_id, name, phone, email, address FROM contacts ORDER BY name;",
            -1, &stmt, nullptr);

        int count = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {   // one loop = one row
            if (count == 0) printHeader();
            printRow(stmt);
            count++;
        }
        sqlite3_finalize(stmt);

        if (count == 0) cout << "No contacts yet.\n";
        else cout << count << " contact(s).\n";
    }

    // 3. Search Contact (by part of the name, or exact phone / email)
    void search(string text) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "SELECT contact_id, name, phone, email, address FROM contacts "
            "WHERE name LIKE ? OR phone = ? OR email = ? ORDER BY name;",
            -1, &stmt, nullptr);
        string pattern = "%" + text + "%";
        sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, text.c_str(),    -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, text.c_str(),    -1, SQLITE_TRANSIENT);

        int count = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            if (count == 0) printHeader();
            printRow(stmt);
            count++;
        }
        sqlite3_finalize(stmt);
        if (count == 0) cout << "No matching contacts.\n";
    }

    bool exists(int id) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, "SELECT 1 FROM contacts WHERE contact_id = ?;", -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, id);
        bool found = sqlite3_step(stmt) == SQLITE_ROW;
        sqlite3_finalize(stmt);
        return found;
    }

    // 4. Update Contact Information
    // fieldNumber: 1 name, 2 phone, 3 email, 4 address
    void updateField(int id, int fieldNumber, string newValue) {
        // Column names can NOT be bound with ?, so we pick them from a fixed list.
        // Never put the user's text directly into the SQL string.
        string sql;
        if      (fieldNumber == 1) sql = "UPDATE contacts SET name = ? WHERE contact_id = ?;";
        else if (fieldNumber == 2) sql = "UPDATE contacts SET phone = ? WHERE contact_id = ?;";
        else if (fieldNumber == 3) sql = "UPDATE contacts SET email = ? WHERE contact_id = ?;";
        else if (fieldNumber == 4) sql = "UPDATE contacts SET address = ? WHERE contact_id = ?;";
        else { cout << "Invalid field.\n"; return; }

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, newValue.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int (stmt, 2, id);

        int result = sqlite3_step(stmt);
        if (result == SQLITE_CONSTRAINT)
            cout << "Another contact already uses this phone number.\n";
        else if (result != SQLITE_DONE)
            cout << "Error: " << sqlite3_errmsg(db) << "\n";
        else if (sqlite3_changes(db) == 0)          // no row had this id
            cout << "Contact not found.\n";
        else
            cout << "Contact updated.\n";
        sqlite3_finalize(stmt);
    }

    // 5. Delete Contact
    void deleteContact(int id) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, "DELETE FROM contacts WHERE contact_id = ?;", -1, &stmt, nullptr);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        if (sqlite3_changes(db) == 0) cout << "Contact not found.\n";
        else cout << "Contact deleted.\n";
        sqlite3_finalize(stmt);
    }
};

// ---------- menu actions (input + validation, then call the database) ----------

void addContactMenu(ContactBook& book) {
    string name = readLine("Name: ");
    if (name.empty()) { cout << "Name is required.\n"; return; }

    string phone = readLine("Phone: ");
    if (!isValidPhone(phone)) { cout << "Phone must be 7-15 digits (may start with +).\n"; return; }

    string email = readLine("Email (optional): ");
    if (!isValidEmail(email)) { cout << "Invalid email format.\n"; return; }

    string address = readLine("Address (optional): ");
    book.addContact(name, phone, email, address);
}

void updateContactMenu(ContactBook& book) {
    int id = readInt("Contact ID: ");
    if (!book.exists(id)) { cout << "Contact not found.\n"; return; }

    cout << "What do you want to update?  1. Name  2. Phone  3. Email  4. Address\n";
    int field = readInt("Choice: ");
    string value = readLine("New value: ");

    if (field == 1 && value.empty())         { cout << "Name is required.\n"; return; }
    if (field == 2 && !isValidPhone(value))  { cout << "Invalid phone number.\n"; return; }
    if (field == 3 && !isValidEmail(value))  { cout << "Invalid email format.\n"; return; }

    book.updateField(id, field, value);
}

void deleteContactMenu(ContactBook& book) {
    int id = readInt("Contact ID: ");
    string answer = readLine("Are you sure? (y/n): ");
    if (answer == "y" || answer == "Y") book.deleteContact(id);
    else cout << "Cancelled.\n";
}

int main() {
    ContactBook book;
    if (!book.open("contacts.db")) return 1;

    int choice;
    do {
        cout << "\n===== Contact Manager =====\n"
             << "1. Add new contact\n"
             << "2. Display all contacts\n"
             << "3. Search contact\n"
             << "4. Update contact\n"
             << "5. Delete contact\n"
             << "0. Exit\n";
        choice = readInt("Choice: ");

        switch (choice) {
            case 1: addContactMenu(book); break;
            case 2: book.displayAll(); break;
            case 3: book.search(readLine("Name, phone or email: ")); break;
            case 4: updateContactMenu(book); break;
            case 5: deleteContactMenu(book); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    book.close();   // 7. Exit: close the database connection safely
    cout << "Goodbye!\n";
    return 0;
}
