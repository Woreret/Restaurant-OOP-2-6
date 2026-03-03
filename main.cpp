#include <iostream>
#include <string>

#include "MenuItem.h"
#include "Customer.h"
#include "Order.h"

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
