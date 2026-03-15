#pragma once
#include <iostream>
#include <string>
#include <utility>
#include "Customer.h"

class Order {
private:
    int orderId;
    std::string status;
    double totalAmount;
    static int totalOrdersCreated;

    Customer orderCustomer; 

public:
    const Customer& getCustomer() const { return orderCustomer; }
    int getOrderId() const { return orderId; }
    std::string getStatus() const { return status; }
    double getTotalAmount() const { return totalAmount; }

public:
    Order(int id, std::string s, double total, const Customer& cust) 
        : orderId(id), status(s), totalAmount(total), orderCustomer(cust) {
        totalOrdersCreated++;
        std::cout << "Order created: " << orderId << "\n";
    }

    Order(int id) : Order(id, "Processing", 0.0, Customer()) {
        std::cout << "Order delegated: " << orderId << "\n";
    }

    Order() : Order(0, "New", 0.0, Customer()) {
        std::cout << "Order default created\n";
    }

    ~Order() {
        totalOrdersCreated--;
        std::cout << "Order destroyed: " << orderId << "\n";
    }

    Order(const Order& other) 
        : orderId(other.orderId), status(other.status), totalAmount(other.totalAmount), orderCustomer(other.orderCustomer) {
        totalOrdersCreated++;
        std::cout << "Order copied: " << orderId << "\n";
    }

    Order(Order&& other) noexcept 
        : orderId(other.orderId), status(std::move(other.status)), totalAmount(other.totalAmount), orderCustomer(std::move(other.orderCustomer)) {
        totalOrdersCreated++;
        other.orderId = 0;
        other.totalAmount = 0.0;
        std::cout << "Order moved: " << orderId << "\n";
    }

    Order& operator=(const Order& other) {
        if (this != &other) {
            orderId = other.orderId;
            status = other.status;
            totalAmount = other.totalAmount;
            orderCustomer = other.orderCustomer;
            std::cout << "Order copy assigned\n";
        }
        return *this;
    }

    Order& operator=(Order&& other) noexcept {
        if (this != &other) {
            orderId = other.orderId;
            status = std::move(other.status);
            totalAmount = other.totalAmount;
            orderCustomer = std::move(other.orderCustomer);
            other.orderId = 0;
            other.totalAmount = 0.0;
            std::cout << "Order move assigned\n";
        }
        return *this;
    }

    static int getTotalOrdersCreated() {
        return totalOrdersCreated;
    }
    
    Order& setStatus(const std::string& status) {
        this->status = status; 
        return *this; 
    }

    Order operator+(double tip) const {
        return Order(this->orderId, this->status, this->totalAmount + tip, this->orderCustomer);
    }

    void printOrder() const {
        std::cout << "Order ID: " << orderId << " | Status: " << status << " | Total: " << totalAmount << " UAH\n";
        std::cout << "Ordered by: ";
        orderCustomer.displayInfo();
    }

    friend std::ostream& operator<<(std::ostream& os, const Order& o) {
        os << "Order ID: " << o.orderId << " | Status: " << o.status << " | Total: " << o.totalAmount << " UAH";
        return os;
    }
};
