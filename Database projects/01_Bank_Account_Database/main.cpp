// Project 01: Bank Account Database Management System (C++ + SQLite)
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

double readAmount(string prompt) {
    while (true) {
        string text = readLine(prompt);
        try {
            size_t used;
            double value = stod(text, &used);
            if (used == text.size() && value >= 0) return value;
        } catch (...) {}
        cout << "Please enter a valid positive amount.\n";
    }
}

bool isDigitsOnly(string text) {
    if (text.empty()) return false;
    for (char c : text)
        if (c < '0' || c > '9') return false;
    return true;
}

// ---------- database class ----------

class Bank {
private:
    sqlite3* db;

    bool execute(const char* sql) {
        char* error = nullptr;
        if (sqlite3_exec(db, sql, nullptr, nullptr, &error) != SQLITE_OK) {
            cout << "SQL error: " << error << "\n";
            sqlite3_free(error);
            return false;
        }
        return true;
    }

    string columnText(sqlite3_stmt* stmt, int col) {
        const unsigned char* text = sqlite3_column_text(stmt, col);
        if (text == nullptr || text[0] == '\0') return "-";
        return string((const char*)text);
    }

    void printHeader() {
        cout << left << setw(12) << "Account No" << setw(22) << "Holder" << setw(10) << "Type"
             << right << setw(14) << "Balance" << "   " << left << setw(14) << "Phone" << "Address\n";
        cout << string(95, '-') << "\n";
    }

    // expects columns: account_number, holder_name, account_type, balance, phone, address
    void printRow(sqlite3_stmt* stmt) {
        cout << left << setw(12) << columnText(stmt, 0)
             << setw(22) << columnText(stmt, 1)
             << setw(10) << columnText(stmt, 2)
             << right << setw(14) << fixed << setprecision(2) << sqlite3_column_double(stmt, 3)
             << "   " << left << setw(14) << columnText(stmt, 4)
             << columnText(stmt, 5) << "\n";
    }

    // Adds one row to the transactions table using the account's CURRENT balance
    bool logTransaction(string accountNumber, string type, double amount) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "INSERT INTO transactions (account_id, type, amount, balance_after) "
            "SELECT account_id, ?, ?, balance FROM accounts WHERE account_number = ?;",
            -1, &stmt, nullptr);
        sqlite3_bind_text  (stmt, 1, type.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 2, amount);
        sqlite3_bind_text  (stmt, 3, accountNumber.c_str(), -1, SQLITE_TRANSIENT);
        bool ok = sqlite3_step(stmt) == SQLITE_DONE;
        sqlite3_finalize(stmt);
        return ok;
    }

public:
    Bank() { db = nullptr; }

    bool open(string fileName) {
        if (sqlite3_open(fileName.c_str(), &db) != SQLITE_OK) {
            cout << "Cannot open database: " << sqlite3_errmsg(db) << "\n";
            return false;
        }
        // SQLite ignores FOREIGN KEY rules unless we turn them on for each connection
        return execute("PRAGMA foreign_keys = ON;") &&
               execute(
                "CREATE TABLE IF NOT EXISTS accounts ("
                "  account_id     INTEGER PRIMARY KEY AUTOINCREMENT,"
                "  account_number VARCHAR(20)  NOT NULL UNIQUE,"
                "  holder_name    VARCHAR(100) NOT NULL,"
                "  account_type   VARCHAR(20)  NOT NULL CHECK (account_type IN ('Savings', 'Current')),"
                "  balance        DECIMAL(12,2) NOT NULL DEFAULT 0 CHECK (balance >= 0),"
                "  phone          VARCHAR(20),"
                "  address        VARCHAR(200),"
                "  created_at     DATETIME DEFAULT CURRENT_TIMESTAMP"
                ");") &&
               execute(
                "CREATE TABLE IF NOT EXISTS transactions ("
                "  transaction_id   INTEGER PRIMARY KEY AUTOINCREMENT,"
                "  account_id       INTEGER NOT NULL REFERENCES accounts(account_id) ON DELETE CASCADE,"
                "  type             VARCHAR(10) NOT NULL CHECK (type IN ('Deposit', 'Withdraw')),"
                "  amount           DECIMAL(12,2) NOT NULL CHECK (amount > 0),"
                "  balance_after    DECIMAL(12,2) NOT NULL,"
                "  transaction_date DATETIME DEFAULT CURRENT_TIMESTAMP"
                ");");
    }

    void close() {
        if (db != nullptr) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    ~Bank() { close(); }

    bool exists(string accountNumber) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, "SELECT 1 FROM accounts WHERE account_number = ?;", -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, accountNumber.c_str(), -1, SQLITE_TRANSIENT);
        bool found = sqlite3_step(stmt) == SQLITE_ROW;
        sqlite3_finalize(stmt);
        return found;
    }

    // 1. Add New Account
    void addAccount(string accountNumber, string holderName, string type,
                    double initialBalance, string phone, string address) {
        execute("BEGIN TRANSACTION;");

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "INSERT INTO accounts (account_number, holder_name, account_type, balance, phone, address) "
            "VALUES (?, ?, ?, ?, ?, ?);", -1, &stmt, nullptr);
        sqlite3_bind_text  (stmt, 1, accountNumber.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text  (stmt, 2, holderName.c_str(),    -1, SQLITE_TRANSIENT);
        sqlite3_bind_text  (stmt, 3, type.c_str(),          -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 4, initialBalance);
        sqlite3_bind_text  (stmt, 5, phone.c_str(),         -1, SQLITE_TRANSIENT);
        sqlite3_bind_text  (stmt, 6, address.c_str(),       -1, SQLITE_TRANSIENT);
        int result = sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (result == SQLITE_CONSTRAINT) {
            execute("ROLLBACK;");
            cout << "This account number already exists.\n";
            return;
        }
        if (result != SQLITE_DONE) {
            execute("ROLLBACK;");
            cout << "Error: " << sqlite3_errmsg(db) << "\n";
            return;
        }

        // The opening balance counts as the first deposit in the history
        if (initialBalance > 0 && !logTransaction(accountNumber, "Deposit", initialBalance)) {
            execute("ROLLBACK;");
            cout << "Error: " << sqlite3_errmsg(db) << "\n";
            return;
        }

        execute("COMMIT;");
        cout << "Account " << accountNumber << " created.\n";
    }

    // 2. Display All Accounts
    void displayAll() {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "SELECT account_number, holder_name, account_type, balance, phone, address "
            "FROM accounts ORDER BY account_number;", -1, &stmt, nullptr);

        int count = 0;
        double total = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            if (count == 0) printHeader();
            printRow(stmt);
            total += sqlite3_column_double(stmt, 3);
            count++;
        }
        sqlite3_finalize(stmt);

        if (count == 0) cout << "No accounts yet.\n";
        else cout << count << " account(s), total balance: " << fixed << setprecision(2) << total << "\n";
    }

    // 3. Search Account (exact account number, or part of the holder name)
    void search(string text) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "SELECT account_number, holder_name, account_type, balance, phone, address "
            "FROM accounts WHERE account_number = ? OR holder_name LIKE ? ORDER BY account_number;",
            -1, &stmt, nullptr);
        string pattern = "%" + text + "%";
        sqlite3_bind_text(stmt, 1, text.c_str(),    -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, pattern.c_str(), -1, SQLITE_TRANSIENT);

        int count = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            if (count == 0) printHeader();
            printRow(stmt);
            count++;
        }
        sqlite3_finalize(stmt);
        if (count == 0) cout << "No matching accounts.\n";
    }

    // 4. Deposit Money
    void deposit(string accountNumber, double amount) {
        if (amount <= 0) { cout << "Amount must be more than 0.\n"; return; }

        // A transaction makes the UPDATE and the INSERT happen together, or not at all
        execute("BEGIN TRANSACTION;");

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "UPDATE accounts SET balance = balance + ? WHERE account_number = ?;",
            -1, &stmt, nullptr);
        sqlite3_bind_double(stmt, 1, amount);
        sqlite3_bind_text  (stmt, 2, accountNumber.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (sqlite3_changes(db) == 0) {
            execute("ROLLBACK;");
            cout << "Account not found.\n";
            return;
        }
        if (!logTransaction(accountNumber, "Deposit", amount)) {
            execute("ROLLBACK;");
            cout << "Error: " << sqlite3_errmsg(db) << "\n";
            return;
        }
        execute("COMMIT;");
        cout << "Deposited " << fixed << setprecision(2) << amount << ".\n";
    }

    // 4. Withdraw Money (no overdrafts)
    void withdraw(string accountNumber, double amount) {
        if (amount <= 0) { cout << "Amount must be more than 0.\n"; return; }
        if (!exists(accountNumber)) { cout << "Account not found.\n"; return; }

        execute("BEGIN TRANSACTION;");

        // The "balance >= ?" condition is the overdraft check: if the money is not
        // enough, no row matches and nothing changes.
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "UPDATE accounts SET balance = balance - ? "
            "WHERE account_number = ? AND balance >= ?;",
            -1, &stmt, nullptr);
        sqlite3_bind_double(stmt, 1, amount);
        sqlite3_bind_text  (stmt, 2, accountNumber.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(stmt, 3, amount);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if (sqlite3_changes(db) == 0) {
            execute("ROLLBACK;");
            cout << "Insufficient balance.\n";
            return;
        }
        if (!logTransaction(accountNumber, "Withdraw", amount)) {
            execute("ROLLBACK;");
            cout << "Error: " << sqlite3_errmsg(db) << "\n";
            return;
        }
        execute("COMMIT;");
        cout << "Withdrew " << fixed << setprecision(2) << amount << ".\n";
    }

    // 5. Update Account Information
    // fieldNumber: 1 holder name, 2 phone, 3 address
    void updateField(string accountNumber, int fieldNumber, string newValue) {
        // Column names can NOT be bound with ?, so we pick them from a fixed list
        string sql;
        if      (fieldNumber == 1) sql = "UPDATE accounts SET holder_name = ? WHERE account_number = ?;";
        else if (fieldNumber == 2) sql = "UPDATE accounts SET phone = ? WHERE account_number = ?;";
        else if (fieldNumber == 3) sql = "UPDATE accounts SET address = ? WHERE account_number = ?;";
        else { cout << "Invalid field.\n"; return; }

        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, newValue.c_str(),      -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, accountNumber.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        if (sqlite3_changes(db) == 0) cout << "Account not found.\n";
        else cout << "Account updated.\n";
        sqlite3_finalize(stmt);
    }

    // 6. Delete Account (its transactions are deleted too: ON DELETE CASCADE)
    void deleteAccount(string accountNumber) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, "DELETE FROM accounts WHERE account_number = ?;", -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, accountNumber.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
        if (sqlite3_changes(db) == 0) cout << "Account not found.\n";
        else cout << "Account deleted.\n";
        sqlite3_finalize(stmt);
    }

    // Bonus: Transaction History (uses a JOIN between the two tables)
    void showHistory(string accountNumber) {
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db,
            "SELECT t.transaction_date, t.type, t.amount, t.balance_after "
            "FROM transactions t JOIN accounts a ON a.account_id = t.account_id "
            "WHERE a.account_number = ? ORDER BY t.transaction_id;",
            -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, accountNumber.c_str(), -1, SQLITE_TRANSIENT);

        int count = 0;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            if (count == 0) {
                cout << left << setw(22) << "Date" << setw(10) << "Type"
                     << right << setw(14) << "Amount" << setw(16) << "Balance after" << "\n";
                cout << string(62, '-') << "\n";
            }
            cout << left << setw(22) << columnText(stmt, 0) << setw(10) << columnText(stmt, 1)
                 << right << fixed << setprecision(2)
                 << setw(14) << sqlite3_column_double(stmt, 2)
                 << setw(16) << sqlite3_column_double(stmt, 3) << "\n";
            count++;
        }
        sqlite3_finalize(stmt);
        if (count == 0) cout << "No transactions for this account.\n";
    }
};

// ---------- menu actions (input + validation, then call the database) ----------

void addAccountMenu(Bank& bank) {
    string number = readLine("Account number (digits only): ");
    if (!isDigitsOnly(number) || number.size() > 20) { cout << "Invalid account number.\n"; return; }
    if (bank.exists(number)) { cout << "This account number already exists.\n"; return; }

    string name = readLine("Holder name: ");
    if (name.empty()) { cout << "Holder name is required.\n"; return; }

    int typeChoice = readInt("Account type  1. Savings  2. Current: ");
    if (typeChoice != 1 && typeChoice != 2) { cout << "Invalid account type.\n"; return; }
    string type = (typeChoice == 1) ? "Savings" : "Current";

    double balance = readAmount("Initial balance: ");
    string phone   = readLine("Phone (optional): ");
    if (!phone.empty() && !isDigitsOnly(phone)) { cout << "Phone must contain digits only.\n"; return; }
    string address = readLine("Address (optional): ");

    bank.addAccount(number, name, type, balance, phone, address);
}

void updateAccountMenu(Bank& bank) {
    string number = readLine("Account number: ");
    if (!bank.exists(number)) { cout << "Account not found.\n"; return; }

    cout << "What do you want to update?  1. Holder name  2. Phone  3. Address\n";
    int field = readInt("Choice: ");
    string value = readLine("New value: ");

    if (field == 1 && value.empty()) { cout << "Holder name is required.\n"; return; }
    if (field == 2 && !value.empty() && !isDigitsOnly(value)) { cout << "Phone must contain digits only.\n"; return; }

    bank.updateField(number, field, value);
}

void deleteAccountMenu(Bank& bank) {
    string number = readLine("Account number: ");
    string answer = readLine("This also deletes the account's history. Are you sure? (y/n): ");
    if (answer == "y" || answer == "Y") bank.deleteAccount(number);
    else cout << "Cancelled.\n";
}

int main() {
    Bank bank;
    if (!bank.open("bank.db")) return 1;

    int choice;
    do {
        cout << "\n===== Bank Account System =====\n"
             << "1. Add new account\n"
             << "2. Display all accounts\n"
             << "3. Search account\n"
             << "4. Deposit\n"
             << "5. Withdraw\n"
             << "6. Update account info\n"
             << "7. Delete account\n"
             << "8. Transaction history\n"
             << "0. Exit\n";
        choice = readInt("Choice: ");

        switch (choice) {
            case 1: addAccountMenu(bank); break;
            case 2: bank.displayAll(); break;
            case 3: bank.search(readLine("Account number or holder name: ")); break;
            case 4: {
                string number = readLine("Account number: ");
                bank.deposit(number, readAmount("Amount: "));
                break;
            }
            case 5: {
                string number = readLine("Account number: ");
                bank.withdraw(number, readAmount("Amount: "));
                break;
            }
            case 6: updateAccountMenu(bank); break;
            case 7: deleteAccountMenu(bank); break;
            case 8: bank.showHistory(readLine("Account number: ")); break;
            case 0: break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    bank.close();   // 8. Exit: close the database connection safely
    cout << "Goodbye!\n";
    return 0;
}
