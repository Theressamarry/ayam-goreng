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
    if (jumlah <= stok) {
        stok -= jumlah;
    } else {
        cout << "Stok tidak cukup!" << jumlah << endl;
    }
}

string BahanBaku::getNamaBahan() {
    return namaBahan;
}

int BahanBaku::getStok() {
    return stok;
}