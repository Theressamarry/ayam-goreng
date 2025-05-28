#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User{
protected:
    int idUser;
    string username;
    string password;
    string role; // admin atau kasir

public:
    // constructor
    User(int id, string uname, string pwd, string r);

    // methode
    bool login(string uname, string pwd);
    void displayInfo();
    string getRole();
};

#endif