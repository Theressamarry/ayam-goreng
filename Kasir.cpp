#include "Kasir.h"
#include "ProdukTerjual.h"
#include <iostream>
#include <vector>

using namespace std;

vector<ProdukTerjual> daftarPenjualan; // menyimpan data penjualan

Kasir::Kasir(int id, string uname, string pwd, string idKaryawan)
    : User(id, uname, pwd, "Kasir"), idKaryawan(idKaryawan){}

void Kasir::kelolaPenjualan(){
    int id, jumlah;
    string tgl, nama;
    double harga;

    cout << "=== C A T A T  P E N J U A L A N ===" << endl;
    cout << "ID Penjualan: "; cin >> id;
    cout << "Tanggal (DD-MM-YYYY): "; cin >> tgl;
    cout << "Nama Produk: "; cin >> nama;
    cout << "Jumlah: "; cin >> jumlah;
    cout << "Harga per unit: "; cin >> harga;
    daftarPenjualan.push_back(ProdukTerjual(id, tgl, nama, jumlah, harga));
    cout << "Penjualan berhasil dicatat!" << endl;
}

void Kasir::lihatStok(){
    cout << "Kasir melihat stok" << endl;
}