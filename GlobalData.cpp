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

    string line;
    // membaca tiap baris
    while (getline(file, line)) {
        stringstream ss(line); // gunakan stringstream untuk memecah baris
        string idStr, namaStr, stokStr; // variabel untuk menyimpan string sementara
        
        // memecah string berdasarkan koma
        getline(ss, idStr, ',');
        getline(ss, namaStr, ',');
        getline(ss, stokStr, ',');

        // konversi string ke tipe data yang sesuai
        // stoi untuk mengkonversi string ke integer
        id = stoi(idStr);
        nama = namaStr;
        stok = stoi(stokStr);

        daftarBahanBaku.push_back(BahanBaku(id, nama, stok));
    }

    file.close();
}

