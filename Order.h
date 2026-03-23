#pragma once
#include <iostream>
#include <string>
#include <utility>
#include "Customer.h"
#include "Transaction.h"
#include "Discount.h"
#include "IPayable.h"

class Order : public Transaction, public IPayable {
private:
    int orderId;
    std::string status;
    double totalAmount;
    double tipAmount;
    static int totalOrdersCreated;

    Customer orderCustomer; 
    Discount orderDiscount; 

public:
    const Customer& getCustomer() const { return orderCustomer; }
    int getOrderId() const { return orderId; }
    std::string getStatus() const { return status; }
    double getTotalAmount() const { return totalAmount; }

public:
    Order(int id, std::string s, double total, Customer cust, Discount disc = Discount()) 
        : Transaction("TRX-" + std::to_string(id)), orderId(id), status(std::move(s)), totalAmount(total), tipAmount(0.0), orderCustomer(std::move(cust)), orderDiscount(disc) {
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

    virtual void processPayment() override {
        std::cout << "Processing payment for Order " << orderId << ", amount: " << calculateFinalPrice() << " UAH\n";
    }
};
