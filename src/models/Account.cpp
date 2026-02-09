#include "Account.h"

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
