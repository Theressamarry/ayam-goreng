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

void savePenjualanToFile(); // deklarasi fungsi untuk menyimpan penjualan ke file

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

                // ambil tanggal today
                time_t now = time(0);
                tm *ltm = localtime(&now);

                char buffer[17]; // untuk format DD-MM-YYYY
                strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M", ltm);
                tgl = buffer; // set tanggal ke hari ini

                cout << "Tanggal: " << tgl << endl;

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
                savePenjualanToFile(); // simpan ke file
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
