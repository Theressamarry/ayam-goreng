#include "Admin.h"
#include "BahanBaku.h"
#include "GlobalData.h"
#include "ProdukTerjual.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>
#include <map>

using namespace std;

// ==== DEKLARASI FUNGSI UNTUK SAVE DATA KE FILE ====
void saveBahanBakuToFile(); // agar data bahan baku ga ilang walaupun program ditutup

// CONSTRUKTOR ADMIN
Admin::Admin(int id, string uname, string pwd, string idAdmin)
    : User(id, uname, pwd, "Admin"), idAdmin(idAdmin){}

void Admin::manajemenUser(){
    cout << "Admin mengelola user" << endl;
}

// ==== FITUR: MANAGE STOK BahanBaku ====
void Admin::manajemenStok(){
    int choice;
    do{
        cout << "\n+===================================+" << endl;
        cout << "|           MENU ADMIN             |" << endl;
        cout << "+===================================+" << endl;
        cout << "| 1. Tambah Produk                 |" << endl;
        cout << "| 2. Lihat Stok Produk             |" << endl;
        cout << "| 3. Update Stok Produk            |" << endl;
        cout << "| 4. Hapus Produk                  |" << endl;
        cout << "| 5. Cari Produk                   |" << endl;
        cout << "| 0. Keluar                        |" << endl;
        cout << "+===================================+" << endl;
        cout << "Pilih menu: ";
        cin>>choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

        switch(choice){
            case 1:{ // nambah bahan baku
                string nama;
                int id, stok;
                double harga;
                
                id = generateBahanId(); // auto generate id
                cout << "\n---------------------------------------------------------" << endl;
                cout << "                TAMBAH BAHAN BAKU BARU                " << endl;
                cout << "---------------------------------------------------------" << endl;
                cout << " ID Bahan       : " << id << endl;
                cout << "---------------------------------------------------------" << endl;
                cout << " Nama Bahan     : ";
                getline(cin, nama);
                cout << "---------------------------------------------------------" << endl;
                cout << " Stok           : ";
                cin >> stok;
                cin.ignore(); // clear buffer
                cout << "---------------------------------------------------------" << endl;
                cout << " Harga per unit : ";
                cin >> harga;
                cout << "---------------------------------------------------------" << endl;

                daftarBahanBaku.push_back(BahanBaku(id, nama, stok, harga));
                cout << " Bahan Baku berhasil ditambahkan!                      " << endl;
                cout << "---------------------------------------------------------" << endl;

                saveBahanBakuToFile(); // langsung simpan ke file
                break;
            }
            case 2:{ // lihat stok bahan baku
                if(daftarBahanBaku.empty()){
                    cout << "Tidak ada bahan baku tersedia." << endl;
                } else {
                    cout << "\n---------------------------------------------------------" << endl;
                    cout << "| ID  | Nama Produk          | Stok  | Harga/unit        |" << endl;
                    cout << "---------------------------------------------------------" << endl;
                    for (BahanBaku &bahan : daftarBahanBaku) {
                        bahan.displayInfo(); // show info BahanBaku
                    }
                    cout << "+--------------------------------------------------------+" << endl;
                }
                break;
            }
            case 3: { // update stok bahan baku
                string nama;
                int jumlah;

                cout << "\n---------------------------------------------------------" << endl;
                cout << "                UPDATE STOK BAHAN BAKU                " << endl;
                cout << "---------------------------------------------------------" << endl;
                cout << " Nama Bahan     : ";
                getline(cin, nama);
                cout << "---------------------------------------------------------" << endl;
                cout << " Jumlah         : ";
                cin >> jumlah;
                cout << "---------------------------------------------------------" << endl;

                bool found = false;
                for(BahanBaku &bahan: daftarBahanBaku){
                    if(bahan.getnamaBahan() == nama){
                        if(jumlah > 0) {
                            bahan.tambahStok(jumlah);
                            cout << " Stok bahan " << nama << " berhasil ditambahkan!" << endl;
                            cout << " Stok sekarang: " << bahan.getstok() << endl;
                        } else {
                            if(bahan.getstok() >= -jumlah){
                                bahan.kurangiStok(-jumlah);
                                cout << " Stok bahan " << nama << " berhasil dikurangi!" << endl;
                                cout << " Stok sekarang: " << bahan.getstok() << endl;
                            } else {
                                cout << " Error: Stok tidak mencukupi!" << endl;
                            }
                        }
                        cout << "---------------------------------------------------------" << endl;
                        saveBahanBakuToFile(); // simpan file
                        found = true;
                        break;
                    }
                }
                
                if(!found){
                    cout << " Bahan Baku " << nama << " tidak ditemukan!" << endl;
                    cout << "---------------------------------------------------------" << endl;
                }
                break;
            }
            case 4:{ // hapus bahan baku
                string nama;
                cout << "Nama Bahan yang ingin dihapus: "; 
                cin >> nama;

                bool found = false;
                for(auto it = daftarBahanBaku.begin(); it != daftarBahanBaku.end(); ++it){
                    if(it->getnamaBahan() == nama){
                        daftarBahanBaku.erase(it);
                        cout << "Bahan Baku " << nama << " berhasil dihapus!" << endl;
                        saveBahanBakuToFile(); // simpan ke file
                        found = true;
                        break;
                    }
                }
                if(!found){
                    cout << "Bahan Baku " << nama << " tidak ditemukan!" << endl;
                }
                break;
            }
            case 5: { // cari bahan baku
                string keyword;
                cout << "Cari BahanBaku: ";
                cin >> keyword;
                for (BahanBaku &bahan : daftarBahanBaku) {
                    if (bahan.getnamaBahan().find(keyword) != string::npos) {
                        bahan.displayInfo();
                    }
                }
                break;
            }
        }   

    } while (choice != 0);
}

void saveBahanBakuToFile() {
    ofstream file("bahan_baku.txt");
    for (const BahanBaku &bahan : daftarBahanBaku) {
        file << bahan.getidBahan() << ","
             << bahan.getnamaBahan() << ","
             << bahan.getstok() << ","
             << bahan.getharga() << "\n";

    }
    file.close();
}