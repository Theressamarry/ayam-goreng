#include "GlobalData.h"
#include "BahanBaku.h"
#include "ProdukTerjual.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// definisi variabel global (alokasi memori terjadi di sini)
vector<BahanBaku> daftarBahanBaku;
vector<ProdukTerjual> daftarPenjualan;

void loadPenjualanFromFile() {
    ifstream file("penjualan.txt");
    int id, jumlah;
    string tanggal, nama;
    double harga;

    while (getline(file, tanggal, ',') && getline(file, nama, ',') &&
           file >> id >> jumlah >> harga) {
        file.ignore();
        daftarPenjualan.push_back(ProdukTerjual(id, tanggal, nama, jumlah, harga));
    }

    file.close();
}

void loadBahanBakuFromFile() {
    ifstream file("bahan_baku.txt");
    int id;
    string nama;
    int stok;

    while (getline(file, nama, ',') && file >> stok) {
        file.ignore(); // skip newline
        daftarBahanBaku.push_back(BahanBaku(id, nama, stok));
    }

    file.close();
}
