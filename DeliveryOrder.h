#pragma once
#include "Order.h"
#include <iostream>
#include <string>

class DeliveryOrder : public Order {
private:
    std::string deliveryAddress;
    std::string courierName; 

public:
    DeliveryOrder(int id, std::string s, double total, const Customer& cust, Discount disc, std::string address, std::string courier)
        : Order(id, std::move(s), total, cust, disc), deliveryAddress(std::move(address)), courierName(std::move(courier)) {
        std::cout << "DeliveryOrder created for " << deliveryAddress << "\n";
    }

    ~DeliveryOrder() override {
        std::cout << "DeliveryOrder destroyed\n";
    }

    void printOrder() const override {
        Order::printOrder();
        std::cout << "Delivery Address: " << deliveryAddress 
                  << " | Courier: " << (courierName.empty() ? "None" : courierName) << "\n";
    }
};

