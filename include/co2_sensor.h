#pragma once
// clang-format off
#include "logger.h"
#include <MHZ19.h>
// clang-format on

namespace meteo {
struct Co2Data {
  std::int32_t temperature;
  std::int32_t co2;
  std::int32_t accuracy;
};
class Co2Sensor {
 public:
  explicit Co2Sensor(Logger& logger);
  bool init();
  Co2Data read();

 private:
  Logger& logger;
  MHZ19 mhz;
};

}  // namespace meteo