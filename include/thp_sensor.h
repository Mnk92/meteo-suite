#pragma once
// clang-format off
#include "logger.h"

#include <Adafruit_BME280.h>
#include <SPI.h>
#include <Wire.h>
// clang-format on

namespace meteo {
struct THPData {
  float temperature;
  float humidity;
  float pressure;
};
class THPSensor {
 public:
  explicit THPSensor(Logger& logger);
  bool init();
  THPData read();

 private:
  Logger& logger;
  Adafruit_BME280 bme;  // I2C
};
}  // namespace meteo