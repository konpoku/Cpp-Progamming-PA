#include "ui.h"
// TODO: 清理屏幕
UI::UI()
{
    currentUser = nullptr;
}

void UI::welcome()
{
    std::cout << "欢迎使用车辆管理系统" << std::endl;
}

bool UI::login()
{
    std::string name, password;
    std::cout << "请输入用户名: ";
    std::cin >> name;
    User *user = userManager.getUser(name);
    if (user == nullptr)
    {
        std::cout << "用户不存在" << std::endl;
        return false;
    }
    std::cout << "请输入密码: ";
    std::cin >> password;
    if (user->checkPassword(password))
    {
        currentUser = user;
        std::cout << "登陆成功" << std::endl;
        std::cout << "当前权限：";
        if (user->isAdmin)
        {
            std::cout<<"管理员"<<std::endl;
        }
        else
        {
            std::cout<<"普通用户"<<std::endl;
        }
        return true;
    }
    else
    {
        std::cout << "密码错误" << std::endl;
        return false;
    }
}

bool UI::registerUser()
{
    std::string name, passwordFirst, passwordSecond;
    std::cout << "请输入用户名: ";
    std::cin >> name;
    if (userManager.getUser(name) != nullptr)
    {
        std::cout << "用户已存在" << std::endl;
        return false;
    }
    std::cout << "请输入密码: ";
    std::cin >> passwordFirst;
    std::cout << "请再次输入密码: ";
    std::cin >> passwordSecond;
    if (passwordFirst != passwordSecond)
    {
        std::cout << "两次输入密码不一致" << std::endl;
        return false;
    }
    User *user = userManager.createUser(name, passwordFirst, false);
    userManager.createUser(name, passwordFirst, false);
    currentUser = user;
    std::cout << "注册成功" << std::endl;
    return true;
}

void UI::logout()
{
    currentUser = nullptr;
    std::cout << "登出成功" << std::endl;
}
void UI::guestUI()
{
    // TODO: Wait for carDB to be implemented
    while (true)
    {
        std::cout << "1. 登出" << std::endl;
        std::cout << "2. 退出" << std::endl;
        std::cout << "请输入: ";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            logout();
            break;
        }
        else if (choice == 2)
        {
            exit(0);
        }
        else
        {
            std::cout << "非法输入" << std::endl;
        }
    }
}

void UI::adminUI()
{
    // TODO: Wait for carDB to be implemented
    while (true)
    {
        std::cout << "1. 登出" << std::endl;
        std::cout << "2. 退出" << std::endl;
        std::cout << "请输入: ";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            logout();
            break;
        }
        else if (choice == 2)
        {
            exit(0);
        }
        else
        {
            std::cout << "非法输入" << std::endl;
        }
    }
}

void UI::controller()
{
    welcome();
    while (true)
    {
        if (isLoggedIn && currentUser != nullptr)
        {
            currentUser->isAdmin ? adminUI() : guestUI();
        }
        else
        {
            std::cout << "1. 登陆" << std::endl;
            std::cout << "2. 注册" << std::endl;
            std::cout << "3. 退出" << std::endl;
            std::cout << "请输入: ";
            int choice;
            std::cin >> choice;
            if (choice == 1)
            {
                if (login())
                {
                    isLoggedIn = true;
                }
            }
            else if (choice == 2)
            {
                if (registerUser())
                {
                    isLoggedIn = true;
                }
            }
            else if (choice == 3)
            {
                break;
            }
            else
            {
                std::cout << "非法输入" << std::endl;
            }
        }
    }
}