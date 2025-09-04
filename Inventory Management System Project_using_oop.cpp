#include <iostream>
#include <vector>
using namespace std;

class Item {
private:
  int id;
  string name;
  int quantity;
  double price;

public:
  Item(int i, string n, int q, double p) {
    this->id = i;
    this->name = n;
    this->quantity = q;
    this->price = p;
  }

  int getId() const { return id; }
  string getName() const { return name; }
  int getQuantity() const { return quantity; }
  double getPrice() const { return price; }

  void setQuantity(int q) { quantity = q; }

  void display() const {
    cout << "ID: " << id << ", Name: " << name << ", Quantity: " << quantity
         << ", Price: " << price << endl;
  }
};

class Inventory {
private:
  vector<Item> items;

public:
  void addItem() {
    int id, quantity;
    string name;
    double price;
    cout << "Enter Item ID: ";
    cin >> id;
    cout << "Enter Item Name: ";
    cin >> name;
    cout << "Enter Quantity: ";
    cin >> quantity;
    cout << "Enter Price: ";
    cin >> price;
    items.push_back(Item(id, name, quantity, price));
    cout << "Item added successfully\n";
  }

  void displayItems() const {
    if (items.empty()) {
      cout << "Inventory is empty.\n";
      return;
    }
    cout << "\n--- Inventory Items ---\n";
    for ( auto &item : items) {
      item.display();
    }
  }

  void searchItem() const {
    int id;
    cout << "Enter Item ID to search: ";
    cin >> id;
    for ( auto &item : items) {
      if (item.getId() == id) {
        item.display();
        return;
      }
    }
    cout << "Item not found.\n";
  }

  void updateQuantity() {
    int id, newQty;
    cout << "Enter Item ID to update quantity: ";
    cin >> id;
    for (auto &item : items) {
      if (item.getId() == id) {
        cout << "Current Quantity: " << item.getQuantity() << endl;
        cout << "Enter new Quantity: ";
        cin >> newQty;
        item.setQuantity(newQty);
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
    for (int i = 0; i < items.size(); i++) {
      if (items[i].getId() == id) {
        items.erase(items.begin() + i);
        cout << "Item deleted successfully\n";
        return;
      }
    }
    cout << "Item not found.\n";
  }
};

int main() {
  Inventory inventory;
  int choice;
  do {
    cout << "\nInventory Management System (OOP + Vector)\n";
    cout << "1. Add Item\n2. Display Items\n3. Search Item\n";
    cout << "4. Update Quantity\n5. Delete Item\n6. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case 1:
      inventory.addItem();
      break;
    case 2:
      inventory.displayItems();
      break;
    case 3:
      inventory.searchItem();
      break;
    case 4:
      inventory.updateQuantity();
      break;
    case 5:
      inventory.deleteItem();
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
