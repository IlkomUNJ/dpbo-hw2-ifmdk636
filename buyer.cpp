#include "buyer.hpp"
#include "item.hpp"
#include "bank.hpp"
#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// === Registrasi User Baru ===
void Buyer::create_user() {
    string username, password;
    vector<Login_Buyer> login_buyer;
    const string FILENAME = "user.txt";

    // Load existing users
    ifstream infile(FILENAME);
    string line;
    if (infile.is_open()) {
        Login_Buyer data_user;
        while (getline(infile, line)) {
            if (!line.empty()) {
                data_user.deserialize(line);
                login_buyer.push_back(data_user);
            }
        }
        infile.close();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Username: ";
    getline(cin, username);
    cout << "Masukkan Password: ";
    getline(cin, password);

    login_buyer.emplace_back(username, password);

    ofstream outfile(FILENAME, ios::trunc);
    if (outfile.is_open()) {
        for (const auto& buyer : login_buyer) {
            outfile << buyer.serialize() << endl;
        }
        outfile.close();
        cout << "USER BERHASIL DIDAFTARKAN!\n";
    } else {
        cerr << "Gagal menulis ke file.\n";
    }
}

// === Login User ===
bool Buyer::login_user() {
    cout << "\n=== LOGIN PENGGUNA ===\n";
    string username, password;
    vector<Login_Buyer> login_buyer;
    const string FILENAME = "user.txt";
    ifstream infile(FILENAME);
    string line;
    if (infile.is_open()) {
        Login_Buyer data_user;
        while (getline(infile, line)) {
            if (!line.empty()) {
                data_user.deserialize(line);
                login_buyer.push_back(data_user);
            }
        }
        infile.close();
    } else {
        cerr << "Tidak bisa membaca file user.txt\n";
        return false;
    }
    cout << "Klik ENTER untuk melanjutkan..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Username: ";
    getline(cin, username);
    cout << "Masukkan Password: ";
    getline(cin, password);

    for (const auto& buyer : login_buyer) {
        if (buyer.GetUsername() == username && buyer.GetPassword() == password) {
            cout << "\nLogin berhasil. Selamat datang, " << username << "!\n";
            this->username = username;
            return true;
        }
    }

    cout << "\nLogin gagal. Username atau password salah.\n";
    return false;
}

// === Buat Akun Bank Baru ===
void Buyer::createBankAccount() {
    Bank bank;
    cout << "\nSelamat datang, " << username << "!" << endl;
    cout << "Masukkan jumlah deposito awal: ";
    cin >> deposito;
    saldo += deposito;
    cout << "Akun bank berhasil dibuat. Saldo sekarang: " << saldo << endl;

    // Simpan ke file
    const string FILENAME = "transactions.txt";
    ofstream outfile(FILENAME, ios::app);
    if (outfile.is_open()) {
        outfile << bank.serialize() << endl;
        outfile.close();
        cout << "Data transaksi tersimpan!\n";
    } else {
        cerr << "Gagal menulis ke file transaksi.\n";
    }
}

// === Cek Saldo ===
void Buyer::cekSaldo() {
    cout << "Saldo saat ini: " << saldo << endl;
}

// === Deposit Tambahan ===
void Buyer::deposit() {
    double amount;
    cout << "Masukkan jumlah deposit tambahan: ";
    cin >> amount;

    if (amount > 0) {
        saldo += amount;
        cout << "Deposit berhasil. Saldo sekarang: " << saldo << endl;
        transaction_history.push_back("Deposit tambahan: +" + to_string(amount));
    } else {
        cout << "Jumlah deposit tidak valid." << endl;
    }
}

// === Penarikan ===
void Buyer::withDrawal() {
    double amount;
    cout << "Masukkan jumlah yang ingin ditarik: ";
    cin >> amount;

    if (amount > saldo) {
        cout << "Saldo tidak mencukupi!" << endl;
    } else if (amount <= 0) {
        cout << "Jumlah tidak valid!" << endl;
    } else {
        saldo -= amount;
        cout << "Penarikan berhasil. Sisa saldo: " << saldo << endl;
        transaction_history.push_back("Penarikan sebesar: -" + to_string(amount));
    }
}

// === Riwayat Transaksi ===
void Buyer::transactionHistory() {
    cout << "\n===== Riwayat Transaksi =====\n";
    for (const string& t : transaction_history)
        cout << t << endl;
    cout << "==============================\n";
}

// === Beli Barang ===
void Buyer::buy_products() {
    const string ITEM_FILE = "item.txt";
    const string TRANSACTION_FILE = "transactions.txt";
    vector<Item> itemList;
    string line;

    ifstream infile(ITEM_FILE);
    if (!infile.is_open()) {
        cerr << "Gagal membuka file item.txt.\n";
        return;
    }

    while (getline(infile, line)) {
        if (!line.empty()) {
            Item item;
            item.deserialize(line);
            itemList.push_back(item);
        }
    }
    infile.close();

    cout << "\n========== DAFTAR BARANG ==========\n";
    cout << left << setw(8) << "ID" 
         << setw(20) << "Nama Barang" 
         << setw(10) << "Harga" 
         << setw(8) << "Stok" 
         << setw(15) << "Penjual" << endl;
    cout << "---------------------------------------------\n";

    for (const auto& item : itemList) {
        cout << left << setw(8) << item.itemID
             << setw(20) << item.name
             << setw(10) << item.price
             << setw(8) << item.stock
             << setw(15) << item.seller << endl;
    }

    string pilihID;
    int jumlah;
    cout << "\nMasukkan ID Barang yang ingin dibeli: ";
    cin >> pilihID;
    cout << "Masukkan jumlah yang ingin dibeli: ";
    cin >> jumlah;

    for (auto &item : itemList) {
        if (item.itemID == pilihID) {
            if (item.stock < jumlah) {
                cout << "Stok tidak mencukupi.\n";
                return;
            }

            double totalHarga = item.price * jumlah;

            if (saldo < totalHarga) {
                cout << "Saldo Anda tidak mencukupi.\n";
                return;
            }

            saldo -= totalHarga;
            item.stock -= jumlah;

            transaction_history.push_back(
                "Membeli " + to_string(jumlah) + "x " + item.name +
                " seharga " + to_string(totalHarga)
            );

            ofstream outTrans(TRANSACTION_FILE, ios::app);
            outTrans << "Pembelian " << item.name << " sebanyak " << jumlah
                     << " total " << totalHarga << endl;
            outTrans.close();

            ofstream outItem(ITEM_FILE, ios::trunc);
            for (const auto& it : itemList)
                outItem << it.serialize() << endl;
            outItem.close();

            cout << "\nPembelian berhasil! Sisa saldo: " << saldo << endl;
            return;
        }
    }

    cout << "Barang dengan ID tersebut tidak ditemukan.\n";
}

// === Menu Utama Buyer ===
void Buyer::menu_bank_user() {
    int choice;
    bool running = true;

    do {
        cout << "\n========== MENU BUYER ==========\n";
        cout << "1. Beli Barang\n";
        cout << "2. Buat Akun Bank\n";
        cout << "3. Deposit Tambahan\n";
        cout << "4. Tarik Saldo (Withdraw)\n";
        cout << "5. Lihat Riwayat Transaksi\n";
        cout << "6. Lihat Saldo Saat Ini\n";
        cout << "7. Keluar\n";
        cout << "================================\n";
        cout << "Pilih menu (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1: buy_products(); break;
            case 2: createBankAccount(); break;
            case 3: deposit(); break;
            case 4: withDrawal(); break;
            case 5: transactionHistory(); break;
            case 6: cekSaldo(); break;
            case 7: running = false; break;
            default: cout << "Pilihan tidak valid!\n"; break;
        }
    } while (running);
}
