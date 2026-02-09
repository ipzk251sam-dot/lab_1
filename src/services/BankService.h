#ifndef BANKSERVICE_H
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
