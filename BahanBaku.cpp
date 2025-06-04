#include "BahanBaku.h"
#include <iostream>

using namespace std;

BahanBaku::BahanBaku(int id, string nama, int stok)
    : idBahan(id), namaBahan(nama), stok(stok) {}

void BahanBaku::displayInfo() {
    cout << "ID: " << idBahan 
         << " | Nama Bahan: " << namaBahan 
         << " | Stok: " << stok << endl;
}

void BahanBaku::tambahStok(int jumlah){
    stok += jumlah;
}

void BahanBaku::kurangiStok(int jumlah){
    try {
        if (jumlah <= 0) throw invalid_argument("Jumlah harus lebih besar dari 0.");
        if (stok < jumlah) throw runtime_error("Stok tidak cukup untuk mengurangi jumlah yang diminta.");
        stok -= jumlah;
    } catch(exception &e){
        cerr << "Error: " << e.what() << endl;
    }
}

string BahanBaku::getNamaBahan() {
    return namaBahan;
}

int BahanBaku::getStok() {
    return stok;
}