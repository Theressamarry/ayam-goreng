#include "ProdukTerjual.h"
#include <iostream>

using namespace std;

// ==== CONSTRUKTOR PRODUK TERJUAL ====
// class ProdukTerjual ini digunakan untuk menyimpan data penjualan produk
ProdukTerjual::ProdukTerjual(int id, string tgl, string nama, int jml, double hrg)
    : idPenjualan(id), tanggal(tgl), namaProduk(nama), jumlah(jml), harga(hrg) {}

// ==== DISPLAY INFO PRODUK TERJUAL ====
void ProdukTerjual::displayInfo() {
    cout << "ID Penjualan: " << idPenjualan 
         << " | Tanggal: " << tanggal 
         << " | Nama Produk: " << namaProduk 
         << " | Jumlah: " << jumlah 
         << " | Total: RP" << harga * jumlah << endl;
}