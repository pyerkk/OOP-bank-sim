#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(const std::string& accNum, const std::string& name, double initialBalance, double rate)
    : Account(accNum, name, initialBalance), interestRate(rate > 0 ? rate : 0) {}

bool SavingsAccount::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        std::cout << "Снято со сберегательного счета: " << amount << " руб.\n";
        return true;
    }
    std::cout << "Ошибка: недостаточно средств или некорректная сумма.\n";
    return false;
}

void SavingsAccount::applyInterest() {
    double interest = balance * interestRate;
    balance += interest;
    std::cout << "Начислены проценты: " << interest << " руб. (Ставка: " << interestRate * 100 << "%)\n";
}

void SavingsAccount::displayInfo() const {
    Account::displayInfo();
    std::cout << " [Тип: Сберегательный, Ставка: " << interestRate * 100 << "%]\n";
}
