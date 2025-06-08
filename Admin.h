#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
using namespace std;

class Admin : public User {
private:
    string idAdmin;
public:
    Admin(int id, string uname,string pwd, string idAdmin);
    string getIdAdmin() const { return idAdmin; }
    void manajemenUser();
    void manajemenStok();
};
#endif