#include "Admin.h"
#include "BahanBaku.h"
#include "GlobalData.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

void saveBahanBakuToFile(); // deklarasi fungsi untuk menyimpan bahan baku ke file

Admin::Admin(int id, string uname, string pwd, string idAdmin)
    : User(id, uname, pwd, "Admin"), idAdmin(idAdmin){}

void Admin::manajemenUser(){
    cout << "Admin mengelola user" << endl;
}

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
                
                // generate id auto
                id = generateBahanId();
                cout << "ID Bahan: " << id << endl;
                // cin.ignore(); // clear buffer

                cout<< "Nama Bahan: "; 
                getline(cin, nama);

                cout<< "Stok: "; 
                cin >> stok;

                daftarBahanBaku.push_back(BahanBaku(id, nama, stok));
                cout << "Bahan Baku berhasil ditambahkan!" << endl;
                saveBahanBakuToFile(); // simpan ke file
                break;
            }
            case 2:{ // lihat stok bahan baku
                if(daftarBahanBaku.empty()){
                    cout << "Tidak ada bahan baku tersedia." << endl;
                } else {
                    cout << "\n=== Daftar Bahan Baku ===" << endl;
                    for (BahanBaku &bahan : daftarBahanBaku) {
                        bahan.displayInfo();
                    }
                }
                break;
            }
            case 3:{ //update stok bahan baku
                string nama;
                int jumlah;

                cout<< "Nama Bahan: "; 
                cin >> nama;
                cin.ignore(); // clear buffer

                cout<< "Jumlah: "; 
                cin >> jumlah;

                for(BahanBaku &bahan: daftarBahanBaku){
                    if(bahan.getnamaBahan()== nama){
                        if(jumlah> 0) {
                            bahan.tambahStok(jumlah);
                        } else {
                            bahan.kurangiStok(-jumlah);
                        }
                        cout << "Stok bahan " << nama << " berhasil diupdate!" << endl;
                        saveBahanBakuToFile(); // simpan ke file
                    }
                }
                break;
            }
            case 4:{ // hapus bahan baku
                string nama;
                cout << "Nama Bahan yang ingin dihapus: "; 
                cin >> nama;

                for(auto it = daftarBahanBaku.begin(); it != daftarBahanBaku.end(); ++it){
                    if(it->getnamaBahan() == nama){
                        daftarBahanBaku.erase(it);
                        cout << "Bahan Baku " << nama << " berhasil dihapus!" << endl;
                        saveBahanBakuToFile(); // simpan ke file
                        break;
                    }
                }
                break;
            }
            case 5: {
                string keyword;
                cout << "Cari produk: ";
                cin >> keyword;
                for (BahanBaku &bahan : daftarBahanBaku) {
                    if (bahan.getnamaBahan().find(keyword) != string::npos) {
                        bahan.displayInfo();
                    }
                }
            }
        }   

    } while (choice != 0);
}


void saveBahanBakuToFile() {
    ofstream file("bahan_baku.txt");
    for (const BahanBaku &bahan : daftarBahanBaku) {
        file << bahan.getidBahan() << ","
             << bahan.getnamaBahan() << ","
             << bahan.getstok() << "\n";
    }
    file.close();
}