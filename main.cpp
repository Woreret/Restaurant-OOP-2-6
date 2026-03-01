#include <iostream>
#include <string>

class MenuItem {
private:
    std::string name;
    double price;
    std::string category;

public:
    MenuItem(std::string n, double p, std::string c) 
        : name(n), price(p), category(c) {
        std::cout << "[MenuItem] Main constructor called\n";
    }

    MenuItem(std::string n, double p) 
        : MenuItem(n, p, "No category") { 
        std::cout << "[MenuItem] Delegated constructor called\n";
    }

    MenuItem() : MenuItem("Unknown dish", 0.0, "General") {
        std::cout << "[MenuItem] Default constructor called\n";
    }

    ~MenuItem() {
        std::cout << "[MenuItem] Destructor called for " << name << "\n";
    }

    void display() const {
        std::cout << "Dish: " << name << " | Price: " << price << " | Category: " << category << "\n";
    }
};

class Customer {
private:
    std::string fullName;
    std::string phoneNumber;
    int loyaltyPoints;

public:
    Customer(std::string name, std::string phone, int points)
        : fullName(name), phoneNumber(phone), loyaltyPoints(points) {
        std::cout << "[Customer] Main constructor called for: " << fullName << std::endl;
    }

    Customer(std::string name) : Customer(name, "Unknown", 10) {
        std::cout << "[Customer] Delegated constructor called for: " << fullName << std::endl;
    }

    Customer() : Customer("Guest", "None", 0) {
        std::cout << "[Customer] Default constructor called for: " << fullName << std::endl;
    }

    ~Customer() {
        std::cout << "[Customer] Destructor called for: " << fullName << std::endl;
    }

    void displayInfo() const {
        std::cout << "Customer: " << fullName << " | Phone: " << phoneNumber << " | Points: " << loyaltyPoints << std::endl;
    }
};

class Order {
private:
    int orderId;
    std::string status;
    double totalAmount;

public:
    Order(int id, std::string s, double total) 
        : orderId(id), status(s), totalAmount(total) {
        std::cout << "[Order] Main constructor called for ID: " << orderId << std::endl;
    }

    Order(int id) : Order(id, "Processing", 0.0) {
        std::cout << "[Order] Delegated constructor called for ID: " << orderId << std::endl;
    }

    Order() : Order(0, "New", 0.0) {
        std::cout << "[Order] Default constructor called for ID: " << orderId << std::endl;
    }

    ~Order() {
        std::cout << "[Order] Destructor called for ID: " << orderId << std::endl;
    }

    void printOrder() const {
        std::cout << "Order ID: " << orderId << " | Status: " << status << " | Total: " << totalAmount << " UAH" << std::endl;
    }
};

int main() {

    std::cout << "Creating MenuItem objects:" << std::endl;
    MenuItem item1("Borsch", 120.5, "First courses");
    MenuItem item2("Coffee", 50.0);
    MenuItem item3;

    std::cout << "\nCreating Customer objects:" << std::endl;
    Customer c1("Alexander", "+380991234567", 100);
    Customer c2("Maria");
    Customer c3;

    std::cout << "\nCreating Order objects:" << std::endl;
    Order o1(101, "Ready", 450.0);
    Order o2(102);
    Order o3;

    std::cout << "\nInformation output (Calling class methods):" << std::endl;
    item1.display();
    item2.display();
    c1.displayInfo();
    c2.displayInfo();
    o1.printOrder();
    o2.printOrder();

    std::cout << "\nDestroying objects:" << std::endl;
    return 0;
}
