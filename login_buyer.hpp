#ifndef LOGIN_BUYER_HPP
#define LOGIN_BUYER_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Login_Buyer {
protected:
    string username;
    string password;

public:
    // Constructor default
    Login_Buyer() {}

    // Constructor dengan parameter
    Login_Buyer(string username, string password) {
        this->username = username;
        this->password = password;
    }

    // Getters
    string GetUsername() const { return username; }
    string GetPassword() const { return password; }

    // Setters
    void SetUsername(const string& uname) { username = uname; }
    void SetPassword(const string& pass) { password = pass; }

    // Serialize
    string serialize() const {
        stringstream ss;
        ss << username << "," << password;
        return ss.str();
    }

    // Deserialize
    void deserialize(const string& serialized_data) {
        stringstream ss(serialized_data);
        getline(ss, username, ',');
        getline(ss, password, ',');
    }
};

#endif
