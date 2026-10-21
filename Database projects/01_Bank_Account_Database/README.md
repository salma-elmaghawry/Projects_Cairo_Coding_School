# Project 01: Bank Account Database Management System

A C++ console app that manages bank accounts stored in SQLite (`bank.db`).

## Features

1. Add new account (account number, holder name, type, initial balance, phone, address)
2. Display all accounts with the total balance
3. Search by account number or part of the holder name
4. Deposit money
5. Withdraw money (no overdrafts)
6. Update holder name, phone or address
7. Delete account (asks for confirmation)
8. Transaction history for an account (bonus, uses a `JOIN`)
0. Exit and close the connection

## Tables

**accounts**

| Field | Type | Notes |
|---|---|---|
| account_id | INTEGER | Primary key |
| account_number | VARCHAR(20) | `UNIQUE`, digits only |
| holder_name | VARCHAR(100) | Required |
| account_type | VARCHAR(20) | `Savings` or `Current` |
| balance | DECIMAL(12,2) | `CHECK (balance >= 0)` |
| phone | VARCHAR(20) | Optional |
| address | VARCHAR(200) | Optional |
| created_at | DATETIME | Set automatically |

**transactions**

| Field | Type | Notes |
|---|---|---|
| transaction_id | INTEGER | Primary key |
| account_id | INTEGER | Foreign key to `accounts`, `ON DELETE CASCADE` |
| type | VARCHAR(10) | `Deposit` or `Withdraw` |
| amount | DECIMAL(12,2) | Must be more than 0 |
| balance_after | DECIMAL(12,2) | Balance right after this operation |
| transaction_date | DATETIME | Set automatically |

## Key points in the solution

- **Overdraft check inside SQL:** `UPDATE accounts SET balance = balance - ? WHERE account_number = ? AND balance >= ?`. If the money is not enough, no row matches and `sqlite3_changes` returns 0.
- **Transactions (`BEGIN` / `COMMIT` / `ROLLBACK`):** a deposit or withdrawal updates `accounts` and inserts into `transactions`. Both happen together, or neither happens.
- **Opening balance:** a new account with an initial balance gets a first `Deposit` row, so the history always adds up.
- **Foreign keys:** SQLite ignores them unless `PRAGMA foreign_keys = ON;` runs on each connection. With it on, deleting an account also deletes its transactions.

## How to run

Add `sqlite3.c` and `sqlite3.h` to this folder (see the parent README), then:

```bash
gcc -c sqlite3.c -o sqlite3.o
g++ main.cpp sqlite3.o -o bank
./bank
```
