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
        cout << "\n+===================================+" << endl;
        cout << "|           MENU KASIR             |" << endl;
        cout << "+===================================+" << endl;
        cout << "| 1. Catat Penjualan               |" << endl;
        cout << "| 2. Lihat Semua Stok              |" << endl;
        cout << "| 3. Cari Produk                   |" << endl;
        cout << "| 4. Laporan Penjualan             |" << endl;
        cout << "| 0. Keluar                        |" << endl;
        cout << "+===================================+" << endl;
        cout << " Pilih menu: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer

        switch(choice){
            case 1: { // catat penjualan
                int id, jumlah;
                string tgl, nama;
                double harga;

                cout << "\n---------------------------------------------------------" << endl;
                cout << "                CATAT PENJUALAN                     " << endl;
                cout << "---------------------------------------------------------" << endl;

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
                cout << "---------------------------------------------------------" << endl;

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
                            if (bahan.getstok() == 0) {
                                cout << "---------------------------------------------------------" << endl;
                                cout << " Stok produk " << nama << " habis. Silakan pilih produk lain." << endl;
                                cout << "---------------------------------------------------------" << endl;
                                continue; // keluar dari loop
                            }
                            cout << " Stok tersedia: " << bahan.getstok() << endl;
                            cout << " Harga satuan : Rp" << bahan.getharga() << endl;
                            cout << "---------------------------------------------------------" << endl;
                            cout << " Jumlah       : ";
                            
                            while (!(cin >> jumlah) || jumlah <= 0 || jumlah > bahan.getstok()) {
                                cout << "---------------------------------------------------------" << endl;
                                cout << " Jumlah tidak valid. Silakan coba lagi: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            double subTotal = jumlah * bahan.getharga();
                            cout << "---------------------------------------------------------" << endl;
                            cout << " Subtotal     : Rp" << jumlah << " x Rp" << bahan.getharga() 
                                << " = Rp" << subTotal << endl;
                            cout << "---------------------------------------------------------" << endl;

                            bahan.kurangiStok(jumlah);
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
                cout << " TOTAL BELANJA: Rp" << totalHarga << endl;
                cout << "---------------------------------------------------------" << endl;
                cout << " Penjualan berhasil dicatat!" << endl;
                cout << "---------------------------------------------------------" << endl;

                savePenjualanToFile(); // simpan ke file
                saveBahanBakuToFile(); // simpan stok ke file
                break;
            }
            case 2: { // lihat semua stok
                cout << "\n+--------------------------------------------------------+" << endl;
                cout << "| ID  | Nama Produk          | Stok  | Harga/unit        |" << endl;
                cout << "+--------------------------------------------------------+" << endl;
                if (daftarBahanBaku.empty()){
                    cout << "Tidak ada stok tersedia"<< endl;
                } else{
                    for (BahanBaku &b: daftarBahanBaku) {
                        b.displayInfo();
                    }
                }
                cout << "+--------------------------------------------------------+" << endl;
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
            case 4:{ // laporan penjualan
                cout << "\n---------------------------------------------------------" << endl;
                cout << "                LAPORAN PENJUALAN                   " << endl;
                cout << "---------------------------------------------------------" << endl;
                if (daftarPenjualan.empty()) {
                    cout << "Belum ada data penjualan." << endl;
                    return;
                }

                cout << "| ID    | Tanggal           | Produk          | Jml | Total    |" << endl;
                cout << "---------------------------------------------------------" << endl;
                
                // Tampilkan semua penjualan
                for (auto& penjualan : daftarPenjualan) {
                    penjualan.displayInfo();
                }
                
                // Hitung total pendapatan
                double total = 0;
                for (auto& penjualan : daftarPenjualan) {
                    total += penjualan.getharga() * penjualan.getjumlah();
                }
                cout << "---------------------------------------------------------" << endl;
                cout << " TOTAL PENDAPATAN: Rp" << total << endl;
                cout << "---------------------------------------------------------" << endl;
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
    for (auto& p : daftarPenjualan) {
        file << p.getidPenjualan() << ","
             << p.gettanggal() << ","
             << p.getnamaProduk() << ","
             << p.getjumlah() << ","
             << p.getharga() << "\n";
    }
    file.close();
}
