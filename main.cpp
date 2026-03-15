#include <iostream>
#include <string>
#include <utility>

#include "MenuItem.h"
#include "Customer.h"
#include "Order.h"
#include "DiscountedOrder.h"

int Order::totalOrdersCreated = 0;

int main() {
    std::cout << "--- Creating core objects ---" << std::endl;

    Customer c1("Alexander", "+380991234567", 100);
    
    Order standardOrder(101, "Ready", 500.0, c1);

    
    DiscountedOrder promoOrder(102, "En route", 600.0, c1, 15.0);


    std::cout << "\n--- Output Demonstration ---\n";
    standardOrder.printOrder();
    std::cout << "\n";
    promoOrder.printOrder();


    std::cout << "\n--- Copy & Move Constructor ---" << std::endl;
    DiscountedOrder copiedOrder = promoOrder; 
    
    DiscountedOrder movedOrder = std::move(promoOrder);

    DiscountedOrder assignedOrder(999, "New", 0.0, c1, 0.0);

    assignedOrder = copiedOrder;

    std::cout << "\n--- Destroying objects ---" << std::endl;
    return 0;
}
