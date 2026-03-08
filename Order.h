#pragma once
#include <iostream>
#include <string>

class Order {
private:
    int orderId;
    std::string status;
    double totalAmount;
    static int totalOrdersCreated;


public:
    Order(int id, std::string s, double total) 
        : orderId(id), status(s), totalAmount(total) {
        totalOrdersCreated++;
        std::cout << "[Order] Main constructor called for ID: " << orderId << std::endl;
    }

    Order(int id) : Order(id, "Processing", 0.0) {
        std::cout << "[Order] Delegated constructor called for ID: " << orderId << std::endl;
    }

    Order() : Order(0, "New", 0.0) {
        std::cout << "[Order] Default constructor called for ID: " << orderId << std::endl;
    }

    ~Order() {
        totalOrdersCreated--;
        std::cout << "[Order] Destructor called for ID: " << orderId << std::endl;
    }

    Order(const Order& other) 
        : orderId(other.orderId), status(other.status), totalAmount(other.totalAmount) {
        totalOrdersCreated++;
        std::cout << "[Order] Copy constructor called for ID: " << orderId << std::endl;
    }

    Order(Order&& other) noexcept 
        : orderId(other.orderId), status(std::move(other.status)), totalAmount(other.totalAmount) {
        totalOrdersCreated++;
        other.orderId = 0;
        other.totalAmount = 0.0;
        std::cout << "[Order] Move constructor called for ID: " << orderId << std::endl;
    }

    static int getTotalOrdersCreated() {
        return totalOrdersCreated;
    }
    Order& setStatus(const std::string& status) {
        this->status = status; 
        return *this; 
    }

    Order operator+(double tip) const {
        return Order(this->orderId, this->status, this->totalAmount + tip);
    }

    void printOrder() const {
        std::cout << "Order ID: " << orderId << " | Status: " << status << " | Total: " << totalAmount << " UAH" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Order& o) {
        os << "Order ID: " << o.orderId << " | Status: " << o.status << " | Total: " << o.totalAmount << " UAH";
        return os;
    }
};
