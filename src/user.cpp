#include "user.h"
#include <rfl/json.hpp>
#include <rfl.hpp>
typedef struct
{
    std::string name;
    int passwdHash;
    bool isAdmin;
} UserJson;
User::User(std::string name, std::string password) : name(name)
{
    if (setPassword(password) < 0)
    {
        std::cout << "密码太长，请不要多于20个字符" << std::endl;
    }
}
int User::setPassword(std::string password)
{
    passwdHash = 0;
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

int User::getPasswdHash()
{
    return passwdHash;
}

Admin::Admin(std::string name, std::string password) : User(name, password)
{
    isAdmin = true;
}

void Admin::printUserInfo()
{
    std::cout << "用户名：" << name << std::endl;
    std::cout << "用户类型：管理员" << std::endl;
}

Guest::Guest(std::string name, std::string password) : User(name, password)
{
    isAdmin = false;
}

void Guest::printUserInfo()
{
    std::cout << "用户名：" << name << std::endl;
    std::cout << "用户类型：普通用户" << std::endl;
}

User *UserManager::createUser(std::string name, std::string password, bool isAdmin)
{
    User *newUser;
    if (isAdmin)
    {
        newUser = new CustomAdmin(name, password);
    }
    else
    {
        newUser = new Guest(name, password);
    }
    users.push_back(newUser);
    userMap.emplace(name, newUser);
    return newUser;
}

User *UserManager::createUser(std::string name, int passwordHash, bool isAdmin)
{
    User *newUser;
    if (isAdmin)
    {
        newUser = new CustomAdmin(name, "");
    }
    else
    {
        newUser = new Guest(name, "");
    }
    newUser->passwdHash = passwordHash;
    users.push_back(newUser);
    userMap.emplace(name, newUser);
    //carManager.userCarsList.emplace(name, std::vector<Car *>());//bug: 反复引用
    return newUser;
}

std::string &User::getName()
{
    return name;
}

void UserManager::deleteUser(User *user)
{
    delete user;
    users.erase(std::find(users.begin(), users.end(), user));
    userMap.erase(user->getName());
}
//void UserManager::serializeUser(User *user, std::ostream &os)
//{
    //user->serialize(os);
//}
void UserManager::serializeUsers(std::ostream &os)
{
    os.clear();
    std::vector<UserJson> userJsons;
    for (auto user : users)
    {
        UserJson DOM;
        DOM.name = user->getName();
        DOM.passwdHash = user->getPasswdHash();
        DOM.isAdmin = user->isAdmin;
        userJsons.push_back(DOM);
    }
    const std::string json_string = rfl::json::write(userJsons);
    os << json_string << std::endl;
}
void UserManager::deserializeUsers(std::istream &is)
{
    std::string json_string;
    is >> json_string;
    auto userJsons = rfl::json::read<std::vector<UserJson>>(json_string).value();
    for (auto userJson : userJsons)
    {
        if (userJson.isAdmin)
        {
            createUser(userJson.name, userJson.passwdHash, true);
        }
        else
        {
            createUser(userJson.name, userJson.passwdHash, false);
        }
    }
}
User *UserManager::getUser(std::string name)
{
    if (userMap.find(name) != userMap.end())
        return userMap[name];
    else
        return nullptr;
}

//void Admin::serialize(std::ostream &os)
//{
//    UserJson DOM;
//    DOM.name = name;
//    DOM.passwdHash = passwdHash;
//    DOM.isAdmin = true;
//    const std::string json_string = rfl::json::write(DOM);
//    os << json_string << std::endl;
//}
//void Guest::serialize(std::ostream &os)
//{
//    UserJson DOM;
//    DOM.name = name;
//    DOM.passwdHash = passwdHash;
//    DOM.isAdmin = false;
//    const std::string json_string = rfl::json::write(DOM);
//    os << json_string << std::endl;
//}

CustomAdmin::CustomAdmin(std::string name, std::string password) : Admin(name, password), Guest(name, password) , User(name, password)
{
    isAdmin = true;
}

void CustomAdmin::printUserInfo()
{
    std::cout << "用户名：" << name << std::endl;
    std::cout << "用户类型：管理员住户" << std::endl;
}
