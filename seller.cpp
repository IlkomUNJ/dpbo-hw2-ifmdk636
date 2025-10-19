#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#include "seller.hpp"
#include "item.hpp"      // penting agar class Item dikenali

using namespace std;

// === Variabel global untuk menyimpan data login seller ===
vector<Login_Seller> login_seller;
vector<Item> item;


// === Registrasi Seller Baru ===
bool Seller::create_user() {
    cout << "\n=== Registrasi Seller Baru ===\n";
    string username;
    string password;

    const string FILENAME = "seller.txt";
    Login_Seller data_user(username, password);

    // Load existing data
    ifstream infile(FILENAME);
    string line;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            data_user.deserialize(line);
            login_seller.push_back(data_user);
        }
        infile.close();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Username: ";
    getline(cin, username);
    cout << "Masukkan Password: ";
    getline(cin, password);

    login_seller.push_back(Login_Seller(username, password));

    // Simpan ke file
    ofstream outfile(FILENAME, ios::trunc);
    if (outfile.is_open()) {
        for (const auto& seller : login_seller) {
            outfile << seller.serialize() << endl;
        }
        outfile.close();
        cout << "USER BERHASIL DIDAFTARKAN!\n";
    } else {
        cerr << "Gagal menulis ke file.\n";
    }
    return true;    
}

// === Login Seller ===
bool Seller::loginSeller() {
    string username;
    string password;
    const string FILENAME = "seller.txt";

    Login_Seller data_user;
    login_seller.clear();

    ifstream infile(FILENAME);
    string line;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            data_user.deserialize(line);
            login_seller.push_back(data_user);
        }
        infile.close();
    } else {
        cerr << "Tidak bisa membaca file seller.txt\n";
        return false;
    }

    cout << "\n ANDA HARUS LOGIN TERLEBIH DAHULU!" << endl;
    cout << "\n=== LOGIN SELLER ===\n";
    cout << "Username: \n";
    getline(cin, username);
    cout << "Password: \n";
    getline(cin, password);


    for (const auto& seller : login_seller) {
        if (seller.GetUsername() == username && seller.GetPassword() == password) {
            cout << "Login berhasil. Selamat datang, " << username << "!\n";
            this->username = username; // simpan username ke objek seller
            return true;
        }
    }

    cout << "Login gagal. Username atau password salah.\n";
    return false;
}

const string FILENAME = "item.txt";

// === Tambah Produk ===
string itemID;
string name;
string description;
double price;
int stock;
string seller;
Item items(itemID, name, description, price, stock, seller);

void Seller::create_product() {
    cout << "\n=== TAMBAH PRODUK BARU ===\n";
    cout << "Masukkan ID Barang     : \n";
    cin >> itemID;
    cin.ignore();
    cout << "Masukkan Nama Barang   : \n";
    getline(cin, name);
    cout << "Masukkan Deskripsi     : \n";
    getline(cin, description);
    cout << "Masukkan Harga         : \n";
    cin >> price;
    cout << "Masukkan Jumlah Stok   : \n";
    cin >> stock;

    Item newItem(itemID, name, description, price, stock, username);
    item.push_back(newItem);
    
    // Simpan ke file
    ofstream outfile(FILENAME, ios::trunc);
    if (outfile.is_open()) {
        for (const auto& Newitem : item) {
            outfile << Newitem.serialize() << endl;
        }
        outfile.close();
        cout << "BARANG BERHASIL DIDAFTARKAN!\n";
    } else {
        cerr << "Gagal menulis ke file.\n";
    }
}

void Seller::edit_product() {
    cout << "\n=== EDIT PRODUK ===\n";
    string editID;
    cout << "Masukkan ID Barang yang ingin diedit: ";
    cin >> editID;

    const string FILENAME = "item.txt";
    vector<Item> items;
    string line;
    Item tempItem;
    bool found = false;

    // === Load data item dari file ===
    ifstream infile(FILENAME);
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (!line.empty()) {
                tempItem.deserialize(line);
                items.push_back(tempItem);
            }
        }
        infile.close();
    } else {
        cerr << "Gagal membuka file " << FILENAME << " untuk membaca data.\n";
        return;
    }

    // === Cari item berdasarkan ID ===
    for (auto &item : items) {
        if (item.itemID == editID && item.seller == username) {
            found = true;
            cout << "\nProduk ditemukan:\n";
            cout << "Nama: " << item.name << "\nDeskripsi: " << item.description
                 << "\nHarga: " << item.price << "\nStok: " << item.stock << endl;

            // Edit data baru
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nMasukkan nama baru (kosongkan jika tidak diubah): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) item.name = newName;

            cout << "Masukkan deskripsi baru (kosongkan jika tidak diubah): ";
            string newDesc;
            getline(cin, newDesc);
            if (!newDesc.empty()) item.description = newDesc;

            cout << "Masukkan harga baru (isi 0 jika tidak diubah): ";
            double newPrice;
            cin >> newPrice;
            if (newPrice > 0) item.price = newPrice;

            cout << "Masukkan stok baru (isi -1 jika tidak diubah): ";
            int newStock;
            cin >> newStock;
            if (newStock >= 0) item.stock = newStock;

            cout << "\n Produk berhasil diperbarui!\n";
            break;
        }
    }

    if (!found) {
        cout << "\n Produk dengan ID " << editID << " tidak ditemukan atau bukan milik Anda.\n";
        return;
    }

    // === Simpan kembali semua item ke file ===
    ofstream outfile(FILENAME, ios::trunc);
    if (outfile.is_open()) {
        for (const auto &it : items) {
            outfile << it.serialize() << endl;
        }
        outfile.close();
    } else {
        cerr << "Gagal menulis ke file " << FILENAME << endl;
    }
};


void Seller::display() {
    const string FILENAME = "item.txt";
    vector<Item> items;
    string line;
    Item tempItem;

    // === Load semua item dari file ===
    ifstream infile(FILENAME);
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (!line.empty()) {
                tempItem.deserialize(line);
                items.push_back(tempItem);
            }
        }
        infile.close();
    } else {
        cerr << "Gagal membuka file \n";
        return;
    }

    // === Tampilkan hanya item milik seller ini ===
    cout << "\n=== DAFTAR PRODUK ANDA ===\n";
    bool found = false;
    for (const auto& item : items) {
        if (item.seller == username) {
            found = true;
            cout << "------------------------------------------\n";
            cout << "ID Barang   : " << item.itemID << endl;
            cout << "Nama Barang : " << item.name << endl;
            cout << "Deskripsi   : " << item.description << endl;
            cout << "Harga       : " << item.price << endl;
            cout << "Stok        : " << item.stock << endl;
            cout << "Penjual     : " << item.seller << endl;
        }
    }
    if (!found) {
        cout << "Belum ada produk yang Anda daftarkan.\n";
    }
}

// === Menu Seller ===
void Seller::menu_seller() {
    int pilihan;
    do {
        cout << "\n====== SELAMAT DATANG, " << username << " ======\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Edit Produk\n";
        cout << "3. Display Produk\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                create_product();
                break;
            case 2:
                edit_product();
                break;
            case 3:
                display();
                break;
            case 4:
                cout << "Terima Kasih " << username << "!\n";
                break;
        }
    } while (pilihan != 4);
}
