#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
// #include <rfl/json.hpp>
// #include <rfl.hpp>

class User
{
public:
    // passwd should be less than 20 characters in case of hash collision
    User(std::string name, std::string password);
    std::string &getName();
    int setPassword(std::string password);
    bool checkPassword(std::string password) const;
    // virtual void serialize(std::ostream &os) = 0;
    bool isAdmin;
    int getPasswdHash();
    virtual void printUserInfo() = 0;

    std::string name;
    int passwdHash = 0;
};

class Admin : virtual public User
{
public:
    Admin(std::string name, std::string password);
    // void serialize(std::ostream &os) override;
    //  void setPassword(std::string password) override;
    //  bool checkPassword(std::string password) const override;
    void printUserInfo() override;
};

class Guest : virtual public User
{
public:
    Guest(std::string name, std::string password);
    void printUserInfo() override;
};

// Manage all users

class CustomAdmin : public Admin, public Guest
{
public:
    CustomAdmin(std::string name, std::string password);
    void printUserInfo() override;
};

class UserManager
{
public:
    User *createUser(std::string name, std::string password, bool isAdmin);
    User *createUser(std::string name, int passwordHash, bool isAdmin);
    void deleteUser(User *user);
    // void serializeUser(User *user, std::ostream &os);
    void serializeUsers(std::ostream &os);
    void deserializeUsers(std::istream &is);
    User *getUser(std::string name);

private:
    std::vector<User *> users;
    std::map<std::string, User *> userMap;
};

extern UserManager userManager;
#endif // USER_H