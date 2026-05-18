#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>

class Account {
private:
    std::string accountNumber;
    std::string ownerName;

protected:
    double balance;

public:
    Account(const std::string& accNum, const std::string& name, double initialBalance);
    virtual ~Account() = default;
    std::string getAccountNumber() const;
    std::string getOwnerName() const;
    double getBalance() const;
    virtual void deposit(double amount);
    virtual bool withdraw(double amount) = 0;
    virtual void displayInfo() const;
};

#endif
