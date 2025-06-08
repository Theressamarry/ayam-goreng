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
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

// ==== DEKLARASI FUNGSI UNTUK SAVE DATA KE FILE ====
void savePenjualanToFile(); // deklarasi fungsi untuk menyimpan penjualan ke file
void saveBahanBakuToFile(); // deklarasi fungsi untuk menyimpan bahan baku ke file

// ==== CONSTRUCTOR KASIR ====
Kasir::Kasir(int id, string uname, string pwd, string idKaryawan)
    : User(id, uname, pwd, "Kasir"), idKaryawan(idKaryawan){}

// ==== FITUR: KELOLA PENJUALAN ====
void Kasir::kelolaPenjualan(){
    int choice;
    do{
        cout << "\n=== M E N U K A S I R ==="<< endl;
        cout << " 1. Catat Penjualan\n 2. Lihat Semua Stok\n 3. Cari Produk\n 0. Quit\n" << endl;
        cout << "Pilih: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        switch(choice){
            case 1: { // catat penjualan
                int id, jumlah;
                string tgl, nama;
                double harga;

                cout << "\n=== C A T A T  P E N J U A L A N ===" << endl;

                // generate id auto
                id = generatePenjualanId();
                cout << "ID Penjualan: " << id << endl;

                // ambil tanggal today
                time_t now = time(0);
                tm *ltm = localtime(&now);
                char buffer[17]; // untuk format DD-MM-YYYY
                strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", ltm);
                tgl = buffer; // set tanggal ke hari ini

                cout << "Tanggal: " << tgl << endl;

                double totalHarga =0;
                while(true){
                    string nama;

                    // nama produk
                    cout << "Nama Produk: "; // tpi klo enter, bakalan keluar dari loop
                    getline(cin, nama); // clear buffer

                    if (nama.empty()) break; // keluar jika user enter

                    bool found = false;
                    for (auto &bahan:daftarBahanBaku){
                        if (bahan.getnamaBahan()==nama){
                            if (bahan.getstok()==0) { // cek stok
                                cout << "Stok produk " << nama << " habis. Silakan pilih produk lain." << endl;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
                                return; // keluar dari loop
                            }

                            // validasi jumlah stok
                            cout << "Jumlah: ";
                            while (!(cin >> jumlah) || jumlah <= 0 || jumlah > bahan.getstok()) {
                            cout << "Jumlah tidak valid. Silakan coba lagi: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            double subTotal = jumlah * bahan.getharga();
                            cout << "Subtotal: Rp" << jumlah << " x Rp" << bahan.getharga() << " = Rp" << subTotal << endl;

                            // kurangi stok dan save penjualan
                            bahan.kurangiStok(jumlah); // kurangi stok
                            daftarPenjualan.push_back(ProdukTerjual(id, tgl, nama, jumlah, bahan.getharga()));
                            totalHarga += subTotal; // tambahkan ke total harga
                            
                            savePenjualanToFile();
                            saveBahanBakuToFile();
                            found = true; // set flag true jika produk ditemukan
                            break;
                        }
                    } if(!found){
                        cout << "Produk tidak ditemukan. Silakan coba lagi." << endl;
                    }
                }
                cout << "Total Belanja: Rp" << totalHarga << endl;
                savePenjualanToFile(); // simpan ke file
                saveBahanBakuToFile(); // simpan stok ke file
                cout << "Penjualan berhasil dicatat!" << endl;
                break;
            }
            case 2: { // lihat semua stok
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
            case 3:{ // cari produk
                string keyword;
                cout << "Masukkan nama produk yang dicari: ";
                cin >> keyword;

                bool found = false;
                for(BahanBaku&b: daftarBahanBaku) {
                    if (b.getnamaBahan().find(keyword) != string::npos) {
                        b.displayInfo();
                        found = true;
                    }
                }
                if (!found){
                    cout << "Produk tidak ditemukan." << endl;
                }
                break;
            }
            case 0:{ // keluar dari menu kasir
                savePenjualanToFile(); // simpan penjualan sebelum keluar
                saveBahanBakuToFile(); // simpan stok sebelum keluar
                cout << "Keluar dari menu kasir." << endl;
                break;
            }
        }
    }   while(choice != 0);
    
}

// ==== FUNGSI UNTUK SIMPAN KE FILE ====
void savePenjualanToFile() {
    ofstream file("penjualan.txt");
    for (const ProdukTerjual& p : daftarPenjualan) {
        file << p.getidPenjualan() << ","
             << p.gettanggal() << ","
             << p.getnamaProduk() << ","
             << p.getjumlah() << ","
             << p.getharga() << "\n";
    }
    file.close();
}
