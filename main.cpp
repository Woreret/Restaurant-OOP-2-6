#include <iostream>
#include <string>

#include "MenuItem.h"
#include "Customer.h"
#include "Order.h"

int Order::totalOrdersCreated = 0;

int main() {
    std::cout << "--- 5. Static modifier demonstration ---" << std::endl;
    std::cout << "Total orders at start: " << Order::getTotalOrdersCreated() << std::endl;

    std::cout << "\n--- Creating Order objects ---" << std::endl;
    Order o1(101, "Ready", 450.0);
    Order o2(102);

    std::cout << "Total orders now: " << Order::getTotalOrdersCreated() << std::endl;

    std::cout << "\n--- 1. Copy Constructor demonstration ---" << std::endl;
    Order o_copy = o1; 
    
    std::cout << "\n--- 2. Move Constructor demonstration ---" << std::endl;
    Order o_move = std::move(o2); 

    std::cout << "\n--- 3. Using `this` pointer for method chaining ---" << std::endl;
    o1.setStatus("Delivered").setStatus("Closed");
    o1.printOrder();

    std::cout << "\n--- 4. Using const modifier with class objects ---" << std::endl;
    const Order const_order(999, "Constants", 100.0);
    const_order.printOrder(); 

    std::cout << "\n--- 6. Overloading Unary and Binary operators ---" << std::endl;
    Customer c1("Alexander", "+380991234567", 100);
    std::cout << "Before unary ++ (prefix): " << c1 << std::endl;
    ++c1;
    std::cout << "After unary ++ (prefix): " << c1 << std::endl;
    
    Order o_tip = o1 + 50.0;
    std::cout << "Original order total: " << o1 << std::endl;
    std::cout << "Order after adding 50 tip (binary +): " << o_tip << std::endl;

    std::cout << "\n--- 7. Overloading stream extraction/insertion (>>, <<) operators ---" << std::endl;
    MenuItem item1("Borsch", 120.5, "First courses");
    std::cout << "Output using overloaded << operator:" << std::endl;
    std::cout << "Item: " << item1 << std::endl;
    
    MenuItem customItem;
    std::string simulatedInput = "Pizza 200.0 Main_course";
    std::cout << "\nSimulated Input using overloaded >> operator with string: '" << simulatedInput << "'" << std::endl;
    
    std::cout << "Uncomment `std::cin >> customItem;` to read interactively" << std::endl;

    std::cout << "\n--- Total orders before destruction: " << Order::getTotalOrdersCreated() << " ---" << std::endl;
    std::cout << "\nDestroying objects:" << std::endl;
    return 0;
}
