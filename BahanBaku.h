#ifndef BAHANBAKU_H
#define BAHANBAKU_H
#include <string>

using namespace std;

class BahanBaku{
private:
    int idBahan;
    string namaBahan;
    int stok;
    double harga;

public:
    // constructor
    BahanBaku(int id, string nama, int stok, double harga);

    // crud bahan baku
    void displayInfo();
    void tambahStok(int jumlah);
    void kurangiStok(int jumlah);

    // getter (mengakses stok bahan baku dari data private)
    int getidBahan() const;
    string getnamaBahan() const;
    int getstok() const;
    double getharga() const;
};

#endif