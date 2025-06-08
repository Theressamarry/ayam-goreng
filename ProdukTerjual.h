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

    // getter methods
    int getidPenjualan() const { return idPenjualan; }
    string gettanggal() const { return tanggal; }
    string getnamaProduk() const { return namaProduk; }
    int getjumlah() const { return jumlah; }
    double getharga() const { return harga; }

    void displayInfo();

};

#endif