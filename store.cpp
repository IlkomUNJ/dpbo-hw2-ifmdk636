// STORES 
// ALL The logic program
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "buyer.hpp"
#include "seller.hpp"
#include "bank.hpp"

using namespace std;

// === MAIN PROGRAM ===
int main() {
    Buyer buyer("001", "Guest", "None");
    Seller seller("Guest", "None", "None", "None");

    int pilihan;
    bool isLoggedIn = false;
    bool isSellerLoggedIn = false;

    do {
        cout << "\n==============================\n";
        cout << "     SISTEM TOKO ONLINE\n";
        cout << "==============================\n";
        cout << "1. Register Buyer\n";
        cout << "2. Login Buyer\n";
        cout << "3. Register Seller\n";
        cout << "4. Login Seller\n";
        cout << "5. Keluar\n";
        cout << "==============================\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
            case 1: {
                buyer.create_user();
                cout << "\nSilakan login untuk melanjutkan\n";
                bool loginSuccess = buyer.login_user();
                if (loginSuccess) {
                    buyer.menu_bank_user();
                } else {
                    cout << "Login gagal. Silakan coba lagi.\n";
                }
                break;
            }
            case 2: {
                bool loginSuccess = buyer.login_user();
                if (loginSuccess) {
                    buyer.menu_bank_user();
                } else {
                    cout << "Login gagal. Silakan coba lagi.\n";
                }
                break;
            }
            case 3: {
                seller.create_user();
                cout << "\nSilakan login untuk melanjutkan...\n";
                bool loginSuccess = seller.loginSeller();

                if (loginSuccess) {
                    seller.menu_seller();
                } else {
                    cout << "Login gagal. Silakan coba lagi.\n";
                }
                break;
            }
            case 4: {
                bool loginSuccess = seller.loginSeller();
                if (loginSuccess) {
                    seller.menu_seller();
                } else {
                    cout << "Login gagal. Silakan coba lagi.\n";
                }
                break;
            }
            case 5:
                cout << "Keluar dari program...\n";
                break;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 5);

    return 0;
}
