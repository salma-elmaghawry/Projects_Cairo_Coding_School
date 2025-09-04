#include <iostream>
#include <vector>
using namespace std;

struct Item {
  int id;
  string name;
  int quantity;
  double price;
};

vector<Item> inventory;

void addItem() {
  Item newItem;
  cout << "Enter Item ID: ";
  cin >> newItem.id;
  cout << "Enter Item Name: ";
  cin >> newItem.name;
  cout << "Enter Quantity: ";
  cin >> newItem.quantity;
  cout << "Enter Price: ";
  cin >> newItem.price;

  inventory.push_back(newItem);
  cout << "Item added successfully\n";
}

void displayItems() {
  if (inventory.empty()) {
    cout << "Inventory is empty.\n";
    return;
  }
  cout << "\n--- Inventory Items ---\n";
  for (auto &item : inventory) {
    cout << "ID: " << item.id << ", Name: " << item.name
         << ", Quantity: " << item.quantity << ", Price: " << item.price
         << endl;
  }
}

void searchItem() {
  int id;
  cout << "Enter Item ID to search: ";
  cin >> id;
  for (auto &item : inventory) {
    if (item.id == id) {
      cout << "ID: " << item.id << ", Name: " << item.name
           << ", Quantity: " << item.quantity << ", Price: " << item.price
           << endl;
      return;
    }
  }
  cout << "Item not found.\n";
}

void updateQuantity() {
  int id, newQty;
  cout << "Enter Item ID to update quantity: ";
  cin >> id;
  for (auto &item : inventory) {
    if (item.id == id) {
      cout << "Current Quantity: " << item.quantity << endl;
      cout << "Enter new Quantity: ";
      cin >> newQty;
      item.quantity = newQty;
      cout << "Quantity updated successfully\n";
      return;
    }
  }
  cout << "Item not found.\n";
}

void deleteItem() {
  int id;
  cout << "Enter Item ID to delete: ";
  cin >> id;
  for (int i = 0; i < inventory.size(); i++) {
    if (inventory[i].id == id) {
      inventory.erase(inventory.begin() + i);
      cout << "Item deleted successfully\n";
      return;
    }
  }
  cout << "Item not found.\n";
}

int main() {
  int choice;
  do {
    cout << "\nInventory Management System \n";
    cout << "1. Add Item\n2. Display Items\n3. Search Item\n";
    cout << "4. Update Quantity\n5. Delete Item\n6. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      addItem();
      break;
    case 2:
      displayItems();
      break;
    case 3:
      searchItem();
      break;
    case 4:
      updateQuantity();
      break;
    case 5:
      deleteItem();
      break;
    case 6:
      cout << "Exiting...\n";
      break;
    default:
      cout << "Invalid choice\n";
    }
  } while (choice != 6);

  return 0;
}
