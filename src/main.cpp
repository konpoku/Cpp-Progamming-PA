#include "ui.h"
UserManager userManager;
CarManager carManager;

int main()
{
    UI ui;
    // TODO: 读取文件和修改 admin 密码
    std::ifstream userFile("users.json");
    std::ifstream carFile("cars.json");
    if(userFile.fail()) userManager.createUser("admin", "admin", true);
    else userManager.deserializeUsers(userFile);
    if(carFile.fail() == false) carManager.deserializeCars(carFile);
    ui.controller();
    return 0;
}