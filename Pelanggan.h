#ifndef PELANGGAN_H
#define PELANGGAN_H

#include "User.h"
#include <string>

class Pelanggan : public User {
private:
    std::string namaLengkap;
public:
    Pelanggan(int id, std::string uname, std::string pwd, std::string nama);
    void displayInfo() override;
    void lihatMenu();
    std::string getNamaLengkap() const;
};

#endif