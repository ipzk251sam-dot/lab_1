import os

# Структура папок
dirs = [
    "src/models",
    "src/services",
    "src/utils"
]

for d in dirs:
    os.makedirs(d, exist_ok=True)

# --- 1. MODEL: Account (Дані) ---

account_h = """#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>

class Account {
private:
    int id;
    std::string name;
    double balance;

public:
    Account(int id, std::string name, double balance);
    
    // Геттери (Інкапсуляція: ми лише читаємо дані)
    int getId() const;
    std::string getName() const;
    double getBalance() const;

    // Методи бізнес-логіки
    void deposit(double amount);
    bool withdraw(double amount);
};

#endif
"""

account_cpp = """#include "Account.h"

Account::Account(int id, std::string name, double balance) {
    this->id = id;
    this->name = name;
    this->balance = balance;
}

int Account::getId() const { return id; }
std::string Account::getName() const { return name; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}
"""

# --- 2. UTILS: FileHandler (Робота з файлами - SRP) ---

filehandler_h = """#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include "../models/Account.h"

class FileHandler {
private:
    std::string filename;

public:
    FileHandler(std::string filename);
    void saveAccounts(const std::vector<Account>& accounts);
    std::vector<Account> loadAccounts();
};

#endif
"""

filehandler_cpp = """#include "FileHandler.h"
#include <fstream>
#include <sstream>

FileHandler::FileHandler(std::string filename) : filename(filename) {}

void FileHandler::saveAccounts(const std::vector<Account>& accounts) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& acc : accounts) {
            file << acc.getId() << "|" << acc.getName() << "|" << acc.getBalance() << "\\n";
        }
        file.close();
    }
}

std::vector<Account> FileHandler::loadAccounts() {
    std::vector<Account> accounts;
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;

            while (std::getline(ss, segment, '|')) {
                parts.push_back(segment);
            }

            if (parts.size() == 3) {
                int id = std::stoi(parts[0]);
                std::string name = parts[1];
                double balance = std::stod(parts[2]);
                accounts.emplace_back(id, name, balance);
            }
        }
        file.close();
    }
    return accounts;
}
"""

# --- 3. SERVICE: BankService (Бізнес-логіка) ---

bankservice_h = """#ifndef BANKSERVICE_H
#define BANKSERVICE_H

#include <vector>
#include "../models/Account.h"
#include "../utils/FileHandler.h"

class BankService {
private:
    std::vector<Account> accounts;
    FileHandler fileHandler;

public:
    BankService(std::string dbFilename);
    
    void createAccount(std::string name, double initialDeposit);
    Account* getAccount(int id);
    void showAllAccounts();
    void saveData();
};

#endif
"""

bankservice_cpp = """#include "BankService.h"
#include <iostream>
#include <iomanip>

BankService::BankService(std::string dbFilename) : fileHandler(dbFilename) {
    accounts = fileHandler.loadAccounts();
}

void BankService::createAccount(std::string name, double initialDeposit) {
    int newId = accounts.empty() ? 1 : accounts.back().getId() + 1;
    Account newAcc(newId, name, initialDeposit);
    accounts.push_back(newAcc);
    std::cout << "Account created successfully! ID: " << newId << "\\n";
    saveData();
}

Account* BankService::getAccount(int id) {
    for (auto& acc : accounts) {
        if (acc.getId() == id) {
            return &acc;
        }
    }
    return nullptr;
}

void BankService::showAllAccounts() {
    std::cout << "\\n--- All Accounts ---\\n";
    for (const auto& acc : accounts) {
        std::cout << "ID: " << acc.getId() 
                  << " | Name: " << acc.getName() 
                  << " | Balance: $" << std::fixed << std::setprecision(2) << acc.getBalance() << "\\n";
    }
}

void BankService::saveData() {
    fileHandler.saveAccounts(accounts);
}
"""

# --- 4. MAIN (Точка входу) ---

main_cpp = """#include <iostream>
#include "services/BankService.h"

void showMenu() {
    std::cout << "\\n=== BANKING SYSTEM ===\\n";
    std::cout << "1. Create Account\\n";
    std::cout << "2. Deposit\\n";
    std::cout << "3. Withdraw\\n";
    std::cout << "4. Show All Accounts\\n";
    std::cout << "5. Exit\\n";
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
                    std::cout << "Deposited successfully.\\n";
                } else {
                    if (acc->withdraw(amount))
                        std::cout << "Withdrawn successfully.\\n";
                    else
                        std::cout << "Insufficient funds!\\n";
                }
                bank.saveData(); // Auto-save after transaction
            } else {
                std::cout << "Account not found!\\n";
            }
        }
        else if (choice == 4) {
            bank.showAllAccounts();
        }
        else if (choice == 5) {
            std::cout << "Goodbye!\\n";
            break;
        }
        else {
            std::cout << "Invalid option!\\n";
        }
    }
    return 0;
}
"""

# Запис файлів
files = {
    "src/models/Account.h": account_h,
    "src/models/Account.cpp": account_cpp,
    "src/utils/FileHandler.h": filehandler_h,
    "src/utils/FileHandler.cpp": filehandler_cpp,
    "src/services/BankService.h": bankservice_h,
    "src/services/BankService.cpp": bankservice_cpp,
    "src/main.cpp": main_cpp
}

for path, content in files.items():
    with open(path, "w", encoding="utf-8") as f:
        f.write(content)

print("Проект успішно створено! Структура:")
print("src/")
print("  ├── main.cpp")
print("  ├── models/")
print("  │   ├── Account.h")
print("  │   └── Account.cpp")
print("  ├── services/")
print("  │   ├── BankService.h")
print("  │   └── BankService.cpp")
print("  └── utils/")
print("      ├── FileHandler.h")
print("      └── FileHandler.cpp")
