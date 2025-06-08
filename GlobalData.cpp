#include "GlobalData.h"
#include "BahanBaku.h"
#include "ProdukTerjual.h"
#include "User.h"
#include "Admin.h"
#include "Kasir.h"
#include "Pelanggan.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// definisi variabel global (alokasi memori terjadi di sini)
vector<BahanBaku> daftarBahanBaku;
vector<ProdukTerjual> daftarPenjualan;

int lastBahanId = 0;
int lastPenjualanId = 0;

void loadLastIdFromFile() {
    ifstream file("last_id.txt");
    if (file.is_open()) {
        file >> lastBahanId >> lastPenjualanId;
        file.close();
    } 
}

void saveLastIdToFile() {
    ofstream file("last_id.txt");
    if (file.is_open()) {
        file << lastBahanId << " " << lastPenjualanId;
        file.close();
    }
}

int generateBahanId() {
    lastBahanId++;
    saveLastIdToFile();
    return lastBahanId;
}

int generatePenjualanId() {
    lastPenjualanId++;
    saveLastIdToFile();
    return lastPenjualanId;
}

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
    // variavel untuk menyimpan data hsil konversi
    int id, stok;
    string nama;
    double harga;

    string line;
    // membaca tiap baris
    while (getline(file, line)) {
        stringstream ss(line); // gunakan stringstream untuk memecah baris
        string idStr, namaStr, stokStr, hargastr; // variabel untuk menyimpan string sementara
        
        // memecah string berdasarkan koma
        getline(ss, idStr, ',');
        getline(ss, namaStr, ',');
        getline(ss, stokStr, ',');
        getline(ss, hargastr, ',');

        // konversi string ke tipe data yang sesuai
        id = stoi(idStr); // stoi untuk mengkonversi string ke integer
        nama = namaStr;
        stok = stoi(stokStr); // stoi untuk mengkonversi string ke integer
        harga = stod(hargastr); // stod untuk mengkonversi string ke double

        daftarBahanBaku.push_back(BahanBaku(id, nama, stok, harga));
    }

    file.close();
}

