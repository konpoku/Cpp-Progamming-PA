#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

class User
{
public:
    // passwd should be less than 20 characters in case of hash collision
    User(std::string name, std::string password);
    std::string& getName();
    int setPassword(std::string password);
    bool checkPassword(std::string password) const;
    virtual void serialize(std::ostream &os) = 0;
    bool isAdmin;

private:
    std::string name;
    int passwdHash = 0;
};

class Admin : public User
{
public:
    Admin(std::string name, std::string password);
    void serialize(std::ostream &os) override;
    // void setPassword(std::string password) override;
    // bool checkPassword(std::string password) const override;
};

class Guest : public User
{
public:
    Guest(std::string name, std::string password);
    void serialize(std::ostream &os) override;
    // void setPassword(std::string password) override;
    // bool checkPassword(std::string password) const override;
};

// Manage all users
class UserManager
{
public:
    User *createUser(std::string name, std::string password, bool isAdmin);
    void deleteUser(User *user);
    void serializeUser(User *user, std::ostream &os);
    void serializeUsers(std::vector<User *> users, std::ostream &os);
    User *getUser(std::string name);

private:
    std::vector<User *> users;
    std::map<std::string, User *> userMap;
};


extern UserManager userManager;
#endif // USER_H