#include "Kasir.h"
#include "ProdukTerjual.h"
#include "BahanBaku.h"
#include "User.h"
#include "Admin.h"
#include "GlobalData.h"
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

Kasir::Kasir(int id, string uname, string pwd, string idKaryawan)
    : User(id, uname, pwd, "Kasir"), idKaryawan(idKaryawan){}

void Kasir::kelolaPenjualan(){
    int choice;
    do{
        cout << "\n=== M E N U K A S I R ==="<< endl;
        cout << " 1. Catat Penjualan\n 2. Lihat Semua Stok\n 3. Cari Produk\n 0. Quit\n" << endl;
        cout << "Pilih: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        switch(choice){
            case 1: {
                int id, jumlah;
                string tgl, nama;
                double harga;

                cout << "\n=== C A T A T  P E N J U A L A N ===" << endl;

                // validasi id adalah angkat postif
                while (true){
                    cout << "ID Penjualan: "; 
                    if (cin >> id && id >0) break;
                    cin.clear(); // clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
                    cout << "Error: ID harus angka positif!\n" << endl;
                }
                
                // validasi format tanggal
                cout << "Tanggal (DD-MM-YYYY): "; cin >> tgl;

                // validasi nama produk
                do{
                    cout << "Nama Produk: ";
                    cin.ignore(); // clear buffer
                    getline(cin, nama);
                } while (nama.empty());

                // validasi jumlah stok
                for (BahanBaku &b: daftarBahanBaku){
                    if (b.getNamaBahan()==nama){
                        while (true){
                            cout << "Jumlah: ";
                            if(cin >> jumlah && jumlah > 0 && jumlah <= b.getStok()){
                                b.kurangiStok(jumlah); // kurangi stok
                                break; // keluar dari loop jika valid
                            }
                            cin.clear(); // clear error flag
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
                            cout << "Error: Jumlah harus valid dan tidak melebihi stok yang tersedia!\n" << endl;
                        }
                    }
                }

                // validasi harga per unit
                while (true){
                    cout << "Harga per unit: ";
                    if (cin >> harga && harga > 0) break; // pastikan harga positif
                    cin.clear(); // clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
                    cout << "Error: Harga harus angka positif!\n" << endl;
                }

                daftarPenjualan.push_back(ProdukTerjual(id, tgl, nama, jumlah, harga));
                cout << "Penjualan berhasil dicatat!" << endl;
                break;
            }
            case 2: {
                cout << "\n=== Daftar Stok ==="<< endl;
                if (daftarBahanBaku.empty()){
                    cout << "Tidak ada stok tersedia"<< endl;
                } else{
                    for (BahanBaku &b: daftarBahanBaku) {
                        b.displayInfo();
                    }
                }
                break;
            }
            case 3:{
                string keyword;
                cout << "Masukkan nama produk yang dicari: ";
                cin >> keyword;

                for(BahanBaku &b: daftarBahanBaku) {
                    if (b.getNamaBahan().find(keyword) != string::npos) {
                        b.displayInfo();
                    }
                }
                if (!daftarBahanBaku.empty()){
                    cout << "Produk tidak ditemukan." << endl;
                }
                break;
            }
            case 0:{
                cout << "Keluar dari menu kasir." << endl;
                break;
            }
        }
    }   while(choice != 0);
    
}

// void Kasir::lihatStok(){
//     int choice;
//     cout << "\n1. Lihat Semua Stok\n2. Cari Produk\nPilih: ";
//     cin >> choice;

//     if (choice == 1){
//         for (BahanBaku &b: daftarBahanBaku) {
//             b.displayInfo();
//         }
//     } else if (choice == 2) {
//         string keyword;
//         cout << "Nama produk: ";
//         cin >> keyword;
//         for (BahanBaku &b: daftarBahanBaku) {
//             if (b.getNamaBahan().find(keyword) != string::npos) {
//                 b.displayInfo();
//             }
//         }
//     } else {
//         cout << "Pilihan tidak valid." << endl;
//     }
// }
