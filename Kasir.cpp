#include "kasir.h"
#include <iostream>

Kasir::Kasir(int id, string uname, string pwd, string idKaryawan)
    : User(id, uname, pwd, "kasir"), idKaryawan(idKaryawan){}

void Kasir::kelolaPenjualan(){
    cout << "Kasir mencatat penjualan" << endl;
}

void Kasir::lihatstok(){
    cout << "Kasir melihat stok" << endl;
}