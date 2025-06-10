#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <vector>
#include "BahanBaku.h"
#include "ProdukTerjual.h"
#include "User.h"

using namespace std;

// ==== DEKLARASI VARIABEL GLOBAL ====
extern vector<BahanBaku> daftarBahanBaku;
extern vector<ProdukTerjual> daftarPenjualan;
extern vector<User*> users; 

// ==== DEKLARASI VARIABEL ID ====
int generateBahanId();
int generatePenjualanId();
void loadLastIdFromFile();
void saveLastIdToFile();

// ==== DEKLARASI FUNGSI UNTUK LOAD DATA ====
void loadBahanBakuFromFile();
void loadPenjualanFromFile();
void loadUsersFromFile();

// ==== DEKLARASI FUNGSI UNTUK SAVE DATA ====
void saveBahanBakuToFile();
void saveUsersToFile();
void savePenjualanToFile();

#endif
