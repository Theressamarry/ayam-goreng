#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Admin.h"
#include "Kasir.h"
#include "Pelanggan.h"
#include "GlobalData.h"

using namespace std;

vector<User*> users; // menyimpan data user

// ==== REGISTRASI PELANGGAN ====
void registrasiPelanggan() {
    static int nextId = 3; // start dari 3 karena admin(1) dan kasir(2) sudah ada
    if (!users.empty()) {
        nextId = users.back()->getId() + 1; // ambil id terakhir + 1
    }

    string username, password, namaLengkap;
    cout << "\n=== REGISTRASI PELANGGAN ===" << endl;
    cout << "Username: "; getline(cin, username);
    cout << "Password: "; getline(cin, password);
    cout << "Nama Lengkap: "; getline(cin, namaLengkap);

    users.push_back(new Pelanggan(nextId++, username, password, namaLengkap));
    saveUsersToFile(); // simpan data user ke file
    cout << "Registrasi berhasil!" << endl;
}

// ==== AUTENTIKASI USER ====
User* authenticate(const string& username, const string& password) {
    for (User* user : users) {
        if (user->login(username, password)) {
            return user;
        }
    }
    return nullptr;
}

// ==== FUNSI UTAMA (MAIN PRIGRAM) ==== 
int main() {
    // Load data dari file
    loadBahanBakuFromFile();
    loadPenjualanFromFile();
    loadLastIdFromFile();
    loadUsersFromFile(); 
    
    // bikin default admin dan kasir
    if (users.empty()) {
        users.push_back(new Admin(1, "admin", "admin123", "ADM01")); // idUser, uname, pwd, idAdmin
        users.push_back(new Kasir(2, "kasir", "kasir123", "KSR01")); // idUser, uname, pwd, idKaryawan
        saveUsersToFile();
    }

    bool running = true;

    while (running) {
        cout << "\n=== MENU UTAMA ===" << endl;
        cout << "1. Login" << endl;
        cout << "2. Registrasi Pelanggan" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";

        int choice;
        cin >> choice;
        cin.ignore(); 

        if (choice == 1) { // login
            string username, password;
            cout << "\n=== L O G I N ===" << endl;
            cout << "Username: ";
            getline(cin, username);
            cout << "Password: ";
            getline(cin, password);

            User* logInUser = authenticate(username, password);

            if (logInUser != nullptr) {
                cout << "\nLogin berhasil!" << endl;

                if (logInUser->getRole() == "Admin") {
                    Admin* admin = dynamic_cast<Admin*>(logInUser);
                    admin->manajemenUser();
                    admin->manajemenStok();
                } else if (logInUser->getRole() == "Kasir") {
                    Kasir* kasir = dynamic_cast<Kasir*>(logInUser);
                    kasir->kelolaPenjualan();
                } else if (logInUser->getRole() == "Pelanggan") {
                    Pelanggan* pelanggan = dynamic_cast<Pelanggan*>(logInUser);
                    pelanggan->displayInfo();
                    pelanggan->lihatMenu();
                }

                string input;
                cout << "\nKembali ke menu utama? (y/n): ";
                getline(cin, input);

                if (!input.empty() && tolower(input[0]) == 'n') {
                    running = false;
                }
            } else {
                cout << "Login gagal!" << endl;
            }

        } else if (choice == 2) { // registrasi pelanggan
            registrasiPelanggan();
        } else if (choice == 3) { // keluar dari program
            running = false;
        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }

    // ==== DEOLKASI USER ====
    for (User* user : users) {
        delete user;
    }

    return 0;
}
