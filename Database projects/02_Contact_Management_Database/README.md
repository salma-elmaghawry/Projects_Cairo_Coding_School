# Project 02: Contact Management Database System

A C++ console app that stores contacts in SQLite (`contacts.db`).

## Features

1. Add new contact (name, phone, email, address)
2. Display all contacts in a table
3. Search by part of the name, or exact phone / email
4. Update one field of a contact
5. Delete contact (asks for confirmation)
0. Exit and close the connection

## Table: contacts

| Field | Type | Notes |
|---|---|---|
| contact_id | INTEGER | Primary key, auto increment |
| name | VARCHAR(100) | Required |
| phone | VARCHAR(20) | Required, `UNIQUE` |
| email | VARCHAR(100) | Optional |
| address | VARCHAR(200) | Optional |
| created_at | DATETIME | Set automatically |

## Validation

- Name cannot be empty.
- Phone: 7 to 15 digits, may start with `+`. Stored as text, never as `INT`.
- Email (if entered) must look like `name@domain.com`.
- Duplicate phone numbers are rejected by the `UNIQUE` constraint (`SQLITE_CONSTRAINT`).

## Key points in the solution

- **Search with `LIKE`:** the name is matched with `%text%`, bound as a value like any other input.
- **Updating one field:** column names cannot be bound with `?`, so the SQL is picked from a fixed list based on the menu choice. The user's text is never put into the SQL string.

## How to run

Add `sqlite3.c` and `sqlite3.h` to this folder (see the parent README), then:

```bash
gcc -c sqlite3.c -o sqlite3.o
g++ main.cpp sqlite3.o -o contacts
./contacts
```
