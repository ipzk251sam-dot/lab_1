#ifndef ACCOUNT_H
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
