#include "BahanBaku.h"
#include <iostream>
#include <string>

using namespace std;

// ==== CONSTRUKTOR BAHAN BAKU ====
BahanBaku::BahanBaku(int id, string nama, int stok, double harga)
    : idBahan(id), namaBahan(nama), stok(stok), harga(harga){}

// ==== TAMPILKAN INFO PRODUK ====
void BahanBaku::displayInfo() {
    cout << "-----------------------------------" << endl;
    cout << "ID         : " << idBahan << endl;
    cout << "Nama Produk : " << namaBahan << endl;
    cout << "Stok       : " << stok << endl;
    cout << "Harga/unit : Rp" << harga << endl;
}

// ==== TAMBAH STOK PRODUK ====
void BahanBaku::tambahStok(int jumlah){
    stok += jumlah;
}

// ==== KURANGI STOK PRODUK ====
void BahanBaku::kurangiStok(int jumlah){
    if(jumlah<=0) {
        cout << "ERROR: Jumlah harus lebih besar dari 0." << endl;
        return;
    }
    if(jumlah > stok) {
        cout << "ERROR: Stok tidak cukup untuk mengurangi " << jumlah << endl;
        return;
    }
    stok -= jumlah;
}

// ==== GETTER BAHAN BAKU ====
int BahanBaku::getidBahan() const {
    return idBahan;
}

string BahanBaku::getnamaBahan() const{
    return namaBahan;
}

int BahanBaku::getstok() const {
    return stok;
}

double BahanBaku::getharga() const {
    return harga;
}