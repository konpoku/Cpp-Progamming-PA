#include "user.h"
User::User(std::string name, std::string password) : name(name)
{
    if(setPassword(password) < 0)
    {
        std::cout<<"密码太长，请不要多于20个字符"<<std::endl;
    }
}
int User::setPassword(std::string password)
{
    if (password.length() > 20)
    {
        return -1;
    }
    
    for (auto c : password)
    {
        passwdHash += c;
    }
    passwdHash *= passwdHash;
    passwdHash %= 998244353;
    passwdHash += 1;
    passwdHash *= passwdHash;
    passwdHash %= 998244353;
    return passwdHash;
}
bool User::checkPassword(std::string password) const
{
    int hash = 0;
    for (auto c : password)
    {
        hash += c;
    }
    hash *= hash;
    hash %= 998244353;
    hash += 1;
    hash *= hash;
    hash %= 998244353;
    return hash == passwdHash;
}

Admin::Admin(std::string name, std::string password) : User(name, password)
{
    isAdmin = true;
}

Guest::Guest(std::string name, std::string password) : User(name, password)
{
    isAdmin = false;
}

User *UserManager::createUser(std::string name, std::string password, bool isAdmin)
{
    User *newUser;
    if (isAdmin)
    {
        newUser = new Admin(name, password);
    }
    else
    {
        newUser = new Guest(name, password);
    }
    users.push_back(newUser);
    userMap.emplace(name, newUser);
    return newUser;
}

std::string& User::getName()
{
    return name;
}

void UserManager::deleteUser(User *user)
{
    delete user;
    users.erase(std::find(users.begin(),users.end(),user));
    userMap.erase(user->getName());
}
void UserManager::serializeUser(User *user, std::ostream &os)
{
    user->serialize(os);
}
void UserManager::serializeUsers(std::vector<User *> users, std::ostream &os)
{
    for (auto user : users)
    {
        serializeUser(user, os);
    }
}
User *UserManager::getUser(std::string name)
{
    if (userMap.find(name) != userMap.end())
        return userMap[name];
    else
        return nullptr;
}

void Admin::serialize(std::ostream &os)
{
    // TODO:implement
}
void Guest::serialize(std::ostream &os)
{
    // TODO:implement
}

