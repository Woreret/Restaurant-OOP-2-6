#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>

#include "MenuItem.h"
#include "Pizza.h"
#include "Customer.h"
#include "Order.h"
#include "Discount.h"
#include "DeliveryOrder.h"
#include "StaffSalary.h"

int Order::totalOrdersCreated = 0;

std::ostream& operator<<(std::ostream& os, const Order& o) {
    o.print(os);
    return os;
}

void processOrder(const Order& order) {
    std::cout << "--- Processing Order ---\n";
    std::cout << order << "\n";
    std::cout << "--------------------------------------\n";
}

int main() {
    std::cout << "--- Creating core objects ---\n";

    Customer c1("Alexander", "+380991234567", 100);
    Discount holidayDiscount(15.0);
    Discount deliveryDiscount(10.0);

    std::unique_ptr<MenuItem> pizza = std::make_unique<Pizza>("Margherita", 150.0);
    std::cout << "\n--- Abstract class Demo ---\n";
    pizza->prepare();

    std::vector<std::unique_ptr<Order>> orders;
    orders.push_back(std::make_unique<Order>(101, "Ready", 500.0, c1));
    
    auto promoOrder = std::make_unique<Order>(102, "En route", 600.0, c1, holidayDiscount);
    *promoOrder += 50.0; 
    orders.push_back(std::move(promoOrder));

    orders.push_back(std::make_unique<DeliveryOrder>(103, "Dispatched", 800.0, c1, deliveryDiscount, "Khreshchatyk 1", "John Doe"));

    std::cout << "\n--- Polymorphism Demo ---\n";
    for (const auto& o : orders) {
        std::cout << *o << "\n"; 
        
        std::cout << "Receipt Type: ";
        o->printReceiptType(); 
        
        std::cout << "Tax Rate: " << o->getTaxRate() << "\n\n";
    }

    std::cout << "\n--- Polymorphism Demo---\n";
    processOrder(*orders[2]); 

    std::cout << "\n--- Interface IPayable Demo---\n";
    std::vector<IPayable*> payables;
    
    payables.push_back(orders[0].get()); 
    
    auto salaryPayment = std::make_unique<StaffSalary>("Manager Mike", 15000.0);
    payables.push_back(salaryPayment.get());

    for (IPayable* p : payables) {
        p->processPayment();
    }

    std::cout << "\n--- Destroying objects ---\n";
    std::cout << "Automatically deleted\n";

    return 0;
}
