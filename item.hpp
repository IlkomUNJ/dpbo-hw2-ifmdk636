#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Item {
public:
    string itemID;
    string name;
    string description;
    double price;
    int stock;
    string seller;

    // === Constructor Default ===
    Item() : price(0.0), stock(0) {}

    // === Constructor Parameter ===
    Item(string id, string n, string d, double p, int s, string sel)
        : itemID(id), name(n), description(d), price(p), stock(s), seller(sel) {}

    // === SERIALIZE ===
    // Ubah data Item ke format string untuk disimpan ke file
    string serialize() const {
        ostringstream ss;

        // Hindari koma dalam teks (diganti dengan titik koma)
        string safeName = name;
        string safeDesc = description;
        for (char &c : safeName) if (c == ',') c = ';';
        for (char &c : safeDesc) if (c == ',') c = ';';

        ss << itemID << ","
           << safeName << ","
           << safeDesc << ","
           << price << ","
           << stock << ","
           << seller;
        return ss.str();
    }

    // === DESERIALIZE ===
    void deserialize(const string& data) {
        istringstream ss(data);
        string token;

        getline(ss, itemID, ',');
        getline(ss, name, ',');
        getline(ss, description, ',');

        getline(ss, token, ',');
        price = stod(token);

        getline(ss, token, ',');
        stock = stoi(token);

        getline(ss, seller, ',');
    };
};


#endif // ITEM_HPP
