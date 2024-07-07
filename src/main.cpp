#include"ui.h"
UserManager userManager;
CarManager carManager;
int main(){
    UI ui;
    //TODO: 读取文件和修改 admin 密码
    userManager.createUser("admin","admin",true);
    ui.controller();
    return 0;
}