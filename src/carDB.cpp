#include "carDB.h"
extern UserManager userManager;
Car::Car(std::string &plate, std::string &owner, CarType type, int year, Color color) : plate(plate), owner(owner), type(type), year(year), color(color)
{
}

CarManager::CarManager()
{
}

CarManager::~CarManager()
{
    for (auto car : cars)
    {
        delete car;
    }
}

void CarManager::addCar(std::string &plate, std::string &owner, CarType type, int year, Color color)
{
    Car *newCar = new Car(plate, owner, type, year, color);
    cars.push_back(newCar);//bug: admin 看不到全部车辆
    carMap[plate] = newCar;
    userCarsList[owner].push_back(newCar);
}

bool CarManager::deleteCar(std::string &plate)
{
    auto checker = carMap.find(plate);
    if (checker == carMap.end())
    {
        return false;
    }
    Car *car = carMap[plate];
    User *owner = userManager.getUser(car->owner);
    
    carMap.erase(plate);
    auto &userCars = userCarsList[owner->getName()];
    userCars.erase(std::remove(userCars.begin(), userCars.end(), car), userCars.end());
    cars.erase(std::remove(cars.begin(), cars.end(), car), cars.end());
    delete car;
    return true;
}

std::vector<Car *> &CarManager::getUserCars(User *user)
{
    return userCarsList[user->getName()];
}

Car *CarManager::findCarByPlate(std::string &plate)
{
    return carMap[plate];
}

void CarManager::Serialize(std::ostream &os)
{
}

bool CarManager::findCarByTypeAndColor(CarType type, Color color, std::vector<Car *> &cars)
{
    cars.clear();
    bool flag = false;
    for (auto car : this->cars)
    {
        if (car->type == type && car->color == color)
        {
            cars.push_back(car);
            flag = true;
        }
    }
    return flag;
}

