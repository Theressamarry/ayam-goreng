#include "Admin.h"
#include "BahanBaku.h"
#include "GlobalData.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

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
        cout<< "\n=== M A N A J E M E N T   S T O K ===" << endl;
        cout << " 1. Tambah Bahan Baku\n 2. Lihat Stok\n 3. Update Stok\n 4. hapus Bahan\n 5. cari bahan\n 0. Quit" << endl;
        cout << "Pilih menu: "; 
        cin>>choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer

        switch(choice){
            case 1:{ // nambah bahan baku
                string nama;
                int id, stok;
                double harga;
                
                id = generateBahanId(); // auto generate id
                cout << "ID Bahan: " << id << endl;

                cout<< "Nama Bahan: "; 
                getline(cin, nama);

                cout<< "Stok: "; 
                cin >> stok;
                cin.ignore(); // clear buffer                

                cout << "Harga per unit: ";
                cin >> harga;

                daftarBahanBaku.push_back(BahanBaku(id, nama, stok, harga));
                cout << "Bahan Baku berhasil ditambahkan!" << endl;
                saveBahanBakuToFile(); // langsung simpan ke file
                break;
            }
            case 2:{ // lihat stok bahan baku
                if(daftarBahanBaku.empty()){
                    cout << "Tidak ada bahan baku tersedia." << endl;
                } else {
                    cout << "\n=== Daftar Bahan Baku ===" << endl;
                    for (BahanBaku &bahan : daftarBahanBaku) {
                        bahan.displayInfo(); // show info BahanBaku
                    }
                }
                break;
            }
            case 3:{ //update stok bahan baku
                string nama;
                int jumlah;

                cout<< "Nama Bahan: "; 
                getline(cin, nama); // clear buffer

                cout<< "Jumlah: "; 
                cin >> jumlah;

                bool found = false;
                for(BahanBaku &bahan: daftarBahanBaku){
                    if(bahan.getnamaBahan()== nama){
                        if(jumlah> 0) {
                            bahan.tambahStok(jumlah);
                            cout << "Stok bahan " << nama << " berhasil ditambahkan! Stok sekarang: " << bahan.getstok() << endl;
                        } else {
                            if(bahan.getstok() >= -jumlah){
                                bahan.kurangiStok(-jumlah);
                            cout << "Stok bahan " << nama << " berhasil dikurangi! Stok sekarang: " << bahan.getstok() << endl;
                            } else {
                                cout << "Error: Stok tidak mencukupi!" << endl;
                            }
                        }
                        saveBahanBakuToFile(); //simpan file
                        found = true;
                        break;
                    }
                }
                if(!found){
                    cout << "Bahan Baku " << nama << " tidak ditemukan!" << endl;
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
            case 5: {
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