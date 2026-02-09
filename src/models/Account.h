#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>

class Account {
private:
    int id;
    std::string name;
    long double balance; // «м≥нено тип дл€ точност≥

public:
    Account(int id, std::string name, long double balance);
    
    int getId() const;
    std::string getName() const;
    long double getBalance() const;

    void deposit(long double amount);
    bool withdraw(long double amount);
};

#endif
