#pragma once
#include <iostream>
#include <string>

class Customer {
private:
    std::string fullName;
    std::string phoneNumber;
    int loyaltyPoints;

public:
    Customer(std::string name, std::string phone, int points)
        : fullName(name), phoneNumber(phone), loyaltyPoints(points) {
        std::cout << "[Customer] Main constructor called for: " << fullName << std::endl;
    }

    Customer(std::string name) : Customer(name, "Unknown", 10) {
        std::cout << "[Customer] Delegated constructor called for: " << fullName << std::endl;
    }

    Customer() : Customer("Guest", "None", 0) {
        std::cout << "[Customer] Default constructor called for: " << fullName << std::endl;
    }

    ~Customer() {
        std::cout << "[Customer] Destructor called for: " << fullName << std::endl;
    }

    void displayInfo() const {
        std::cout << "Customer: " << fullName << " | Phone: " << phoneNumber << " | Points: " << loyaltyPoints << std::endl;
    }
};
