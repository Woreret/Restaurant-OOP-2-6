#pragma once
#include <iostream>
#include <string>
#include <utility>
#include "IPayable.h"

class StaffSalary : public IPayable {
private:
    std::string employeeName;
    double salaryAmount;

public:
    StaffSalary(std::string name, double amount) 
        : employeeName(std::move(name)), salaryAmount(amount) {}
    
    virtual void processPayment() override {
        std::cout << "Processing salary payment of " << salaryAmount << " UAH for employee: " << employeeName << "\n";
    }
};
