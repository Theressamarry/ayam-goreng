#include "Admin.h"
#include <iostream>

Admin::Admin(int id, string uname, string pwd, string idAdmin)
    : User(id, uname, pwd, "Admin"), idAdmin(idAdmin){}

void Admin::manajemenUser(){
    cout << "Admin mengelola user" << endl;
}

void Admin::manajemenStok(){
    cout << "Admin mengelola stok" << endl;
}
