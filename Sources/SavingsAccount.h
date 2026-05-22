#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate;
public:
    SavingsAccount(const std::string& accNum, const std::string& name, double initialBalance, double rate);
    bool withdraw(double amount) override; 
    void displayInfo() const override;
    void applyInterest();
    double getInterestRate() const { return interestRate; }
};

#endif
