// Isi seller merupakan turunan dari user.
// method seller menyesuaikan.
#include <iostream>
#include <string>
#include "item.hpp"
#include "login_seller.hpp"

using namespace std;

class Seller : public Item, public Login_Seller {
    protected:
    string name;
    string orders;
    string password;
    string username;

    public:
    Seller(string name, string orders, string password, string username) {
        this->name = name;
        this->orders = orders;
        this->password = password;
        this->username = username;
    }

    bool create_user();
    bool loginSeller();
    void menu_seller();
    void create_product();
    void edit_product();
    void delete_product();
    void display();
};