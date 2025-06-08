#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Kasir.h"
#include "Admin.h"
#include "GlobalData.h" 

using namespace std;

vector<User*> users; // menyimpan data user

void dataUser(){
    users.push_back(new Admin(1, "admin", "admin123", "ADM01")); // idUser, uname, pwd, idAdmin
    users.push_back(new Kasir(2, "kasir", "kasir123", "KSR01")); // idUser, uname, pwd, idKasir
}

User* authenticate(string username, string password){
    for (User* user : users){
        if (user->login(username, password)){
            return user;
        }
    }
    return nullptr;
}

int main(){
    // load data dari file
    loadBahanBakuFromFile();
    loadPenjualanFromFile();
    loadLastIdFromFile(); 

    dataUser();

    while (true){
        string username, password;
        cout << "=== L O G I N ===" << endl;
        cout << "Username: "; cin >> username;
        cout << "password: "; cin >> password;

        User* logInUser = authenticate(username, password);

        if(logInUser != nullptr){
            cout << "\nLogin berhasil Role: " << logInUser->getRole() << endl;
            
            if(logInUser->getRole()=="Admin"){
                Admin* admin = dynamic_cast<Admin*>(logInUser);
                admin->manajemenUser();
                admin->manajemenStok();
            } else if(logInUser->getRole()=="Kasir"){
                Kasir* kasir = dynamic_cast<Kasir*>(logInUser);
                kasir->kelolaPenjualan();
            }
        } else{
            cout << "Login gagal!" << endl;
        }

        char choice = 'y';
        string input;

        cout << "\nKembali ke login? (y/n): ";
        getline(cin, input);


        // jika user tidak memasukkan input, default ke 'y'
        if (input.empty() || tolower(input[0]) == 'y') {
            // Kembali ke login (default behavior)
        } 
        // jika user input 'n' atau 'N', keluar dari loop
        else if (tolower(input[0]) == 'n') {
            break; // keluar dari loop
        }
        else {
            cout << "Pilihan tidak valid, kembali ke login..." << endl;
        }
    }
    
    // clean memory
    for (User* user : users){
        delete user;
    }

    return 0;
};
