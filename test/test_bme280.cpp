#include <gtest/gtest.h>
#include "bme280.h"

TEST(BME280Test, InitializationTest) {
    // For simplicity, let's assume init_bme280 always returns true
    EXPECT_TRUE(init_bme280());
}

TEST(BME280Test, TemperatureTest) {
    // Here you can use any appropriate value for testing
    // For example, assuming a known temperature value of 25.0
    EXPECT_EQ(read_temperature(), 25.0);
}

TEST(BME280Test, HumidityTest) {
    // Similar to temperature, use known values for testing
    EXPECT_EQ(read_humidity(), 50.0);
}

TEST(BME280Test, PressureTest) {
    // Use known values for testing
    EXPECT_EQ(read_pressure(), 1013.0);
}

TEST(BME280Test, AltitudeTest) {
    // Use known values for testing
    EXPECT_EQ(read_altitude(), 100.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
