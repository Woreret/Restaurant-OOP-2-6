#pragma once
#include <iostream>
#include <string>

class Transaction {
private:
    std::string transactionId;

public:
    Transaction(std::string tId) : transactionId(std::move(tId)) {}

    std::string getTransactionId() const {
        return transactionId;
    }

    virtual ~Transaction() = default;

    virtual void printTransaction() const {
        std::cout << "Transaction ID: " << transactionId << "\n";
    }
};
