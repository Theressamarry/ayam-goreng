#ifndef KASIR_H
#define KASIR_H
#include "User.h"
using namespace std;

// ==== DEKLARASI KASIR CLASS ====
// class kasir ini merupakan turunan dari class User
// tpi dia punya fitur tambahan yatu kelola penjualan
class Kasir : public User {
private:
    string idKaryawan;
public:
    // ==== CONSTRUCTOR KASIR ====
    Kasir(int id, string uname, string pwd, string idKaryawan);
    
    // ==== GETTER KASIR ====
    string getIdKaryawan() const { return idKaryawan; }

    // ==== METHODE KASIR ====
    void kelolaPenjualan();
    void lihatStok();

};
#endif