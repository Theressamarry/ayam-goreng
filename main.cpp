#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Kasir.h"
#include "Admin.h"

using namespace std;

vector<User*> users; // menyimpan data user

void dataUser(){
    users.push_back(new Admin(1, "admin", "admin123", "ADM01")); // idUser, uname, pwd, idAdmin
    users.push_back(new Kasir(1, "kasir", "kasir123", "KSR01")); // idUser, uname, pwd, idKasir
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
    dataUser();

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
        } else if(logInUser->getRole()=="Kasir"){
            Kasir* kasir = dynamic_cast<Kasir*>(logInUser);
            kasir->kelolaPenjualan();
        }
    } else{
        cout << "Login gagal!" << endl;
    }

    // clean memory
    for (User* user : users){
        delete user;
    }

    return 0;
};
