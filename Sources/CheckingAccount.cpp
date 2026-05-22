#include "CheckingAccount.h"

CheckingAccount::CheckingAccount(const std::string& accNum, const std::string& name, double initialBalance, double fee)
    : Account(accNum, name, initialBalance), transactionFee(fee >= 0 ? fee : 0) {}
bool CheckingAccount::withdraw(double amount) {
    double totalAmount = amount + transactionFee;
    if (amount > 0 && balance >= totalAmount) {
        balance -= totalAmount;
        std::cout << "Снято: " << amount << " руб. Комиссия: " << transactionFee << " руб.\n";
        return true;
    }
    std::cout << "Ошибка: недостаточно средств для снятия с учетом комиссии.\n";
    return false;
}
void CheckingAccount::displayInfo() const {
    Account::displayInfo();
    std::cout << " [Тип: Текущий, Комиссия: " << transactionFee << " руб.]\n";
}
