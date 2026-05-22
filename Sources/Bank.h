#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include "Account.h"

class Bank {
private:
    std::vector<Account*> accounts;

    Account* findAccount(const std::string& accNum) const;

public:
    ~Bank();

    void addAccount(Account* account);
    void depositTo(const std::string& accNum, double amount);
    void withdrawFrom(const std::string& accNum, double amount);
    void transfer(const std::string& fromAccNum, const std::string& toAccNum, double amount);
    void applyInterestToAll();
    void showAllAccounts() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

#endif

