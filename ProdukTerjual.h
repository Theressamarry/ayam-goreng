#ifndef PRODUKTERJUAL_H
#define PRODUKTERJUAL_H
#include <string>

using namespace std;

class ProdukTerjual{
private:
    int idPenjualan;
    string tanggal;
    string namaProduk;
    int jumlah;
    double harga;

public:
    ProdukTerjual(int id, string tgl, string nama, int jml, double hrg);
    void displayInfo();
};

#endif