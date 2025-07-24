#include <iostream>
using namespace std;

// Global Variables-> to make it easy to access them in all functions without
// passing them as parameters
string ownerName;
double balance = 0.0;
int pinCode;

void createAccount() {
  cout << "Enter your name: ";
  getline(cin, ownerName);
  cout << "Set your 4-digit PIN: ";
  cin >> pinCode;
  cout << "Account created successfully\n";
}

bool verifyPIN() {
  int enteredPIN;
  cout << "Enter your PIN: ";
  cin >> enteredPIN;
  if (enteredPIN == pinCode)
    return true;
  else
    return false;
}

void deposit() // add money to the account
{
  if (!verifyPIN()) {
    cout << "Incorrect PIN. Access denied.\n";
    return;
  } else {
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    if (amount > 0) {
      balance += amount;
      cout << "Deposited " << amount << " EGP successfully.\n";
    } else {
      cout << "Invalid amount.\n";
    }
  }
}

void withdraw() // remove money from the account
{
  if (!verifyPIN()) {
    cout << "Incorrect PIN. Access denied.\n";
    return;
  } else {
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (amount > balance) {
      cout << "There is not enough money in the account";
    } else if (amount > 0) {
      balance -= amount;
      cout << "Withdrew " << amount << " EGP successfully.\n";
    } else {
      cout << "Invalid amount.\n";
    }
  }
}

void displayAccount() {
  if (!verifyPIN()) {
    cout << "Incorrect PIN. Access denied.\n";
    return;
  } 
  else 
  {
    cout << "\n--- Account Info ---\n";
    cout << "Name: " << ownerName << endl;
    cout << "Balance: " << balance << " EGP" << endl;
  }
}

int main() {
  cout << "Welcome to Our Bank System\n";
  cout << "-------------------------------\n";
  createAccount();
  int choice;
  do {
    cout << "\n--- Menu ---\n";
    cout << "1. Deposit\n";
    cout << "2. Withdraw\n";
    cout << "3. Display Account Info\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
      deposit();
      break;
    case 2:
      withdraw();
      break;
    case 3:
      displayAccount();
      break;
    case 4:
      cout << "Thank you for using our bank. Goodbye\n";
      break;
    default:
      cout << "Invalid choice. Try again.\n";
    }

  } while (choice != 4);

  return 0;
}
