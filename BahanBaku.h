#ifndef BAHANBAKU_H
#define BAHANBAKU_H
#include <string>

using namespace std;

// ==== DEKLARASI BAHAN BAKU CLASS ====
class BahanBaku{
private:
    int idBahan;
    string namaBahan;
    int stok;
    double harga;

public:
    // ==== CONSTRUKTOR BAHAN BAKU ====
    BahanBaku(int id, string nama, int stok, double harga);

    // ==== DISPLAY INFO PRODUK ====
    void displayInfo();

    // ==== UPDATE STOK PRODUK ====
    void tambahStok(int jumlah); // menambah stok bahan baku
    void kurangiStok(int jumlah); // mengurangi stok bahan baku

    // ==== GETTER BAHAN BAKU ====
    int getidBahan() const; // ambil id bahan baku
    string getnamaBahan() const; // ambil nama bahan baku
    int getstok() const; // ambil stok bahan baku
    double getharga() const; // ambil harga bahan baku
};

#endif