#include "ui.h"
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
            std::cout << "管理员" << std::endl;
        }
        else
        {
            std::cout << "普通用户" << std::endl;
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
    currentUser = user;
    std::cout << "注册成功" << std::endl;
    return true;
}

void UI::changePassword()
{
    std::string passwordFirst, passwordSecond;
    std::cout << "请输入新密码: ";
    std::cin >> passwordFirst;
    std::cout << "请再次输入新密码: ";
    std::cin >> passwordSecond;
    if (passwordFirst != passwordSecond)
    {
        std::cout << "两次输入密码不一致" << std::endl;
        return;
    }
    currentUser->setPassword(passwordFirst);
    std::cout << "修改成功" << std::endl;
}

void UI::logout()
{
    currentUser = nullptr;
    std::cout << "登出成功" << std::endl;
}
void UI::printUserCars()
{
    const std::string &name = currentUser->getName();
    std::vector<Car *> &cars = carManager.getUserCars(currentUser);
    int index = 1;
    std::cout << "共有" << cars.size() << "辆车" << std::endl;
    for (auto car : cars)
    {
        std::cout << index << ". ";
        std::cout << "车牌号: " << car->plate << std::endl;
        // std::cout << "车辆类型: " << car->type << std::endl;
        // std::cout << "车辆年份: " << car->year << std::endl;
        // std::cout << "车辆颜色: " << car->color << std::endl;
    }
    int choice = -1;
    if (cars.size() == 0)
    {
        return;
    }
    while (choice != 0)
    {
        std::cout << "请输入要查看的车辆序号" << std::endl;
        std::cout << "输入0返回上一级" << std::endl;
        std::cin >> choice;
        if (choice > 0 && choice <= cars.size())
        {
            printSingleCar(cars[choice - 1]);
        }
        else if (choice != 0)
        {
            std::cout << "非法输入" << std::endl;
        }
    }
}
void UI::printCars()
{
    const std::vector<Car *> &cars = carManager.cars;
    int index = 1;
    std::cout << "共有" << cars.size() << "辆车" << std::endl;
    for (auto car : cars)
    {
        std::cout << index << ". ";
        std::cout << "车牌号: " << car->plate << std::endl;
        // std::cout << "车辆类型: " << car->type << std::endl;
        // std::cout << "车辆年份: " << car->year << std::endl;
        // std::cout << "车辆颜色: " << car->color << std::endl;
    }
    int choice = -1;
    if (cars.size() == 0)
    {
        return;
    }
    while (choice != 0)
    {
        std::cout << "请输入要查看的车辆序号" << std::endl;
        std::cout << "输入0返回上一级" << std::endl;
        std::cin >> choice;
        if (choice > 0 && choice <= cars.size())
        {
            printSingleCar(cars[choice - 1]);
        }
        else if (choice != 0)
        {
            std::cout << "非法输入" << std::endl;
        }
    }
}
void checkPlate(const std::string &plate)
{
    for (auto c : plate)
    {
        if (!(c >= '0' && c <= '9' || c >= 'A' && c <= 'Z'))
        {
            std::cout << "车牌号非法" << std::endl;
            return;
        }
    }
}
void UI::addCar()
{
    std::string plate, owner;
    int year;
    CarType type;
    Color color;
    std::cout << "请输入车牌号: ";
    std::cin >> plate;
    checkPlate(plate);
    if (carManager.findCarByPlate(plate) != nullptr)
    {
        std::cout << "车牌号已存在" << std::endl;
        return;
    }
    std::cout << "请输入车辆主人: ";
    std::cin >> owner;
    if (userManager.getUser(owner) == nullptr)
    {
        std::cout << "该用户不存在" << std::endl;
        return;
    }
    std::cout << "请输入车辆年份: ";
    std::cin >> year;
    std::cout << "请输入车辆类型: " << std::endl;
    std::cout << "1. 宝牛" << std::endl;
    std::cout << "2. 比非迪" << std::endl;
    std::cout << "3. 奔跑" << std::endl;
    std::cout << "4. 标至" << std::endl;
    std::cout << "5. 有刺无刺牌超级跑车" << std::endl;
    std::cout << "6. 小众" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        type = BaoNiu;
        break;
    case 2:
        type = BiFeiDi;
        break;
    case 3:
        type = BenPao;
        break;
    case 4:
        type = BiaoZhi;
        break;
    case 5:
        type = TogeToge;
        break;
    case 6:
        type = XiaoZhong;
        break;
    default:
        std::cout << "非法输入" << std::endl;
        return;
    }
    std::cout << "请输入车辆颜色: " << std::endl;
    std::cout << "1. 红色" << std::endl;
    std::cout << "2. 蓝色" << std::endl;
    std::cout << "3. 绿色" << std::endl;
    std::cout << "4. 黄色" << std::endl;
    std::cout << "5. 黑色" << std::endl;
    std::cout << "6. 白色" << std::endl;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        color = Red;
        break;
    case 2:
        color = Blue;
        break;
    case 3:
        color = Green;
        break;
    case 4:
        color = Yellow;
        break;
    case 5:
        color = Black;
        break;
    case 6:
        color = White;
        break;
    default:
        std::cout << "非法输入" << std::endl;
        return;
    }
    carManager.addCar(plate, owner, type, year, color);
    std::cout << "添加成功" << std::endl;
}

void UI::deleteCar()
{
    std::vector<Car *> &cars = carManager.cars;
    std::string plate;
    int index = 1;
    std::cout << "共有" << cars.size() << "辆车" << std::endl;
    if (cars.size() == 0)
    {
        return;
    }
    for (auto car : cars)
    {
        std::cout << index << ". ";
        std::cout << "车牌号: " << car->plate << std::endl;
        // std::cout << "车辆类型: " << car->type << std::endl;
        // std::cout << "车辆年份: " << car->year << std::endl;
        // std::cout << "车辆颜色: " << car->color << std::endl;
    }
    std::cout << "请输入要删除的车牌号: ";
    std::cin >> plate;
    if (carManager.deleteCar(plate) == true)
    {
        std::cout << "删除成功" << std::endl;
    }
    else
    {
        std::cout << "删除失败" << std::endl;
    }
}
void UI::searchCar()
{

    // std::string plate;
    // std::cout << "请输入车牌号: ";
    // std::cin >> plate;
    // Car *car = carManager.findCarByPlate(plate);
    // if (car == nullptr)
    //{
    //     std::cout << "未找到车辆" << std::endl;
    // }
    // else
    //{
    //     printSingleCar(car);
    //     std::cout << "车牌号: " << car->plate << std::endl;
    //     std::cout << "车辆主人: " << car->owner << std::endl;
    //     std::cout << "车辆类型: " << car->type << std::endl;
    //     std::cout << "车辆年份: " << car->year << std::endl;
    //     std::cout << "车辆颜色: " << car->color << std::endl;
    // }
    std::cout << "请选择查询方式" << std::endl;
    std::cout << "1.按车牌号查询" << std::endl;
    std::cout << "2.按车辆类型和颜色查询" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == 1)
    {
        std::string plate;
        std::cout << "请输入车牌号: ";
        std::cin >> plate;
        Car *car = carManager.findCarByPlate(plate);
        if (car == nullptr)
        {
            std::cout << "未找到车辆" << std::endl;
        }
        else
        {
            printSingleCar(car);
        }
    }
    else if (choice == 2)
    {
        std::cout << "请输入车辆类型: " << std::endl;
        std::cout << "1. 宝牛" << std::endl;
        std::cout << "2. 比非迪" << std::endl;
        std::cout << "3. 奔跑" << std::endl;
        std::cout << "4. 标至" << std::endl;
        std::cout << "5. 有刺无刺牌超级跑车" << std::endl;
        std::cout << "6. 小众" << std::endl;
        int choice;
        std::cin >> choice;
        CarType type;
        switch (choice)
        {
        case 1:
            type = BaoNiu;
            break;
        case 2:
            type = BiFeiDi;
            break;
        case 3:
            type = BenPao;
            break;
        case 4:
            type = BiaoZhi;
            break;
        case 5:
            type = TogeToge;
            break;
        case 6:
            type = XiaoZhong;
            break;
        default:
            std::cout << "非法输入" << std::endl;
            return;
        }
        std::cout << "请输入车辆颜色: " << std::endl;
        std::cout << "1. 红色" << std::endl;
        std::cout << "2. 蓝色" << std::endl;
        std::cout << "3. 绿色" << std::endl;
        std::cout << "4. 黄色" << std::endl;
        std::cout << "5. 黑色" << std::endl;
        std::cout << "6. 白色" << std::endl;
        std::cin >> choice;
        Color color;
        switch (choice)
        {
        case 1:
            color = Red;
            break;
        case 2:
            color = Blue;
            break;
        case 3:
            color = Green;
            break;
        case 4:
            color = Yellow;
            break;
        case 5:
            color = Black;
            break;
        case 6:
            color = White;
            break;
        default:
            std::cout << "非法输入" << std::endl;
            return;
        }
        std::vector<Car *> cars;
        carManager.findCarByTypeAndColor(type, color, cars);
        if (cars.size() == 0)
        {
            std::cout << "未找到车辆" << std::endl;
        }
        else
        {
            for (auto car : cars)
            {
                printSingleCar(car);
            }
        }
    }
}
void UI::addUserCar()
{
    std::string plate, owner;
    int year;
    CarType type;
    Color color;
    std::cout << "请输入车牌号: ";
    std::cin >> plate;
    checkPlate(plate);
    if (carManager.findCarByPlate(plate) != nullptr)
    {
        std::cout << "车牌号已存在" << std::endl;
        return;
    }
    std::cout << "请输入车辆年份: ";
    std::cin >> year;
    std::cout << "请输入车辆类型: " << std::endl;
    std::cout << "1. 宝牛" << std::endl;
    std::cout << "2. 比非迪" << std::endl;
    std::cout << "3. 奔跑" << std::endl;
    std::cout << "4. 标至" << std::endl;
    std::cout << "5. 有刺无刺牌超级跑车" << std::endl;
    std::cout << "6. 小众" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        type = BaoNiu;
        break;
    case 2:
        type = BiFeiDi;
        break;
    case 3:
        type = BenPao;
        break;
    case 4:
        type = BiaoZhi;
        break;
    case 5:
        type = TogeToge;
        break;
    case 6:
        type = XiaoZhong;
        break;
    default:
        std::cout << "非法输入" << std::endl;
        return;
    }
    std::cout << "请输入车辆颜色: " << std::endl;
    std::cout << "1. 红色" << std::endl;
    std::cout << "2. 蓝色" << std::endl;
    std::cout << "3. 绿色" << std::endl;
    std::cout << "4. 黄色" << std::endl;
    std::cout << "5. 黑色" << std::endl;
    std::cout << "6. 白色" << std::endl;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        color = Red;
        break;
    case 2:
        color = Blue;
        break;
    case 3:
        color = Green;
        break;
    case 4:
        color = Yellow;
        break;
    case 5:
        color = Black;
        break;
    case 6:
        color = White;
        break;
    default:
        std::cout << "非法输入" << std::endl;
        return;
    }
    carManager.addCar(plate, currentUser->getName(), type, year, color);
    std::cout << "添加成功" << std::endl;
}
void UI::modifyCar()
{
    std::vector<Car *> *cars;
    if (currentUser->isAdmin)
    {
        cars = &carManager.cars;
    }
    else
    {
        cars = &carManager.getUserCars(currentUser);
    }
    std::string plate;
    int index = 1;
    std::cout << "共有" << cars->size() << "辆车" << std::endl;
    if (cars->size() == 0)
    {
        return;
    }
    for (auto car : *cars)
    {
        std::cout << index << ". ";
        std::cout << "车牌号: " << car->plate << std::endl;
        // std::cout << "车辆类型: " << car->type << std::endl;
        // std::cout << "车辆年份: " << car->year << std::endl;
        // std::cout << "车辆颜色: " << car->color << std::endl;
    }
    std::cout << "请输入要修改的车牌号: ";
    std::cin >> plate;
    Car *car = carManager.findCarByPlate(plate);
    if (car == nullptr)
    {
        std::cout << "未找到车辆" << std::endl;
        return;
    }
    printSingleCar(car);
    int choice;
    std::cout << "请选择要修改的项目" << std::endl;
    std::cout << "1. 车辆年份" << std::endl;
    std::cout << "2. 车辆类型" << std::endl;
    std::cout << "3. 车辆颜色" << std::endl;
    std::cin >> choice;
    int year;
    std::string owner;

    switch (choice)
    {
    case 1:
        std::cout << "请输入新车辆年份: ";
        std::cin >> year;
        car->year = year;
        break;
    case 2:
        std::cout << "请输入新车辆类型: " << std::endl;
        std::cout << "1. 宝牛" << std::endl;
        std::cout << "2. 比非迪" << std::endl;
        std::cout << "3. 奔跑" << std::endl;
        std::cout << "4. 标至" << std::endl;
        std::cout << "5. 有刺无刺牌超级跑车" << std::endl;
        std::cout << "6. 小众" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            car->type = BaoNiu;
            break;
        case 2:
            car->type = BiFeiDi;
            break;
        case 3:
            car->type = BenPao;
            break;
        case 4:
            car->type = BiaoZhi;
            break;
        case 5:
            car->type = TogeToge;
            break;
        case 6:
            car->type = XiaoZhong;
            break;
        default:
            std::cout << "非法输入" << std::endl;
            return;
        }
        break;
    case 3:
        std::cout << "请输入新车辆颜色: " << std::endl;
        std::cout << "1. 红色" << std::endl;
        std::cout << "2. 蓝色" << std::endl;
        std::cout << "3. 绿色" << std::endl;
        std::cout << "4. 黄色" << std::endl;
        std::cout << "5. 黑色" << std::endl;
        std::cout << "6. 白色" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            car->color = Red;
            break;
        case 2:
            car->color = Blue;
            break;
        case 3:
            car->color = Green;
            break;
        case 4:
            car->color = Yellow;
            break;
        case 5:
            car->color = Black;
            break;
        case 6:
            car->color = White;
            break;
        default:
            std::cout << "非法输入" << std::endl;
            return;
        }
        break;
    default:
        std::cout << "非法输入" << std::endl;
        break;
    }
}
void UI::deleteUserCar()
{
    std::vector<Car *> &cars = carManager.getUserCars(currentUser);
    std::string plate;
    int index = 1;
    std::cout << "共有" << cars.size() << "辆车" << std::endl;
    if (cars.size() == 0)
    {
        return;
    }
    for (auto car : cars)
    {
        std::cout << index << ". ";
        std::cout << "车牌号: " << car->plate << std::endl;
        // std::cout << "车辆类型: " << car->type << std::endl;
        // std::cout << "车辆年份: " << car->year << std::endl;
        // std::cout << "车辆颜色: " << car->color << std::endl;
    }
    std::cout << "请输入要删除的车牌号: ";
    std::cin >> plate;
    if (carManager.deleteCar(plate) == true)
    {
        std::cout << "删除成功" << std::endl;
    }
    else
    {
        std::cout << "删除失败" << std::endl;
    }
}
void UI::printSingleCar(Car *car)
{
    std::cout << "车牌号: " << car->plate << std::endl;
    std::cout << "车辆主人: " << car->owner << std::endl;
    std::cout << "车辆类型: ";
    switch (car->type)
    {
    case BaoNiu:
        std::cout << "宝牛" << std::endl;
        break;
    case BiFeiDi:
        std::cout << "比非迪" << std::endl;
        break;
    case BenPao:
        std::cout << "奔跑" << std::endl;
        break;
    case BiaoZhi:
        std::cout << "标至" << std::endl;
        break;
    case TogeToge:
        std::cout << "有刺无刺牌超级跑车" << std::endl;
        break;
    case XiaoZhong:
        std::cout << "小众" << std::endl;
        break;
    }
    std::cout << "车辆年份: " << car->year << std::endl;
    std::cout << "车辆颜色: ";
    switch (car->color)
    {
    case Red:
        std::cout << "红色" << std::endl;
        break;
    case Blue:
        std::cout << "蓝色" << std::endl;
        break;
    case Green:
        std::cout << "绿色" << std::endl;
        break;
    case Yellow:
        std::cout << "黄色" << std::endl;
        break;
    case Black:
        std::cout << "黑色" << std::endl;
        break;
    case White:
        std::cout << "白色" << std::endl;
        break;
    }
}
void UI::quit()
{
    //TODO:Serialize
    std::ofstream userDB("users.json");
    userManager.serializeUsers(userDB);
    //carManager.serializeCars();
    exit(0);
}
void UI::guestUI()
{
    // TODO: Wait for carDB to be implemented
    bool flag = true;
    while (flag == true)
    {
        std::cout << "1. 登出" << std::endl;
        std::cout << "2. 退出" << std::endl;
        std::cout << "3. 查看个人车辆" << std::endl;
        std::cout << "4. 查询车辆" << std::endl;
        std::cout << "5. 修改密码" << std::endl;
        std::cout << "6. 添加个人车辆" << std::endl;
        std::cout << "7. 删除个人车辆" << std::endl;
        std::cout << "8. 修改个人车辆" << std::endl;
        std::cout << "请输入: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            logout();
            flag = false;
            break;
        case 2:
            quit();
            break;
        case 3:
            printUserCars();
            break;
        case 4:
            searchCar();
            break;
        case 5:
            changePassword();
            break;
        case 6:
            addUserCar();
            break;
        case 7:
            deleteUserCar();
            break;
        case 8:
            modifyCar();
            break;
        default:
            std::cout << "非法输入" << std::endl;
            break;
        }
    }
}

void UI::adminUI()
{
    // TODO: Wait for carDB to be implemented
    bool flag = true;
    while (flag == true)
    {
        std::cout << "1. 登出" << std::endl;
        std::cout << "2. 退出" << std::endl;
        std::cout << "3. 查看车辆" << std::endl;
        std::cout << "4. 搜索车辆" << std::endl;
        std::cout << "5. 添加车辆" << std::endl;
        std::cout << "6. 删除车辆" << std::endl;
        std::cout << "7. 修改车辆" << std::endl;
        std::cout << "8. 修改密码" << std::endl;
        std::cout << "请输入: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            logout();
            flag = false;
            break;
        case 2:
            quit();
            break;
        case 3:
            printCars();
            break;
        case 4:
            searchCar();
            break;
        case 5:
            addCar();
            break;
        case 6:
            deleteCar();
            break;
        case 7:
            modifyCar();
            break;
        case 8:
            changePassword();
            break;
        default:
            std::cout << "非法输入" << std::endl;
            break;
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
                quit();
            }
            else
            {
                std::cout << "非法输入" << std::endl;
            }
        }
    }
}