#include "FileHandler.h"
#include <fstream>
#include <sstream>

FileHandler::FileHandler(std::string filename) : filename(filename) {}

void FileHandler::saveAccounts(const std::vector<Account>& accounts) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& acc : accounts) {
            file << acc.getId() << "|" << acc.getName() << "|" << acc.getBalance() << "\n";
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
