#pragma once
#include "Order.h"
#include <iostream>
#include <string>
#include <utility>

class DiscountedOrder : public Order {
private:
    double discountPercentage;

public:
    DiscountedOrder(int id, std::string s, double total, const Customer& cust, double discount)
        : Order(id, s, total, cust), discountPercentage(discount) {
        std::cout << "DiscountedOrder created\n";
    }

    ~DiscountedOrder() {
        std::cout << "DiscountedOrder destroyed\n";
    }

    DiscountedOrder(const DiscountedOrder& other) 
        : Order(other), discountPercentage(other.discountPercentage) {
        std::cout << "DiscountedOrder copied\n";
    }

    DiscountedOrder(DiscountedOrder&& other) noexcept 
        : Order(std::move(other)), discountPercentage(other.discountPercentage) {
        std::cout << "DiscountedOrder moved\n";
    }
    
    DiscountedOrder& operator=(const DiscountedOrder& other) {
        if (this != &other) {
            Order::operator=(other);
            discountPercentage = other.discountPercentage;
            std::cout << "DiscountedOrder copy assigned\n";
        }
        return *this;
    }

    DiscountedOrder& operator=(DiscountedOrder&& other) noexcept {
        if (this != &other) {
            Order::operator=(std::move(other));
            discountPercentage = other.discountPercentage;
            std::cout << "DiscountedOrder move assigned\n";
        }
        return *this;
    }

    void printOrder() const {
        double finalAmount = getTotalAmount() - (getTotalAmount() * (discountPercentage / 100.0));
        std::cout << "Order ID: " << getOrderId() << " | Status: " << getStatus() << " | Total with " 
                  << discountPercentage << "% discount: " << finalAmount << " UAH\n";
        std::cout << "Ordered by: ";
        getCustomer().displayInfo();
    }
};
