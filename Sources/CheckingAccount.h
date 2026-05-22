#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : public Account {
private:
    double transactionFee;

public:
    CheckingAccount(const std::string& accNum, const std::string& name, double initialBalance, double fee);

    bool withdraw(double amount) override;
    void displayInfo() const override;

    double getTransactionFee() const { return transactionFee; }
};

#endif
