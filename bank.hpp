#ifndef BANK_HPP
#define BANK_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include "login_buyer.hpp"

using namespace std;

class Bank : public Login_Buyer{
protected:
    double saldo = 0;
    double deposito = 0;
    double withdrawal = 0;
    vector<string> transaction_history;

public:
    // === Constructors ===
    Bank() = default;

    // === Getters ===
    double GetSaldo() const { return saldo; }
    vector<string> GetTransactionHistory() const { return transaction_history; }

    string serialize() const {
        stringstream ss;
        ss << saldo;
        return ss.str();
    }

    // === Deserialization (for loading from file) ===
    void deserialize(const string& serialized_data) {
    stringstream ss(serialized_data);
    string saldoStr, depositoStr, withdrawalStr;

    getline(ss, saldoStr, ',');
    getline(ss, depositoStr, ',');
    getline(ss, withdrawalStr, ',');

    saldo = saldoStr.empty() ? 0 : stod(saldoStr);
    deposito = depositoStr.empty() ? 0 : stod(depositoStr);
    withdrawal = withdrawalStr.empty() ? 0 : stod(withdrawalStr);
}

};

#endif
