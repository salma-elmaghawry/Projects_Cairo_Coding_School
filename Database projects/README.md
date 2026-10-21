# Database Projects

Solutions for the two Level 2 database projects (Cairo Coding School). Both are C++ console apps that store their data in **SQLite**.

| # | Project | Tables | Folder |
|---|---|---|---|
| 01 | Bank Account Database Management System | `accounts`, `transactions` | `01_Bank_Account_Database` |
| 02 | Contact Management Database System | `contacts` | `02_Contact_Management_Database` |

## Why SQLite?

SQLite needs no server and no installation. The whole database is one file (`bank.db` / `contacts.db`) created next to the program the first time it runs, and the library is just two files you add to the project.

## Setup (do this once per project folder)

1. Download the **amalgamation** zip from <https://www.sqlite.org/download.html> (`sqlite-amalgamation-XXXXXXX.zip`).
2. Copy `sqlite3.c` and `sqlite3.h` into the project folder, next to `main.cpp`.

## How to run

**Windows / macOS / Linux (using the amalgamation files):**

```bash
gcc -c sqlite3.c -o sqlite3.o
g++ main.cpp sqlite3.o -o app
./app
```

`sqlite3.c` is C code, so it is compiled with `gcc`, not `g++`.

**Linux (using the system library instead):**

```bash
sudo apt install libsqlite3-dev
g++ main.cpp -lsqlite3 -o app
./app
```

## Main ideas used in both projects

- **Prepared statements:** every value from the user goes through a `?` placeholder and `sqlite3_bind_*`. User input is never joined into the SQL string, which is what prevents SQL injection.
- **`sqlite3_changes(db)`:** after an `UPDATE` or `DELETE`, it tells you how many rows changed. `0` means the record was not found.
- **Constraints in the table:** `UNIQUE`, `NOT NULL` and `CHECK` let the database itself reject bad data.
- **`sqlite3_finalize`:** every prepared statement is finalized after use, and the connection is closed on exit.
