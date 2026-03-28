#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <sstream>
#include "Customer.h"
#include "Discount.h"

class Order {
protected:
    std::string transactionId;
    int orderId;
    std::string status;
    double totalAmount;
    double tipAmount;
    static int totalOrdersCreated;

    Customer orderCustomer; 
    Discount orderDiscount; 

public:
    const Customer& getCustomer() const { return orderCustomer; }
    std::string getTransactionId() const { return transactionId; }
    int getOrderId() const { return orderId; }
    std::string getStatus() const { return status; }
    double getTotalAmount() const { return totalAmount; }

public:
    Order(int id, std::string s, double total, Customer cust, Discount disc = Discount()) 
        : transactionId("TRX-" + std::to_string(id)), orderId(id), status(std::move(s)), totalAmount(total), tipAmount(0.0), orderCustomer(std::move(cust)), orderDiscount(disc) {
        totalOrdersCreated++;
    }

    Order(int id) : Order(id, "Processing", 0.0, Customer()) {}

    Order() : Order(0) {}

    virtual ~Order() {
        totalOrdersCreated--;
    }



    static int getTotalOrdersCreated() {
        return totalOrdersCreated;
    }

    void setDiscount(Discount d) {
        orderDiscount = d;
    }
    
    Order& setStatus(const std::string& newStatus) {
        this->status = newStatus; 
        return *this; 
    }

    Order& operator+=(double tip) {
        this->tipAmount += tip;
        return *this;
    }

    std::string serialize() const {
        return std::to_string(orderId) + ";" + status + ";" + 
               std::to_string(totalAmount) + ";" + std::to_string(tipAmount) + ";" + 
               orderCustomer.serialize();
    }

    static Order deserialize(const std::string& line) {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> parts;
        while (std::getline(ss, token, ';')) {
            parts.push_back(token);
        }
        
        if (parts.size() < 7) return Order(); 
        
        int id = std::stoi(parts[0]);
        std::string st = parts[1];
        double total = std::stod(parts[2]);
        double tip = std::stod(parts[3]);
        
        std::string custLine = parts[4] + ";" + parts[5] + ";" + parts[6];
        Customer cust = Customer::deserialize(custLine);
        
        Order o(id, st, total, cust);
        o += tip;
        return o;
    }

    virtual void print(std::ostream& os) const {
        os << "TX: " << getTransactionId() << " | Order ID: " << orderId << " | Status: " << status << " | Final Total: " << calculateFinalPrice() << " UAH";
        if (tipAmount > 0) {
            os << " (" << tipAmount << " UAH tip included)";
        }
        if (orderDiscount.getPercentage() > 0) {
            os << " (Includes " << orderDiscount.getPercentage() << "% discount)";
        }
        os << "\nOrdered by: ";
        orderCustomer.displayInfo();
    }

    void printReceiptType() const {
        std::cout << "Regular Receipt\n";
    }

    virtual double calculateFinalPrice() const {
        return orderDiscount.applyDiscount(totalAmount) + tipAmount;
    }

    virtual double getTaxRate() const final {
        return 0.20;
    }

    void processPayment() {
        std::cout << "Processing payment for Order " << orderId << ", amount: " << calculateFinalPrice() << " UAH\n";
    }
};
