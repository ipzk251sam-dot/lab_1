#include <iostream>
#include <limits> // Додано для numeric_limits
#include "services/BankService.h"

void showMenu() {
    std::cout << "\n=== BANKING SYSTEM ===\n";
    std::cout << "1. Create Account\n";
    std::cout << "2. Deposit\n";
    std::cout << "3. Withdraw\n";
    std::cout << "4. Show All Accounts\n";
    std::cout << "5. Exit\n";
    std::cout << "Choose option: ";
}

int main() {
    BankService bank("bank_data.txt");
    int choice;
    
    while (true) {
        showMenu();
        if (!(std::cin >> choice)) { // ВИПРАВЛЕННЯ: Перевірка вводу
            std::cout << "Invalid input! Please enter a number.\n";
            std::cin.clear(); // Скидання помилки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            continue;
        }

        if (choice == 1) {
            std::string name;
            double amount;
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Initial deposit: ";
            while (!(std::cin >> amount)) { // Валідація суми
                std::cout << "Invalid amount! Try again: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            bank.createAccount(name, amount);
        }
        else if (choice == 2 || choice == 3) {
            int id;
            double amount;
            std::cout << "Enter Account ID: ";
            std::cin >> id;
            
            Account* acc = bank.getAccount(id);
            if (acc) {
                std::cout << "Enter amount: ";
                std::cin >> amount;
                
                if (choice == 2) {
                    acc->deposit(amount);
                    std::cout << "Deposited successfully.\n";
                } else {
                    if (acc->withdraw(amount))
                        std::cout << "Withdrawn successfully.\n";
                    else
                        std::cout << "Insufficient funds!\n";
                }
                bank.saveData();
            } else {
                std::cout << "Account not found!\n";
            }
        }
        else if (choice == 4) {
            bank.showAllAccounts();
        }
        else if (choice == 5) {
            std::cout << "Goodbye!\n";
            break;
        }
        else {
            std::cout << "Invalid option!\n";
        }
    }
    return 0;
}
