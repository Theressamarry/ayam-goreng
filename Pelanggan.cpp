#include "Pelanggan.h"
#include <iostream>
#include "GlobalData.h"
#include <iomanip>

Pelanggan::Pelanggan(int id, std::string uname, std::string pwd, std::string nama)
    : User(id, uname, pwd, "Pelanggan"), namaLengkap(nama) {}

void Pelanggan::displayInfo() {
    std::cout << "\n=== INFO PELANGGAN ===" << std::endl;
    std::cout << "ID: " << idUser << std::endl;
    std::cout << "Username: " << username << std::endl;
    std::cout << "Nama Lengkap: " << namaLengkap << std::endl;
}

void Pelanggan::lihatMenu() {
    std::cout << "\n=== DAFTAR MENU ===" << std::endl;
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Nama Produk" 
              << std::setw(10) << "Stok" 
              << std::setw(15) << "Harga" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    
    for (const BahanBaku &bahan : daftarBahanBaku) {
        std::cout << std::left << std::setw(5) << bahan.getidBahan()
                  << std::setw(20) << bahan.getnamaBahan()
                  << std::setw(10) << bahan.getstok()
                  << "Rp" << std::setw(13) << bahan.getharga() << std::endl;
    }
}

std::string Pelanggan::getNamaLengkap() const {
    return namaLengkap;
}