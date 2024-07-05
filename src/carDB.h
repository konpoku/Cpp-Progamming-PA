#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "user.h"
#include <map>
typedef enum
{
    BaoNiu,   // 宝牛
    BiFeiDi,  // 比非迪
    BenPao,   // 奔跑
    BiaoZhi,  // 标至
    TogeToge, // 有刺无刺牌超级跑车
    XiaoZhong // 小众
} CarType;

typedef enum
{
    Red,
    Blue,
    Green,
    Yellow,
    Black,
    White,
    Gray,
    Purple,
    Pink,
    Brown,
    Orange
} Color;

class Car
{
public:
    std::string plate;
    std::string owner;
    CarType type;
    int year;
    Color color;
    Car(std::string &plate, std::string &owner, CarType type, int year, Color color);
};

class CarManager
{
private:
    std::vector<Car *> cars;//存储所有车辆用于析构
    std::map<std::string, Car *> carMap;
    std::map<std::string, std::vector<Car *>> userCarsList;//这里使用的key是用户名，value是用户车辆数组
public:
    CarManager();
    ~CarManager();
    //TODO:对owner是否存在进行检查
    void addCar(std::string &plate, std::string &owner, CarType type, int year, Color color);
    void deleteCar(std::string &plate);
    std::vector<Car *> &getUserCars(User *user);
    Car *findCarByPlate(std::string &plate);
    void Serialize(std::ostream &os);
};
