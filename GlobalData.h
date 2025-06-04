// GlobalData.h
#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <vector>
#include "BahanBaku.h"
#include "ProdukTerjual.h"

// Deklarasi variabel global (tidak menduplikat memori)
extern std::vector<BahanBaku> daftarBahanBaku;
extern std::vector<ProdukTerjual> daftarPenjualan;

#endif
