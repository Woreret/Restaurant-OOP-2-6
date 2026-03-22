#pragma once
#include <iostream>
#include <string>

class Transaction {
private:
    std::string transactionId;

public:
    Transaction(std::string tId) : transactionId(std::move(tId)) {
        std::cout << "Transaction created: " << transactionId << "\n";
    }

    std::string getTransactionId() const {
        return transactionId;
    }

    virtual ~Transaction() {
        std::cout << "Transaction destroyed: " << transactionId << "\n";
    }

    Transaction(const Transaction& other) = default;
    Transaction(Transaction&& other) noexcept = default;
    Transaction& operator=(const Transaction& other) = default;
    Transaction& operator=(Transaction&& other) noexcept = default;

    virtual void printTransaction() const {
        std::cout << "Transaction ID: " << transactionId << "\n";
    }
};
