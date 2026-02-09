#include "BankService.h"
#include <iostream>
#include <iomanip>

BankService::BankService(std::string dbFilename) : fileHandler(dbFilename) {
    accounts = fileHandler.loadAccounts();
}

void BankService::createAccount(std::string name, double initialDeposit) {
    int newId = accounts.empty() ? 1 : accounts.back().getId() + 1;
    Account newAcc(newId, name, initialDeposit);
    accounts.push_back(newAcc);
    std::cout << "Account created successfully! ID: " << newId << "\n";
    saveData();
}

// WARNING: Returns raw pointer. Ensure vector is not resized while using this pointer.
Account* BankService::getAccount(int id) {
    for (auto& acc : accounts) {
        if (acc.getId() == id) {
            return &acc;
        }
    }
    return nullptr;
}

void BankService::showAllAccounts() {
    std::cout << "\n--- All Accounts ---\n";
    for (const auto& acc : accounts) {
        std::cout << "ID: " << acc.getId() 
                  << " | Name: " << acc.getName() 
                  << " | Balance: $" << std::fixed << std::setprecision(2) << acc.getBalance() << "\n";
    }
}

void BankService::saveData() {
    fileHandler.saveAccounts(accounts);
}
