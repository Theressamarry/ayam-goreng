#include "Admin.h"
#include "BahanBaku.h"
#include <iostream>
#include <vector>

using namespace std;

vector<BahanBaku> daftarBahanBaku; // menyimpan data bahan baku

Admin::Admin(int id, string uname, string pwd, string idAdmin)
    : User(id, uname, pwd, "Admin"), idAdmin(idAdmin){}

void Admin::manajemenUser(){
    cout << "Admin mengelola user" << endl;
}

void Admin::manajemenStok(){
    int choice;
    do{
        cout<< "=== M A N A J E M E N T   S T O K ===" << endl;
        cout << "1. Tambah Bahan Baku\n 2. Lihat Stok\n 3. Update Stok\n 4. hapus Bahan\n 0. Quit" << endl;
        cout << "Pilih menu: "; cin>>choice;

        switch(choice){
            case 1:{ // nambah bahan baku
                string nama;
                int id, stok;

                cout<< "ID Bahan: "; cin >> id;
                cout<< "Nama Bahan: "; cin >> nama;
                cout<< "Stok: "; cin >> stok;
                daftarBahanBaku.push_back(BahanBaku(id, nama, stok));
                cout << "Bahan Baku berhasil ditambahkan!" << endl;
                break;
            }
            case 2:{ // lihat stok bahan baku
                for (BahanBaku &bahan : daftarBahanBaku) {
                    bahan.displayInfo();
                }
                break;
            }
            case 3:{ //update stok bahan baku
                string nama;
                int jumlah;

                cout<< "Nama Bahan: "; cin >> nama;
                cout<< "Jumlah: "; cin >> jumlah;
                for(BahanBaku &bahan: daftarBahanBaku){
                    if(bahan.getNamaBahan()== nama){
                        if(jumlah>0) bahan.tambahStok(jumlah);
                        else bahan.kurangiStok(-jumlah);
                        cout << "Stok bahan " << nama << " berhasil diupdate!" << endl;
                    }
                }
                break;
            }
        }   

    } while (choice != 0);
    cout << "Admin mengelola stok" << endl;
}
