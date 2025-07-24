#include <iostream>
using namespace std;

class BankAccount {
private:
  string ownerName;
  double balance;
  int pinCode;

  bool verifyPIN() {
    int enteredPIN;
    cout << "Enter your PIN: ";
    cin >> enteredPIN;
    if (enteredPIN == pinCode)
      return true;
    else
      return false;
  }

public:
  BankAccount() { balance = 0.0; }

  void createAccount() {
    cout << "Enter your name: ";

    getline(cin, ownerName);
    cout << "Set your 4-digit PIN: ";
    cin >> pinCode;
    cout << "Account created successfully.\n";
  }

  void deposit() {
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

  void withdraw() {
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
    } else {
      cout << "\n--- Account Info ---\n";
      cout << "Name: " << ownerName << endl;
      cout << "Balance: " << balance << " EGP" << endl;
    }}
  };

  int main() {
    BankAccount myAccount;
    int choice;

    cout << "Welcome to Our Bank System\n";
    cout << "--------------------------------------\n";
    myAccount.createAccount();

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
        myAccount.deposit();
        break;
      case 2:
        myAccount.withdraw();
        break;
      case 3:
        myAccount.displayAccount();
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
