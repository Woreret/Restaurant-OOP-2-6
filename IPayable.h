#pragma once

class IPayable {
public:
    virtual ~IPayable() = default;
    virtual void processPayment() = 0;
};
