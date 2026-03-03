#pragma once
#include <iostream>
#include <string>

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
