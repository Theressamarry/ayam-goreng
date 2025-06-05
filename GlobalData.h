#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <vector>
#include "BahanBaku.h"
#include "ProdukTerjual.h"

using namespace std;

// deklarasi variabel global (tidak menduplikat memori)
extern vector<BahanBaku> daftarBahanBaku;
extern vector<ProdukTerjual> daftarPenjualan;

// fungsi untuk memuat data dari file
int generateBahanId();
int generatePenjualanId();
void loadLastIdFromFile();
void saveLastIdToFile();
void loadBahanBakuFromFile();
void loadPenjualanFromFile();

#endif
