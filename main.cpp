#include <iostream>
#include <string>
#include <utility>

#include "MenuItem.h"
#include "Customer.h"
#include "Order.h"
#include "Discount.h"
#include "DeliveryOrder.h"

int Order::totalOrdersCreated = 0;

int main() {
    std::cout << "--- Creating core objects ---" << std::endl;

    Customer c1("Alexander", "+380991234567", 100);
    
    Order standardOrder(101, "Ready", 500.0, c1);
    
    Order promoOrder(102, "En route", 600.0, c1);
    Discount holidayDiscount(15.0);
    promoOrder.setDiscount(holidayDiscount);


    std::cout << "\n--- Output Demonstration ---\n";
    standardOrder.printOrder();
    std::cout << "\n";
    promoOrder.printOrder();


    std::cout << "\n--- Delivery Order ---\n";
    Discount deliveryDiscount(10.0);
    DeliveryOrder delOrder(103, "Dispatched", 800.0, c1, deliveryDiscount, "Khreshchatyk 1", "John Doe");
    delOrder.printOrder();

    std::cout << "\n--- Copy & Move Constructor ---" << std::endl;
    Order copiedOrder = promoOrder; 
    
    Order movedOrder = std::move(promoOrder);

    DeliveryOrder copiedDelOrder = delOrder; 
    DeliveryOrder movedDelOrder = std::move(delOrder); 

    Order assignedOrder(999);
    assignedOrder = copiedOrder;

    std::cout << "\n--- Destroying objects ---" << std::endl;
    return 0;
}
