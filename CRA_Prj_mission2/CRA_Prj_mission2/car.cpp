#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>

#include <iostream>
#include <memory>

using namespace std;

enum CarType
{
    SEDAN = 1,
    SUV,
    TRUCK,
    MAX_CAR_TYPE,
};

enum Engine
{
    GM = 1,
    TOYOTA,
    WIA,
    MAX_ENGINE_TYPE,
};

enum brakeSystem
{
    MANDO = 1,
    CONTINENTAL,
    BOSCH_B,
    MAX_BRAKE_SYSTEM_TYPE,
};

enum SteeringSystem
{
    BOSCH_S = 1,
    MOBIS,
    MAX_STEERING_SYSTEM_TYPE,
};

class Car {
public:
    virtual void produceComponent() = 0;
    virtual ~Car() {}
};

class   SedanType : public Car {
public:
    void produceComponent() override { std::cout << "차량 타입으로 Sedan을 선택하셨습니다.\n"; }
};

class   SuvType : public Car {
public:
    void produceComponent() override { std::cout << "차량 타입으로 SUV을 선택하셨습니다.\n"; }
};

class   TruckType : public Car {
public:
    void produceComponent() override { std::cout << "차량 타입으로 Truck을 선택하셨습니다.\n"; }
};

class   GmEngine : public Car {
public:
    void produceComponent() override { std::cout << "GM 엔진을 선택하셨습니다.\n"; }
};

class   ToyotaEngine : public Car {
public:
    void produceComponent() override { std::cout << "TOYOTA 엔진을 선택하셨습니다.\n"; }
};

class   WiaEngine : public Car {
public:
    void produceComponent() override { std::cout << "WIA 엔진을 선택하셨습니다.\n"; }
};

class MandoBrakeSystem : public Car {
public:
    void produceComponent() override { std::cout << "MANDO 제동장치를 선택하셨습니다.\n"; }
};

class ContinentalBrakeSystem : public Car {
public:
    void produceComponent() override { std::cout << "CONTINENTAL 제동장치를 선택하셨습니다.\n"; }
};

class BoschBrakeSystem : public Car {
public:
    void produceComponent() override { std::cout << "BOSCH 제동장치를 선택하셨습니다.\n"; }
};


class BoschSteeringSystem : public Car {
public:
    void produceComponent() override { std::cout << "BOSCH 조향장치를 선택하셨습니다.\n"; }
};

class MobisSteeringSystem : public Car {
public:
    void produceComponent() override { std::cout << "MOBIS 조향장치를 선택하셨습니다.\n"; }
};

class Factory {
private:
    int car_type;
    int engine_sel;
    int brake_sel;
    int steering_sel;
public:
    virtual std::unique_ptr<Car> createType() = 0;
    virtual std::unique_ptr<Car> createEngine() = 0;
    virtual std::unique_ptr<Car> createBrakeSystem() = 0;
    virtual std::unique_ptr<Car> createSteeringSystem() = 0;
    void setCarType(int type) { car_type = type; }
    void setEngine(int type) { engine_sel = type; }
    void setBrake(int type) { brake_sel = type; }
    void setSteering(int type) { steering_sel = type; }
    int getCarType(void) { return car_type; }
    int getEngine(void) { return engine_sel; }
    int getBrake(void) { return brake_sel; }
    int getSteering(void) { return steering_sel; }
    virtual ~Factory() {}
};

class PersonalFactory : public Factory {
public:
    std::unique_ptr<Car> createType() override {
        int car_type_ = Factory::getCarType();
        if (car_type_ == SEDAN)
            return std::make_unique<SedanType>();
        if (car_type_ == SUV)
            return std::make_unique<SedanType>();
        if (car_type_ == TRUCK)
            return std::make_unique<SedanType>();
    }
    std::unique_ptr<Car> createEngine() override {
        int engine_ = Factory::getEngine();
        if (engine_ == GM)
            return std::make_unique<GmEngine>();
        if (engine_ == TOYOTA)
            return std::make_unique<ToyotaEngine>();
        if (engine_ == WIA)
            return std::make_unique<WiaEngine>();
    }
    std::unique_ptr<Car> createBrakeSystem() override {
        int brake_ = Factory::getBrake();
        if (brake_ == MANDO)
            return std::make_unique<MandoBrakeSystem>();
        if (brake_ == CONTINENTAL)
            return std::make_unique<ContinentalBrakeSystem>();
        if (brake_ == BOSCH_B)
            return std::make_unique<BoschBrakeSystem>();   
    }
    std::unique_ptr<Car> createSteeringSystem() override {
        int steering_ = Factory::getBrake();
        if (steering_ == BOSCH_S)
            return std::make_unique<BoschSteeringSystem>();
        if (steering_ == MOBIS)
            return std::make_unique<MobisSteeringSystem>();
    }
};

class Custumer {
private:
    std::unique_ptr<Factory> _factory;

public:
    Custumer(std::unique_ptr<Factory> f) : _factory(std::move(f)) {}

    void drive()
    {
        _factory->createType()->produceComponent();
        _factory->createEngine()->produceComponent();
        _factory->createBrakeSystem()->produceComponent();
        _factory->createSteeringSystem()->produceComponent();
    }

    void showType()
    {
        _factory->createType()->produceComponent();
    }

    void showEngine()
    {
        _factory->createEngine()->produceComponent();
    }

    void showBrakeSystem()
    {
        _factory->createBrakeSystem()->produceComponent();
    }
    void showSteeringSystem()
    {
        _factory->createSteeringSystem()->produceComponent();
    }
};

//int main() {
//    std::unique_ptr<Factory> factory = std::make_unique<PersonalFactory>();
//    Custumer custumer(std::move(factory));
//    custumer.drive();
//
//    return 0;
//}
