#include "Kasir.h"
#include <iostream>

Kasir::Kasir(int id, string uname, string pwd, string idKaryawan)
    : User(id, uname, pwd, "Kasir"), idKaryawan(idKaryawan){}

void Kasir::kelolaPenjualan(){
    cout << "Kasir mencatat penjualan" << endl;
}

void Kasir::lihatStok(){
    cout << "Kasir melihat stok" << endl;
}