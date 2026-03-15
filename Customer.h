#pragma once
#include <iostream>
#include <string>
#include <utility>

class Customer {
protected:
    std::string fullName;
    std::string phoneNumber;
    int loyaltyPoints;

public:
    Customer(std::string name, std::string phone, int points)
        : fullName(name), phoneNumber(phone), loyaltyPoints(points) {
        std::cout << "Customer created: " << fullName << "\n";
    }

    Customer(std::string name) : Customer(name, "Unknown", 10) {
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

    Customer& operator++() {
        this->loyaltyPoints += 10;
        return *this;
    }

    Customer operator++(int) {
        Customer temp = *this;
        this->loyaltyPoints += 10;
        return temp;
    }

    void displayInfo() const {
        std::cout << "Customer: " << fullName << " | Phone: " << phoneNumber << " | Points: " << loyaltyPoints << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Customer& c) {
        os << "Customer: " << c.fullName << " | Phone: " << c.phoneNumber << " | Points: " << c.loyaltyPoints;
        return os;
    }
};
