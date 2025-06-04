#include "Kasir.h"
#include "ProdukTerjual.h"
#include "BahanBaku.h"
#include "User.h"
#include "Admin.h"
#include "GlobalData.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

Kasir::Kasir(int id, string uname, string pwd, string idKaryawan)
    : User(id, uname, pwd, "Kasir"), idKaryawan(idKaryawan){}

void Kasir::kelolaPenjualan(){
    int id, jumlah;
    string tgl, nama;
    double harga;

    cout << "\n=== C A T A T  P E N J U A L A N ===" << endl;
    cout << "ID Penjualan: "; cin >> id;
    cout << "Tanggal (DD-MM-YYYY): "; cin >> tgl;
    cout << "Nama Produk: "; cin >> nama;
    cout << "Jumlah: "; cin >> jumlah;
    cout << "Harga per unit: "; cin >> harga;
    daftarPenjualan.push_back(ProdukTerjual(id, tgl, nama, jumlah, harga));
    cout << "Penjualan berhasil dicatat!" << endl;
}

void Kasir::lihatStok(){
    int choice;
    cout << "\n1. Lihat Semua Stok\n2. Cari Produk\nPilih: ";
    cin >> choice;

    if (choice == 1){
        for (BahanBaku &b: daftarBahanBaku) {
            b.displayInfo();
        }
    } else if (choice == 2) {
        string keyword;
        cout << "Nama produk: ";
        cin >> keyword;
        for (BahanBaku &b: daftarBahanBaku) {
            if (b.getNamaBahan().find(keyword) != string::npos) {
                b.displayInfo();
            }
        }
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}
