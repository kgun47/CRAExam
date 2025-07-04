#include "gmock/gmock.h"
#include "car.cpp"

class CarTest : public testing::Test {
public:
    std::unique_ptr<Factory> factory;
protected:

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        factory = std::make_unique<PersonalFactory>();

    }

    void TearDown() override {
        
    }

};

TEST_F(CarTest, TC1) {
   factory->setCarType(1);
   factory->setEngine(1);
   factory->setBrake(1);
   factory->setSteering(1);
   EXPECT_EQ(factory->getCarType(), 1);
   EXPECT_EQ(factory->getEngine(), 1);
   EXPECT_EQ(factory->getBrake(), 1);
   EXPECT_EQ(factory->getSteering(), 1);
}


TEST_F(CarTest, TC2) {
    factory->setCarType(1);
    factory->setEngine(2);
    factory->setBrake(1);
    factory->setSteering(1);
    EXPECT_EQ(factory->getCarType(), 1);
    EXPECT_EQ(factory->getEngine(), 2);
    EXPECT_EQ(factory->getBrake(), 1);
    EXPECT_EQ(factory->getSteering(), 1);
}
