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
        : Order(id, std::move(s), total, cust, disc), deliveryAddress(std::move(address)), courierName(std::move(courier)) {}

    ~DeliveryOrder() override = default;

    void print(std::ostream& os) const override {
        Order::print(os);
        os << "Delivery Address: " << deliveryAddress 
           << " | Courier: " << (courierName.empty() ? "None" : courierName) << "\n";
    }

    void printReceiptType() const {
        std::cout << "Delivery Receipt\n";
    }

    virtual double calculateFinalPrice() const override {
        double basePrice = Order::calculateFinalPrice();
        double deliveryFee = 100.0; 
        return basePrice + deliveryFee;
    }
};

