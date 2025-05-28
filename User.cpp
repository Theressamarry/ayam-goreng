#include "User.h"
#include <iostream>
using namespace std;

User::User(int id, string uname, string pwd, string r)
    : idUser(id), username (uname), password(pwd), role(r){}

bool User::login(string uname, string pwd){
    return (username == uname && password == pwd);
} 

void User::displayInfo(){
    cout << "ID: " << idUser << "\nUsername: " << username << "\nRole" << role << endl;
}

string User::getRole(){
    return role;
}

User::~User(){
    
}