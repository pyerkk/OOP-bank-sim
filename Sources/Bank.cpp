#include "Bank.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include <fstream>
#include <iostream>
#include <sstream>

Bank::~Bank() {
    for (Account* acc : accounts) {
        delete acc;
    }
    accounts.clear();
}

Account* Bank::findAccount(const std::string& accNum) const {
    for (Account* acc : accounts) {
        if (acc->getAccountNumber() == accNum) {
            return acc;
        }
    }
    return nullptr;
}

void Bank::addAccount(Account* account) {
    if (account != nullptr) {
        accounts.push_back(account);
    }
}

void Bank::depositTo(const std::string& accNum, double amount) {
    Account* acc = findAccount(accNum);
    if (acc) {
        acc->deposit(amount);
    } else {
        std::cout << "Счет не найден.\n";
    }
}

void Bank::withdrawFrom(const std::string& accNum, double amount) {
    Account* acc = findAccount(accNum);
    if (acc) {
        acc->withdraw(amount);
    } else {
        std::cout << "Счет не найден.\n";
    }
}

void Bank::transfer(const std::string& fromAccNum, const std::string& toAccNum, double amount) {
    Account* fromAcc = findAccount(fromAccNum);
    Account* toAcc = findAccount(toAccNum);

    if (!fromAcc || !toAcc) {
        std::cout << "Ошибка: один или оба счета не найдены.\n";
        return;
    }

    if (fromAcc->withdraw(amount)) {
        toAcc->deposit(amount);
        std::cout << "Перевод успешно выполнен.\n";
    }
}

void Bank::applyInterestToAll() {
    for (Account* acc : accounts) {
        SavingsAccount* sa = dynamic_cast<SavingsAccount*>(acc);
        if (sa) {
            sa->applyInterest();
        }
    }
}

void Bank::showAllAccounts() const {
    std::cout << "\n=== СПИСОК ВСЕХ СЧЕТОВ БАНКА ===\n";
    for (const Account* acc : accounts) {
        acc->displayInfo();
    }
    std::cout << "================================\n";
}


void Bank::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "Ошибка записи: не удалось создать файл " << filename << "\n";
        return;
    }

    for (const Account* acc : accounts) {
        const SavingsAccount* sa = dynamic_cast<const SavingsAccount*>(acc);
        if (sa) {
            outFile << "S;" << sa->getAccountNumber() << ";" 
                    << sa->getBalance() << ";" 
                    << sa->getInterestRate() << ";" 
                    << sa->getOwnerName() << "\n";
        } else {
            const CheckingAccount* ca = dynamic_cast<const CheckingAccount*>(acc);
            if (ca) {
                outFile << "C;" << ca->getAccountNumber() << ";" 
                        << ca->getBalance() << ";" 
                        << ca->getTransactionFee() << ";" 
                        << ca->getOwnerName() << "\n";
            }
        }
    }
}

void Bank::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        return;
    }
    for (Account* acc : accounts) {
        delete acc;
    }
    accounts.clear();
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string type, accNum, balanceStr, paramStr, name;
        std::getline(ss, type, ';');
        std::getline(ss, accNum, ';');
        std::getline(ss, balanceStr, ';');
        std::getline(ss, paramStr, ';');
        std::getline(ss, name, ';');
        double balance = std::stod(balanceStr);
        double param = std::stod(paramStr);
        if (type == "S") {
            accounts.push_back(new SavingsAccount(accNum, name, balance, param));
        } else if (type == "C") {
            accounts.push_back(new CheckingAccount(accNum, name, balance, param));
        }
    }
}
