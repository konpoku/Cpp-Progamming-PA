#ifndef UI_H
#define UI_H
#include"user.h"
#include"carDB.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
class UI{
public:
    UI();
    void controller();
    void welcome();
    bool login();
    void guestUI();
    void adminUI();
    bool registerUser();
    void logout();
private:
    //UserManager* userManager;
    User* currentUser = NULL;
    bool isLoggedIn;
};


#endif