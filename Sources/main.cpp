#include <iostream>
#include <limits>
#include <cstdlib>
#include "Bank.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void showMenu() {
    std::cout << "\n--- МЕНЮ БАНКОВСКОГО ТЕРМИНАЛА ---\n"
              << "1. Показать все счета\n"
              << "2. Создать сберегательный счет\n"
              << "3. Создать расчетный счет\n"
              << "4. Пополнить счет\n"
              << "5. Снять деньги\n"
              << "6. Перевести между счетами\n"
              << "7. Начислить проценты (всем сберегательным)\n"
              << "0. Сохранить и выйти\n"
              << "Выберите действие: ";
}

void waitForEnter() {
    std::cout << "\nНажмите Enter, чтобы продолжить...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int main() {
#ifdef _WIN32
    std::system("chcp 65001 > nul");
#endif
    Bank myBank;
    myBank.loadFromFile("accounts.txt");
    int choice = -1;
    while (choice != 0) {
        clearScreen();
        
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            waitForEnter();
            continue;
        }

        std::string num, name, targetNum;
        double balance, param, amount;

        switch (choice) {
            case 1:
                myBank.showAllAccounts();
                waitForEnter();
                break;
            case 2:
                std::cout << "Введите номер счета: "; std::cin >> num;
                std::cout << "Введите имя владельца: "; std::cin.ignore(); std::getline(std::cin, name);
                std::cout << "Начальный баланс: "; std::cin >> balance;
                std::cout << "Годовой процент (например, 0.05): "; std::cin >> param;
                myBank.addAccount(new SavingsAccount(num, name, balance, param));
                waitForEnter();
                break;
            case 3:
                std::cout << "Введите номер счета: "; std::cin >> num;
                std::cout << "Введите имя владельца: "; std::cin.ignore(); std::getline(std::cin, name);
                std::cout << "Начальный баланс: "; std::cin >> balance;
                std::cout << "Комиссия за снятие (руб): "; std::cin >> param;
                myBank.addAccount(new CheckingAccount(num, name, balance, param));
                waitForEnter();
                break;
            case 4:
                std::cout << "Введите номер счета: "; std::cin >> num;
                std::cout << "Сумма пополнения: "; std::cin >> amount;
                myBank.depositTo(num, amount);
                waitForEnter();
                break;
            case 5:
                std::cout << "Введите номер счета: "; std::cin >> num;
                std::cout << "Сумма снятия: "; std::cin >> amount;
                myBank.withdrawFrom(num, amount);
                waitForEnter();
                break;
            case 6:
                std::cout << "Откуда переводить (номер счета): "; std::cin >> num;
                std::cout << "Куда переводить (номер счета): "; std::cin >> targetNum;
                std::cout << "Сумма перевода: "; std::cin >> amount;
                myBank.transfer(num, targetNum, amount);
                waitForEnter();
                break;
            case 7:
                myBank.applyInterestToAll();
                waitForEnter();
                break;
            case 0:
                myBank.saveToFile("accounts.txt");
                clearScreen();
                std::cout << "==================================================\n";
                std::cout << "Данные успешно сохранены. Спасибо за работу!\n";
                std::cout << "==================================================\n";
                break;
            default:
                std::cout << "Неверный пункт меню.\n";
                waitForEnter();
        }
    }

    std::cout << "\nПрограмма завершена. Нажмите Enter для закрытия окна...";
    std::cin.get();

    return 0;
}
