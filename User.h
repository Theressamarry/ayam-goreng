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
    virtual ~User();

    // methode
    void displayInfo();
    bool login(string uname, string pwd);
    string getRole();
};

#endif