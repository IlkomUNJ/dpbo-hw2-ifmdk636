#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
#include "bank.hpp"
#include "login_buyer.hpp"
#include "item.hpp"
// constructor from bank and login_buyer
// Bank::Bank(double saldo, string username, string password, double deposito, double withdrawal, vector<string> transaction_history);

class Buyer :  public Bank, public Item{
protected:
    string orders;
public:
    string id;
    string name;
    Buyer(string id, string name, string orders) {
        this->id = id;
        this->name = name;
        this->orders = orders;
    };

    void createBankAccount();
    void create_user();
    bool login_user();
    void deposit();
    void transactionHistory();
    void withDrawal();
    void cekSaldo();
    void buy_products();
    void menu_bank_user();
        // Getter & Setter
    string getOrders() const { return orders; }
    void setOrders(const string& o) { orders = o; }    
};

