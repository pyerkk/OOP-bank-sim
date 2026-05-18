#include "Account.h"

Account::Account(const std::string& accNum, const std::string& name, double initialBalance)
    : accountNumber(accNum), ownerName(name), balance(initialBalance >= 0 ? initialBalance : 0) {}

std::string Account::getAccountNumber() const { return accountNumber; }
std::string Account::getOwnerName() const { return ownerName; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Успешно внесено: " << amount << " руб.\n";
    } else {
        std::cout << "Ошибка: сумма пополнения должна быть больше 0.\n";
    }
}

void Account::displayInfo() const {
    std::cout << "Счет #: " << accountNumber 
              << " | Владелец: " << ownerName 
              << " | Баланс: " << balance << " руб.";
}
