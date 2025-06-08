#include "Pelanggan.h"
#include "User.h"
#include <iostream>
#include "GlobalData.h"
#include <iomanip>

using namespace std;

// ==== CONSTRUKTOR PELANGGAN ====
// class pelanggan merupakan turunan dari class User
Pelanggan::Pelanggan(int id, string uname, string pwd, string nama)
    : User(id, uname, pwd, "Pelanggan"), namaLengkap(nama) {}

// ==== DISPLAY INFO PELANGGAN ====
void Pelanggan::displayInfo() {
    cout << "\n=== INFO PELANGGAN ===" << endl;
    cout << "Username: " << username << endl;
    cout << "Nama Lengkap: " << namaLengkap << endl;
}

// ==== LIHAT MENU PRODUK ====
void Pelanggan::lihatMenu() {
    cout << "\n=== DAFTAR MENU ===" << endl;
    cout << left << setw(5) << "Nama Produk" 
         << right << setw(12) << "Harga" << endl;
    cout << "---------------------------" << endl;
    
    for (const BahanBaku &bahan : daftarBahanBaku) {
        cout << left << setw(5) << bahan.getnamaBahan() 
             << right << setw(15) << "Rp" << bahan.getharga() << endl;
    }
}

// ==== GETTER NAMA LENGKAP PELANGGAN ====
string Pelanggan::getNamaLengkap() const {
    return namaLengkap;
}