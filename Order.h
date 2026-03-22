#pragma once
#include <iostream>
#include <string>
#include <utility>
#include "Customer.h"
#include "Transaction.h"
#include "Discount.h"

class Order : public Transaction {
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
        std::cout << "Order created: " << orderId << "\n";
    }

    Order(int id) : Order(id, "Processing", 0.0, Customer()) {
        std::cout << "Order delegated: " << orderId << "\n";
    }

    Order() : Order(0) {
        std::cout << "Order default created\n";
    }

    virtual ~Order() {
        totalOrdersCreated--;
        if (orderId != 0) {
            std::cout << "Order destroyed: " << orderId << "\n";
        }
    }

    Order(const Order& other) 
        : Transaction(other), orderId(other.orderId), status(other.status), totalAmount(other.totalAmount), tipAmount(other.tipAmount), orderCustomer(other.orderCustomer), orderDiscount(other.orderDiscount) {
        totalOrdersCreated++;
        std::cout << "Order copied: " << orderId << "\n";
    }

    Order(Order&& other) noexcept 
        : Transaction(std::move(other)), orderId(other.orderId), status(std::move(other.status)), totalAmount(other.totalAmount), tipAmount(other.tipAmount), orderCustomer(std::move(other.orderCustomer)), orderDiscount(std::move(other.orderDiscount)) {
        totalOrdersCreated++; 
        other.orderId = 0;
        other.totalAmount = 0.0;
        other.tipAmount = 0.0;
        std::cout << "Order moved: " << orderId << "\n";
    }

    Order& operator=(const Order& other) {
        if (this != &other) {
            Transaction::operator=(other);
            orderId = other.orderId;
            status = other.status;
            totalAmount = other.totalAmount;
            tipAmount = other.tipAmount;
            orderCustomer = other.orderCustomer;
            orderDiscount = other.orderDiscount;
            std::cout << "Order copy assigned\n";
        }
        return *this;
    }

    Order& operator=(Order&& other) noexcept {
        if (this != &other) {
            Transaction::operator=(std::move(other));
            orderId = other.orderId;
            status = std::move(other.status);
            totalAmount = other.totalAmount;
            tipAmount = other.tipAmount;
            orderCustomer = std::move(other.orderCustomer);
            orderDiscount = std::move(other.orderDiscount);
            
            other.orderId = 0; 
            other.totalAmount = 0.0;
            other.tipAmount = 0.0;
            std::cout << "Order move assigned\n";
        }
        return *this;
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

    virtual void printOrder() const {
        double finalAmount = orderDiscount.applyDiscount(totalAmount) + tipAmount;
        std::cout << "TX: " << getTransactionId() << " | Order ID: " << orderId << " | Status: " << status << " | Final Total: " << finalAmount << " UAH";
        if (tipAmount > 0) {
            std::cout << " (" << tipAmount << " UAH tip included)";
        }
        if (orderDiscount.getPercentage() > 0) {
            std::cout << " (Includes " << orderDiscount.getPercentage() << "% discount)";
        }
        std::cout << "\nOrdered by: ";
        orderCustomer.displayInfo();
    }

    friend std::ostream& operator<<(std::ostream& os, const Order& o) {
        double finalAmount = o.orderDiscount.applyDiscount(o.totalAmount) + o.tipAmount;
        os << "TX: " << o.getTransactionId() << " | Order ID: " << o.orderId << " | Status: " << o.status << " | Final Total: " << finalAmount << " UAH";
        if (o.tipAmount > 0) {
            os << " (" << o.tipAmount << " UAH tip included)";
        }
        if (o.orderDiscount.getPercentage() > 0) {
            os << " (Includes " << o.orderDiscount.getPercentage() << "% discount)";
        }
        return os;
    }
};
