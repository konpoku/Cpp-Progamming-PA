#include "carDB.h"
#include <rfl/json.hpp>
#include <rfl.hpp>
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

void CarManager::serialize(std::ostream &os)
{
    os.clear();
    std::vector<CarJson> carJsons;
    for(auto car : cars)
    {
        CarJson carJson;
        carJson.plate = car->plate;
        carJson.owner = car->owner;
        carJson.type = car->type;
        carJson.year = car->year;
        carJson.color = car->color;
        carJsons.push_back(carJson);
    }
    const std::string carsJson = rfl::json::write(carJsons);
    os<<carsJson<<std::endl;
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

void CarManager::deserializeCars(std::ifstream &is)
{
    std::string json_string;
    is >> json_string;
    auto carJsons = rfl::json::read<std::vector<CarJson>>(json_string).value();
    for (auto carJson : carJsons)
    {
        Car *car = new Car(carJson.plate, carJson.owner, carJson.type, carJson.year, carJson.color);
        cars.push_back(car);
        carMap[carJson.plate] = car;
        userCarsList[carJson.owner].push_back(car);
    }
}
