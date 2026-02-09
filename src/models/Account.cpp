#include "Account.h"

Account::Account(int id, std::string name, long double balance) {
    this->id = id;
    this->name = name;
    this->balance = balance;
}

int Account::getId() const { return id; }
std::string Account::getName() const { return name; }
long double Account::getBalance() const { return balance; }

void Account::deposit(long double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool Account::withdraw(long double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}
