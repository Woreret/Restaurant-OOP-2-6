#pragma once
#include <iostream>
#include <string>
#include <utility>

class Customer {
private:
    std::string fullName;
    std::string phoneNumber;
    int loyaltyPoints;

public:
    Customer(std::string name, std::string phone, int points)
        : fullName(std::move(name)), phoneNumber(std::move(phone)), loyaltyPoints(points) {
        std::cout << "Customer created: " << fullName << "\n";
    }

    Customer(std::string name) : Customer(std::move(name), "Unknown", 10) {
        std::cout << "Customer delegated: " << fullName << "\n";
    }

    Customer() : Customer("Guest", "None", 0) {
        std::cout << "Customer default created\n";
    }

    ~Customer() {
        std::cout << "Customer destroyed: " << fullName << "\n";
    }

    Customer(const Customer& other) = default;
    Customer(Customer&& other) = default;
    Customer& operator=(const Customer& other) = default;
    Customer& operator=(Customer&& other) = default;

    void addLoyaltyPoints(int points) {
        this->loyaltyPoints += points;
    }

    void displayInfo() const {
        std::cout << "Customer: " << fullName << " | Phone: " << phoneNumber << " | Points: " << loyaltyPoints << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Customer& c) {
        os << "Customer: " << c.fullName << " | Phone: " << c.phoneNumber << " | Points: " << c.loyaltyPoints;
        return os;
    }
};
