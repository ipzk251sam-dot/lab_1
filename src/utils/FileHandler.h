#ifndef FILEHANDLER_H
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
