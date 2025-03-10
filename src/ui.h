#ifndef UI_H
#define UI_H
#include "user.h"
#include "carDB.h"
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
class UI
{
public:
    UI();
    void controller();
    void welcome();
    bool login();
    void guestUI();
    void adminUI();
    void customAdminUI();
    bool registerUser();
    void changePassword();
    void logout();
    void printUserCars();
    void printCars();
    void addCar(); // TODO:添加车辆时进行格式检查
    void deleteCar();
    void searchCar();
    void addUserCar();
    void modifyCar();
    void modifyUserCar();
    void deleteUserCar();
    void printSingleCar(Car *car);
    void quit();
    UserManager* currUserManager;
    User *currentUser = NULL;
    bool isLoggedIn;
    bool isUIActive;
    bool isAdmin;
    bool isGuest;
    
};
extern CarManager carManager;
extern UserManager userManager;
#endif