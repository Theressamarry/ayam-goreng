#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "ProdukTerjual.h"
#include <vector>

using namespace std;

// ==== DEKLARASI ADMIN CLASS ====
// class admin ini merupakan turunan dari class User
// tpi dia punya fitur tambahan yatu kelola BahanBaku
class Admin : public User {
private:
    string idAdmin; // id khusus admin yg berbeda dg user lain
    vector<ProdukTerjual> daftarPenjualan;
public:
    // ==== CONSTRUCTOR ADMIN ====
    Admin(int id, string uname,string pwd, string idAdmin);

    // ==== GETTER ADMIN ====
    string getIdAdmin() const { return idAdmin; }

    // ==== METHODE ADMIN ====
    void manajemenUser();
    void manajemenStok();
};
#endif