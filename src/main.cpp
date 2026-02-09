#include <iostream>
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
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            double amount;
            std::cout << "Enter name: ";
            std::cin >> name;
            std::cout << "Initial deposit: ";
            std::cin >> amount;
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
                bank.saveData(); // Auto-save after transaction
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
