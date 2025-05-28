#ifndef KASIR_H
#define KASIR_H
#include "User.h"
using namespace std;

class Kasir : public User {
private:
    string idKaryawan;
public:
    Kasir(int id, string uname, string pwd, string idKaryawan);
    void kelolaPenjualan();
    void lihatStok();

};
#endif